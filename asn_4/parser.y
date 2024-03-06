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

bool debug = false;
void printDebug(string msg)
{
   if(debug == true)
   {
      cout << msg << "- ";
   }
}

TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
   // printDebug("in addSibling func\n");
   if(s == nullptr)
   {
      printDebug("Sibling is null!\n");
      exit(1);
   }

   if(t == nullptr)
   {
      // printDebug("main is null\n");
      return s;
   }

   TreeNode *ptr = t;
   // ptr = t;
   while(ptr->sibling != nullptr)
   {
      ptr = ptr->sibling;
   }
   ptr->sibling = s;

   // printDebug("leaving sibling\n");
   return t;
}

// pass the static and type attribute down the sibling list
void setType(TreeNode *t, ExpType type, bool isStatic)
{
   // printDebug("in settype func.\n");
   while (t != nullptr)
   {
      t->type = type;
      t->isStatic = isStatic;
      t = t->sibling;
   }
}

// the syntax tree goes here
TreeNode *syntaxTree;

TreeNode *initTree(TreeNode *start)
{
   // new nodes to create
   TreeNode *input, *output, *param_output;
   TreeNode *inputb, *outputb, *param_outputb;
   TreeNode *inputc, *outputc, *param_outputc;
   TreeNode *outnl;

   ///////// Stuff from next slides
   input = newDeclNode(DeclKind::FuncK, ExpType::Integer);
   input->lineno = -1; // all are -1
   input->attr.name = strdup("input");
   input->type = ExpType::Integer; // is this needed??

   inputb = newDeclNode(DeclKind::FuncK, ExpType::Boolean);
   inputb->lineno = -1;
   inputb->attr.name = strdup("inputb");

   inputc = newDeclNode(DeclKind::FuncK, ExpType::Boolean);
   inputc->lineno = -1;
   inputc->attr.name = strdup("inputc");

   param_output = newDeclNode(DeclKind::ParamK, ExpType::Void);
   param_output->lineno = -1;
   param_output->attr.name = strdup("*dummy*");

   output = newDeclNode(DeclKind::FuncK, ExpType::Void);
   output->lineno = -1;
   output->attr.name = strdup("output");

   param_outputb = newDeclNode(DeclKind::ParamK, ExpType::Void);
   param_outputb->lineno = -1;
   param_outputb->attr.name = strdup("*dummy*");

   outputb = newDeclNode(DeclKind::FuncK, ExpType::Void);
   outputb->lineno = -1;
   outputb->attr.name = strdup("outputb");

   param_outputc = newDeclNode(DeclKind::ParamK, ExpType::Void);
   param_outputc->lineno = -1;
   param_outputc->attr.name = strdup("*dummy*");

   outputc = newDeclNode(DeclKind::FuncK, ExpType::Void);
   outputc->lineno = -1;
   outputc->attr.name = strdup("outputc");

   outnl = newDeclNode(DeclKind::FuncK, ExpType::Void);
   outnl->lineno = -1;
   outnl->attr.name = strdup("outnl");

   // link them and prefix the tree we are interested in traversing.
   // This will put the symbols in the symbol table.
   input->sibling = output;
   output->sibling = inputb;
   inputb->sibling = outputb;
   outputb->sibling = inputc;
   inputc->sibling = outputc;
   outputc->sibling = outnl;
   outnl->sibling = start; // add in the tree we were given
   
   return input;
}

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
program : precomList declList                { syntaxTree = $2; printDebug("start"); }
   ;

precomList : precomList PRECOMPILER          { cout << yylval.tinfo->tokenstr << "\n"; $$ = nullptr; printDebug("precompile list"); }
   | PRECOMPILER                             { cout << yylval.tinfo->tokenstr << "\n"; $$ = nullptr; printDebug("start2"); }
   | /* empty */                             { $$ = nullptr; }
   ;

declList : declList decl                     { $$ = addSibling($1, $2); printDebug("declList"); }
   | decl                                    { $$ = $1; printDebug("decl"); }
   ;

decl : varDecl                               { $$ = $1; printDebug("varDecl"); }
   | funDecl                                 { $$ = $1; printDebug("funDecl"); }
   ;

varDecl : typeSpec varDeclList ';'           { $$ = $2; setType($2, $1, false); printDebug("typespec varDeclL"); }
   ;

scopedVarDecl : STATIC typeSpec varDeclList ';'    { $$ = $3; setType($3, $2, true); $$->isStatic = true; printDebug("scopedVarDecl"); }
   | typeSpec varDeclList ';'                { $$ = $2; setType($2, $1, false); $$->isStatic = false; printDebug("type varDeclList"); }
   ;

