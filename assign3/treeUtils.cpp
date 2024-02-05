#include "treeUtils.h"

static int nodeNumber = 0;

TreeNode *cloneNode(TreeNode *currnode)
{
//   std::cout << "in cloneNode func\n";
    TreeNode *newNode = new TreeNode;

    // newNode->child = currnode->child;
    for (int i = 0; i < MAXCHILDREN; i++)
    {
        newNode->child[i] = currnode->child[i];
    }
    newNode->sibling = currnode->sibling;
    newNode->nodeNum = nodeNumber++;

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
  // std::cout << "newDeclNode created\n";
    // did in class
    TreeNode *newNode = new TreeNode;
    newNode->nodekind = NodeKind::DeclK;
    newNode->kind.decl = kind;
    newNode->child[0] = c0;
    newNode->child[1] = c1;
    newNode->child[2] = c2;
    newNode->sibling = NULL;

    newNode->type = type;
    newNode->nodeNum = nodeNumber++;

    // // setting token data??
    newNode->attr.op = token->tokenclass;
    newNode->attr.value = token->nvalue;
    newNode->attr.cvalue = token->cvalue;
    newNode->attr.name = token->svalue;
    newNode->attr.string = token->tokenstr;

    return newNode;
}

TreeNode *newStmtNode(StmtKind kind,
                      TokenData *token,
                      TreeNode *c0,
                      TreeNode *c1,
                      TreeNode *c2)
{
    //std::cout << "adding new stmtNode\n";
    // did in class
    TreeNode *newNode = new TreeNode;
    newNode->nodekind = NodeKind::StmtK;
    newNode->kind.stmt = kind;
    newNode->child[0] = c0;
    newNode->child[1] = c1;
    newNode->child[2] = c2;
    newNode->sibling = NULL;

    newNode->nodeNum = nodeNumber++;

    // // setting token data??
    newNode->attr.op = token->tokenclass;
    newNode->attr.value = token->nvalue;
    newNode->attr.cvalue = token->cvalue;
    newNode->attr.name = token->svalue;
    newNode->attr.string = token->tokenstr;

    return newNode;
}

TreeNode *newExpNode(ExpKind kind,
                     TokenData *token,
                     TreeNode *c0,
                     TreeNode *c1,
                     TreeNode *c2)
{
    // did in class
    TreeNode *newNode = new TreeNode;
    newNode->nodekind = NodeKind::ExpK;
    newNode->kind.exp = kind;
    newNode->child[0] = c0;
    newNode->child[1] = c1;
    newNode->child[2] = c2;
    newNode->sibling = NULL;

    newNode->nodeNum = nodeNumber++;

    return newNode;

    // TreeNode *newNode = new TreeNode;

    // newNode->kind.exp = kind;
    // // newNode->type = type;

    // // setting token data??
    // newNode->attr.op = token->tokenclass;
    // newNode->attr.value = token->nvalue;
    // newNode->attr.cvalue = token->cvalue;
    // newNode->attr.name = token->svalue;
    // newNode->attr.string = token->tokenstr;

    // newNode->child[0] = c0;
    // newNode->child[1] = c1;
    // newNode->child[2] = c2;

    // return newNode;
}

// need to know what string should be returned
char *tokenToStr(int type)
{
    char *str;

    if (type == DeclK)
        strcpy(str, "DECL");
    // str = "DECL";
    else if (type == StmtK)
        // str = "STMT";
        strcpy(str, "STMT");
    // else if(type == ExpK)
    else
        // str = "EXPR";
        strcpy(str, "EXPR");

    return str;
}

char *expTypeToStr(ExpType type, bool isArray, bool isStatic)
{
    char *str;

    if (type == Void)
        strcpy(str, "VOID");
    else if (type == Integer)
        strcpy(str, "INT");
    else if (type == Boolean)
        strcpy(str, "BOOL");
    else if(type == Char)
        strcpy(str, "CHAR");
    else
        strcpy(str, "UNDF");

    return str;
}

void printTreeNode(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
    if(syntaxTree->nodekind == NodeKind::DeclK)
    {
        fprintf(out, "Hey I'm a declK node.");
    }
    else if(syntaxTree->nodekind == NodeKind::StmtK)
    {
        fprintf(out, "Hey I'm a stmtK node.");
    }
    else if(syntaxTree->nodekind == NodeKind::ExpK)
    {
        fprintf(out, "Hey I'm an expK node.");
    }
    else 
    fprintf(out, "Hey I'm a node, say something here.");

    return;
}

void printDots(FILE *out, int depth)
{
    for(int i=0; i<depth; i++)
    {
       fprintf(out, ".   ");
    }
}

void printTree(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
//   fprintf(out, "printing tree\n");
    if(syntaxTree == nullptr)
    {
        fprintf(out, "NULL\n");
        return;
    }

    printTreeRecursive(out, syntaxTree, showExpType, showAllocation, 1);
    return;
}

void printTreeRecursive(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation, int depth, int siblingCount)
{
    // check if null
    if(syntaxTree == NULL) 
    {
//        fprintf(out, "node is null\n");
        return;
    }

    //for(int i=0; i<depth; i++)
    //{
      // fprintf(out, ".   ");
    //}

    // current node
    printTreeNode(out, syntaxTree, showExpType, showAllocation);
    fprintf(out, "\n");

    // recursively search each child
    for(int i=0; i<MAXCHILDREN; i++)
    {
        //fprintf(out, "searching child %d \n", i);
        //for(int j=0; j<depth; j++)
        //{
        //    fprintf(out, ".   ");
        //}
        if(syntaxTree->child[i] != nullptr)
        {
            printDots(out, depth);

            fprintf(out, "Child: %i  ", i);
            printTreeRecursive(out, syntaxTree->child[i], showExpType, showAllocation, depth+1);
        }
    }

    TreeNode *sibling = syntaxTree->sibling;
    if(sibling != NULL)
    {
        fprintf(out, "Sibling: %d  ", siblingCount);
        printTreeRecursive(out, sibling, showExpType, showAllocation, depth, siblingCount+1);
    }
}
