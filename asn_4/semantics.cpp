#include "semantics.h"
#include "parser.tab.h" //always put this last
static int goffset;
static int foffset;

TreeNode *loadIOLib(TreeNode *start)
{
    // printf("started load iolib\n");
    // new nodes to create
    TreeNode *input, *output, *param_output;
    TreeNode *inputb, *outputb, *param_outputb;
    TreeNode *inputc, *outputc, *param_outputc;
    TreeNode *outnl;
    // printf("nodes declared\n");

    ///////// Stuff from next slides
    input = newDeclNode(DeclKind::FuncK, ExpType::Integer);
    // printf("input node done1");
    input->lineno = -1; // all are -1
    input->attr.name = strdup("input");
    input->type = ExpType::Integer; // is this needed??
    // printf("input node done");

    inputb = newDeclNode(DeclKind::FuncK, ExpType::Boolean);
    inputb->lineno = -1;
    inputb->attr.name = strdup("inputb");

    inputc = newDeclNode(DeclKind::FuncK, ExpType::Boolean);
    inputc->lineno = -1;
    inputc->attr.name = strdup("inputc");
    inputc->type = ExpType::Char;

    param_output = newDeclNode(DeclKind::ParamK, ExpType::Void);
    // param_output->lineno = -1;
    param_output->attr.name = strdup("*dummy*");
    param_output->type = ExpType::Integer;

    output = newDeclNode(DeclKind::FuncK, ExpType::Void);
    output->lineno = -1;
    output->attr.name = strdup("output");

    param_outputb = newDeclNode(DeclKind::ParamK, ExpType::Void);
    // param_outputb->lineno = -1;
    param_outputb->attr.name = strdup("*dummy*");
    param_outputb->type = ExpType::Boolean;

    outputb = newDeclNode(DeclKind::FuncK, ExpType::Void);
    outputb->lineno = -1;
    outputb->attr.name = strdup("outputb");

    param_outputc = newDeclNode(DeclKind::ParamK, ExpType::Void);
    // param_outputc->lineno = -1;
    param_outputc->attr.name = strdup("*dummy*");
    param_outputc->type = ExpType::Char;

    outputc = newDeclNode(DeclKind::FuncK, ExpType::Void);
    outputc->lineno = -1;
    outputc->attr.name = strdup("outputc");

    outnl = newDeclNode(DeclKind::FuncK, ExpType::Void);
    outnl->lineno = -1;
    outnl->attr.name = strdup("outnl");
    // printf("outnl node done");

    // link them and prefix the tree we are interested in traversing.
    // This will put the symbols in the symbol table.
    input->sibling = output;
    output->sibling = inputb;
    output->child[0] = param_output;
    inputb->sibling = outputb;
    outputb->sibling = inputc;
    outputb->child[0] = param_outputb;
    inputc->sibling = outputc;
    outputc->sibling = outnl;
    outputc->child[0] = param_outputc;
    outnl->sibling = start; // add in the tree we were given
    outnl->child[0] = nullptr;

    // printf("ending io lib");
    return input;
}

TreeNode *semanticAnalysis(TreeNode *syntree,          // pass in and return an annotated syntax tree
                           bool shareCompoundSpaceIn,   // SPECIAL OPTION: make compound after a function share scope
                           bool noDuplicateUndefsIn,    // SPECIAL OPTION: no duplicate undefines
                           SymbolTable *symtabX,       // pass in and return the symbol table
                           int &globalOffset            // return the offset past the globals
    )
{
    syntree = loadIOLib(syntree);
    
    return syntree;
}

void treeTraverse(TreeNode *syntree, SymbolTable *symtab)
{
    printf("starting tree traversal\n");
}