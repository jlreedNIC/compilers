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
//extern int yylex();
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
   ptr = t->sibling;
   while(ptr != nullptr)
   {
      ptr = ptr->sibling;
   }
   ptr->sibling = s;
   // make sure s is not null. If it is this s a major error. Exit the program!
   // Make sure t is not null. If it is, just return s
   // look down t’s sibling list until you fin with with sibblin = null (the end o f the lsit) and add s there.
   return s;
}

// pass the static and type attribute down the sibling list
void setType(TreeNode *t, ExpType type, bool isStatic)
{
   while (t != nullptr)
   {
      t->type = type;
      t->isStatic = isStatic;
//      set t->type and t->isStatic
      t = t->sibling;
   }
}
// the syntax tree goes here
TreeNode *syntaxTree;

extern "C" int yylex();
//extern "C" int yyparse();
//extern "C" FILE *yyin;

void yyerror(const char *msg);

void printToken(TokenData myData, string tokenName, int type = 0) {
   if(tokenName == "COMMENT") return;

   cout << "Line: " << myData.linenum << " Type: " << tokenName;
   if(type==0)
     cout << " Token: " << myData.tokenstr;
   if(type==1)
     cout << " Token: " << myData.nvalue;
   if(type==2)
     cout << " Token: " << myData.cvalue;
   cout << endl;
}

%}
%union
{
   struct   TokenData *tinfo;
//   TokenData *tokenData;
   struct   TreeNode *tree;
   ExpType  type;
}

// tree data?
%type    <tree>   parmIdList parmId stmt matched iterRange unmatched expstmt
%type    <tree>   compoundstmt localDecls stmtList returnstmt breakstmt
%type    <tree>   precomList declList decl varDecl funDecl varDeclList
%type    <tree>   program typeSpec

// token data
%token   <tinfo>  OP
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
%token   <tinfo>  FIRSTSTOP LASTSTOP
//%type    <tinfo>  term program

//%type   <tree>  program compoundstmt

%%
program : precomList declList {syntaxTree = $2;}
   ;

precomList : precomList PRECOMPILER { cout << "I'm a node.\n"; $$ = nullptr; }
   | PRECOMPILER { cout << "I'm a node.\n"; $$ = nullptr; }
   ;

declList : declList decl {$$ = addSibling($1, $2);}
   | decl {$$ = $1;}
   ;

decl : varDecl {$$ = $1;}
   | funDecl {$$ = $1;}
   ;

varDecl : typeSpec varDeclList ';' { cout << "I'm a node.\n"; $$ = addSibling($1, $2); }
   ;

varDeclList : varDeclList ',' varDeclInit { cout << "I'm a node.\n"; }
   | varDeclInit { cout << "I'm a node.\n"; }
   ;

varDeclInit : varDeclId { cout << "I'm a node.\n"; }
   | varDeclId ':' simpleExp { cout << "I'm a node.\n"; }
   ;

varDeclId : ID { cout << "I'm a node.\n"; }
   | ID '[' NUMCONST ']' { cout << "I'm a node.\n"; }
   ;

parms : parmList { cout << "I'm a node.\n"; }
   | /* empty */ { cout << "I'm a node.\n"; }
   ;

parmList : parmList ';' parmTypeList { cout << "I'm a node.\n"; }
   | parmTypeList { cout << "I'm a node.\n"; }
   ;

parmTypeList : typeSpec parmIdList { cout << "I'm a node.\n"; }
   ;

compoundstmt : '{' localDecls stmtList '}' { cout << "I'm a node.\n"; }//$$ = newStmtNode(StmtKind::CompoundK, $1, $2, $3);}
   ;

matched : IF simpleExp THEN matched ELSE matched { cout << "I'm a node.\n"; }
   | WHILE simpleExp DO matched { cout << "I'm a node.\n"; }
   | FOR ID '=' iterRange DO matched { cout << "I'm a node.\n"; }
   | expstmt { cout << "I'm a node.\n"; }
   | compoundstmt {$$ = $1;}
   | returnstmt { cout << "I'm a node.\n"; }
   | breakstmt { cout << "I'm a node.\n"; }
   ;

iterRange : simpleExp TO simpleExp { cout << "I'm a node.\n"; }
   | simpleExp TO simpleExp BY simpleExp { cout << "I'm a node.\n"; }
   ;

unmatched : IF simpleExp THEN stmt { cout << "I'm a node.\n"; }
   | IF simpleExp THEN matched ELSE unmatched { cout << "I'm a node.\n"; }
   | WHILE simpleExp DO unmatched { cout << "I'm a node.\n"; }
   | FOR ID '=' iterRange DO unmatched { cout << "I'm a node.\n"; }
   ;

localDecls : localDecls scopedVarDecl { cout << "I'm a node.\n"; }
   | /* empty */ { cout << "I'm a node.\n"; }
   ;

stmtList : stmtList stmt { cout << "I'm a node.\n"; }
   | /* empty*/ { cout << "I'm a node.\n"; }
   ;

returnstmt : RETURN ';' { cout << "I'm a node.\n"; }
   | RETURN exp ';' { cout << "I'm a node.\n"; }
   ;

