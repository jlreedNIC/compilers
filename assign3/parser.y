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
   cout << "in addSibling func.\n";
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
   cout << "in settype func.\n";
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
program : precomList declList                { syntaxTree = $2;}// cout << syntaxTree->nodeNum << " num\n"; }
   ;

precomList : precomList PRECOMPILER          { cout << yylval.tinfo->tokenstr << "\n"; $$ = nullptr; }
   | PRECOMPILER                             { cout << yylval.tinfo->tokenstr << "\n"; $$ = nullptr; }
   ;

declList : declList decl                     { $$ = addSibling($1, $2);}
   | decl                                    { $$ = $1;}
   ;

decl : varDecl                               { $$ = $1; }
   | funDecl                                 { $$ = $1; }
   ;

varDecl : typeSpec varDeclList ';'           { $$ = $2; setType($2, $1, false); }
   ;

varDeclList : varDeclList ',' varDeclInit    { $$ = addSibling($1, $3);}
   | varDeclInit                             { $$ = $1;}
   ;

varDeclInit : varDeclId                      { $$ = $1;}
   | varDeclId ':' simpleExp                 { $$ = addSibling($1, $3);}
   ;

varDeclId : ID                               { $$ = newDeclNode(DeclKind::VarK, UndefinedType, $1); $$->isArray = false;}
   | ID '[' NUMCONST ']'                     { $$ = newDeclNode(DeclKind::VarK, UndefinedType, $1); $$->isArray = true;}
   ;

parms : parmList                             { $$ = $1;}
   | /* empty */                             { $$ = nullptr;}
   ;

parmList : parmList ';' parmTypeList         { $$ = addSibling($1, $3);}
   | parmTypeList                            { $$ = $1;}
   ;

parmTypeList : typeSpec parmIdList           { $$ = $2; setType($2, $1, false);}
   ;

parmIdList : parmIdList ',' parmId           {  $$ = addSibling($1, $3);}
   | parmId                                  {  $$ = $1;}
   ;

parmId : ID                                  {  $$ = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, $1); 
                                                $$->isArray = false; $$->isStatic = false;}
   | ID '[' ']'                              {  $$ = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, $1); 
                                                $$->isArray = true; $$->isStatic = false;}
   ;

compoundstmt : '{' localDecls stmtList '}'   { $$ = newStmtNode(StmtKind::CompoundK, $1, $2, $3);}
   ;

matched : IF simpleExp THEN matched ELSE matched   { $$ = nullptr;}
   | WHILE simpleExp DO matched              { $$ = nullptr;}
   | FOR ID '=' iterRange DO matched         { $$ = nullptr;}
   | expstmt                                 { $$ = $1;}
   | compoundstmt                            { $$ = $1;}
   | returnstmt                              { $$ = $1;}
   | breakstmt                               { $$ = $1;}
   ;

iterRange : simpleExp TO simpleExp           {  $$ = nullptr;}
   | simpleExp TO simpleExp BY simpleExp     {  $$ = nullptr;}
   ;

unmatched : IF simpleExp THEN stmt           {  $$ = nullptr;}
   | IF simpleExp THEN matched ELSE unmatched   {  $$ = nullptr;}
   | WHILE simpleExp DO unmatched            {  $$ = nullptr;}
   | FOR ID '=' iterRange DO unmatched       {  $$ = nullptr;}
   ;

localDecls : localDecls scopedVarDecl        {  $$ = nullptr;}
   | /* empty */                             {  $$ = nullptr;}
   ;

stmtList : stmtList stmt                     {  $$ = nullptr;}
   | /* empty*/                              {  $$ = nullptr;}
   ;

returnstmt : RETURN ';'                      {  } // $$ = StmtKind::ReturnK;}
   | RETURN exp ';'                          {  $$ = nullptr;}
   ;

scopedVarDecl : STATIC typeSpec varDeclList ';'    {  $$ = nullptr;}
   | typeSpec varDeclList ';'                {  $$ = nullptr;}
   ;

stmt : matched                               {  $$ = $1;}
   | unmatched                               {  $$ = $1;}
   ;

