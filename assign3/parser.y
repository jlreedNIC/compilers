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
      cout << "Sibling is null!\n";
      exit(1);
   }

   if(t == nullptr)
   {
      cout << "main is null\n";
      return s;
   }

   TreeNode *ptr = new TreeNode;
   ptr = t;
   while(ptr->sibling != nullptr)
   {
      ptr = ptr->sibling;
   }
   ptr->sibling = s;
   cout << "leaving sibling\n";
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
%type    <tinfo>  sumop mulop relop assignop minmaxop unaryop

%type    <tree>   parmIdList parmId stmt matched iterRange unmatched expstmt
%type    <tree>   compoundstmt localDecls stmtList returnstmt breakstmt
%type    <tree>   precomList declList decl varDecl funDecl varDeclList
%type    <tree>   program parms varDeclId constant argList args  immutable
%type    <tree>   simpleExp mulExp exp varDeclInit mutable
%type    <tree>   call factor unaryExp sumExp minmaxExp relExp
%type    <tree>   unaryRelExp andExp scopedVarDecl parmTypeList parmList

%type    <type>   typeSpec

// token data
%token   <tinfo>  '=' '*' '+' '/' '%' '-' '<' '>' '?'
%token   <tinfo>  '(' ')' ',' ';' '[' '{' '}' ']' ':'
%token   <tinfo>  NEQ LEQ GEQ EQ
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
%token   <tinfo>  FIRSTSTOP LASTSTOP LASTTERM


%%
program : precomList declList                { cout << "start-"; syntaxTree = $2;}
   ;

precomList : precomList PRECOMPILER          { cout << yylval.tinfo->tokenstr << "\n"; $$ = nullptr;}
   | PRECOMPILER                             { cout << "start2- " << yylval.tinfo->tokenstr << "\n"; $$ = nullptr; }
   | /* empty */                             { $$ = nullptr; }
   ;

declList : declList decl                     { cout << "declList- "; $$ = addSibling($1, $2);}
   | decl                                    { cout << "decl- "; $$ = $1;}
   ;

decl : varDecl                               { cout << "varDecl- "; $$ = $1; }
   | funDecl                                 { cout << "funDecl- "; $$ = $1; }
   ;

varDecl : typeSpec varDeclList ';'           { cout << "typespec varDeclL- "; $$ = $2; setType($2, $1, false); }
   ;

scopedVarDecl : STATIC typeSpec varDeclList ';'    { $$ = $3; setType($3, $2, true);}
   | typeSpec varDeclList ';'                { $$ = $2; setType($2, $1, false);}
   ;

varDeclList : varDeclList ',' varDeclInit    { cout << "varDeclList- "; $$ = addSibling($1, $3);}
   | varDeclInit                             { cout << "varDeclInit- "; $$ = $1;}
   ;

varDeclInit : varDeclId                      { cout << "varDeclId- "; $$ = $1;}
   | varDeclId ':' simpleExp                 { $$ = addSibling($1, $3);}
   ;

varDeclId : ID                               { $$ = newDeclNode(DeclKind::VarK, UndefinedType, $1); $$->isArray = false;}
   | ID '[' NUMCONST ']'                     { $$ = newDeclNode(DeclKind::VarK, UndefinedType, $1); $$->isArray = true;}
   ;

typeSpec : INT                               { $$ = ExpType::Integer;}
   | BOOL                                    { $$ = ExpType::Boolean;}
   | CHAR                                    { $$ = ExpType::Char;}
   ;

funDecl : typeSpec ID '(' parms ')' stmt     { $$ = newDeclNode(DeclKind::FuncK, $1, $2, $4, $6);}
   | ID '(' parms ')' stmt                   { $$ = newDeclNode(DeclKind::FuncK, ExpType::Void, $1, $3, $5);}
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

stmt : matched                               { cout << "matched stmt- "; $$ = $1;}
   | unmatched                               { $$ = $1;}
   ;

matched : IF simpleExp THEN matched ELSE matched   { $$ = newStmtNode(StmtKind::IfK, $1, $2, $4, $6);}
   | WHILE simpleExp DO matched              { $$ = newStmtNode(StmtKind::WhileK, $1, $2, $4);}
   | FOR ID '=' iterRange DO matched         { $$ = newStmtNode(StmtKind::ForK, $1, $4, $6);}
   | expstmt                                 { cout << "matched exp- "; $$ = $1;}
   | compoundstmt                            { $$ = $1;}
   | returnstmt                              { $$ = $1;}
   | breakstmt                               { $$ = $1;}
   ;

iterRange : simpleExp TO simpleExp           {  $$ = nullptr;}
   | simpleExp TO simpleExp BY simpleExp     {  $$ = nullptr;}
   ;

unmatched : IF simpleExp THEN stmt           {  $$ = newStmtNode(StmtKind::IfK, $1, $2, $4);}
   | IF simpleExp THEN matched ELSE unmatched   {  $$ = nullptr;}
   | WHILE simpleExp DO unmatched            {  $$ = nullptr;}
   | FOR ID '=' iterRange DO unmatched       {  $$ = nullptr;}
   ;

expstmt : exp ';'                            { cout << "expstmt- "; $$ = $1;}
   | ';'                                     { $$ = nullptr; }
   ;

compoundstmt : '{' localDecls stmtList '}'   { cout << "compound stmt- "; $$ = newStmtNode(StmtKind::CompoundK, $1, $2, $3);}
   ;


