%{
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "treeUtils.h"
#include "treeNodes.h"
#include "scanType.h"
#include "dot.h"
using namespace std;

int numErrors;
int numWarnings;
extern int line;
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char *msg);

TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
   if(s == nullptr)
   {
      exit(1);
   }

   if(t == nullptr)
   {
      return s;
   }

   TreeNode *ptr = new TreeNode;
   ptr = t;
   while(ptr->sibling != nullptr)
   {
      ptr = ptr->sibling;
   }
   ptr->sibling = s;
   return s;
}

// pass the static and type attribute down the sibling list
void setType(TreeNode *t, ExpType type, bool isStatic)
{
   while (t != nullptr)
   {
      t->type = type;
      t->isStatic = isStatic;
      t = t->sibling;
   }
}

// the syntax tree goes here
TreeNode *syntaxTree;

%}

%union
{
   struct   TokenData *tinfo;
   struct   TreeNode *tree;
   ExpType  type;
}

// tree data?
%type    <tree>   parmIdList parmId stmt matched iterRange unmatched expstmt
%type    <tree>   compoundstmt localDecls stmtList returnstmt breakstmt
%type    <tree>   precomList declList decl varDecl funDecl varDeclList
%type    <tree>   program parms varDeclId constant argList args  immutable mutable
%type    <tree>   simpleExp sumop mulop mulExp relop assignop exp varDeclInit
%type    <tree>   call factor unaryop unaryExp sumExp minmaxop minmaxExp relExp
%type    <tree>   unaryRelExp andExp scopedVarDecl parmTypeList parmList

%type    <type>   typeSpec

// token data
%token   <tinfo>  OP
%token   <tinfo>  '(' ')' ',' ';' '[' '{' '}' ']' ':'
%token   <tinfo>  NEQ LEQ GEQ
%token   <tinfo>  MAX MIN
%token   <tinfo>  INC DEC
%token   <tinfo>  AND OR NOT
%token   <tinfo>  PRECOMPILER
%token   <tinfo>  NUMCONST
%token   <tinfo>  ERROR COMMENT
%token   <tinfo>  ID INT CHAR
%token   <tinfo>  IF THEN ELSE
%token   <tinfo>  WHILE DO FOR TO BY
%token   <tinfo>  STRINGCONST CHARCONST
%token   <tinfo>  BOOL BOOLCONST
%token   <tinfo>  STATIC
%token   <tinfo>  RETURN BREAK
%token   <tinfo>  SUBASS ADDASS MULASS DIVASS
%token   <tinfo>  EQ
%token   <tinfo>  FIRSTSTOP LASTSTOP LASTTERM


%%
program : precomList declList                {cout << yylval.tinfo->tokenstr << " precom declList\n"; syntaxTree = $2;}
   ;

precomList : precomList PRECOMPILER          { cout << yylval.tinfo->tokenstr << " precom list\n"; $$ = nullptr; }
   | PRECOMPILER                             { cout << yylval.tinfo->tokenstr << " precom \n"; $$ = nullptr; }
   ;

declList : declList decl                     {cout << yylval.tinfo->tokenstr << "declList \n"; $$ = addSibling($1, $2);}
   | decl                                    {cout << yylval.tinfo->tokenstr << " decl \n"; $$ = $1;}
   ;

decl : varDecl                               {$$ = $1; cout << yylval.tinfo->tokenstr << " vardecl \n"; $$ = nullptr;}
   | funDecl                                 {$$ = $1; cout << yylval.tinfo->tokenstr << " fundecl \n"; $$ = nullptr;}
   ;

varDecl : typeSpec varDeclList ';'           { cout <<  yylval.tinfo->tokenstr << " varDeclList \n"; $$ = $2; setType($2, $1, false); }
   ;

varDeclList : varDeclList ',' varDeclInit    { cout <<  yylval.tinfo->tokenstr << " varDeclInit list \n"; $$ = nullptr;}
   | varDeclInit                             { cout <<  yylval.tinfo->tokenstr << " varDeclInit \n"; $$ = nullptr;}
   ;