scopedVarDecl : STATIC typeSpec varDeclList ';' { cout << "I'm a node.\n"; }
   | typeSpec varDeclList ';' { cout << "I'm a node.\n"; }
   ;

stmt : matched { cout << "I'm a node.\n"; }
   | unmatched { cout << "I'm a node.\n"; }
   ;

parmId : ID { cout << "I'm a node.\n"; }
   | ID '[' ']' { cout << "I'm a node.\n"; }
   ;

parmIdList : parmIdList ',' parmId { cout << "I'm a node.\n"; }
   | parmTypeList { cout << "I'm a node.\n"; }
   ;

typeSpec : INT { cout << "I'm a node.\n"; } //$$ = ExpType::Integer;}
   | BOOL { cout << "I'm a node.\n"; }
   | CHAR { cout << "I'm a node.\n"; }
   ;

funDecl : typeSpec ID '(' parms ')' stmt { cout << "I'm a node.\n"; }
   | ID '(' parms ')' stmt { cout << "I'm a node.\n"; }//$$ = newDeclNode(DeclKind::FuncK, );}
   ;

breakstmt : BREAK { cout << "I'm a node.\n"; }
   ;

expstmt : exp { cout << "I'm a node.\n"; }
   ;

exp : mutable assignop exp { cout << "I'm a node.\n"; }
   | mutable INC { cout << "I'm a node.\n"; }
   | mutable DEC { cout << "I'm a node.\n"; }
   | simpleExp { cout << "I'm a node.\n"; }
   | mutable assignop ERROR { cout << "I'm a node.\n"; }
   ;

assignop : ADDASS { cout << "I'm a node.\n"; }
   | SUBASS { cout << "I'm a node.\n"; }
   | MULASS { cout << "I'm a node.\n"; }
   | DIVASS { cout << "I'm a node.\n"; }
   ;

simpleExp : simpleExp OR andExp { cout << "I'm a node.\n"; }
   | andExp { cout << "I'm a node.\n"; }
   ;

andExp : andExp AND unaryRelExp { cout << "I'm a node.\n"; }
   | unaryRelExp { cout << "I'm a node.\n"; }
   ;

unaryRelExp : NOT unaryRelExp { cout << "I'm a node.\n"; }
   | relExp { cout << "I'm a node.\n"; }
   ;

relExp : minmaxExp relop minmaxExp { cout << "I'm a node.\n"; }
   | minmaxExp { cout << "I'm a node.\n"; }
   ;

relop : LEQ { cout << "I'm a node.\n"; }
   | '<' { cout << "I'm a node.\n"; }
   | '>' { cout << "I'm a node.\n"; }
   | GEQ { cout << "I'm a node.\n"; }
   | EQ { cout << "I'm a node.\n"; }
   | NEQ { cout << "I'm a node.\n"; }
   ;

minmaxExp : minmaxExp minmaxop sumExp { cout << "I'm a node.\n"; }
   | sumExp { cout << "I'm a node.\n"; }
   ;

minmaxop : ":>:" { cout << "I'm a node.\n"; }
   | ":<:" { cout << "I'm a node.\n"; }
   ;

sumExp : sumExp sumop mulExp { cout << "I'm a node.\n"; }
   | mulExp { cout << "I'm a node.\n"; }
   ;

sumop : '+' { cout << "I'm a node.\n"; }
   | '-' { cout << "I'm a node.\n"; }
   ;

mulExp : mulExp mulop unaryExp { cout << "I'm a node.\n"; }
   | unaryExp { cout << "I'm a node.\n"; }
   ;

mulop : '*' { cout << "I'm a node.\n"; }
   | '/' { cout << "I'm a node.\n"; }
   | '%' { cout << "I'm a node.\n"; }
   ;

unaryExp : unaryop unaryExp { cout << "I'm a node.\n"; }
   | factor { cout << "I'm a node.\n"; }
   ;

unaryop : '-' { cout << "I'm a node.\n"; }
   | '*' { cout << "I'm a node.\n"; }
   | '?' { cout << "I'm a node.\n"; }
   ;

factor : immutable { cout << "I'm a node.\n"; }
   | mutable { cout << "I'm a node.\n"; }
   ;

mutable : ID { cout << "I'm a node.\n"; }
   | ID '[' exp ']' { cout << "I'm a node.\n"; }
   ;

immutable : '(' exp ')' { cout << "I'm a node.\n"; }
   | call { cout << "I'm a node.\n"; }
   | constant { cout << "I'm a node.\n"; }
   ;

call : ID '(' args ')' { cout << "I'm a node.\n"; }
   ;

args : argList { cout << "I'm a node.\n"; }
   | /* empty */ { cout << "I'm a node.\n"; }
   ;

argList : argList ',' exp { cout << "I'm a node.\n"; }
   | exp { cout << "I'm a node.\n"; }
   ;

constant : NUMCONST { cout << "I'm a node.\n"; }
   | CHARCONST { cout << "I'm a node.\n"; }
   | STRINGCONST { cout << "I'm a node.\n"; }
   | BOOLCONST { cout << "I'm a node.\n"; }
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

