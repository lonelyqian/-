#pragma once
#include"SNL_utl.h"
TreeNode* p; //当前正在处理的结点
TreeNode** t;
TreeNode* savep;// 22 结构体声明
DecKind* temp;// 回填基础类型
TreeNode* opt; //临时操作符栈元素
TreeNode* opnt;//临时操作数栈元素
bool getExpResult = true;//判断比较表达式处理完毕 后是否弹栈与语法树连接
bool getExpResult2;      //判断数组【】中的表达式是否处理完毕
int expflag = 0;//'(' 的数量
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
	*t = p; // nb 指针真神奇（恶心）
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
	symbol_stack.push(TypeDec);   //书上是func
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
	snltree_stack.push(&p->sibling); // 其他声明
	snltree_stack.push(&p->child[0]); // 具体节点
}
void SNL::process8()
{
	symbol_stack.push(TypeDecMore);
	symbol_stack.push(SEMI);
	symbol_stack.push(TypeName);  // 什么情况，书上是TypeDef
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
void SNL::process14()     //和书上有出入，没有idnum++;
{
	symbol_stack.push(ID);
	p->kind.dec = IdK;
	p->type_name = tokens[pos].sem;
}
void SNL::process15()
{
	symbol_stack.push(INTEGER);
	*temp = IntegerK; //可否不用temp，而是直接赋值呢
}
void SNL::process16()
{
	symbol_stack.push(CHAR);
	*temp = CharK;  //可否不用temp，而是直接赋值呢
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
	/* *temp = ArrayK; 不行，因为12上采用的是basetype才用temp保存*/
	p->kind.dec = ArrayK;
	temp = &p->attr.ArrayAttr.childtype;//基类型
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
	savep = p;        // 当原来为空时，不能间接改指向的值，只能赋值   p-> =xx（*t = p）;  不为空的话，可以进行间接改p = t; p-> =XXX;  
	snltree_stack.push(&p->child[0]);// 记录的儿子指向的是类型
}
void SNL::process23()    //gg,书上这里并没有弹栈艹
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
void SNL::process24()   //和大佬有细微差别
{
	symbol_stack.push(FieldDecMore);
	symbol_stack.push(SEMI);
	symbol_stack.push(IdList);
	symbol_stack.push(ArrayType);
	p = create_node(DecK);
	//p->kind.dec = ArrayK; 为啥不写啊，书上也没写 因为在ArrayType为左的产生式19函数中，已经对其赋值了，不需要重复赋值？？
	t = snltree_stack.top();
	snltree_stack.pop();
	*t = p;
	snltree_stack.push(&p->sibling);

}
void SNL::process25()
{
	snltree_stack.pop();
	p = savep;  //也不是很懂，record还有啥没写的吗
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

}// 新篇章
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
void SNL::process41()  // ta少压了个basetype和：
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
	snltree_stack.push(&p->child[2]);//过程体
	snltree_stack.push(&p->child[1]);//声明
	snltree_stack.push(&p->child[0]);//形参
}
void SNL::process42()
{
	//为啥不弹procdecmore  兄弟啊
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
	snltree_stack.pop();//弹形参
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
void SNL::process48()//重大分歧  得出原因，：不是特殊符号，函数无返回类型！！？
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
	/*下面将前面child1(无声明)或者child1 的兄弟（有声明）弹栈！！*/  
	snltree_stack.pop();
	/*上面*/
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
	p = create_node(StmtK);//暂时不知道是赋值还是过程调用
	auto q = create_node(ExpK);
	q->kind.exp = VariK;     // 我怎么感觉不是在这里写啊，应该在后面回写，gg，书上这里也没写？！
	q->name.push_back(tokens[pos].sem);
	q->idnum++;
	p->child[0] = q;         //如果是，赋值，则这是他的左部，如果是函数调用，这是他的名字
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
	p->child[0]->attr.ExpAttr.varkind = IdV; //标识符变量，这个东西是函数名字，但是，非常不理解为啥这么写？！！！
}
void SNL::process69()
{
	symbol_stack.push(Exp);
	symbol_stack.push(ASSIGN);
	symbol_stack.push(VariMore);
	snltree_stack.push(&p->child[1]); // 赋值语句右部结点
	//压入特殊栈底标志，表示进入表达式处理？？！
	opt = create_ExpKop_node(END);
	op_stack.push(opt);
	p = p->child[0]; // 回填赋值左部的属性
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
	snltree_stack.push(&p->child[1]); // 循环体
	snltree_stack.push(&p->child[0]); // 条件表达式
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
	snltree_stack.push(&p->child[0]); // 表达式树的根结点
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
	snltree_stack.push(&p->child[1]);  // 干啥为止？！应该是指向实参列表，对了第一个儿子是函数名字exp varkind idk
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
void SNL::process81()// relexp  条件表达式
{
	symbol_stack.push(OtherRelE);
	symbol_stack.push(Exp);
	opt = create_ExpKop_node(END);
	op_stack.push(opt);
	getExpResult = false;//左表达式处理完毕后不弹栈（不进入语法树）

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
	getExpResult = true;//比较符右边表达式结束，可以出栈。(进入语法树)
}
void SNL::process83()
{
	symbol_stack.push(OtherTerm);
	symbol_stack.push(Term);
}
void SNL::process84()// very complex for me . ?!
{
	if (tokens[pos].lex == RPAREN && expflag != 0) //表达式还没结束,弹栈建子树直到最近左括号
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
		op_stack.pop();//将（弹栈
		expflag--;
	}
	else                                           //表达式结束，疯狂建子树
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
			op_stack.pop();//将END弹栈
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
void SNL::process93()// 是整形变量还是数组，记录什么的通过varimore来判断
{
	p->attr.ExpAttr.varkind = IdV;
}
void SNL::process94()
{
	symbol_stack.push(RMIDPAREN);
	symbol_stack.push(Exp);
	symbol_stack.push(LMIDPAREN);
	p->attr.ExpAttr.varkind = ArrayMembV;
	snltree_stack.push(&p->child[0]); // 指向[]表达式结点
	opt = create_ExpKop_node(END);
	op_stack.push(opt);
	getExpResult2 = true;
}
void SNL::process95()
{
	symbol_stack.push(FieldVar);
	symbol_stack.push(DOT);
	p->attr.ExpAttr.varkind = FieldMembV;
	snltree_stack.push(&p->child[0]);// 指向子成员.
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