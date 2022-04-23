#pragma once
#include"SNL_utl.h"
TreeNode* p; //��ǰ���ڴ���Ľ��
TreeNode** t;
TreeNode* savep;// 22 �ṹ������
DecKind* temp;// �����������
TreeNode* opt; //��ʱ������ջԪ��
TreeNode* opnt;//��ʱ������ջԪ��
bool getExpResult = true;//�жϱȽϱ��ʽ������� ���Ƿ�ջ���﷨������
bool getExpResult2;      //�ж����顾���еı��ʽ�Ƿ������
int expflag = 0;//'(' ������
void SNL::process1()
{
	symbol_stack.push(ProgramBody);
	symbol_stack.push(DeclarePart);// Type ;Var 
	symbol_stack.push(ProgramHead);
}
void SNL::process2()
{
	symbol_stack.push(ProgramName);
	symbol_stack.push(PROGRAM);
	p = create_node(PheadK);
	t = snltree_stack.top();
	*t = p; // nb ָ�������棨���ģ�
	snltree_stack.pop();
}
void SNL::process3()
{
	symbol_stack.push(ID);
	p->idnum++;
	p->name.push_back(tokens[pos].sem);
	
}
void SNL::process4()
{
	symbol_stack.push(ProcDec);
	symbol_stack.push(VarDec);
	symbol_stack.push(TypeDec);   //������func
}
void SNL::process5()
{
	;
}
void SNL::process6()
{
	symbol_stack.push(TypeDeclaration);
}
void SNL::process7()
{
	symbol_stack.push(TypeDecList);
	symbol_stack.push(TYPE);
	p = create_node(TypeK);
	t = snltree_stack.top();
	snltree_stack.pop();
	*t = p;
	snltree_stack.push(&p->sibling); // ��������
	snltree_stack.push(&p->child[0]); // ����ڵ�
}
void SNL::process8()
{
	symbol_stack.push(TypeDecMore);
	symbol_stack.push(SEMI);
	symbol_stack.push(TypeName);  // ʲô�����������TypeDef
	symbol_stack.push(ASSIGN);
	symbol_stack.push(TypeId);
	p = create_node(DecK);
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->sibling);

}
void SNL::process9()
{
	snltree_stack.pop();
}
void SNL::process10()
{
	symbol_stack.push(TypeDecList);
}
void SNL::process11()
{
	symbol_stack.push(ID);
	p->name.push_back(tokens[pos].sem);
	p->idnum++;
}
void SNL::process12()
{
	symbol_stack.push(BaseType);
	temp = &(p->kind.dec);
}
void SNL::process13()
{
	symbol_stack.push(StructureType);
}
void SNL::process14()     //�������г��룬û��idnum++;
{
	symbol_stack.push(ID);
	p->kind.dec = IdK;
	p->type_name = tokens[pos].sem;
}
void SNL::process15()
{
	symbol_stack.push(INTEGER);
	*temp = IntegerK; //�ɷ���temp������ֱ�Ӹ�ֵ��
}
void SNL::process16()
{
	symbol_stack.push(CHAR);
	*temp = CharK;  //�ɷ���temp������ֱ�Ӹ�ֵ��
}
void SNL::process17()
{
	symbol_stack.push(ArrayType);
}
void SNL::process18()
{
	symbol_stack.push(RecType);
}
void SNL::process19()
{
	symbol_stack.push(BaseType);
	symbol_stack.push(OF);
	symbol_stack.push(RMIDPAREN);
	symbol_stack.push(Top);
	symbol_stack.push(UNDERRANGE);
	symbol_stack.push(Low);
	symbol_stack.push(LMIDPAREN);
	symbol_stack.push(ARRAY);
	/* *temp = ArrayK; ���У���Ϊ12�ϲ��õ���basetype����temp����*/
	p->kind.dec = ArrayK;
	temp = &p->attr.ArrayAttr.childtype;//������
}
void SNL::process20()
{
	symbol_stack.push(INTC);
	p->attr.ArrayAttr.low = stoi(tokens[pos].sem, 0, 10);
}
void SNL::process21()
{
	symbol_stack.push(INTC);
	p->attr.ArrayAttr.up = stoi(tokens[pos].sem, 0, 10);
}
void SNL::process22()
{
	symbol_stack.push(END);
	symbol_stack.push(FieldDecList);
	symbol_stack.push(RECORD);
	p->kind.dec = RecordK;
	savep = p;        // ��ԭ��Ϊ��ʱ�����ܼ�Ӹ�ָ���ֵ��ֻ�ܸ�ֵ   p-> =xx��*t = p��;  ��Ϊ�յĻ������Խ��м�Ӹ�p = t; p-> =XXX;  
	snltree_stack.push(&p->child[0]);// ��¼�Ķ���ָ���������
}
void SNL::process23()    //gg,�������ﲢû�е�ջܳ
{
	symbol_stack.push(FieldDecMore);
	symbol_stack.push(SEMI);
	symbol_stack.push(IdList);
	symbol_stack.push(BaseType);
	p = create_node(DecK);
	t = snltree_stack.top();
	snltree_stack.pop();
	*t = p;
	temp = &p->kind.dec;
	snltree_stack.push(&p->sibling);

}
void SNL::process24()   //�ʹ�����ϸ΢���
{
	symbol_stack.push(FieldDecMore);
	symbol_stack.push(SEMI);
	symbol_stack.push(IdList);
	symbol_stack.push(ArrayType);
	p = create_node(DecK);
	//p->kind.dec = ArrayK; Ϊɶ��д��������Ҳûд ��Ϊ��ArrayTypeΪ��Ĳ���ʽ19�����У��Ѿ����丳ֵ�ˣ�����Ҫ�ظ���ֵ����
	t = snltree_stack.top();
	snltree_stack.pop();
	*t = p;
	snltree_stack.push(&p->sibling);

}
void SNL::process25()
{
	snltree_stack.pop();
	p = savep;  //Ҳ���Ǻܶ���record����ɶûд����
}
void SNL::process26()
{
	symbol_stack.push(FieldDecList);

}
void SNL::process27()
{
	symbol_stack.push(IdMore);
	symbol_stack.push(ID);
	p->name.push_back(tokens[pos].sem);
	p->idnum++;
}
void SNL::process28()
{
	;
}
void SNL::process29()
{
	symbol_stack.push(IdList);
	symbol_stack.push(COMMA);

}// ��ƪ��
void SNL::process30()
{
	;
}
void SNL::process31()
{
	symbol_stack.push(VarDeclaration);
}
void SNL::process32()
{
	symbol_stack.push(VarDecList);
	symbol_stack.push(VAR);
	p = create_node(VarK);
	t = snltree_stack.top();
	snltree_stack.pop();
	*t = p;
	snltree_stack.push(&p->sibling);
	snltree_stack.push(&p->child[0]);
}
void SNL::process33()
{
	symbol_stack.push(VarDecMore);
	symbol_stack.push(SEMI);
	symbol_stack.push(VarIdList);
	symbol_stack.push(TypeName);
	p = create_node(DecK);
	t = snltree_stack.top();
	snltree_stack.pop();
	*t = p;
	snltree_stack.push(&p->sibling);
}
void SNL::process34()
{
	snltree_stack.pop();
}
void SNL::process35()
{
	symbol_stack.push(VarDecList);
}
void SNL::process36()
{
	symbol_stack.push(VarIdMore);
	symbol_stack.push(ID);
	p->name.push_back(tokens[pos].sem);
	p->idnum++;

};
void SNL::process37()
{
	;
}
void SNL::process38()
{
	symbol_stack.push(VarIdList);
	symbol_stack.push(COMMA);
}
void SNL::process39()
{
	;
}
void SNL::process40()
{
	symbol_stack.push(ProcDeclaration);
}
void SNL::process41()  // ta��ѹ�˸�basetype�ͣ�
{
	symbol_stack.push(ProcDecMore);
	symbol_stack.push(ProcBody);
	symbol_stack.push(ProcDecPart);
	symbol_stack.push(SEMI);
	/*symbol_stack.push(BaseType);//here
	symbol_stack.push(COLON);   //and here*/
	symbol_stack.push(RPAREN);
	symbol_stack.push(ParamList);
	symbol_stack.push(LPAREN);
	symbol_stack.push(ProcName);
	symbol_stack.push(PROCEDURE);
	p = create_node(ProcDecK);
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->sibling);
	snltree_stack.push(&p->child[2]);//������
	snltree_stack.push(&p->child[1]);//����
	snltree_stack.push(&p->child[0]);//�β�
}
void SNL::process42()
{
	//Ϊɶ����procdecmore  �ֵܰ�
	;
}
void SNL::process43()
{
	symbol_stack.push(ProcDeclaration);
}
void SNL::process44()
{
	symbol_stack.push(ID);
	p->name.push_back(tokens[pos].sem);
	p->idnum++;
}
void SNL::process45()
{
	snltree_stack.pop();//���β�
}
void SNL::process46()
{
	symbol_stack.push(ParamDecList);
}
void SNL::process47()
{
	symbol_stack.push(ParamMore);
	symbol_stack.push(Param);
}
void SNL::process48()//�ش����  �ó�ԭ�򣬣�����������ţ������޷������ͣ�����
{
	snltree_stack.pop();
}
void SNL::process49()
{
	symbol_stack.push(ParamDecList);
	symbol_stack.push(SEMI);
}
void SNL::process50()
{
	symbol_stack.push(FormList);
	symbol_stack.push(TypeName);
	p = create_node(DecK);
	p->attr.ProcAttr.paramt = valparamType;
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->sibling);
}
void SNL::process51()
{
	symbol_stack.push(FormList);
	symbol_stack.push(TypeName);
	symbol_stack.push(VAR);
	p = create_node(DecK);
	p->attr.ProcAttr.paramt = varparamType;
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->sibling);
}
void SNL::process52()
{
	symbol_stack.push(FidMore);
	symbol_stack.push(ID);
	p->name.push_back(tokens[pos].sem);
	p->idnum++;
}
void SNL::process53()
{
	;
}
void SNL::process54()
{
	symbol_stack.push(FormList);
	symbol_stack.push(COMMA);
}
void SNL::process55()
{
	symbol_stack.push(DeclarePart);
}
void SNL::process56()
{
	symbol_stack.push(ProgramBody);
}
void SNL::process57()
{
	symbol_stack.push(END);
	symbol_stack.push(StmList);
	symbol_stack.push(BEGIN);
	/*���潫ǰ��child1(������)����child1 ���ֵܣ�����������ջ����*/  
	snltree_stack.pop();
	/*����*/
	p = create_node(StmLK);
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->child[0]);
}
void SNL::process58()
{
	symbol_stack.push(StmMore);
	symbol_stack.push(Stm);
}
void SNL::process59()
{
	snltree_stack.pop();
}
void SNL::process60()
{
	symbol_stack.push(StmList);
	symbol_stack.push(SEMI);
}
void SNL::process61()
{
	symbol_stack.push(ConditionalStm);
	p = create_StmtK_node(IfK);
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->sibling);

}
void SNL::process62()
{
	symbol_stack.push(LoopStm);
	p = create_StmtK_node(WhileK);
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->sibling);
}
void SNL::process63()
{
	symbol_stack.push(InputStm);
	p = create_StmtK_node(ReadK);
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->sibling);
}
void SNL::process64()
{
	symbol_stack.push(OutputStm);
	p = create_StmtK_node(WriteK);
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->sibling);
}
void SNL::process65()
{
	symbol_stack.push(ReturnStm);
	p = create_StmtK_node(ReturnK);
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->sibling);
}
void SNL::process66()
{
	symbol_stack.push(AssCall);
	symbol_stack.push(ID);
	p = create_node(StmtK);//��ʱ��֪���Ǹ�ֵ���ǹ��̵���
	auto q = create_node(ExpK);
	q->kind.exp = VariK;     // ����ô�о�����������д����Ӧ���ں����д��gg����������Ҳûд����
	q->name.push_back(tokens[pos].sem);
	q->idnum++;
	p->child[0] = q;         //����ǣ���ֵ�������������󲿣�����Ǻ������ã�������������
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();
	snltree_stack.push(&p->sibling);
}
void SNL::process67()
{
	symbol_stack.push(AssignmentRest);
	p->kind.stmt = AssignK;
}
void SNL::process68()
{
	symbol_stack.push(CallStmRest);
	p->kind.stmt = CallK;
	p->child[0]->attr.ExpAttr.varkind = IdV; //��ʶ����������������Ǻ������֣����ǣ��ǳ������Ϊɶ��ôд��������
}
void SNL::process69()
{
	symbol_stack.push(Exp);
	symbol_stack.push(ASSIGN);
	symbol_stack.push(VariMore);
	snltree_stack.push(&p->child[1]); // ��ֵ����Ҳ����
	//ѹ������ջ�ױ�־����ʾ������ʽ��������
	opt = create_ExpKop_node(END);
	op_stack.push(opt);
	p = p->child[0]; // ���ֵ�󲿵�����
}
void SNL::process70()
{
	symbol_stack.push(FI);
	symbol_stack.push(StmList);
	symbol_stack.push(ELSE);
	symbol_stack.push(StmList);
	symbol_stack.push(THEN);
	symbol_stack.push(RelExp);
	symbol_stack.push(IF);
	snltree_stack.push(&p->child[2]);// else
	snltree_stack.push(&p->child[1]);// then
	snltree_stack.push(&p->child[0]);// if
}
void SNL::process71()
{
	symbol_stack.push(ENDWH);
	symbol_stack.push(StmList);
	symbol_stack.push(DO);
	symbol_stack.push(RelExp);
	symbol_stack.push(WHILE);
	snltree_stack.push(&p->child[1]); // ѭ����
	snltree_stack.push(&p->child[0]); // �������ʽ
}
void SNL::process72()
{
	symbol_stack.push(RPAREN);
	symbol_stack.push(InVar);
	symbol_stack.push(LPAREN);
	symbol_stack.push(READ);

}
void SNL::process73()
{
	symbol_stack.push(ID);
	p->name.push_back(tokens[pos].sem);
	p->idnum++;
}
void SNL::process74()
{
	symbol_stack.push(RPAREN);
	symbol_stack.push(Exp);
	symbol_stack.push(LPAREN);
	symbol_stack.push(WRITE);
	snltree_stack.push(&p->child[0]); // ���ʽ���ĸ����
	opt = create_ExpKop_node(END);
	op_stack.push(opt);
}
void SNL::process75()
{
	symbol_stack.push(RETURN);
}
void SNL::process76()
{
	symbol_stack.push(RPAREN);
	symbol_stack.push(ActParamList);
	symbol_stack.push(LPAREN);
	snltree_stack.push(&p->child[1]);  // ��ɶΪֹ����Ӧ����ָ��ʵ���б����˵�һ�������Ǻ�������exp varkind idk
}
void SNL::process77()
{
	snltree_stack.pop();
}
void SNL::process78()
{
	symbol_stack.push(ActParamMore);
	symbol_stack.push(Exp);
	opt = create_ExpKop_node(END);
	op_stack.push(opt);
}
void SNL::process79()
{
	;
}
void SNL::process80()
{
	symbol_stack.push(ActParamList);
	symbol_stack.push(COMMA);
	snltree_stack.push(&p->sibling);
}
void SNL::process81()// relexp  �������ʽ
{
	symbol_stack.push(OtherRelE);
	symbol_stack.push(Exp);
	opt = create_ExpKop_node(END);
	op_stack.push(opt);
	getExpResult = false;//����ʽ������Ϻ󲻵�ջ���������﷨����

}
void SNL::process82()
{
	symbol_stack.push(Exp);
	symbol_stack.push(CmpOp);
	p = create_ExpKop_node(tokens[pos].lex);
	while (priosity(p->attr.ExpAttr.op) <= priosity(op_stack.top()->attr.ExpAttr.op))
	{
		opt = op_stack.top();
		op_stack.pop();
		TreeNode* opt_num1 = opnum_stack.top();
		opnum_stack.pop();
		TreeNode* opt_num0 = opnum_stack.top();
		opnum_stack.pop();
		opt->child[0] = opt_num0;
		opt->child[1] = opt_num1;
		opnum_stack.push(opt);  
	}
	op_stack.push(p);
	getExpResult = true;//�ȽϷ��ұ߱��ʽ���������Գ�ջ��(�����﷨��)
}
void SNL::process83()
{
	symbol_stack.push(OtherTerm);
	symbol_stack.push(Term);
}
void SNL::process84()// very complex for me . ?!
{
	if (tokens[pos].lex == RPAREN && expflag != 0) //���ʽ��û����,��ջ������ֱ�����������
	{
		opt = op_stack.top();
		while (opt->attr.ExpAttr.op != LPAREN)
		{
			op_stack.pop();
			TreeNode* opt_num1 = opnum_stack.top();
			opnum_stack.pop();
			TreeNode* opt_num0 = opnum_stack.top();
			opnum_stack.pop();
			opt->child[0] = opt_num0;
			opt->child[1] = opt_num1;
			opnum_stack.push(opt);
			opt = op_stack.top();
		}
		op_stack.pop();//������ջ
		expflag--;
	}
	else                                           //���ʽ�������������
	{
		if (getExpResult || getExpResult2)
		{
			opt = op_stack.top();
			while (opt->attr.ExpAttr.op != END)
			{
				op_stack.pop();
				TreeNode* opt_num1 = opnum_stack.top();
				opnum_stack.pop();
				TreeNode* opt_num0 = opnum_stack.top();
				opnum_stack.pop();
				opt->child[0] = opt_num0;
				opt->child[1] = opt_num1;
				opnum_stack.push(opt);
				opt = op_stack.top();
			}
			op_stack.pop();//��END��ջ
			t = snltree_stack.top();
			snltree_stack.pop();
			opnt = opnum_stack.top();
			opnum_stack.pop();
			*t = opnt;
			if (getExpResult2)getExpResult2 = false;
		}
	}
}
void SNL::process85()
{
	symbol_stack.push(Exp);
	symbol_stack.push(AddOp);
	p = create_ExpKop_node(tokens[pos].lex);
	while (priosity(p->attr.ExpAttr.op) <= priosity(op_stack.top()->attr.ExpAttr.op))
	{
		opt = op_stack.top();
		op_stack.pop();
		TreeNode* opt_num1 = opnum_stack.top();
		opnum_stack.pop();
		TreeNode* opt_num0 = opnum_stack.top();
		opnum_stack.pop();
		opt->child[0] = opt_num0;
		opt->child[1] = opt_num1;
		opnum_stack.push(opt);
	}
	op_stack.push(p);
}
void SNL::process86()
{
	symbol_stack.push(OtherFactor);
	symbol_stack.push(Factor);
}
void SNL::process87()
{
	;
}
void SNL::process88()
{
	symbol_stack.push(Exp);
	symbol_stack.push(MultOp);
	p = create_ExpKop_node(tokens[pos].lex);
	while (priosity(p->attr.ExpAttr.op) <= priosity(op_stack.top()->attr.ExpAttr.op))
	{
		opt = op_stack.top();
		op_stack.pop();
		TreeNode* opt_num1 = opnum_stack.top();
		opnum_stack.pop();
		TreeNode* opt_num0 = opnum_stack.top();
		opnum_stack.pop();
		opt->child[0] = opt_num0;
		opt->child[1] = opt_num1;
		opnum_stack.push(opt);
	}
	op_stack.push(p);
}
void SNL::process89()
{
	symbol_stack.push(RPAREN);
	symbol_stack.push(Exp);
	symbol_stack.push(LPAREN);
	opt = create_ExpKop_node(tokens[pos].lex);
	op_stack.push(opt);
	expflag++;
}
void SNL::process90()
{
	symbol_stack.push(INTC);
	p = create_node(ExpK);
	p->kind.exp = ConstK;
	p->attr.ExpAttr.val = stoi(tokens[pos].sem, 0, 10);
	opnum_stack.push(p);

}
void SNL::process91()
{
	symbol_stack.push(Variable);
}
void SNL::process92()//warning 
{
	symbol_stack.push(VariMore);
	symbol_stack.push(ID);
	p = create_node(ExpK);
	p->kind.exp = VariK;
	p->name.push_back(tokens[pos].sem);
	p->idnum++;
	opnum_stack.push(p);

}
void SNL::process93()// �����α����������飬��¼ʲô��ͨ��varimore���ж�
{
	p->attr.ExpAttr.varkind = IdV;
}
void SNL::process94()
{
	symbol_stack.push(RMIDPAREN);
	symbol_stack.push(Exp);
	symbol_stack.push(LMIDPAREN);
	p->attr.ExpAttr.varkind = ArrayMembV;
	snltree_stack.push(&p->child[0]); // ָ��[]���ʽ���
	opt = create_ExpKop_node(END);
	op_stack.push(opt);
	getExpResult2 = true;
}
void SNL::process95()
{
	symbol_stack.push(FieldVar);
	symbol_stack.push(DOT);
	p->attr.ExpAttr.varkind = FieldMembV;
	snltree_stack.push(&p->child[0]);// ָ���ӳ�Ա.
}
void SNL::process96()
{
	symbol_stack.push(FieldVarMore);
	symbol_stack.push(ID);
	p = create_node(ExpK);
	p->kind.exp = VariK;
	p->name.push_back(tokens[pos].sem);
	p->idnum++;
	t = snltree_stack.top();
	*t = p;
	snltree_stack.pop();

}
void SNL::process97()
{
	p->attr.ExpAttr.varkind = IdV;
}
void SNL::process98()
{
	symbol_stack.push(RMIDPAREN);
	symbol_stack.push(Exp);
	symbol_stack.push(LMIDPAREN);
	p->attr.ExpAttr.varkind = ArrayMembV;
	snltree_stack.push(&p->child[0]);
	opt = create_ExpKop_node(END);
	op_stack.push(opt);
	getExpResult2 = true;

}
void SNL::process99()
{
	symbol_stack.push(LT);
}
void SNL::process100()
{
	symbol_stack.push(EQ);
}
void SNL::process101()
{
	symbol_stack.push(PLUS);
}
void SNL::process102()
{
	symbol_stack.push(MINUS);
}
void SNL::process103()
{
	symbol_stack.push(TIMES);
}
void SNL::process104()
{
	symbol_stack.push(DIVIDE);
}
void SNL::error_SNL1()
{

}