#pragma once
#include <string>
using namespace std;
typedef enum {intTy, charTy, arrayTy, recordTy,boolTy} Typekind;
typedef enum {typeKind, varKind,procKind}IdKind;
typedef enum{indir,dir}AccessKind;
struct intPtr
{
	int size = 1;
	Typekind kind = intTy;
};
struct charPtr
{
	int size = 1;
	Typekind kind = charTy;
};
struct arrayPtr
{
	int size; // calculate to confirm
	Typekind kind = arrayTy;
	int indexTy;  //�����±����͵��ڲ���ʾ��
	int elemTy; // ����Ԫ�����͵��ڲ���ʾ��
};
struct recordPtr
{
	int size;
	Typekind kind = recordTy;
	struct fieldChain* body;
};
struct typeIR
{
	int size;
	Typekind kind;
	union
	{
		struct
		{
			struct typeIR* indexTy;
			struct typeIR* elemTy;
		}ArrayAttr;
		fieldChain* body;
	}More;
};
struct fieldChain
{
	string idname;
	typeIR* unitType;  //���г�Ա������
	int offset;
	fieldChain* next;
};
struct AttributeIR
{
	struct typeIR* idtype;
	IdKind kind;  //��֪����ɶ
	union
	{
		struct
		{
			AccessKind access;   //δ���壬�м�������ɿ��ܻ����ϡ�������д
			int level;
			int off;
		}VarAttr;
		struct
		{
			int level;
			struct ParamTable* param;
			int code;
			int size;
		}ProcAttr;
	}More;
};
struct ParamTable
{
	symbtable* entry;
	ParamTable* next;
};

typeIR* newTy(Typekind kind)
{
	typeIR* ty = new typeIR; ty->kind = kind;
	if (kind == intTy || kind == charTy || kind == boolTy)
	{
		ty->size = 1;
	}
	else if (kind == arrayTy)
	{
		ty->More.ArrayAttr.indexTy = nullptr;
		ty->More.ArrayAttr.elemTy = nullptr;
	}
	else
	{
		ty->More.body = nullptr;
	}
	return ty;
}
struct symbtable
{
	string idname;
	AttributeIR attrIR;
	symbtable* next;
};
