#include<string.h>
void CreateSymbolTable(struct SymbolTable *_tablehead,struct tnode* stmts);

const int intnode = 0;
const int idnode = 1;
const int opnode = 2;
const int assgnode = 3;
const int writenode = 4;
const int readnode = 5;
const int connectnode = 6;
const int boolnode = 7;
const int ifnode = 8;
const int ifelsenode = 9;
const int funccallnode = 10;
const int returnnode = 11;


struct tnode* create_Number_Node(int n) {
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = n;
	temp->op = '\0';
	temp->type = intnode;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

struct tnode* create_ID_Node(char* c) {
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = '\0';
	temp->type = idnode;
	temp->varname = strdup(c);
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

struct tnode* create_OP_Node(struct tnode* left,struct tnode* right,char op) {
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = op;
	temp->type = opnode;
	temp->left = left;
	temp->right = right;
	return temp;
}

struct tnode* create_Assgn_Node(struct tnode* left,struct tnode* right) {
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = '\0';
	temp->type = assgnode;
	temp->left = left;
	temp->right = right;
	return temp;
}

struct tnode* create_Read_Node(struct tnode* _node) {
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = '\0';
	temp->type = readnode;
	temp->left = _node;
	temp->right = NULL;
	return temp;
}

struct tnode* create_Write_Node(struct tnode* _node) {
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = '\0';
	temp->type = writenode;
	temp->left = _node;
	temp->right = NULL;
	return temp;
}

struct tnode* Connect_Node(struct tnode* left,struct tnode* right) {
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = '\0';
	temp->type = connectnode;
	temp->left = left;
	temp->right = right;
	return temp;
}

struct tnode* create_Bool_Node(struct tnode* left,struct tnode* right,char comp[2]) {
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = '\0';
	temp->type = boolnode;
	temp->comp[0]=comp[0];
	temp->comp[1]=comp[1];
	temp->left = left;
	temp->right = right;
	return temp;
}

struct tnode* create_If_Node(struct tnode* l_exp,struct tnode* _satements){
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = '\0';
	temp->type = ifnode;
	temp->left = l_exp;
	temp->right = _satements;
	return temp;
}

struct tnode* create_IfElse_Node(struct tnode* l_exp,struct tnode* _satements_1,struct tnode* _satements_2){
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = '\0';
	temp->type = ifelsenode;
	temp->left = l_exp;
	temp->right = Connect_Node(_satements_1,_satements_2);
	return temp;
}

struct tnode* create_Func_Call_Node(struct tnode* _exp){
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = '\0';
	temp->type = funccallnode;
	temp->left = _exp;
	temp->right = NULL;
	return temp;
}

struct tnode* create_Return_Node(struct tnode* ret){
	struct tnode* temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->val = -1;
	temp->op = '\0';
	temp->type = returnnode;
	temp->left = ret;
	temp->right = NULL;
	return temp;
}

int reg_index=-1;
int Get_register(){
	if(reg_index>19){
		printf("No more Registers\n");	
		exit(1);
	}
	reg_index++;
	return reg_index;
}
void Free_register(){
	if(reg_index<0){
		printf("Cannot free register\n");
		exit(1);
	}
	reg_index--;
}

//L0 Reserved for FUN() 
int label=1;
int Get_Label(){
	label++;
	return label-1;
}
void init() {
	fprintf(stdout, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0); 
	fprintf(stdout, "MOV SP, 4096\n");
}
void Brk() {
	fprintf(stdout, "BRKP\n");
}
void exit_safely(){
	int r0 = Get_register();
	printf("MOV R%d,\"Exit\"\n",r0);
	printf("PUSH R%d\n",r0);
	printf("PUSH R%d\n",r0);
	printf("PUSH R%d\n",r0);
	printf("PUSH R%d\n",r0);
	printf("PUSH R%d\n",r0);
	printf("CALL 0\n");
}

int GetAddressRegFromSymbolTable(struct SymbolTable *head,char *name){
	int idpos = 0;
	struct SymbolTable *_ptr;
	for(_ptr = head;_ptr!=NULL;_ptr=_ptr->next){
		if(strcmp(_ptr->name,name)==0){
			idpos =  _ptr->binding;
		}
	}
	_ptr=head;

	int r0 = Get_register();
	printf("MOV R%d,BP\n",r0);
	if(idpos<0){
		int sub_idpos = -1*idpos;
		printf("SUB R%d,%d\n",r0,sub_idpos);
	}
	else{
		printf("ADD R%d,%d\n",r0,idpos);
	}
	return r0;
}

int code_Gen(struct tnode* _node,struct SymbolTable *head){
	if(_node==NULL){
		return -1;
	}
	else if(_node->type==intnode){
		int r0 = Get_register();
		printf("MOV R%d,%d\n",r0,_node->val);
		return r0;
	}
	else if(_node->type==idnode){
		int r0 = GetAddressRegFromSymbolTable(head,_node->varname);
		printf("MOV R%d,[R%d]\n",r0,r0);
		return r0;
	}
	else if(_node->type == opnode){
		int r0 = code_Gen(_node->left,head);
		int r1 = code_Gen(_node->right,head);
		switch(_node->op){
			case '+' : printf("ADD R%d,R%d\n",r0,r1);break;
			case '-' : printf("SUB R%d,R%d\n",r0,r1);break;
			case '*' : printf("MUL R%d,R%d\n",r0,r1);break;
		}
		Free_register(r1);
		return r0;
	}
	else if(_node->type == assgnode){
		int r0 = GetAddressRegFromSymbolTable(head,_node->left->varname);
		int r1 = code_Gen(_node->right,head);
		printf("MOV [R%d],R%d\n",r0,r1);
		Free_register();
		return r0;
	}
	else if(_node->type == writenode){
		int r0 = Get_register();
		int r1 = code_Gen(_node->left,head);
		printf("MOV R%d,\"Write\"\n",r0);
		printf("PUSH R%d\n",r0);//Function code
		printf("MOV R%d,-2\n",r0);
		printf("PUSH R%d\n",r0);//Arg 1
		printf("PUSH R%d\n",r1);//Arg 2
		printf("PUSH R%d\n",r0);//Arg 3 dummy
		printf("PUSH R%d\n",r0);//Ret
		printf("CALL 0\n");
		printf("POP R%d\n",r0);
		printf("POP R%d\n",r0);
		printf("POP R%d\n",r0);
		printf("POP R%d\n",r0);
		printf("POP R%d\n",r0);
		Free_register();
		Free_register();
		return -1;
	}
	else if(_node->type == readnode){
		int r0 = Get_register();
		int r1 = GetAddressRegFromSymbolTable(head,_node->left->varname);
		//printf("%d %d\n",r0,r1);
		printf("MOV R%d,\"Read\"\n",r0);
		printf("PUSH R%d\n",r0);//Function code
		printf("MOV R%d,-1\n",r0);
		printf("PUSH R%d\n",r0);//Arg 1
		printf("MOV R%d,R%d\n",r0,r1);
		printf("PUSH R%d\n",r0);//Arg 2
		printf("PUSH R%d\n",r0);//dummy Arg 3
		printf("PUSH R%d\n",r0);//Ret
		printf("CALL 0\n");
		printf("POP R%d\n",r0);
		printf("POP R%d\n",r0);
		printf("POP R%d\n",r0);
		printf("POP R%d\n",r0);
		printf("POP R%d\n",r0);
		Free_register();
		return -1;
	}
	else if(_node->type == connectnode){
		int r0 = code_Gen(_node->left,head);
		int r1 = code_Gen(_node->right,head);
		return -1;
	}
	else if(_node->type == boolnode){
		int r0 = code_Gen(_node->left,head);
		int r1 = code_Gen(_node->right,head);
		if(_node->comp[0]=='g' && _node->comp[1]=='t'){
			printf("GT R%d,R%d\n",r0,r1);
		}
		else if(_node->comp[0]=='l' && _node->comp[1]=='t'){
			printf("LT R%d,R%d\n",r0,r1);
		}
		else if(_node->comp[0]=='g' && _node->comp[1]=='e'){
			printf("GE R%d,R%d\n",r0,r1);
		}
		else if(_node->comp[0]=='l' && _node->comp[1]=='e'){
			printf("LE R%d,R%d\n",r0,r1);
		}
		else if(_node->comp[0]=='e' && _node->comp[1]=='q'){
			printf("EQ R%d,R%d\n",r0,r1);
		}
		else if(_node->comp[0]=='n' && _node->comp[1]=='e'){
			printf("NE R%d,R%d\n",r0,r1);
		}
		Free_register();
		return r0;
	}
	else if(_node->type == ifnode){
		int r0 = code_Gen(_node->left,head);
		int label1 = Get_Label();
		int label2 = Get_Label();
		printf("JNZ R%d,L%d\n",r0,label1);
		printf("JMP L%d\n",label2);
		printf("L%d:\n",label1);
		int _t = code_Gen(_node->right,head);
		printf("L%d:\n",label2);
		return-1;
	}
	else if(_node->type == ifelsenode){
		int r0 = code_Gen(_node->left,head);
		int label1 = Get_Label();
		int label2 = Get_Label();
		printf("JNZ R%d,L%d\n",r0,label1);
		int _t = code_Gen(_node->right->right,head);
		printf("JMP L%d\n",label2);
		printf("L%d:\n",label1);
		_t = code_Gen(_node->right->left,head);
		printf("L%d:\n",label2);
		return-1;
	}
	else if(_node->type==funccallnode){
		for(int i=0;i<=reg_index;i++)
			printf("PUSH R%d\n",i);
		int temp=reg_index;
		reg_index=-1;
		int r0 = code_Gen(_node->left,head);
		printf("PUSH R%d\n",r0);
		Free_register();
		printf("PUSH R0\n");
		printf("CALL L0\n");
		printf("POP R%d\n",temp+1);
		printf("POP R0\n");
		for(int i=temp;i>-1;i--)
			printf("POP R%d\n",i);
		reg_index=temp;
		r0 = Get_register();
		printf("MOV R%d,R%d\n",r0,temp+1);
		return r0;
	}
	else if(_node->type==returnnode){
		int r0=Get_register();
		int r1 = code_Gen(_node->left,head);
		printf("MOV R%d,BP\n",r0);
		printf("SUB R%d,2\n",r0);
		printf("MOV [R%d],R%d\n",r0,r1);
		SymbolTable *thead;
		SymbolTable *pre=NULL;
		for(thead = head->next;thead!=NULL;thead=thead->next){
			printf("POP R%d\n",r1);
			free(pre);
			pre=thead;
		}
		printf("POP BP\n");
		printf("RET\n");
		Free_register();
		return r0;
	}
	printf("Nothing Satisfied\n");
	printf("bla %d\n",_node->type);
	return -1;
}
struct tnode* InitProgram(struct tnode* stmts){
	init();
	int r0,r1;
	//read(argc);
	r0 = Get_register();
	Brk();
	printf("MOV R%d,\"Read\"\n",r0);
	printf("PUSH R%d\n",r0);//Function code
	printf("MOV R%d,-1\n",r0);
	printf("PUSH R%d\n",r0);//Arg 1
	printf("MOV R%d,4096\n",r0);
	printf("PUSH R%d\n",r0);//Arg 2
	printf("PUSH R%d\n",r0);//dummy Arg 3
	printf("PUSH R%d\n",r0);//Ret
	printf("CALL 0\n");
	Brk();
	printf("POP R%d\n",r0);
	printf("POP R%d\n",r0);
	printf("POP R%d\n",r0);
	printf("POP R%d\n",r0);
	printf("POP R%d\n",r0);
	Free_register();

