typedef struct tnode {
	int val;
	char op;
	int type;
	char *varname;
	char comp[2];
	struct tnode *left, *right;
}tnode;

typedef struct SymbolTable{
	char *name;
	int binding;
	struct SymbolTable *next;
}SymbolTable;

struct tnode* create_Number_Node(int n);
struct tnode* create_ID_Node(char* c);
struct tnode* create_OP_Node(struct tnode* left, struct tnode* right,char op);
struct tnode* create_Assgn_Node(struct tnode* left, struct tnode* right);
struct tnode* create_Write_Node(struct tnode* _node);
struct tnode* create_Read_Node(struct tnode* _node);
struct tnode* Connect_Node(struct tnode* left, struct tnode* right);
struct tnode* create_Bool_Node(struct tnode* left, struct tnode* right,char* comp);
struct tnode* create_If_Node(struct tnode* l_exp,struct tnode* _satements);
struct tnode* create_IfElse_Node(struct tnode* l_exp,struct tnode* _satements_1,struct tnode* _satements_2);
struct tnode* create_Func_Call_Node(struct tnode* _exp);
struct tnode* create_Func_Def_Node(struct tnode* stmts);
struct tnode* InitProgram(struct tnode* stmts);
struct tnode* create_Return_Node(struct tnode* ret);	
int getReg();
void freeReg();

int codeGen(struct tnode* t); //returns the register number with the result

void Brk();
void init();
void exit_safely();
