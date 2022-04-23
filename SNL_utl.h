#pragma once
#include <map>
#include <string>
#include <set>
#include "LNL_utl.h"
const int max_child = 3; //�ֽ��������
using namespace std;                           /*��־�ڵ�+ ����ڵ�*/
typedef enum { ProK, PheadK, DecK, TypeK, VarK, ProcDecK, StmLK, StmtK, ExpK }NodeKind;
extern map<NodeKind, string> nodekind_map;

typedef enum { ArrayK, CharK, IntegerK, RecordK, IdK }  DecKind;
extern map<DecKind, string> deckind_map;

typedef enum { IfK, WhileK, AssignK, ReadK, WriteK, CallK, ReturnK } StmtKind;
extern map<StmtKind, string> stmtkind_map;

typedef enum { OpK, ConstK, VariK } ExpKind;
extern map<ExpKind, string> expkind_map;

typedef enum { IdV, ArrayMembV, FieldMembV } VarKind;
extern map<VarKind, string> varkind_map;

typedef enum { Void, Integer, Boolean } ExpType;
extern map<ExpType, string> exptype_map;

typedef enum { valparamType, varparamType } ParamType;//valֻ��
extern map<ParamType, string> paramtype_map;


map<NodeKind, string> nodekind_map = {
{ProK,"ProK"},
{PheadK,"PheadK"},
{DecK,"DecK"},
{TypeK,"TypeK"},
{VarK,"VarK"},
{ProcDecK,"ProcDecK"},
{StmLK,"StmLK"},
{StmtK,"StmtK"},
{ExpK,"ExpK"},
};
map<DecKind, string> deckind_map = {
{ArrayK,"ArrayK"},
{CharK,"CharK"},
{IntegerK,"IntegerK"},
{RecordK,"RecordK"},
{IdK,"IdK"},
};
map<StmtKind, string> stmtkind_map = {
{IfK,"IfK"},
{WhileK,"WhileK"},
{AssignK,"AssignK"},
{ReadK,"ReadK"},
{WriteK,"WriteK"},
{CallK,"CallK"},
{ReturnK,"ReturnK"},
};
map<ExpKind, string> expkind_map = {
{OpK,"OpK"},
{ConstK,"ConstK"},
{VariK,"VariK"},
};
map<VarKind, string> varkind_map = {
{IdV,"IdV"},
{ArrayMembV,"ArrayMembV"},
{FieldMembV,"FieldMembV"},
};
map<ExpType, string> exptype_map = {
{Void,"Void"},
{Integer,"Integer"},
{Boolean,"Boolean"},
};
map<ParamType, string> paramtype_map = {
{valparamType,"valparamType"},
{varparamType,"varparamType"},
};