	r0 = Get_register();
	printf("MOV R%d,[4096]\n",r0); 	//getting argc
	printf("PUSH R%d\n",r0);		//pushing argc
	printf("PUSH R%d\n",r0);		//pushing space for return val
	printf("CALL L0\n");



	// 2 pops , ret val -> argc
	r1 = Get_register();

	printf("MOV R%d,4096\n",r0);
	printf("POP R%d\n",r1);
	printf("MOV [R%d],R%d\n",r0,r1);
	printf("POP R%d\n",r1);
	Free_register();
	Free_register();

	//write(argc)
	r0 = Get_register();
	r1 = Get_register();
	printf("MOV R%d,4096\n",r1);
	printf("MOV R%d,[R%d]\n",r1,r1);
	printf("MOV R%d,\"Write\"\n",r0);
	printf("PUSH R%d\n",r0);//Function code
	printf("MOV R%d,-2\n",r0);
	printf("PUSH R%d\n",r0);//Arg 1
	printf("PUSH R%d\n",r1);//Arg 2
	printf("PUSH R%d\n",r0);//Arg 3 dummy
	printf("PUSH R%d\n",r0);//Ret
	printf("CALL 0\n");
	printf("POP R%d\n",r0);
	printf("POP R%d\n",r0);
	printf("POP R%d\n",r0);
 	printf("POP R%d\n",r0);
	printf("POP R%d\n",r0);
	Free_register();
	Free_register();
	exit_safely();
	printf("L0:\n");
	//symbol_table_gen PUSH BP
	printf("PUSH BP\n");
	printf("MOV BP,SP\n");
	SymbolTable *head;
	head = malloc(sizeof(SymbolTable));
	head->next=NULL;
	head->name=strdup("argc");
	head->binding=-2;
	CreateSymbolTable(head,stmts);
	SymbolTable *_head=head;
	code_Gen(stmts,head);
}

void CreateSymbolTable(struct SymbolTable *_tablehead,struct tnode* _stmts){
	if(_stmts==NULL)
		return;
	if(_stmts->type==idnode){
		struct SymbolTable *_ptr;
		struct SymbolTable *pre=NULL;
		int count = 0;
		int flag=0;
		for(_ptr = _tablehead;_ptr!=NULL;_ptr=_ptr->next){
			if(strcmp(_ptr->name,_stmts->varname)==0){
				flag = 1;
				return;
			}
			count++;
			pre=_ptr;
		}
		if(flag==0){
			SymbolTable *temp;
			temp = malloc(sizeof(SymbolTable));
			temp->next=NULL;
			temp->name=strdup(_stmts->varname);
			temp->binding=count;
			pre->next = temp;
			printf("PUSH SP\n");
		}
		return;
	}
	CreateSymbolTable(_tablehead,_stmts->left);
	CreateSymbolTable(_tablehead,_stmts->right);
}