varDeclList : varDeclList ',' varDeclInit    { $$ = addSibling($1, $3); printDebug("varDeclList"); }
   | varDeclInit                             { $$ = $1; printDebug("varDeclInit"); }
   ;

varDeclInit : varDeclId                      { $$ = $1; printDebug("varDeclId"); }
   | varDeclId ':' simpleExp                 { $$ = $1; $1->child[0] = $3; } // addSibling($1, $3);}
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

parmIdList : parmIdList ',' parmId           { $$ = addSibling($1, $3);}
   | parmId                                  { $$ = $1;}
   ;

parmId : ID                                  { $$ = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, $1); 
                                               $$->isArray = false; $$->isStatic = false;}
   | ID '[' ']'                              { $$ = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, $1); 
                                               $$->isArray = true; $$->isStatic = false;}
   ;

stmt : matched                               { $$ = $1; printDebug("matched stmt"); }
   | unmatched                               { $$ = $1; }
   ;

matched : IF simpleExp THEN matched ELSE matched   { $$ = newStmtNode(StmtKind::IfK, $1, $2, $4, $6); }
   | WHILE simpleExp DO matched              { $$ = newStmtNode(StmtKind::WhileK, $1, $2, $4); }
   | FOR ID '=' iterRange DO matched         { $$ = newStmtNode(StmtKind::ForK, $1, nullptr, $4, $6); 
                                               $$->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, $2);}
   | expstmt                                 { $$ = $1; printDebug("matched exp"); }
   | compoundstmt                            { $$ = $1; }
   | returnstmt                              { $$ = $1; }
   | breakstmt                               { $$ = $1; }
   ;

iterRange : simpleExp TO simpleExp           {  $$ = newStmtNode(StmtKind::RangeK, $2, $1, $3); }
   | simpleExp TO simpleExp BY simpleExp     {  $$ = newStmtNode(StmtKind::RangeK, $2, $1, $3, $5); }
   ;

unmatched : IF simpleExp THEN stmt           { $$ = newStmtNode(StmtKind::IfK, $1, $2, $4); }
   | IF simpleExp THEN matched ELSE unmatched   { $$ = newStmtNode(StmtKind::IfK, $1, $2, $4, $6); }
   | WHILE simpleExp DO unmatched            { $$ = newStmtNode(StmtKind::WhileK, $1, $2, $4); }
   | FOR ID '=' iterRange DO unmatched       { $$ = newStmtNode(StmtKind::ForK, $1, nullptr, $4, $6); 
                                               $$->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, $2);}
   ;

expstmt : exp ';'                            { $$ = $1; printDebug("expstmt"); }
   | ';'                                     { $$ = nullptr; }
   ;

compoundstmt : '{' localDecls stmtList '}'   { $$ = newStmtNode(StmtKind::CompoundK, $1, $2, $3); printDebug("compound stmt"); }
   | compoundstmt ';'                        { $$ = $1; }
   ;


localDecls : localDecls scopedVarDecl        { $$ = addSibling($1, $2);}
   | /* empty */                             { $$ = nullptr;}
   ;

stmtList : stmtList stmt                     { $$ = addSibling($1, $2); printDebug("stmtList"); }
   | /* empty */                             { $$ = nullptr;}
   ;

returnstmt : RETURN ';'                      { $$ = newStmtNode(StmtKind::ReturnK, $1);}
   | RETURN exp ';'                          { $$ = newStmtNode(StmtKind::ReturnK, $1, $2);}
   ;

breakstmt : BREAK ';'                        { $$ = newStmtNode(StmtKind::BreakK, $1);}
   ;

exp : mutable assignop exp                   { $$ = newExpNode(ExpKind::AssignK, $2, $1, $3); $$->isAssigned = true; printDebug("mutable"); } 
   | mutable INC                             { $$ = newExpNode(ExpKind::AssignK, $2, $1);}
   | mutable DEC                             { $$ = newExpNode(ExpKind::AssignK, $2, $1);}
   | simpleExp                               { $$ = $1; printDebug("simpleExp"); }
   | mutable assignop ERROR                  { $$ = newExpNode(ExpKind::AssignK, $2, $1); yyerror($3->tokenstr); printDebug("mutable error"); }
   ;

assignop : '='                               { $$ = $1; }
   | ADDASS                                  { $$ = $1; }
   | SUBASS                                  { $$ = $1; }
   | MULASS                                  { $$ = $1; }
   | DIVASS                                  { $$ = $1; }
   ;

