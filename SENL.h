#pragma once
#include "SENL_utl.h"
#include "SNL_ll1.h"
#include <iostream>
const int max_len = 100;
const int init_off = 7;
void SENL_error(int lineno, int id, string name = "",int colom = 0);
class SENL
{
public :
	symbtable* SymbTable;
	int sym_level = -1;
	int OFF = 0;
	symbtable* Scope[max_len];  // Scope[i] point to i_th symbtable;局部化符号表头指针
	typeIR* intPtr;
	typeIR* charPtr;
	typeIR* boolPtr;

	void CreateTable();
	void DestroyTable();
	bool Enter(string id, AttributeIR* AttribP, symbtable** Entry);  //写入新的标识符信息
	bool FindEntry(string id, int flag, symbtable** Entry);			//符号表中查找标识符
	bool SearchoneTable(string id, int currentLevel, symbtable** Entry);//上面的工具
	bool FindField(string name, fieldChain* head, fieldChain** Entry); //在域表中查找域名
	

	void Analyze(TreeNode* root);
	void initialize();
	typeIR* TypeProcess(TreeNode* t, DecKind deckind);
	typeIR* nameType(TreeNode* t);
	typeIR* arrayType(TreeNode* t);
	typeIR* recordType(TreeNode* t);
	
	void TypeDecPart(TreeNode* t);
	void VarDecPart(TreeNode* t);
	void ProcDecPart(TreeNode* t);
	symbtable* HeadProcess(TreeNode* t);
	ParamTable* ParaDecList(TreeNode* t);
	void Body(TreeNode* t);
	void statement(TreeNode* t);

	typeIR* Expr(TreeNode* t, AccessKind* Ekind);
	typeIR* arrayVar(TreeNode* t);
	typeIR* recordVar(TreeNode* t);


	void assignstatement(TreeNode* t);
	void callstatement(TreeNode* t);
	void ifstatement(TreeNode* t);
	void whilestatement(TreeNode* t);
	void readstatement(TreeNode* t);
	void writestatement(TreeNode* t);
	void returnstatement(TreeNode* t);

};
void SENL::CreateTable()
{
	sym_level++;
	symbtable* syt = new symbtable;
	OFF = init_off;
	syt->idname = "";
	syt->next = nullptr;
	Scope[sym_level] = syt;//只是新建，还没有具体指向
}
void SENL::DestroyTable()
{
	sym_level--;
}
bool SENL::Enter(string id, AttributeIR* AttribP, symbtable** Entry)
{
	bool present = FindEntry(id, 1, Entry);
	
	if (present)
	{
		Entry = nullptr;
		return true;
	}
	else
	{
		symbtable* syt = new symbtable;
		syt->next = nullptr;
		syt->idname = id;
		syt->attrIR = *AttribP;
		symbtable* p = Scope[sym_level];
		if (p->idname == "")
		{
			Scope[sym_level] = syt;
			*Entry = Scope[sym_level];
			return false;
		}
		while (p->next)
		{
			p = p->next;
		}//链入尾部
		p->next = syt;*Entry = (p->next);
		return false;
	}
}
bool SENL::FindEntry(string id, int flag, symbtable** Entry)
{
	int temp_level = sym_level;
	bool present = SearchoneTable(id, temp_level, Entry); 
	if (flag < 0)// 不知道为啥要向后查找，感觉很奇怪
	{
		temp_level--;
		while (temp_level >= 0 && !present)
		{
			present = SearchoneTable(id, temp_level, Entry);
			temp_level--;
		}
	}
	return present;
}
bool SENL::SearchoneTable(string id, int currentLevel, symbtable** Entry)
{
	symbtable* syt = Scope[currentLevel];
	while (syt)
	{
		if (syt->idname == id)
		{
			*Entry = syt;
			return true;
		}
		syt = syt->next;
	}
	*Entry = nullptr;
	return false;
}
bool SENL::FindField(string name, fieldChain* head, fieldChain** Entry)
{
	fieldChain* p = head;
	while (p)
	{
		if (p->idname == name)
		{
			*Entry = p;
			return true;
		}
		p = p->next;
	}
	return false;
}

