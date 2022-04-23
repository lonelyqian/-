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
	cout << "�Զ��������1��/Ĭ�����(0)  ������Ϊ��Ч����\n";
	cin >> ins;
	while (ins != 1 && ins != 0)
	{
		cout << "����������ѡ��\n";
		cin >> ins;
	}
	if (ins == 1)
	{
		cout << "�Ƿ���ʾԴ����  �ǣ�1��/��0��������Ϊ��Ч����\n";
		cin >> show_text;
		while (show_text != 1 && show_text != 0)
		{
			cout << "����������ѡ��\n";
			cin >> show_text;
		}

		cout << "�Ƿ���ʾtoken����  �ǣ�1��/��0��������Ϊ��Ч����\n";
		cin >> show_lnl;
		while (show_lnl != 1 && show_lnl != 0)
		{
			cout << "����������ѡ��\n";
			cin >> show_lnl;
		}

		cout << "�Ƿ���ʾԴ����  �ǣ�1��/��0��������Ϊ��Ч����\n";
		cin >> show_snl;
		while (show_snl != 1 && show_snl != 0)
		{
			cout << "����������ѡ��\n";
			cin >> show_snl;
		}
	}
}
int main()
{
	cout << "������Դ��������·��������д��׺����\n";
	string names;
	cin >> names;
	ifstream in;
	in.open(names + ".txt", ios::in);
	while (!in)
	{
		cout << "�޷��򿪸��ļ�,����������\n";
		cin >> names;
		in.open(names + ".txt", ios::in);
	}
	istreambuf_iterator<char> beg(in), end;
	string strdata(beg, end);//����string st;st.assign(beg,end);
	
	//in.close();
	interaction();
	if(show_text)
		cout << strdata << endl;
	//�ʷ�����
	bool flag = true;
	Initsym_lex();
	cout << "�������������ʷ�������ʼ������������" << endl;
	if (tok.getTokenlist(strdata)) {
		if(show_lnl)
		for (int i = 0; i < tok.tokens.size(); i++) {// <<setw(10)<<asd[i] 
			cout << i << "  " << tok.tokens[i].line << " " << lexName[tok.tokens[i].lex] << " " << tok.tokens[i].sem << endl;
		}
	}
	else
	{
		flag = false;
		cout << "�������������ʷ�������������������" << endl;
		return 0;
	}
	
	cout << "�������������ʷ���������������������" << endl;
	cout << endl;
	//�﷨����
	cout << "�������������﷨������ʼ������������" << endl;
	snl.tokens = tok.tokens;
	snl.ggroot = snl.create_tree();
	if (!snl.snlcheck)
	{
		cout << "�������������﷨������������������" << endl;
		return 0;
	}
	else cout << "����Ϊ�﷨��\n"; 
	if(show_snl)
		show_SNLtree(snl.ggroot,0, false);
	cout << "�������������﷨��������������������" << endl;
	cout << endl;
	//���岿��
	cout << "���������������������ʼ������������" << endl;
	senl.Analyze(snl.ggroot);
	cout << "�����������������������������������" << endl;
}