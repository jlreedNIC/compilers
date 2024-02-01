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
extern int yylex();
TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
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
extern "C" int yyparse();
extern "C" FILE *yyin;

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
%type    <tree>   precomList declList decl varDecl funDecl
%type    <tree>   program

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
%token   <tinfo> FIRSTSTOP LASTSTOP
//%type    <tinfo>  term program

//%type   <tree>  program compoundstmt

%%
program : precomList declList {syntaxTree = $2;}
   ;

precomList : precomList PRECOMPILER {}
   | PRECOMPILER {}
   ;

declList : declList decl {$$ = addSibling($1, $2);}
   | decl {$$ = $1;}
   ;

decl : varDecl {$$ = $1;}
   | funDecl {$$ = $1;}
   ;

compoundstmt : '{' localDecls stmtList '}' {$$ = newStmtNode(StmtKind::CompoundK, $1, $2, $3);}
   ;

matched : IF simpleExp THEN matched ELSE matched {}
   | WHILE simpleExp DO matched {}
   | FOR ID '=' iterRange DO matched {}
   | expstmt {}
   | compoundstmt {$$ = $1;}
   | returnstmt {}
   | breakstmt {}
   ;

stmt : matched {}
   | unmatched {}
   ;

parmId : ID {}
   | ID '[' ']' {}
   ;

parmIdList : parmIdList ',' parmId {}
   | parmTypeList {}
   ;

typeSpec : INT {$$ = ExpType::Integer;}
   | BOOL {}
   | CHAR {}
   ;

funDecl : typeSpec ID '(' parms ')' stmt {}
   | ID '(' parms ')' stmt {}//$$ = newDeclNode(DeclKind::FuncK, );}
   ;

breakstmt : BREAK
   ;

expstmt : exp {}
   ;

exp : mutable assignop exp {}
   | mutable INC {}
   | mutable DEC {}
   | simpleExp {}
   | mutable assignop ERROR {}
   ;

assignop : ADDASS {}
   | SUBASS {}
   | MULASS {}
   | DIVASS {}
   ;

simpleExp : simpleExp OR andExp {}
   | andExp {}
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
   yylvala.tinfo = (TokenData*)malloc(sizeof(TokenData));
   yylvlal.tree = (TreeNode*)malloc(sizeof(TreeNode));
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