typeSpec : INT                               {  $$ = ExpType::Integer;}
   | BOOL                                    {  $$ = ExpType::Boolean;}
   | CHAR                                    {  $$ = ExpType::Char;}
   ;

funDecl : typeSpec ID '(' parms ')' stmt     { $$ = newDeclNode(DeclKind::FuncK, $1, $2, $4, $6);}
   | ID '(' parms ')' stmt                   { $$ = newDeclNode(DeclKind::FuncK, ExpType::Void, $1, $3, $5);}
   ;

breakstmt : BREAK                            {  $$ = nullptr;}
   ;

expstmt : exp                                {  $$ = $1;}
   ;

exp : mutable assignop exp                   {  $$ = nullptr;}
   | mutable INC                             {  $$ = nullptr;}
   | mutable DEC                             {  $$ = nullptr;}
   | simpleExp                               {  $$ = $1;}
   | mutable assignop ERROR                  {  $$ = nullptr;}
   ;

assignop : ADDASS                            {  $$ = nullptr;}
   | SUBASS                                  {  $$ = nullptr;}
   | MULASS                                  {  $$ = nullptr;}
   | DIVASS                                  {  $$ = nullptr;}
   ;

simpleExp : simpleExp OR andExp              {  $$ = nullptr;}
   | andExp                                  {  $$ = $1;}
   ;

andExp : andExp AND unaryRelExp              {  $$ = nullptr;}
   | unaryRelExp                             {  $$ = $1;}
   ;

unaryRelExp : NOT unaryRelExp                {  $$ = nullptr;}
   | relExp                                  {  $$ = nullptr;}
   ;

relExp : minmaxExp relop minmaxExp           {  $$ = nullptr;}
   | minmaxExp                               {  $$ = nullptr;}
   ;

relop : LEQ                                  {  $$ = nullptr;}
   | '<'                                     {  $$ = nullptr;}
   | '>'                                     {  $$ = nullptr;}
   | GEQ                                     {  $$ = nullptr;}
   | EQ                                      {  $$ = nullptr;}
   | NEQ                                     {  $$ = nullptr;}
   ;

minmaxExp : minmaxExp minmaxop sumExp        {  $$ = nullptr;}
   | sumExp                                  {  $$ = nullptr;}
   ;

minmaxop : ":>:"                             {  $$ = nullptr;}
   | ":<:"                                   {  $$ = nullptr;}
   ;

sumExp : sumExp sumop mulExp                 {  $$ = nullptr;}
   | mulExp                                  {  $$ = nullptr;}
   ;

sumop : '+'                                  {  $$ = nullptr;}
   | '-'                                     {  $$ = nullptr;}
   ;

mulExp : mulExp mulop unaryExp               {  $$ = nullptr;}
   | unaryExp                                {  $$ = nullptr;}
   ;

mulop : '*'                                  {  $$ = nullptr;}
   | '/'                                     {  $$ = nullptr;}
   | '%'                                     {  $$ = nullptr;}
   ;

unaryExp : unaryop unaryExp                  {  $$ = nullptr;}
   | factor                                  {  $$ = nullptr;}
   ;

unaryop : '-'                                {  $$ = nullptr;}
   | '*'                                     {  $$ = nullptr;}
   | '?'                                     {  $$ = nullptr;}
   ;

factor : immutable                           {  $$ = nullptr;}
   | mutable                                 {  $$ = nullptr;}
   ;

mutable : ID                                 {  $$ = nullptr;}
   | ID '[' exp ']'                          {  $$ = nullptr;}
   ;

immutable : '(' exp ')'                      {  $$ = nullptr;}
   | call                                    {  $$ = nullptr;}
   | constant                                {  $$ = nullptr;}
   ;

call : ID '(' args ')'                       {  $$ = nullptr;}
   ;

args : argList                               {  $$ = nullptr;}
   | /* empty */                             {  $$ = nullptr;}
   ;

argList : argList ',' exp                    {  $$ = nullptr;}
   | exp                                     {  $$ = nullptr;}
   ;

constant : NUMCONST                          {  $$ = nullptr;}
         | CHARCONST                         {  $$ = nullptr;}
         | STRINGCONST                       {  $$ = nullptr;}
         | BOOLCONST                         {  $$ = nullptr;}
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