localDecls : localDecls scopedVarDecl        {  $$ = addSibling($1, $2);}
   | /* empty */                             {  $$ = nullptr;}
   ;

stmtList : stmtList stmt                     { cout << "stmtList- "; $$ = addSibling($1, $2);}
   | /* empty */                              {  $$ = nullptr;}
   ;

returnstmt : RETURN ';'                      { $$ = newStmtNode(StmtKind::ReturnK, $1);}
   | RETURN exp ';'                          { $$ = newStmtNode(StmtKind::ReturnK, $1, $2);}
   ;

breakstmt : BREAK ';'                        { $$ = newStmtNode(StmtKind::BreakK, $1);}
   ;

exp : mutable assignop exp                   { cout << "mutable: "; $$ = newExpNode(ExpKind::AssignK, $2, $1, $3); $$->isAssigned = true;} //CHECK HERE
   | mutable INC                             { $$ = newExpNode(ExpKind::OpK, $2, $1);}
   | mutable DEC                             { $$ = newExpNode(ExpKind::OpK, $2, $1);}
   | simpleExp                               { cout << "simpleExp- "; $$ = $1;}
   | mutable assignop ERROR                  { cout << "mutable error "; $$ = newExpNode(ExpKind::AssignK, $2, $1); yyerror($3->tokenstr);}
   ;

assignop : '='                               { $$ = $1; }
   | ADDASS                                  { $$ = $1; }
   | SUBASS                                  { $$ = $1; }
   | MULASS                                  { $$ = $1; }
   | DIVASS                                  { $$ = $1; }
   ;

simpleExp : simpleExp OR andExp              { cout << "simpleexp new node\n"; $$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | andExp                                  { cout << "simpleexp and- "; $$ = $1;}
   ;

andExp : andExp AND unaryRelExp              { cout << "and op- "; $$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | unaryRelExp                             { cout << "and unary- "; $$ = $1;}
   ;

unaryRelExp : NOT unaryRelExp                { cout << "not unary exp- "; $$ = nullptr;}
   | relExp                                  { cout << "rel exp- "; $$ = $1;}
   ;

relExp : minmaxExp relop minmaxExp           { $$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | minmaxExp                               { cout << "minmax exp- "; $$ = $1;}
   ;

relop : LEQ                                  { $$ = $1;}
   | '<'                                     { $$ = $1;}
   | '>'                                     { $$ = $1;}
   | GEQ                                     { $$ = $1;}
   | EQ                                      { $$ = $1;} 
   | NEQ                                     { $$ = $1;}
   ;

minmaxExp : minmaxExp minmaxop sumExp        { $$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | sumExp                                  { cout << "sum exp- "; $$ = $1;}
   ;

minmaxop : MAX                               {  $$ = $1;}
   | MIN                                     {  $$ = $1;}
   ;

sumExp : sumExp sumop mulExp                 {  $$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | mulExp                                  { cout << "muloexp- "; $$ = $1;}
   ;

sumop : '+'                                  {  $$ = $1;}
   | '-'                                     {  $$ = $1;}
   ;

mulExp : mulExp mulop unaryExp               {  $$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | unaryExp                                { cout << "unaryexp- "; $$ = $1;}
   ;

mulop : '*'                                  {  $$ = $1;}
   | '/'                                     {  $$ = $1;}
   | '%'                                     {  $$ = $1;}
   ;

unaryExp : unaryop unaryExp                  {  $$ = newExpNode(ExpKind::OpK, $1, $2);}
   | factor                                  { cout << "factor- "; $$ = $1;}
   ;

unaryop : '-'                                {  $$ = $1;}
   | '*'                                     {  $$ = $1;}
   | '?'                                     {  $$ = $1;}
   ;

factor : immutable                           { cout << "immutable- "; $$ = $1;}
   | mutable                                 { cout << "mutable- "; $$ = $1;}
   ;

mutable : ID                                 { $$ = newExpNode(ExpKind::IdK, $1); $$->isArray = false;}
   | ID '[' exp ']'                          {  $$ = newExpNode(ExpKind::IdK, $1, $3);  $$->isArray = true;}
   ;

immutable : '(' exp ')'                      { cout << "immutable exp- "; $$ = $2;}
   | call                                    { cout << "immutable call- "; $$ = $1;}
   | constant                                { cout << "constant- "; $$ = $1;}
   ;

call : ID '(' args ')'                       { cout << "call ID- "; $$ = newExpNode(ExpKind::CallK, $1, $3);}
   ;

args : argList                               { cout << "arglist- "; $$ = $1;}
   | /* empty */                             {  $$ = nullptr;}
   ;

argList : argList ',' exp                    { cout << "arglist , exp- "; $$ = addSibling($1, $3);}
   | exp                                     { cout << "argList exp- "; $$ = $1;}
   ;

constant : NUMCONST                          { cout << "numconst- "; $$ = newExpNode(ExpKind::ConstantK, $1); $$->attr.value = $1->nvalue; }
         | CHARCONST                         { cout << "charconst- "; $$ = newExpNode(ExpKind::ConstantK, $1);}
         | STRINGCONST                       { cout << "stringconst- "; $$ = newExpNode(ExpKind::ConstantK, $1);}
         | BOOLCONST                         { cout << "boolconst- "; $$ = newExpNode(ExpKind::ConstantK, $1);}
         ;

/* assignment or const */
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

   printf("Number of warnings: %d\n", numWarnings);
   printf("Number of errors: %d\n", numErrors);
   return 0;
}