simpleExp : simpleExp OR andExp              { $$ = newExpNode(ExpKind::OpK, $2, $1, $3); printDebug("simpleexp new node"); }
   | andExp                                  { $$ = $1; printDebug("simpleexp and"); }
   ;

andExp : andExp AND unaryRelExp              { $$ = newExpNode(ExpKind::OpK, $2, $1, $3); printDebug("and op"); }
   | unaryRelExp                             { $$ = $1; printDebug("and unary"); }
   ;

unaryRelExp : NOT unaryRelExp                { $$ = newExpNode(ExpKind::OpK, $1, $2); printDebug("not unary exp"); }
   | relExp                                  { $$ = $1; printDebug("rel exp"); }
   ;

relExp : minmaxExp relop minmaxExp           { $$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | minmaxExp                               { $$ = $1; printDebug("minmax exp"); }
   ;

relop : LEQ                                  { $$ = $1;}
   | '<'                                     { $$ = $1;}
   | '>'                                     { $$ = $1;}
   | GEQ                                     { $$ = $1;}
   | EQ                                      { $$ = $1;} 
   | NEQ                                     { $$ = $1;}
   ;

minmaxExp : minmaxExp minmaxop sumExp        { $$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | sumExp                                  { $$ = $1; printDebug("sum exp"); }
   ;

minmaxop : MAX                               { $$ = $1;}
   | MIN                                     { $$ = $1;}
   ;

sumExp : sumExp sumop mulExp                 { $$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | mulExp                                  { $$ = $1; printDebug("muloexp"); }
   ;

sumop : '+'                                  { $$ = $1;}
   | '-'                                     { $$ = $1;}
   ;

mulExp : mulExp mulop unaryExp               { $$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | unaryExp                                { $$ = $1; printDebug("unaryexp"); }
   ;

mulop : '*'                                  { $$ = $1;}
   | '/'                                     { $$ = $1;}
   | '%'                                     { $$ = $1;}
   ;

unaryExp : unaryop unaryExp                  { $$ = newExpNode(ExpKind::OpK, $1, $2);}
   | factor                                  { $$ = $1; printDebug("factor"); }
   ;

unaryop : '-'                                { $$ = $1; $$->svalue = (char *)"chsign"; }
   | '*'                                     { $$ = $1; $$->svalue = (char *)"sizeof"; }
   | '?'                                     { $$ = $1;}
   ;

factor : immutable                           { $$ = $1; printDebug("immutable"); }
   | mutable                                 { $$ = $1; printDebug("mutable"); }
   ;

mutable : ID                                 { $$ = newExpNode(ExpKind::IdK, $1); $$->isArray = false;}
   | ID '[' exp ']'                          { $$ = newExpNode(ExpKind::OpK, $2, nullptr, $3); $$->child[0] = newExpNode(ExpKind::IdK, $1);}
   ;

immutable : '(' exp ')'                      { $$ = $2; printDebug("immutable exp"); }
   | call                                    { $$ = $1; printDebug("immutable call"); }
   | constant                                { $$ = $1; printDebug("constant"); }
   ;

call : ID '(' args ')'                       { $$ = newExpNode(ExpKind::CallK, $1, $3); printDebug("call ID"); }
   ;

args : argList                               { $$ = $1; printDebug("arglist"); }
   | /* empty */                             { $$ = nullptr;}
   ;

argList : argList ',' exp                    { $$ = addSibling($1, $3); printDebug("arglist , exp"); }
   | exp                                     { $$ = $1; printDebug("argList exp"); }
   ;

constant : NUMCONST                          { $$ = newExpNode(ExpKind::ConstantK, $1); 
                                               $$->type = ExpType::Integer; 
                                               $$->isArray = false;
                                               $$->size = 1;               // not needed for asn3, but asn4
                                               printDebug("numconst"); }
         | CHARCONST                         { $$ = newExpNode(ExpKind::ConstantK, $1); 
                                               $$->type = ExpType::Char; 
                                               $$->isArray = false;
                                               $$->attr.cvalue = $1->cvalue;  // not needed for asn3, but asn4
                                               printDebug("charconst"); }
         | STRINGCONST                       { $$ = newExpNode(ExpKind::ConstantK, $1); 
                                               $$->type = ExpType::Char; 
                                               $$->isArray = true; 
                                               printDebug("stringconst"); }
         | BOOLCONST                         { $$ = newExpNode(ExpKind::ConstantK, $1); 
                                               $$->type = ExpType::Boolean; 
                                               $$->isArray = false;
                                               printDebug("boolconst"); }
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
         //printDotTree(stdout, syntaxTree, false, false);
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

