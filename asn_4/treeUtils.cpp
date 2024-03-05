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
    // std::cout << "newDeclNode created of " << expTypeToStr(type) << "\n";
    // did in class
    TreeNode *newNode = new TreeNode;

    newNode->size = 1;
    newNode->offset = 0;

    newNode->nodekind = NodeKind::DeclK;
    newNode->kind.decl = kind;
    newNode->child[0] = c0;
    newNode->child[1] = c1;
    newNode->child[2] = c2;
    newNode->sibling = NULL;

    newNode->type = type;
    newNode->nodeNum = nodeNumber++;
    newNode->lineno = token->linenum;

    newNode->attr.op = token->tokenclass;
    newNode->attr.value = token->nvalue;
    newNode->attr.cvalue = token->cvalue;
    newNode->attr.name = token->svalue;
    // newNode->attr.string = token->tokenstr;
    


    return newNode;
}

TreeNode *newStmtNode(StmtKind kind,
                      TokenData *token,
                      TreeNode *c0,
                      TreeNode *c1,
                      TreeNode *c2)
{
    // std::cout << "adding new stmtNode\n";
    // did in class
    TreeNode *newNode = new TreeNode;

    newNode->size = 1;
    newNode->offset = 0;

    newNode->nodekind = NodeKind::StmtK;
    newNode->kind.stmt = kind;
    newNode->child[0] = c0;
    newNode->child[1] = c1;
    newNode->child[2] = c2;
    newNode->sibling = NULL;

    newNode->nodeNum = nodeNumber++;
    newNode->lineno = token->linenum;

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
    // std::cout << "new exp node\n";
    // did in class
    TreeNode *newNode = new TreeNode;

    newNode->size = 1;
    newNode->offset = 0;
    
    newNode->nodekind = NodeKind::ExpK;
    newNode->kind.exp = kind;
    newNode->child[0] = c0;
    newNode->child[1] = c1;
    newNode->child[2] = c2;
    newNode->sibling = NULL;

    newNode->nodeNum = nodeNumber++;
    newNode->lineno = token->linenum;

    newNode->attr.op = token->tokenclass;
    newNode->attr.value = token->nvalue;
    newNode->attr.cvalue = token->cvalue;
    newNode->attr.name = token->svalue;
    // newNode->attr.string = token->tokenstr;

    return newNode;
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

char result[100];
char *expTypeToStr(ExpType type, bool isArray, bool isStatic)
{
    char *str;

    if (type == ExpType::Void)
        str = (char *)"type void";
        // strType += "type void";
    else if (type == ExpType::Integer)
        str = (char *)"type int";
        // strType += "type int";
    else if (type == ExpType::Boolean)
        str = (char *)"type bool";
        // strType += "type bool";
    else if (type == ExpType::Char)
        str = (char *)"type char";
        // strType += "type char";
    else str = (char *)"undefined";

    // if(isArray)
    //     std::cout << "is array\n";
    // else
    //     std::cout << "not array- ";

    sprintf(result, "%s%s%s%s", (isArray && isStatic ? (char *)"static " : ""), (isArray ? (char *)"array of " : ""), (isStatic && !isArray ? (char *)"static " : ""), str);
    return result;
}

void printTreeNode(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
    if(syntaxTree->nodekind == NodeKind::DeclK)
    {
        switch(syntaxTree->kind.decl)
        {
            case DeclKind::VarK:
                fprintf(out, "Var: %s of %s", syntaxTree->attr.name, expTypeToStr(syntaxTree->type, syntaxTree->isArray, syntaxTree->isStatic));
                break;
            case DeclKind::FuncK:
                fprintf(out, "Func:");
                fprintf(out, " %s", syntaxTree->attr.name);
                fprintf(out, " returns %s", expTypeToStr(syntaxTree->type, syntaxTree->isArray, syntaxTree->isStatic));
                break;
            case DeclKind::ParamK:
                fprintf(out, "Parm: %s of %s", syntaxTree->attr.name, expTypeToStr(syntaxTree->type, syntaxTree->isArray, syntaxTree->isStatic));
                break;
            default:
                fprintf(out, "Hey I'm a declK node.");
                break;
        }
    }
    else if(syntaxTree->nodekind == NodeKind::StmtK)
    {
        switch(syntaxTree->kind.stmt)
        {
            case StmtKind::IfK:
                fprintf(out, "If");
                break;
            case StmtKind::WhileK:
                fprintf(out, "While");
                break;
            case StmtKind::ForK:
                fprintf(out, "For");
                break;
            case StmtKind::CompoundK:
                fprintf(out, "Compound");
                break;
            case StmtKind::ReturnK:
                fprintf(out, "Return");
                break;
            case StmtKind::BreakK:
                fprintf(out, "Break");
                break;
            case StmtKind::RangeK:
                fprintf(out, "Range");
                break;
            default:
                fprintf(out, "Hey I'm a stmtK node.");
                break;
        }
    }
    else if(syntaxTree->nodekind == NodeKind::ExpK)
    {
        switch(syntaxTree->kind.exp)
        {
            case ExpKind::AssignK:
                fprintf(out, "Assign: %s", syntaxTree->attr.name);
                break;
            case ExpKind::CallK:
                fprintf(out, "Call: %s", syntaxTree->attr.name);
                break;
            case ExpKind::ConstantK:
                char *value;

                fprintf(out, "Const");

                if(syntaxTree->type == ExpType::Boolean)
                {
                    if(syntaxTree->attr.value == 1)
                    {
                        value = (char *)"true";
                    }
                    else
                        value = (char *)"false";

                    fprintf(out, " %s", value);
                }
                else if(syntaxTree->type == ExpType::Char)
                {
                    if(syntaxTree->isArray)
                        fprintf(out, " %s", syntaxTree->attr.name);
                    else
                        fprintf(out, " '%c'", syntaxTree->attr.cvalue);
                }
                else fprintf(out, " %d", syntaxTree->attr.value);
                break;
            case ExpKind::IdK:
                fprintf(out, "Id: %s", syntaxTree->attr.name);
                break;
            case ExpKind::OpK:
                fprintf(out, "Op: %s", syntaxTree->attr.name);
                break;
            default:
                fprintf(out, "Hey I'm a ExpK node.");
                break;
        }
    }
    else fprintf(out, "Hey I'm a node, say something here.");
    fprintf(out, " [line: %d]", syntaxTree->lineno);
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
    // fprintf(out, "printing tree\n");
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
    //    fprintf(out, "node is null\n");
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
        printDots(out, depth - 1);
        fprintf(out, "Sibling: %d  ", siblingCount);
        printTreeRecursive(out, sibling, showExpType, showAllocation, depth, siblingCount+1);
    }
    // std::cout << "sibling null!\n";
}
