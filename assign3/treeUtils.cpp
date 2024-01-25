#include "treeUtils.h"

TreeNode *cloneNode(TreeNode *currnode)
{
    TreeNode *newNode = new TreeNode;

    // newNode->child = currnode->child;
    for (int i = 0; i < 3; i++)
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
}

TreeNode *newDeclNode(DeclKind kind,
                      ExpType type,
                      TokenData *token=NULL,
                      TreeNode *c0=NULL,
                      TreeNode *c1=NULL,
                      TreeNode *c2=NULL)  // save TokenData block!!
{

}

TreeNode *newStmtNode(StmtKind kind,
                      TokenData *token,
                      TreeNode *c0=NULL,
                      TreeNode *c1=NULL,
                      TreeNode *c2=NULL)
{

}

TreeNode *newExpNode(ExpKind kind,
                     TokenData *token,
                     TreeNode *c0=NULL,
                     TreeNode *c1=NULL,
                     TreeNode *c2=NULL)
{

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