//�ռ���
set<LexType> TTSet = {
	ENDFILE, ERROR,
	PROGRAM, PROCEDURE, TYPE, VAR, IF,
	THEN, ELSE, FI, WHILE, DO,
	ENDWH, BEGIN, END, READ, WRITE,
	ARRAY, OF, RECORD, RETURN, INTEGER, CHAR,
	INTEGER_T, CHAR_T,
	ID, INTC, CHARC, INTC_VAL, CHARC_VAL,
	ASSIGN, EQ, LT, PLUS, MINUS,
	TIMES, DIVIDE, LPAREN, RPAREN, DOT,
	COLON, SEMI, COMMA, LMIDPAREN, RMIDPAREN,
	UNDERRANGE,
};
//���ռ���
set<LexType> NTSet = {
	//feizhongjiefu
	Program,	      ProgramHead,	    ProgramName,	DeclarePart,
	TypeDec,        TypeDeclaration,	TypeDecList,	TypeDecMore,
	TypeId,	      TypeName,			BaseType,	    StructureType,
	ArrayType,      Low,	            Top,            RecType,
	FieldDecList,   FieldDecMore,	    IdList,	        IdMore,
	VarDec,	      VarDeclaration,	VarDecList,		VarDecMore,
	VarIdList,	  VarIdMore,		ProcDec,		ProcDeclaration,
	ProcDecMore,    ProcName,		    ParamList,		ParamDecList,
	ParamMore,      Param,		    FormList,		FidMore,
	ProcDecPart,    ProcBody,	    	ProgramBody,	StmList,
	StmMore,        Stm,				AssCall,		AssignmentRest,
	ConditionalStm, StmL,			    LoopStm,		InputStm,
	InVar,          OutputStm,		ReturnStm,		CallStmRest,
	ActParamList,   ActParamMore,		RelExp,			OtherRelE,
	Exp,			  OtherTerm,		Term,           OtherFactor,
	Factor,         Variable,			VariMore,		FieldVar,
	FieldVarMore,   CmpOp,			AddOp,          MultOp,
};
struct TreeNode
{
	TreeNode* child[max_child];//���ӣ�proc��
	TreeNode* sibling;//�ֵ�
	int lineno;
	NodeKind nodekind;
	union
	{
		DecKind  dec; //����
		StmtKind stmt;//���
		ExpKind  exp;//���ʽ
	}kind; //ע���Сд
	int idnum; //һ���ڵ��б�ʶ��������
	vector<string> name; //��ʶ������
	struct symbtable* table[10]; //���﷨�����й�
	string type_name;  //Deck && Ϊ Idk
	struct
	{
		struct
		{
			int low;
			int up;
			DecKind childtype;
		}ArrayAttr;
		struct
		{
			ParamType paramt;
		}ProcAttr;
		struct
		{
			LexType op;
			int val;
			VarKind  varkind;
			ExpType type;
		}ExpAttr;
	}attr;
};
int lineno = 0;
TreeNode* create_node(NodeKind kind)
{
	TreeNode* t = new TreeNode;
	for (int i = 0; i < max_child; i++)
		t->child[i] = nullptr;
	t->sibling = nullptr;
	t->nodekind = kind; 
	t->idnum = 0;
	t->lineno = lineno;
	return t;
}
TreeNode* create_StmtK_node(StmtKind kind)
{
	TreeNode* t = new TreeNode;
	for (int i = 0; i < max_child; i++)
		t->child[i] = nullptr;
	t->sibling = nullptr;
	t->idnum = 0;
	t->nodekind = StmtK;
	t->kind.stmt = kind;
	t->lineno = lineno;
	return t;
}
TreeNode* create_ExpKop_node(LexType op)
{
	TreeNode* t = new TreeNode;
	for (int i = 0; i < max_child; i++)
		t->child[i] = nullptr;
	t->sibling = nullptr;
	t->idnum = 0;
	t->nodekind = ExpK;
	t->kind.exp = OpK;
	t->attr.ExpAttr.op = op;
	t->lineno = lineno;
	return t;
}
void big_block()
{
	for (int i = 0; i < 4; i++)cout << " ";
}
void small_block(int len = 3)
{
	for (int i = 0; i < len; i++)cout << " ";
}
void show_SNLtree(TreeNode* root, int block, bool issibing)
{
	if (!root) return;
	if (1)
	{
		for (int i = 0; i < block; i++)
			big_block();
		cout << nodekind_map[root->nodekind]; 
		if (root->kind.exp == ExpKind::ConstK && root->kind.exp != DecKind::CharK)  //������Ϊ����΢����
			small_block(1);
		else small_block();
		if (root->nodekind == DecK || root->nodekind == PheadK || root->nodekind == ProcDecK)
		{
			if (root->nodekind == DecK)
			{
				cout << deckind_map[root->kind.dec]; small_block();
			}
			for (int i = 0; i < root->idnum; i++)
				cout << root->name[i] << " ";
			if (root->kind.dec == DecKind::ArrayK)
			{
				cout << "of" << " ";
				cout << deckind_map[root->attr.ArrayAttr.childtype] << " ";
				cout << "low:" << root->attr.ArrayAttr.low << " ";
				cout << "up:" << root->attr.ArrayAttr.up << " ";
			}
		}
		if (root->nodekind == StmtK)
		{
			cout << stmtkind_map[root->kind.stmt]; small_block();
			if (root->kind.stmt == StmtKind::ReadK)
				cout << root->name[0];
			small_block();
		}
		if (root->nodekind == ExpK)
		{
			if (root->kind.exp == VariK)
			{
				cout << root->name[0];
				small_block();
				cout << varkind_map[root->attr.ExpAttr.varkind];
			}
			else if (root->kind.exp == ConstK)
			{
				cout << expkind_map[root->kind.exp];
				small_block();
				cout << root->attr.ExpAttr.val;
			}
			else if (root->kind.exp == OpK)
			{
				cout << expkind_map[root->kind.exp];
				small_block();
				cout << lexName[root->attr.ExpAttr.op];
			}
				
		}
		cout << "::" << root->lineno << " ";
		cout  <<endl;
	}
	for (int i = 0; i < max_child; i++)
	{
		show_SNLtree(root->child[i], block + 1, false);
	}
	show_SNLtree(root->sibling,block,true);
}
class SNL
{
public:
	TreeNode* ggroot;
	stack<LexType> symbol_stack;
	stack<TreeNode**>snltree_stack;  // ����
	stack<TreeNode*>op_stack;
	stack<TreeNode*>opnum_stack;
	map<pair<LexType, LexType>, int>symbol_table;
	vector<Token> tokens;
	int pos = 0;
	bool snlcheck = true;

	TreeNode* create_tree();
	void create_symbol_table();
	void predict(int num);
	int priosity(LexType op);
	







	//���²���ʽ����//
	void process1();
	void process2();
	void process3();
	void process4();
	void process5();
	void process6();
	void process7();
	void process8();
	void process9();
	void process10();
	void process11();
	void process12();
	void process13();
	void process14();
	void process15();
	void process16();
	void process17();
	void process18();
	void process19();
	void process20();
	void process21();
	void process22();
	void process23();
	void process24();
	void process25();
	void process26();
	void process27();
	void process28();
	void process29();
	void process30();
	void process31();
	void process32();
	void process33();
	void process34();
	void process35();
	void process36();
	void process37();
	void process38();
	void process39();
	void process40();
	void process41();
	void process42();
	void process43();
	void process44();
	void process45();
	void process46();
	void process47();
	void process48();
	void process49();
	void process50();
	void process51();
	void process52();
	void process53();
	void process54();
	void process55();
	void process56();
	void process57();
	void process58();
	void process59();
	void process60();
	void process61();
	void process62();
	void process63();
	void process64();
	void process65();
	void process66();
	void process67();
	void process68();
	void process69();
	void process70();
	void process71();
	void process72();
	void process73();
	void process74();
	void process75();
	void process76();
	void process77();
	void process78();
	void process79();
	void process80();
	void process81();
	void process82();
	void process83();
	void process84();
	void process85();
	void process86();
	void process87();
	void process88();
	void process89();
	void process90();
	void process91();
	void process92();
	void process93();
	void process94();
	void process95();
	void process96();
	void process97();
	void process98();
	void process99();
	void process100();
	void process101();
	void process102();
	void process103();
	void process104();
	//����Ϊ����ʽ����

	//������
	void error_SNL1();
};
SNL snl;



/*
�﷨����һ���Ĺ淶
���������з������� ��void���ֵ�
�������һ��������" ; "����ʵ���
�ڴʷ������ԸĶ�ʹ֮��ʶ�����е�dot!!!!
*/