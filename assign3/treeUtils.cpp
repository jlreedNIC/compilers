#include "treeUtils.h"

TreeNode *cloneNode(TreeNode *currnode)
{
    TreeNode *newNode = new TreeNode;

    // newNode->child = currnode->child;
    for (int i = 0; i < MAXCHILDREN; i++)
    {
        newNode->child[i] = currnode->child[i];
    }
    newNode->sibling = currnode->sibling;
    newNode->nodeNum = currnode->nodeNum;

    newNode->lineno = currnode->lineno;
    newNode->nodekind = currnode->nodekind;
    newNode->kind.decl = currnode->kind.decl;
    newNode->kind.stmt = currnode->kind.stmt;
    newNode->kind.exp = currnode->kind.exp;

    newNode->attr.op = currnode->attr.op;
    newNode->attr.value = currnode->attr.value;
    newNode->attr.cvalue = currnode->attr.cvalue;
    newNode->attr.name = currnode->attr.name;
    newNode->attr.string = currnode->attr.string;

    newNode->type = currnode->type;
    newNode->isStatic = currnode->isStatic;
    newNode->isArray = currnode->isArray;
    newNode->isConst = currnode->isConst;
    newNode->isUsed = currnode->isUsed;
    newNode->isAssigned = currnode->isAssigned;

    newNode->varKind = currnode->varKind;
    newNode->offset = currnode->offset;
    newNode->size = currnode->size;

    return newNode;
}

TreeNode *newDeclNode(DeclKind kind,
                      ExpType type,
                      TokenData *token,
                      TreeNode *c0,
                      TreeNode *c1,
                      TreeNode *c2)  // save TokenData block!!
{
    TreeNode *newNode = new TreeNode;

    newNode->kind.decl = kind;
    newNode->type = type;

    // setting token data??
    newNode->attr.op = token->tokenclass;
    newNode->attr.value = token->nvalue;
    newNode->attr.cvalue = token->cvalue;
    newNode->attr.name = token->svalue;
    newNode->attr.string = token->tokenstr;

    newNode->child[0] = c0;
    newNode->child[1] = c1;
    newNode->child[2] = c2;

    return newNode;
}

TreeNode *newStmtNode(StmtKind kind,
                      TokenData *token,
                      TreeNode *c0,
                      TreeNode *c1,
                      TreeNode *c2)
{
    TreeNode *newNode = new TreeNode;

    newNode->kind.stmt = kind;
    // newNode->type = type;

    // setting token data??
    newNode->attr.op = token->tokenclass;
    newNode->attr.value = token->nvalue;
    newNode->attr.cvalue = token->cvalue;
    newNode->attr.name = token->svalue;
    newNode->attr.string = token->tokenstr;

    newNode->child[0] = c0;
    newNode->child[1] = c1;
    newNode->child[2] = c2;

    return newNode;
}

TreeNode *newExpNode(ExpKind kind,
                     TokenData *token,
                     TreeNode *c0,
                     TreeNode *c1,
                     TreeNode *c2)
{

    TreeNode *newNode = new TreeNode;

    newNode->kind.exp = kind;
    // newNode->type = type;

    // setting token data??
    newNode->attr.op = token->tokenclass;
    newNode->attr.value = token->nvalue;
    newNode->attr.cvalue = token->cvalue;
    newNode->attr.name = token->svalue;
    newNode->attr.string = token->tokenstr;

    newNode->child[0] = c0;
    newNode->child[1] = c1;
    newNode->child[2] = c2;

    return newNode;
}

char *tokenToStr(int type)
{

}

char *expTypeToStr(ExpType type, bool isArray=false, bool isStatic=false)
{

}

void printTreeNode(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{

}

void printTree(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
    
}