void SENL::Analyze(TreeNode* root)
{
	CreateTable();
	initialize();
	TreeNode* t = root->child[1]; //处理声明部分
	while (t)
	{
		switch (t->nodekind)
		{
		case TypeK: TypeDecPart(t->child[0]); break;
		case VarK:VarDecPart(t->child[0]); break;
		case ProcDecK: ProcDecPart(t); break;
		default: cout << "error150\n"; return;
		}
		t = t->sibling;
		
	}
	TreeNode* p = root->child[2]; //处理主程序体部分
	if (p->nodekind == NodeKind::StmLK) Body(p);
	else cout << "error\n";

	DestroyTable();
	return;
}
void SENL::initialize()
{
	intPtr = newTy(intTy);
	charPtr = newTy(charTy);
	boolPtr = newTy(boolTy);
}
typeIR* SENL::TypeProcess(TreeNode* t, DecKind deckind)
{
	switch (deckind)
	{
	case DecKind::IdK :return nameType(t); break;
	case DecKind::ArrayK:return arrayType(t); break;
	case DecKind::RecordK:return recordType(t); break;
	case DecKind::IntegerK:return intPtr; break;
	case DecKind::CharK:return charPtr; break;
	default:return nullptr;
	}
}
typeIR* SENL::nameType(TreeNode* t)  // typedef inta int; typedef c inta;  nametype 指的是后一种情况
{
	symbtable* entry = nullptr;
	bool present = FindEntry(t->name[0], -1, &entry);
	if (present)
	{
		if (entry->attrIR.kind == typeKind)
		{
			return entry->attrIR.idtype;
		}
		else
		{
			cout << t->lineno << " : " << t->name[0] << " 非类型标识符错误" << endl;
			SENL_error(t->lineno, 3, t->name[0]);  //????还需考虑细分问题
		}
	}
	else
	{
		cout << t->lineno << " : " << t->name[0] << " 无声明错误" << endl;
		SENL_error(t->lineno, 2, t->name[0]);
	}
	return nullptr;
}
typeIR* SENL::arrayType(TreeNode* t)
{
	typeIR* ty = newTy(arrayTy);
	if (t->attr.ArrayAttr.low > t->attr.ArrayAttr.up)
	{
		//cout << t->lineno << " : " << t->name[0] << " 下标越界错误" << endl;
		SENL_error(t->lineno, 4, t->name[0]);
	}
	//else
	{
		ty->More.ArrayAttr.indexTy = TypeProcess(t, DecKind::IntegerK); //下标类型
		ty->More.ArrayAttr.elemTy = TypeProcess(t, t->attr.ArrayAttr.childtype);
		if(ty->More.ArrayAttr.elemTy)
		ty->size = (t->attr.ArrayAttr.up - t->attr.ArrayAttr.low + 1) * ty->More.ArrayAttr.elemTy->size;
	}
	return ty;
}
typeIR* SENL::recordType(TreeNode* t)
{
	typeIR* Ptr = newTy(recordTy);
	fieldChain* fc = new fieldChain;
	Ptr->More.body = fc;
	fieldChain* tmp;
	tmp = fc;
	t = t->child[0];
	int sum = 0;
	while (t)
	{
		for (int i = 0; i < t->idnum; i++)
		{
			typeIR* p = TypeProcess(t, t->kind.dec);
			fieldChain* f = new fieldChain;
			f->unitType = p;
			f->offset = sum;
			f->idname = t->name[i];
			f->next = nullptr;
			sum += f->unitType->size;
			tmp->next = f;
			tmp = f;
		}
		t = t->sibling;
	}
	// 我这种写法中间应该是多了个无用的节点。   //全部写完一定要debug这里.???????????????????????????????????????????????
	Ptr->More.body = Ptr->More.body->next;//跳过这个无用节点
	Ptr->size = sum;
	return Ptr;
}
void SENL::TypeDecPart(TreeNode * t)
{
	bool present = false;
	typeIR* Tptr = new typeIR;
	AttributeIR* Aptr = new AttributeIR;
	Aptr->kind = typeKind;
	symbtable* entry = nullptr;
	while (t)
	{
		present = Enter(t->name[0], Aptr, &entry);
		if (present)
		{
			//cout << t->lineno << " : " << t->name[0] << " 重复定义" << endl;
			SENL_error(t->lineno, 1, t->name[0]);
			entry = NULL;
		}
		else
		{
			entry->attrIR.idtype = TypeProcess(t, t->kind.dec);
		}
		t = t->sibling;
		
	}
}
void SENL::VarDecPart(TreeNode* t)  //我觉得这里所有的判空意义不大，（肯定是有助于提高鲁棒性，但是前面做的没问题的话，应该时触发不了的）
{
	bool present = false;
	int sum = 0;
	symbtable* entry = nullptr;
	AttributeIR* Aptr = new AttributeIR;
	while (t)
	{
		for (int i = 0; i < t->idnum; i++)
		{
			Aptr->kind = IdKind::varKind;
			Aptr->More.VarAttr.level = sym_level + 1;
			Aptr->idtype = TypeProcess(t, t->kind.dec);
			if (t->attr.ProcAttr.paramt == ParamType::varparamType)
			{
				Aptr->More.VarAttr.access = indir;
				Aptr->More.VarAttr.off = OFF;
				OFF++;
			}
			else
			{
				Aptr->More.VarAttr.access = dir;
				Aptr->More.VarAttr.off = OFF;
				if (Aptr->idtype) 
				{
					OFF += Aptr->idtype->size;
				}
			}
			if (Aptr->idtype)
			{
				present = Enter(t->name[i], Aptr, &entry);
				if (present)
				{
					//cout << t->lineno << " : " << t->name[0] << " 重复定义" << endl;
					SENL_error(t->lineno, 1, t->name[0]);
					entry = nullptr;
				}
				else
				{
					t->table[i] = entry;  // 符号表地址回填
				}
			}
		}
		t = t->sibling;
	}
	// 老哥这里最后的操作让我些许不接？
}
void SENL::ProcDecPart(TreeNode* t)
{
	
	symbtable* Entry = HeadProcess(t);//函数形参
	TreeNode* t2 = t->child[1];
	while (t2)					      //函数声明
	{
		switch (t2->nodekind)
		{
		case TypeK: TypeDecPart(t2->child[0]); break;
		case VarK:VarDecPart(t2->child[0]); break;
		case ProcDecK: ProcDecPart(t2); break;
		default: cout << "error325\n"; return;
		}
		t2 = t2->sibling;
	}
	Body(t->child[2]);						  //函数体
	DestroyTable();
}
symbtable* SENL::HeadProcess(TreeNode* t)
{
	symbtable* entry;
	AttributeIR* Aptr = new AttributeIR;
	Aptr->kind = IdKind::procKind;
	Aptr->More.ProcAttr.level = sym_level + 1;
	if (!t)
	{
		return nullptr;
	}
	bool present = Enter(t->name[0], Aptr, &entry);
	t->table[0] = nullptr;
	entry->attrIR.More.ProcAttr.param = ParaDecList(t);
	return entry;
	
}
ParamTable* SENL::ParaDecList(TreeNode* t)
{
	TreeNode* pt;
	ParamTable* Pptr = new ParamTable;
	ParamTable* tmp = new ParamTable;
	Pptr->next = tmp;
	if (t->child[0])
	{
		pt = t->child[0];
		CreateTable();
		VarDecPart(pt);  //形参符号表已经建好了！ 后面只需要其与参数相连即可。
		symbtable* p = Scope[sym_level];
		while (p)
		{
			ParamTable* f = new ParamTable;
			f->entry = p;
			f->next = nullptr;
			tmp->next = f;
			tmp = f;
			p = p->next;
		}
	}
	return Pptr->next->next;
}
void SENL::Body(TreeNode* t)
{
	TreeNode* p = t->child[0];
	while (p)
	{
		statement(p);
		p = p->sibling;
	}
}
void SENL::statement(TreeNode* t)
{
	switch (t->kind.stmt)
	{
	case StmtKind::ReadK:readstatement(t); break;
	case StmtKind::AssignK:assignstatement(t); break;
	case StmtKind::CallK:callstatement(t); break;
	case StmtKind::IfK:ifstatement(t); break;
	case StmtKind::ReturnK:returnstatement(t); break;
	case StmtKind::WhileK:whilestatement(t); break;
	case StmtKind::WriteK:writestatement(t); break;
	default:cout << t->lineno <<"error416\n";
	}
}
typeIR* SENL::Expr(TreeNode* t, AccessKind* Ekind)
{
	typeIR* ans = nullptr;
	symbtable* entry;
	bool present = false;
	if (t->kind.exp == ExpKind::ConstK)
	{
		if(Ekind)
			*Ekind = dir;
		ans = TypeProcess(t, DecKind::IntegerK);//默认表达式中常量只有int
	}
	else if (t->kind.exp == ExpKind::VariK)
	{
		if (!t->child[0]) //单纯的变量
		{
			bool present = FindEntry(t->name[0], -1, &entry);
			if (!present)
				SENL_error(t->lineno, 2 , t->name[0]);
			else
			{
				if (entry->attrIR.kind != IdKind::varKind)
				{
					SENL_error(t->lineno, 3, t->name[0]);///?????/
				}
				else
				{
					ans = entry->attrIR.idtype;
					if (Ekind)
					{
						if (t->attr.ProcAttr.paramt == ParamType::varparamType)
							*Ekind = indir;
						else *Ekind = dir;
					}
					
				}
			}
			
		}
		else//数组成员或者记录
		{
			if (t->attr.ExpAttr.varkind == VarKind::ArrayMembV)
				arrayVar(t);
			else recordVar(t);
			*Ekind = AccessKind::dir;
		}
	}
	else if (t->kind.exp == ExpKind::OpK)
	{
		typeIR* tIR0;
		typeIR* tIR1;
		tIR0 = Expr(t->child[0], Ekind);
		tIR1 = Expr(t->child[1], Ekind);
		if (!tIR0 || !tIR1)return nullptr;
		if (tIR0 == tIR1)
		{
			if (t->attr.ExpAttr.op == LexType::EQ || t->attr.ExpAttr.op == LexType::LT)
			{
				ans = boolPtr;
			}
			else if (t->attr.ExpAttr.op == LexType::PLUS || t->attr.ExpAttr.op == LexType::MINUS || t->attr.ExpAttr.op == LexType::DIVIDE || t->attr.ExpAttr.op == LexType::TIMES)
			{
				ans = intPtr;
			}
			if(Ekind)
				*Ekind = AccessKind::dir;
		}
		else
			SENL_error(t->lineno, 12);
		
	}
	return ans;
}
typeIR* SENL::arrayVar(TreeNode* t)
{
	symbtable* entry;
	typeIR* ans = nullptr;
	bool present = FindEntry(t->name[0], -1, &entry);
	if (!present)
	{
		SENL_error(t->lineno, 2, t->name[0]);
	}
	else if (entry->attrIR.kind != IdKind::varKind)
	{
		SENL_error(t->lineno, 3, t->name[0]); 
	}
	else if (entry->attrIR.idtype->kind != Typekind::arrayTy)
	{
		SENL_error(t->lineno, 3, t->name[0]); 
	}
	else
	{
		AccessKind* Ekind = nullptr;
		typeIR* tIRa = Expr(t->child[0], Ekind);
		typeIR* tIRb = entry->attrIR.idtype->More.ArrayAttr.indexTy;
		if (!tIRa || !tIRb)return nullptr;
		if (tIRa != tIRb)
		{
			SENL_error(t->lineno, 5, t->name[0]); ///???
			cout << "下标变量不符合\n";
		}
		else ans = entry->attrIR.idtype->More.ArrayAttr.elemTy;
	}
	return ans;
}
typeIR* SENL::recordVar(TreeNode* t)
{
	symbtable* entry;
	typeIR* ans = nullptr;
	fieldChain* entryf;
	bool present = FindEntry(t->name[0], -1, &entry);
	if (!present)
	{
		SENL_error(t->lineno, 2, t->name[0]);
	}
	else if (entry->attrIR.kind != IdKind::varKind)
	{
		SENL_error(t->lineno, 3, t->name[0]);
	}
	else if (entry->attrIR.idtype->kind != Typekind::recordTy)
	{
		SENL_error(t->lineno, 3, t->name[0]);
	}
	else
	{
		bool presentf = FindField(t->child[0]->name[0], entry->attrIR.idtype->More.body, &entryf);
		if (!presentf)
		{
			SENL_error(t->lineno, 2, t->child[0]->name[0]);//????记录中未声明
		}
		else
			ans = entryf->unitType;
	}
	return ans;
}
void SENL::readstatement(TreeNode* t)   //对于变量标识符的操作，向前寻找时，不需要全找一遍，前面不可能出现多次声明的情况了，上面的代码已经杜绝这种情况
{
	symbtable* entry;
	bool present = FindEntry(t->name[0], -1, &entry);
	if (!present)
	{
		SENL_error(t->lineno, 2, t->name[0]);
	}
	else if(entry->attrIR.kind != IdKind::varKind)
	{
		SENL_error(t->lineno, 3, t->name[0]);
	}
	t->table[0] = entry;
}
//在过程没有返回类型的情况下，这个语句令人堪忧，更何况书上还啥都没写
void SENL::returnstatement(TreeNode* t)
{
	if (sym_level == 0)
	{
		cout << "在主程序中出现返回语句\n";
	}
}
void SENL::callstatement(TreeNode* t)
{
	AccessKind* Aptr = nullptr;
	symbtable* entry = nullptr;
	bool present = FindEntry(t->child[0]->name[0], -1, &entry);
	if (present) // 形实参结合
	{
		if(entry->attrIR.kind != IdKind::procKind)
			SENL_error(t->lineno, 10, t->name[0]);  // ???
		TreeNode* tp = t->child[1];
		ParamTable* pp = entry->attrIR.More.ProcAttr.param;
		
		while (tp)
		{
			if (!pp)
			{
				SENL_error(tp->lineno, 9); //?
				break;
			}
			typeIR* tIR = Expr(tp, Aptr);
			if (Aptr && *Aptr != pp->entry->attrIR.More.VarAttr.access)
			{
				SENL_error(tp->lineno, 8); //?
			}
			else if (tIR != pp->entry->attrIR.idtype)
			{
				SENL_error(tp->lineno, 8);//?
			}
			tp = tp->sibling;
			pp = pp->next;
		}
		if (pp)
		{
			SENL_error(t->lineno, 9);//?
		}
	}
	else
	{
		SENL_error(t->lineno, 2, t->name[0]);
	}
}
void SENL::ifstatement(TreeNode* t)
{
	AccessKind* Aptr = nullptr;
	typeIR* tIR = Expr(t->child[0], Aptr);
	if (!tIR) return;
	if (tIR->kind != Typekind::boolTy)
	{
		SENL_error(t->lineno, 11);
	}
	else  // 这个else真的需要吗
	{
		TreeNode* p = t->child[1];
		while (p)
		{
			statement(t->child[1]);
			p = p->sibling;
		}
		p = t->child[2];
		while (p)
		{
			statement(t->child[2]);
			p = p->sibling;
		}
	}
	
}
void SENL::whilestatement(TreeNode* t)
{
	AccessKind* Aptr = nullptr;
	typeIR* tIR = Expr(t->child[0], Aptr);
	if (!tIR) return;
	if (tIR->kind != Typekind::boolTy)
	{
		SENL_error(t->lineno, 11);
	}
	else
	{
		TreeNode* p = t->child[1];
		while (p)
		{
			statement(p);
			p = p->sibling;
		}
	}
}
void SENL::writestatement(TreeNode* t)
{
	AccessKind* Aptr = nullptr;
	typeIR* tIR = Expr(t->child[0], Aptr);
	if (!tIR)return;
	if (tIR->kind == Typekind::boolTy)
	{
		cout << "类型出错\n";
	}
}
void SENL::assignstatement(TreeNode* t)
{
	symbtable* entry = nullptr;
	TreeNode* child0 = t->child[0];
	TreeNode* child1 = t->child[1];
	typeIR* tIR0 = nullptr;
	typeIR* tIR1 = nullptr;
	AccessKind* Aptr = nullptr;
	//bool present = FindEntry(child0->name[0], -1, &entry);
	if (!child0->child[0])// 非数组或记录成员
	{
		bool present = FindEntry(child0->name[0], -1, &entry);
		if (!present)
		{
			SENL_error(child0->lineno, 2, child0->name[0]);
		}
		else if (entry->attrIR.kind != IdKind::varKind)
		{
			SENL_error(child0->lineno, 7, child0->name[0]);
		}
		else tIR0 = entry->attrIR.idtype;
	}
	else
	{
		if (child0->attr.ExpAttr.varkind == VarKind::ArrayMembV)
		{
			tIR0 = arrayVar(child0);
		}
		else
			tIR0 = recordVar(child0);
	}
	tIR1 = Expr(child1, Aptr);
	if (!tIR1)return;
	if (tIR1 != tIR0)
	{

		SENL_error(t->lineno, 6,"");
	}
}
void SENL_error(int lineno, int id, string name,int colom)
{
	cout << "第" << lineno << "行:" << name << "--";
	switch (id)
	{
	case 1:cout << "标识符的重复定义；"; break;
	case 2:cout << "无声明的标识符；"; break;
	case 3:cout << "标识符为非期望的标识符类别（类型标识符，变量标识符，过程名标识符）；"; break;
	case 4:cout << "数组类型下标越界错误；"; break;
	case 5:cout << "数组成员变量和域变量的引用不合法；"; break;
	case 6:cout << "赋值语句的左右两边类型不相容；"; break;
	case 7:cout << "赋值语句左端不是变量标识符；"; break;
	case 8:cout << "过程调用中 ，形实参类型不匹配；"; break;
	case 9:cout << "过程调用中， 形实参个数不相同；"; break;
	case 10:cout << "过程调用语句中，标识符不是过程标识符；"; break;
	case 11:cout << "if 和while 语句的条件部分不是bool类型；"; break;
	case 12:cout << "表达式中运算符的分量的类型不相容"; break;
	}
	if (colom)cout << colom;
	cout << endl;
	//接具体调用!!
}

SENL senl;
/*
（1） 标识符的重复定义；
（2） 无声明的标识符；
（3） 标识符为非期望的标识符类别（类型标识符，变量标识符，过程名
标识符）；
（4） 数组类型下标越界错误；
（5） 数组成员变量和域变量的引用不合法；
（6） 赋值语句的左右两边类型不相容；
（7） 赋值语句左端不是变量标识符；
（8） 过程调用中 ，形实参类型不匹配；
（9） 过程调用中， 形实参个数不相同；
（10）过程调用语句中，标识符不是过程标识符；
（11）if 和while 语句的条件部分不是bool类型；
（12）表达式中运算符的分量的类型不相容
等等

*/