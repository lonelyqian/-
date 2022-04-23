#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Token
{
	int type;
	int content;
};
vector <string> Identifier_table;//type 1
vector <int> Int_cons_table;	 //type 2
vector <char> Char_cons_table;   //type 3
								 //type 4-24为保留字，  25-43 为特殊符号
vector <string> Spec_Char_table = {" "," "," "," ","program","type","var","procedure","begin","end","array","of","record","if","then","else","fi","while","do","endwh","read","write","return","integer","char"
									,"+","-","*","/","(",")",".","[","]",";",":",",","<","=",":=","..","EOF","{","}"};
int SearchInSpec_Char_table(string a)
{
	for (int i = 4; i <= 24; i++)
	{
		if (a == Spec_Char_table[i])
			return i;
	}
	return -1;
}