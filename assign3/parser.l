%{
#include "scanType.h"
#include "treeNodes.h"
#include "treeUtils.h"
#include "parser.tab.h" // This has to be the last include

using namespace std;

#define YY_DECL extern "C" int yylex()
#define YYSTYPE int

int line=1;
char *lastToken=(char *)"";
//extern int numErrors;

int setValue(int linenum, int tokenClass, char *svalue) {
    yylval.tinfo = new TokenData;

    yylval.tinfo->tokenclass = tokenClass;
    yylval.tinfo->linenum = linenum;
    yylval.tinfo->tokenstr = strdup(svalue);
    yylval.tinfo->cvalue = '@';
    yylval.tinfo->nvalue = 777;
    yylval.tinfo->svalue = NULL;

    yylval.tinfo->tokenstr = lastToken = strdup(svalue);

    switch (tokenClass) {

    case NUMCONST:
         yylval.tinfo->nvalue = stoi(svalue);
         break;
    case ID:
         yylval.tinfo->svalue = strdup(svalue);
         break;

    case '=': // op
    case '*':
    case '+':
    case '/':
    case '%':
    case '-':
    case '<':
    case '>':
    case '?':
    case ':':
         yylval.tinfo->cvalue = svalue[0];
         break;
    }


    return tokenClass;
}

%}

%option noyywrap

letter      [a-zA-Z]
digit    [0-9]
quote    [\']
underbar [_]
letdig      {digit}|{letter}|{underbar}
limitters   [\;\,\(\)\{\}\[\]]
op    [\-\+\*\/\%]
whitespace  [\ \t]
%%
[\(\)\{\}\[\]\+\=\-\;\:\,\<\>\*\/\%\?]         { return setValue(line, yytext[0], yytext); } // single char tokens

[\/][\/].*      {  }

"!="            { return setValue(line, NEQ, yytext); }

">="            { return setValue(line, GEQ, yytext); }

"<="            { return setValue(line, LEQ, yytext); }

":<:"           { return setValue(line, MIN, yytext); }

":>:"           { return setValue(line, MAX, yytext); }

"=="            { return setValue(line, EQ, yytext); }

"-="            { return setValue(line, SUBASS, yytext); }

"+="            { return setValue(line, ADDASS, yytext); }

"*="            { return setValue(line, MULASS, yytext); }

"/="            { return setValue(line, DIVASS, yytext); }

"++"            { return setValue(line, INC, yytext); }

"--"            { return setValue(line, DEC, yytext); }

"not"           { return setValue(line, NOT, yytext); }

"and"           { return setValue(line, AND, yytext); }

"or"            { return setValue(line, OR, yytext); }

"bool"          { return setValue(line, BOOL, yytext); }

"int"           { return setValue(line, INT, yytext); }

"char"          { return setValue(line, CHAR, yytext); }

"static"        { return setValue(line, STATIC, yytext); }

"if"            { return setValue(line, IF, yytext); }

"then"          { return setValue(line, THEN, yytext); }

"else"          { return setValue(line, ELSE, yytext); }

"while"         { return setValue(line, WHILE, yytext); }

"do"            { return setValue(line, DO, yytext); }

"for"           { return setValue(line, FOR, yytext); }

"to"            { return setValue(line, TO, yytext); }

"by"            { return setValue(line, BY, yytext); }

"return"        { return setValue(line, RETURN, yytext); }

"break"         { return setValue(line, BREAK, yytext); }

"true"          { return setValue(line, BOOLCONST, yytext); }

"false"         { return setValue(line, BOOLCONST, yytext); }

^"#DRBC ".*     { return setValue(line, PRECOMPILER, yytext); }

[\'](.|"\\n")[\']       { return setValue(line, CHARCONST, yytext); }

[\"].*[\"]      { return setValue(line, STRINGCONST, yytext); }

[0-9]+          { return setValue(line, NUMCONST, yytext); }

[a-zA-Z][a-zA-Z0-9]*    { return setValue(line, ID, yytext); }

\n              {  line++; }
{whitespace}+  ;
.              { printf("ERROR(%d): Token error, invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]);}


