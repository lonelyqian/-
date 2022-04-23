#include <iostream>
#include <iomanip> 
#include <fstream>
#include "SNL_ll1.h"
#include "SENL.h"
using namespace std;
int show_text = 1;
int show_lnl = 1;
int show_snl = 1;
void interaction()
{
	int ins;
	cout << "自定义输出（1）/默认输出(0)  其他视为无效输入\n";
	cin >> ins;
	while (ins != 1 && ins != 0)
	{
		cout << "请重新输入选项\n";
		cin >> ins;
	}
	if (ins == 1)
	{
		cout << "是否显示源代码  是（1）/否（0）其他视为无效输入\n";
		cin >> show_text;
		while (show_text != 1 && show_text != 0)
		{
			cout << "请重新输入选项\n";
			cin >> show_text;
		}

		cout << "是否显示token序列  是（1）/否（0）其他视为无效输入\n";
		cin >> show_lnl;
		while (show_lnl != 1 && show_lnl != 0)
		{
			cout << "请重新输入选项\n";
			cin >> show_lnl;
		}

		cout << "是否显示源代码  是（1）/否（0）其他视为无效输入\n";
		cin >> show_snl;
		while (show_snl != 1 && show_snl != 0)
		{
			cout << "请重新输入选项\n";
			cin >> show_snl;
		}
	}
}
int main()
{
	cout << "请输入源代码的相对路径（无需写后缀名）\n";
	string names;
	cin >> names;
	ifstream in;
	in.open(names + ".txt", ios::in);
	while (!in)
	{
		cout << "无法打开该文件,请重新输入\n";
		cin >> names;
		in.open(names + ".txt", ios::in);
	}
	istreambuf_iterator<char> beg(in), end;
	string strdata(beg, end);//或者string st;st.assign(beg,end);
	
	//in.close();
	interaction();
	if(show_text)
		cout << strdata << endl;
	//词法部分
	bool flag = true;
	Initsym_lex();
	cout << "——————词法分析开始——————" << endl;
	if (tok.getTokenlist(strdata)) {
		if(show_lnl)
		for (int i = 0; i < tok.tokens.size(); i++) {// <<setw(10)<<asd[i] 
			cout << i << "  " << tok.tokens[i].line << " " << lexName[tok.tokens[i].lex] << " " << tok.tokens[i].sem << endl;
		}
	}
	else
	{
		flag = false;
		cout << "——————词法分析出错——————" << endl;
		return 0;
	}
	
	cout << "——————词法分析结束——————" << endl;
	cout << endl;
	//语法部分
	cout << "——————语法分析开始——————" << endl;
	snl.tokens = tok.tokens;
	snl.ggroot = snl.create_tree();
	if (!snl.snlcheck)
	{
		cout << "——————语法分析出错——————" << endl;
		return 0;
	}
	else cout << "以下为语法树\n"; 
	if(show_snl)
		show_SNLtree(snl.ggroot,0, false);
	cout << "——————语法分析结束——————" << endl;
	cout << endl;
	//语义部分
	cout << "——————语义分析开始——————" << endl;
	senl.Analyze(snl.ggroot);
	cout << "——————语义分析结束——————" << endl;
}