varDeclInit : varDeclId                      { cout << "I'm a node.\n"; $$ = nullptr;}
   | varDeclId ':' simpleExp                 { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

varDeclId : ID                               { cout << yylval.tinfo->tokenstr << " decl id \n"; $$ = newDeclNode(DeclKind::VarK, UndefinedType, $1);}
   | ID '[' NUMCONST ']'                     { cout << yylval.tinfo->tokenstr << " decl id array\n"; $$ = newDeclNode(DeclKind::VarK, UndefinedType, $1);}
   ;

parms : parmList                             { cout << "I'm a node.\n"; $$ = nullptr;}
   | /* empty */                             { cout << yylval.tinfo->tokenstr << " empty parmlist \n"; $$ = nullptr;}
   ;

parmList : parmList ';' parmTypeList         { cout << "I'm a node.\n"; $$ = nullptr;}
   | parmTypeList                            { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

parmTypeList : typeSpec parmIdList           { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

compoundstmt : '{' localDecls stmtList '}'   { cout << "I'm a node.\n"; $$ = newStmtNode(StmtKind::CompoundK, $1, $2, $3);}
   ;

matched : IF simpleExp THEN matched ELSE matched   { cout << "I'm a node.\n"; $$ = nullptr;}
   | WHILE simpleExp DO matched              { cout << "I'm a node.\n"; $$ = nullptr;}
   | FOR ID '=' iterRange DO matched         { cout << "I'm a node.\n"; $$ = nullptr;}
   | expstmt                                 { cout << "I'm a node.\n"; $$ = nullptr;}
   | compoundstmt                            {$$ = $1;}
   | returnstmt                              { cout << "I'm a node.\n"; $$ = nullptr;}
   | breakstmt                               { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

iterRange : simpleExp TO simpleExp           { cout << "I'm a node.\n"; $$ = nullptr;}
   | simpleExp TO simpleExp BY simpleExp     { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

unmatched : IF simpleExp THEN stmt           { cout << "I'm a node.\n"; $$ = nullptr;}
   | IF simpleExp THEN matched ELSE unmatched   { cout << "I'm a node.\n"; $$ = nullptr;}
   | WHILE simpleExp DO unmatched            { cout << "I'm a node.\n"; $$ = nullptr;}
   | FOR ID '=' iterRange DO unmatched       { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

localDecls : localDecls scopedVarDecl        { cout << "I'm a node.\n"; $$ = nullptr;}
   | /* empty */                             { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

stmtList : stmtList stmt                     { cout << "I'm a node.\n"; $$ = nullptr;}
   | /* empty*/                              { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

returnstmt : RETURN ';'                      { cout << "I'm a node.\n"; $$ = nullptr;}
   | RETURN exp ';'                          { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

scopedVarDecl : STATIC typeSpec varDeclList ';'    { cout << "I'm a node.\n"; $$ = nullptr;}
   | typeSpec varDeclList ';'                { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

stmt : matched                               { cout << "I'm a node.\n"; $$ = nullptr;}
   | unmatched                               { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

parmId : ID                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   | ID '[' ']'                              { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

parmIdList : parmIdList ',' parmId           { cout << "I'm a node.\n"; $$ = nullptr;}
   | parmTypeList                            { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

typeSpec : INT                               { cout << "I'm a node.\n"; $$ = ExpType::Integer;}
   | BOOL                                    { cout << "I'm a node.\n"; $$ = ExpType::Boolean;}
   | CHAR                                    { cout << "I'm a node.\n"; $$ = ExpType::Char;}
   ;

funDecl : typeSpec ID '(' parms ')' stmt     { cout << "I'm a node.\n"; $$ = nullptr;}
   | ID '(' parms ')' stmt                   { cout << "I'm a node.\n"; $$ = nullptr;} //$$ = newDeclNode(DeclKind::FuncK, );}
   ;

breakstmt : BREAK                            { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

expstmt : exp                                { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

exp : mutable assignop exp                   { cout << "I'm a node.\n"; $$ = nullptr;}
   | mutable INC                             { cout << "I'm a node.\n"; $$ = nullptr;}
   | mutable DEC                             { cout << "I'm a node.\n"; $$ = nullptr;}
   | simpleExp                               { cout << "I'm a node.\n"; $$ = nullptr;}
   | mutable assignop ERROR                  { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

assignop : ADDASS                            { cout << "I'm a node.\n"; $$ = nullptr;}
   | SUBASS                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   | MULASS                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   | DIVASS                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

simpleExp : simpleExp OR andExp              { cout << "I'm a node.\n"; $$ = nullptr;}
   | andExp                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

andExp : andExp AND unaryRelExp              { cout << "I'm a node.\n"; $$ = nullptr;}
   | unaryRelExp                             { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

unaryRelExp : NOT unaryRelExp                { cout << "I'm a node.\n"; $$ = nullptr;}
   | relExp                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

relExp : minmaxExp relop minmaxExp           { cout << "I'm a node.\n"; $$ = nullptr;}
   | minmaxExp                               { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

relop : LEQ                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   | '<'                                     { cout << "I'm a node.\n"; $$ = nullptr;}
   | '>'                                     { cout << "I'm a node.\n"; $$ = nullptr;}
   | GEQ                                     { cout << "I'm a node.\n"; $$ = nullptr;}
   | EQ                                      { cout << "I'm a node.\n"; $$ = nullptr;}
   | NEQ                                     { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

minmaxExp : minmaxExp minmaxop sumExp        { cout << "I'm a node.\n"; $$ = nullptr;}
   | sumExp                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

minmaxop : ":>:"                             { cout << "I'm a node.\n"; $$ = nullptr;}
   | ":<:"                                   { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

sumExp : sumExp sumop mulExp                 { cout << "I'm a node.\n"; $$ = nullptr;}
   | mulExp                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

sumop : '+'                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   | '-'                                     { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

mulExp : mulExp mulop unaryExp               { cout << "I'm a node.\n"; $$ = nullptr;}
   | unaryExp                                { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

mulop : '*'                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   | '/'                                     { cout << "I'm a node.\n"; $$ = nullptr;}
   | '%'                                     { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

unaryExp : unaryop unaryExp                  { cout << "I'm a node.\n"; $$ = nullptr;}
   | factor                                  { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

unaryop : '-'                                { cout << "I'm a node.\n"; $$ = nullptr;}
   | '*'                                     { cout << "I'm a node.\n"; $$ = nullptr;}
   | '?'                                     { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

factor : immutable                           { cout << "I'm a node.\n"; $$ = nullptr;}
   | mutable                                 { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

mutable : ID                                 { cout << "I'm a node.\n"; $$ = nullptr;}
   | ID '[' exp ']'                          { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

immutable : '(' exp ')'                      { cout << "I'm a node.\n"; $$ = nullptr;}
   | call                                    { cout << "I'm a node.\n"; $$ = nullptr;}
   | constant                                { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

call : ID '(' args ')'                       { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

args : argList                               { cout << "I'm a node.\n"; $$ = nullptr;}
   | /* empty */                             { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

argList : argList ',' exp                    { cout << "I'm a node.\n"; $$ = nullptr;}
   | exp                                     { cout << "I'm a node.\n"; $$ = nullptr;}
   ;

constant : NUMCONST                          { cout << "I'm a node.\n"; $$ = nullptr;}
         | CHARCONST                         { cout << "I'm a node.\n"; $$ = nullptr;}
         | STRINGCONST                       { cout << "I'm a node.\n"; $$ = nullptr;}
         | BOOLCONST                         { cout << "I'm a node.\n"; $$ = nullptr;}
         ;

/*
program  :  program term
   |  term  {$$=$1;}
   ;
term  : 
      OP {printToken(yylval.tinfo, "OP");}
   |  NEQ {printToken(yylval.tinfo, "NEQ");}
   |  GEQ {printToken(yylval.tinfo, "GEQ");}
   |  LEQ {printToken(yylval.tinfo, "LEQ");}
   |  AND {printToken(yylval.tinfo, "AND");}
   |  PRECOMPILER {printToken(yylval.tinfo, "PRECOMPILER");}
   |  NUMCONST {printToken(yylval.tinfo, "NUMCONST");}
   |  ID {printToken(yylval.tinfo, "ID");}
   |  INT {printToken(yylval.tinfo, "INT");}
   |  CHAR {printToken(yylval.tinfo, "CHAR");}
   |  STRINGCONST {printToken(yylval.tinfo, "STRINGCONST");}
   |  IF {printToken(yylval.tinfo, "IF");}
   |  THEN {printToken(yylval.tinfo, "THEN");}
   |  ELSE {printToken(yylval.tinfo, "ELSE");}
   |  WHILE {printToken(yylval.tinfo, "WHILE");}
   |  DO {printToken(yylval.tinfo, "DO");}
   |  FOR {printToken(yylval.tinfo, "FOR");}
   |  TO {printToken(yylval.tinfo, "TO");}
   |  BY {printToken(yylval.tinfo, "BY");}
   |  OR {printToken(yylval.tinfo, "OR");}
   |  BOOL {printToken(yylval.tinfo, "BOOL");}
   |  STATIC {printToken(yylval.tinfo, "STATIC");}
   |  RETURN {printToken(yylval.tinfo, "RETURN");}
   |  BREAK {printToken(yylval.tinfo, "BREAK");}
   |  BOOLCONST {printToken(yylval.tinfo, "BOOLCONST");}
   |  COMMENT {printToken(yylval.tinfo, "COMMENT");}
   |  MAX {printToken(yylval.tinfo, "MAX");}
   |  MIN {printToken(yylval.tinfo, "MIN");}
   |  MULASS {printToken(yylval.tinfo, "MULASS");}
   |  DIVASS {printToken(yylval.tinfo, "DIVASS");}
   |  ADDASS {printToken(yylval.tinfo, "ADDASS");}
   |  SUBASS {printToken(yylval.tinfo, "SUBASS");}
   |  NOT {printToken(yylval.tinfo, "NOT");}
   |  EQ {printToken(yylval.tinfo, "EQ");}
   |  CHARCONST {printToken(yylval.tinfo, "CHARCONST");}
   |  INC {printToken(yylval.tinfo, "INC");}
   |  DEC {printToken(yylval.tinfo, "DEC");}
   |  ERROR    {cout << "ERROR(SCANNER Line " << yylval.tinfo.linenum << "): Invalid input character " << yylval.tinfo.tokenstr << endl; }
   ; */
%%
void yyerror (const char *msg)
{ 
   cout << "Error: " <<  msg << endl;
}

/*
char *largerTokens[LASTTERM+1]; // used in the utils.cpp file printing routines
// create a mapping from token class enum to a printable name in a
// way that makes it easy to keep the mapping straight.
void initTokenStrings()
{
   largerTokens[ADDASS] = (char *)"+=";
   largerTokens[AND] = (char *)"and";
   largerTokens[BOOL] = (char *)"bool";
   largerTokens[BOOLCONST] = (char *)"boolconst";
   largerTokens[BREAK] = (char *)"break";
   largerTokens[BY] = (char *)"by";
   largerTokens[CHAR] = (char *)"char";
   largerTokens[CHARCONST] = (char *)"charconst";
   largerTokens[CHSIGN] = (char *)"chsign";
   largerTokens[DEC] = (char *)"--";
   largerTokens[DIVASS] = (char *)"/=";
   largerTokens[DO] = (char *)"do";
   largerTokens[ELSE] = (char *)"else";
   largerTokens[EQ] = (char *)"==";
   largerTokens[FOR] = (char *)"for";
   largerTokens[GEQ] = (char *)">=";
   largerTokens[ID] = (char *)"id";
   largerTokens[IF] = (char *)"if";
   largerTokens[INC] = (char *)"++";
   largerTokens[INT] = (char *)"int";
   largerTokens[LEQ] = (char *)"<=";
   largerTokens[MAX] = (char *)":>:";
   largerTokens[MIN] = (char *)":<:";
   largerTokens[MULASS] = (char *)"*=";
   largerTokens[NEQ] = (char *)"!=";
   largerTokens[NOT] = (char *)"not";
   largerTokens[NUMCONST] = (char *)"numconst";
   largerTokens[OR] = (char *)"or";
   largerTokens[RETURN] = (char *)"return";
   largerTokens[SIZEOF] = (char *)"sizeof";
   largerTokens[STATIC] = (char *)"static";
   largerTokens[STRINGCONST] = (char *)"stringconst";
   largerTokens[SUBASS] = (char *)"-=";
   largerTokens[THEN] = (char *)"then";
   largerTokens[TO] = (char *)"to";
   largerTokens[WHILE] = (char *)"while";
   largerTokens[LASTTERM] = (char *)"lastterm";
}
*/

int main(int argc, char **argv) 
{
   yylval.tinfo = (TokenData*)malloc(sizeof(TokenData));
   yylval.tree = (TreeNode*)malloc(sizeof(TreeNode));
   yylval.tinfo->linenum = 1;

   int index;
   char *file = NULL;
   bool dotAST = false;             // make dot file of AST
   extern FILE *yyin;

   int ch;
  // initTokenStrings();

   while ((ch = getopt(argc, argv, "d")) != -1) 
   {
      switch (ch) 
      {
         case 'd':
                 dotAST = true;
                 break;
         case '?':
         default:
                 //usage();
               ;
      }
   }

   if ( optind == argc ) yyparse();
   for (index = optind; index < argc; index++)
   {
      yyin = fopen (argv[index], "r");
      yyparse();
      fclose (yyin);
   }
   if (numErrors==0) 
   {
      printTree(stdout, syntaxTree, true, true);
      if(dotAST) {
         printDotTree(stdout, syntaxTree, false, false);
      }
   }
   else 
   {
      printf("-----------\n");
      printf("Errors: %d\n", numErrors);
      printf("-----------\n");
   }
   return 0;
}

