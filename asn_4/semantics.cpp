#include "semantics.h"
#include "parser.tab.h" //always put this last
static int goffset; // size?
static int foffset; // location?

bool treeDebug = true;

void debugPrintf(const char *input)
{
	if(treeDebug) printf("%s\n", input);
}

bool insertCheck(TreeNode *syntree, SymbolTable *symtab)
{
	if(!symtab->insert(syntree->attr.name, syntree)) 
	{
		return false;
	}
	return true;
}

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
    debugPrintf("starting tree traversal");
    if(syntree != nullptr)
    {
        if(syntree->nodekind == NodeKind::DeclK)
        {
            treeTraverseDecl(syntree, symtab);
        }
        else if(syntree->nodekind == NodeKind::ExpK)
        {
            treeTraverseExp(syntree, symtab);
        }
        else if(syntree->nodekind == NodeKind::StmtK)
        {
            treeTraverseStmt(syntree, symtab);
        }
        if(syntree->sibling != nullptr)
            treeTraverse(syntree->sibling, symtab);
    }
}

void treeTraverseDecl(TreeNode *syntree, SymbolTable *symtab)
{
    debugPrintf("tree traversal decl");
    TreeNode *c0, *c1, *temp;
    c0 = syntree->child[0];
    c1 = syntree->child[1];

    switch(syntree->kind.decl)
    {
        case FuncK:
            debugPrintf("case funck");
            foffset = -2;
            insertCheck(syntree, symtab); // should return a bool we need to check?
            symtab->enter(syntree->attr.name);

            treeTraverse(c0, symtab);

            syntree->varKind = Global;
            syntree->size = foffset;  // why does this change work???

            treeTraverse(c1, symtab);

            symtab->leave();
            break;
        case VarK:
            debugPrintf("VarK");
            if(c0 != NULL)
            {
                debugPrintf("has child");
                syntree->varKind = Local;
                syntree->isAssigned = true;
                treeTraverse(c0, symtab);
            }
            // no break on purpose
        case ParamK:
            debugPrintf("ParamK");
            if(insertCheck(syntree, symtab) )
            {
                if(symtab->depth() == 1)
                {
                    syntree->varKind = Global;
                    syntree->offset = goffset;
                    goffset -= syntree->size;
                }
                else if(syntree->isStatic)
                {
                    ///// REMEMBER TO FINISH THIS
                }
                else
                {
                    syntree->varKind = Local;
                    syntree->offset = foffset; // change here works???
                    foffset -= syntree->size;
                }
            }
            
            if(syntree->kind.decl == ParamK)
            {
                debugPrintf("param kind again");
                syntree->varKind = Parameter;
            }
            else if(syntree->isArray)
            {
                debugPrintf("array");
                syntree->offset--;
            }
            
            break;
        default:
            debugPrintf("Unknown kind.decl");
    }
}

void treeTraverseExp(TreeNode *syntree, SymbolTable *symtab)
{
    debugPrintf("tree traversal exp");
    TreeNode *c0, *c1, *temp;
	c0 = syntree->child[0];
	c1 = syntree->child[1];
	
	switch(syntree->kind.exp)
	{
		case OpK:
			debugPrintf("OpK");
			// no break on purpose because
			// opk and assignk are similar
		case AssignK:
			debugPrintf("AssignK");
			treeTraverse(c0, symtab);
			treeTraverse(c1, symtab);

            if (syntree->attr.op == int('+') || syntree->attr.op == int('['))
            {
				syntree->type = c0->type;
			}
			else if(syntree->attr.op == AND || syntree->attr.op == OR || 
                    syntree->attr.op == GEQ || 
                    syntree->attr.op == LEQ || 
                    syntree->attr.op == int('<') || 
                    syntree->attr.op == int('>') || 
                    syntree->attr.op == int('=') || 
                    syntree->attr.op == EQ ||
                    syntree->attr.op == NEQ || 
                    syntree->attr.op == NOT)
			{
				syntree->type = ExpType::Boolean;
			}
			else
			{
				syntree->type = ExpType::Integer;
			}
			break;
		case CallK:
			debugPrintf("CallK");
			if(temp = (TreeNode *)(symtab->lookup(syntree->attr.name)))
			{
				temp->isUsed = true;
				syntree->type = temp->type;
				syntree->size = temp->size;
			}
			else
			{
				// THIS LOOKS LIKE AN ERROR CONDITION
			}
			break;
		case ConstantK:
			debugPrintf("ConstantK");
			syntree->isConst = true; // is it isConst???
			break;
		case IdK:
			debugPrintf("IdK");
			if(temp = (TreeNode*)(symtab->lookup(syntree->attr.name)))
			{
				temp->isUsed = true;
				syntree->type = temp->type;
				syntree->isStatic = temp->isStatic;
				syntree->isArray = temp->isArray;
				syntree->size = temp->size;
				syntree->varKind = temp->varKind;
				syntree->offset = temp->offset;
			}
			else
			{
				// PROBABLY AN ERROR
			}
			break;
		default:
			// put something here
            debugPrintf("unknown exp kind");
        }
}

void treeTraverseStmt(TreeNode *syntree, SymbolTable *symtab)
{
    debugPrintf("tree traversal stmt");

    int tempOffset;

    TreeNode *c0, *c1, *c2, *temp;
	c0 = syntree->child[0];
	c1 = syntree->child[1];
    c2 = syntree->child[2];

    switch(syntree->kind.stmt)
	{
		case CompoundK:
            // foffset = -2;
            debugPrintf("CompoundK");

            symtab->enter((char *)"compoundStmt"); // enter new scope for compound statement

            treeTraverse(c0, symtab);
            // what other stuff goes here?
            syntree->size = foffset;
			treeTraverse(c1, symtab);
            // what stuff goes here?

            symtab->leave(); // leave scope
            break;
        case ReturnK:
			debugPrintf("ReturnK");

            treeTraverse(c0, symtab);
            break;
        case IfK:
			debugPrintf("IfK");
            // foffset = -1;
            
            treeTraverse(c0, symtab);
            syntree->size = foffset;
            treeTraverse(c1, symtab);
            treeTraverse(c2, symtab);
            break;
        case WhileK:
			debugPrintf("WhileK");
			break;
		case ForK:
			debugPrintf("ForK");
            // syntree->size = foffset-1;
            symtab->enter((char *)"forStmt");

            // remember current offset
            tempOffset = foffset;

            treeTraverse(c0, symtab);
            foffset -= 2;
            syntree->size = foffset;
            treeTraverse(c1, symtab);
            treeTraverse(c2, symtab);
            foffset = tempOffset;

            symtab->leave();
            break;
        case BreakK:
			debugPrintf("BreakK");
            break;
        case RangeK:
			debugPrintf("RangeK");
            // syntree->size = foffset-1;
            treeTraverse(c0, symtab);
            treeTraverse(c1, symtab);
            treeTraverse(c2, symtab);
            break;
        default:
			// put something here
            debugPrintf("unknown stmt kind");
    }
}
