#pragma once
#include <vector>
#include <stack>
#include <unordered_map>
#include "SNL_utl.h"
#include "SNL_ll1_process.h"

void SNL::create_symbol_table()
{
	symbol_table = {
		{{Program,PROGRAM},1},
		{{ProgramHead,PROGRAM},2},
		{{ProgramName,ID},3},
		{{DeclarePart,TYPE},4},
		{{DeclarePart,VAR},4},
		{{DeclarePart,PROCEDURE},4},
		{{DeclarePart,BEGIN},4},
		{{TypeDec,VAR},5},
		{{TypeDec,PROCEDURE},5},
		{{TypeDec,BEGIN},5},
		{{TypeDec,TYPE},6},
		{{TypeDeclaration,TYPE},7},
		{{TypeDecList,ID},8},
		{{TypeDecMore,VAR},9},
		{{TypeDecMore,PROCEDURE},9},
		{{TypeDecMore,BEGIN},9},
		{{TypeDecMore,ID},10},
		{{TypeId,ID},11},
		{{TypeName,INTEGER},12},
		{{TypeName,CHAR},12},
		{{TypeName,ARRAY},13},
		{{TypeName,RECORD},13},
		{{TypeName,ID},14},
		{{BaseType,INTEGER},15},
		{{BaseType,CHAR},16},
		{{StructureType,ARRAY},17},
		{{StructureType,RECORD},18},
		{{ArrayType,ARRAY},19},
		{{Low,INTC},20},
		{{Top,INTC},21},
		{{RecType,RECORD},22},
		{{FieldDecList,INTEGER},23},
		{{FieldDecList,CHAR},23},
		{{FieldDecList,ARRAY},24},
		{{FieldDecMore,END},25},
		{{FieldDecMore,INTEGER},26},
		{{FieldDecMore,CHAR},26},
		{{FieldDecMore,ARRAY},26},
		{{IdList,ID},27},
		{{IdMore,SEMI},28},
		{{IdMore,COMMA},29},
		{{VarDec,PROCEDURE},30},
		{{VarDec,BEGIN},30},
		{{VarDec,VAR},31},
		{{VarDeclaration,VAR},32},
		{{VarDecList,INTEGER},33},
		{{VarDecList,CHAR},33},
		{{VarDecList,ARRAY},33},
		{{VarDecList,RECORD},33},
		{{VarDecList,ID},33},
		{{VarDecMore,PROCEDURE},34},
		{{VarDecMore,BEGIN},34},
		{{VarDecMore,INTEGER},35},
		{{VarDecMore,CHAR},35},
		{{VarDecMore,ARRAY},35},
		{{VarDecMore,RECORD},35},
		{{VarDecMore,ID},35},
		{{VarIdList,ID},36},
		{{VarIdMore,SEMI},37},
		{{VarIdMore,COMMA},38},
		{{ProcDec,BEGIN},39},
		{{ProcDec,PROCEDURE},40},
		{{ProcDeclaration,PROCEDURE},41},
		{{ProcDecMore,PROCEDURE},43},  //什么情况
		{{ProcDecMore,BEGIN},42},
		{{ProcName,ID},44},





		{{ParamList,RPAREN},45},
		{{ParamList,INTEGER},46},
		{{ParamList,CHAR},46},
		{{ParamList,ARRAY},46},
		{{ParamList,RECORD},46},
		{{ParamList,VAR},46},
		{{ParamList,ID},46},
		{{ParamDecList,INTEGER},47},
		{{ParamDecList,CHAR},47},
		{{ParamDecList,ARRAY},47},
		{{ParamDecList,RECORD},47},
		{{ParamDecList,VAR},47},
		{{ParamDecList,ID},47},
		{{ParamMore,SEMI},49},
		{{ParamMore,RPAREN},48},
		{{Param,INTEGER},50},
		{{Param,CHAR},50},
		{{Param,ARRAY},50},
		{{Param,RECORD},50},
	//	{{Param,END},51}, 什么情况
		{{Param,ID},50},

		{{Param,VAR},51},
		{{FormList,ID},52},
		{{FidMore,SEMI},53},

		{{FidMore,COMMA},54},
		{{FidMore,RPAREN},53},

		{{ProcDecPart,TYPE},55},
		{{ProcDecPart,VAR},55},
		{{ProcDecPart,PROCEDURE},55},

		{{ProcDecPart,BEGIN} , 55},

		{{ProcBody,BEGIN},56},

		{{ProgramBody,BEGIN},57},
		{{StmList,IF},58},
		{{StmList,WHILE},58},

		{{StmList,READ},58},
		{{StmList,WRITE},58},
		{{StmList,RETURN},58},
		{{StmList,ID},58},
		{{StmMore,END},59},

		{{StmMore,ELSE},59},
		{{StmMore,FI},59},
		{{StmMore,ENDWH},59},
		{{StmMore,SEMI},60},

		{{Stm,IF},61},
		{{Stm,WHILE},62},
		{{Stm,READ},63},
		{{Stm,WRITE},64},
		{{Stm,RETURN},65},
		{{Stm,ID},66},






		//TODO shushang cuole
		{{AssCall,ASSIGN},67},
		{{AssCall,DOT},67},
		{{AssCall,LMIDPAREN},67},

		{{AssCall,LPAREN},68},
		{{AssignmentRest,DOT},69},
		{{AssignmentRest,LMIDPAREN},69},
		{{AssignmentRest,ASSIGN},69},
		{{ConditionalStm,IF},70},
		{{LoopStm,WHILE},71},
		{{InputStm,READ},72},
		{{InVar,ID},73},
		{{OutputStm,WRITE},74},
		{{ReturnStm,RETURN},75},
		{{CallStmRest,LPAREN},76},
		{{ActParamList,INTC},78},
		{{ActParamList,ID},78},
		{{ActParamList,LPAREN},78},
		{{ActParamList,RPAREN},77},
		{{ActParamMore,COMMA},80},
		{{ActParamMore,RPAREN},79},
		{{RelExp,INTC},81},
		{{RelExp,ID},81},
		{{RelExp,LMIDPAREN},81},
		{{OtherRelE,LT},82},
		{{OtherRelE,EQ},82},

		{{Exp,INTC},83},

		{{OtherFactor,END},87},
		{{OtherFactor,THEN},87},
		{{OtherFactor,ELSE},87},
		{{OtherFactor,FI},87},
		{{OtherFactor,DO},87},
		{{OtherFactor,ENDWH},87},
		{{OtherFactor,SEMI},87},
		{{OtherFactor,COMMA},87},
		{{OtherFactor,RPAREN},87},
		{{OtherFactor,RMIDPAREN},87},
		{{OtherFactor,LT},87},
		{{OtherFactor,EQ},87},
		{{OtherFactor,PLUS},87},
		{{OtherFactor,MINUS},87},


		{{OtherFactor,TIMES},88},
		{{OtherFactor,DIVIDE},88},







		{{Term,INTC},86},
		{{Factor,INTC},90},

		{{OtherTerm,END},84},
		{{Term,END},87},
		{{VariMore,END},93},
		{{FieldVarMore,END},97},

		{{OtherTerm,THEN},84},
		{{Term,THEN},87},
		{{VariMore,THEN},93},
		{{FieldVarMore,THEN},97},

		{{OtherTerm,ELSE},84},
		{{Term,ELSE},87},
		{{VariMore,ELSE},93},
		{{FieldVarMore,ELSE},97},

		{{OtherTerm,FI},84},
		{{Term,FI},87},
		{{VariMore,FI},93},
		{{FieldVarMore,FI},97},

		{{OtherTerm,DO},84},
		{{Term,DO},87},
		{{VariMore,DO},93},
		{{FieldVarMore,DO},97},

		{{OtherTerm,ENDWH},84},
		{{Term,ENDWH},87},
		{{VariMore,ENDWH},93},
		{{FieldVarMore,ENDWH},97},

		{{Exp,ID},83},
		{{Term,ID},86},
		{{Factor,ID},91},
		{{Variable,ID},92},
		{{FieldVar,ID},96},

		{{VariMore,DOT},95},

		{{OtherTerm,SEMI},84},
		{{Term,SEMI},87},
		{{VariMore,SEMI},93},
		{{FieldVarMore,SEMI},97},

		{{OtherTerm,COMMA},84},
		{{Term,COMMA},87},
		{{VariMore,COMMA},93},
		{{FieldVarMore,COMMA},97},

		{{Exp,LPAREN},83},
		{{Term,LPAREN},86},
		{{Factor,LPAREN},89},

		{{OtherTerm,RPAREN},84},
		{{Term,RPAREN},87},
		{{VariMore,RPAREN},93},
		{{FieldVarMore,RPAREN},97},

		{{VariMore,LMIDPAREN},94},
		{{FieldVarMore,LMIDPAREN},98},

		{{OtherTerm,RMIDPAREN},84},
		{{Term,RMIDPAREN},87},
		{{VariMore,RMIDPAREN},93},
		{{FieldVarMore,RMIDPAREN},97},

		{{OtherTerm,LT},84},
		{{Term,LT},87},
		{{VariMore,LT},93},
		{{FieldVarMore,LT},97},
		{{CmpOp,LT},99},

		{{OtherTerm,EQ},84},
		{{Term,EQ},87},
		{{VariMore,EQ},93},
		{{FieldVarMore,EQ},97},
		{{CmpOp,EQ},100},

		{{OtherTerm,PLUS},85},
		{{Term,PLUS},87},
		{{VariMore,PLUS},93},
		{{FieldVarMore,PLUS},97},
		{{AddOp,PLUS},101},

		{{OtherTerm,MINUS},85},
		{{Term,MINUS},87},
		{{VariMore,MINUS},93},
		{{FieldVarMore,MINUS},97},
		{{AddOp,MINUS},102},

		{{Term,TIMES},88},
		{{VariMore,TIMES},93},
		{{FieldVarMore,TIMES},97},
		{{MultOp,TIMES},103},

		{{Term,DIVIDE},88},
		{{VariMore,DIVIDE},93},
		{{FieldVarMore,DIVIDE},97},
		{{MultOp,DIVIDE},104},

		{{VariMore,ASSIGN},93},
		{{FieldVarMore,ASSIGN},97},


		{{CmpOp,LT},99},
		{{CmpOp,EQ},100},
		{{AddOp,PLUS},101},
		{{AddOp,MINUS},102},
		{{MultOp,TIMES},103},
		{{MultOp,DIVIDE},104},
	};
}
TreeNode* SNL::create_tree()
{
	create_symbol_table();
	symbol_stack.push(Program);
	TreeNode* root = create_node(ProK);
	snltree_stack.push(&root->child[2]);
	snltree_stack.push(&root->child[1]);
	snltree_stack.push(&root->child[0]);
	for (pos = 0; pos < tokens.size();)
	{
		lineno = tokens[pos].line;
		if (symbol_stack.empty())
		{
			if (pos >= tokens.size())
			{
				cout << "语法0错误\n"; snlcheck = false;
			}
			
			break;
		}
		LexType st = symbol_stack.top();
		if (TTSet.find(st) != TTSet.end()) //为TT
		{
			//cout << "TT:" << lexName[st] << " " <<  lexName[tokens[pos].lex] << ":" << tokens[pos].sem << endl;
			if (st == tokens[pos].lex)
			{
				symbol_stack.pop();
				pos++;
			}
			else
			{
				cout << tokens[pos].line << "行，有语法错误TT\n"; snlcheck = false; break;
			}
		}
		else
		{
			cout <<"NT:"<<st << " " << lexName[tokens[pos].lex] << ":" << tokens[pos].sem << endl;
			cout << "predict" << symbol_table[{st, tokens[pos].lex}] << endl;
			if (symbol_table[{st, tokens[pos].lex}])
			{
				symbol_stack.pop();
				predict(symbol_table[{st, tokens[pos].lex}]);	
			}
			else
			{
				cout << tokens[pos].line << "行，有语法错误NT\n"; snlcheck = false; break;
			}
		}
		//cout << "__________________________________________\n";
	}
	if (!symbol_stack.empty())
	{
		cout << "语法*错误\n"; snlcheck = false;
	}
	//cout << symbol_stack.empty() << endl;
	return root;
};
void SNL::predict(int num)
{
	switch (num)
	{
	case 1: process1(); break;
	case 2: process2(); break;
	case 3: process3(); break;
	case 4: process4(); break;
	case 5: process5(); break;
	case 6: process6(); break;
	case 7: process7(); break;
	case 8: process8(); break;
	case 9: process9(); break;
	case 10: process10(); break;
	case 11: process11(); break;
	case 12: process12(); break;
	case 13: process13(); break;
	case 14: process14(); break;
	case 15: process15(); break;
	case 16: process16(); break;
	case 17: process17(); break;
	case 18: process18(); break;
	case 19: process19(); break;
	case 20: process20(); break;
	case 21: process21(); break;
	case 22: process22(); break;
	case 23: process23(); break;
	case 24: process24(); break;
	case 25: process25(); break;
	case 26: process26(); break;
	case 27: process27(); break;
	case 28: process28(); break;
	case 29: process29(); break;
	case 30: process30(); break;
	case 31: process31(); break;
	case 32: process32(); break;
	case 33: process33(); break;
	case 34: process34(); break;
	case 35: process35(); break;
	case 36: process36(); break;
	case 37: process37(); break;
	case 38: process38(); break;
	case 39: process39(); break;
	case 40: process40(); break;
	case 41: process41(); break;
	case 42: process42(); break;
	case 43: process43(); break;
	case 44: process44(); break;
	case 45: process45(); break;
	case 46: process46(); break;
	case 47: process47(); break;
	case 48: process48(); break;
	case 49: process49(); break;
	case 50: process50(); break;
	case 51: process51(); break;
	case 52: process52(); break;
	case 53: process53(); break;
	case 54: process54(); break;
	case 55: process55(); break;
	case 56: process56(); break;
	case 57: process57(); break;
	case 58: process58(); break;
	case 59: process59(); break;
	case 60: process60(); break;
	case 61: process61(); break;
	case 62: process62(); break;
	case 63: process63(); break;
	case 64: process64(); break;
	case 65: process65(); break;
	case 66: process66(); break;
	case 67: process67(); break;
	case 68: process68(); break;
	case 69: process69(); break;
	case 70: process70(); break;
	case 71: process71(); break;
	case 72: process72(); break;
	case 73: process73(); break;
	case 74: process74(); break;
	case 75: process75(); break;
	case 76: process76(); break;
	case 77: process77(); break;
	case 78: process78(); break;
	case 79: process79(); break;
	case 80: process80(); break;
	case 81: process81(); break;
	case 82: process82(); break;
	case 83: process83(); break;
	case 84: process84(); break;
	case 85: process85(); break;
	case 86: process86(); break;
	case 87: process87(); break;
	case 88: process88(); break;
	case 89: process89(); break;
	case 90: process90(); break;
	case 91: process91(); break;
	case 92: process92(); break;
	case 93: process93(); break;
	case 94: process94(); break;
	case 95: process95(); break;
	case 96: process96(); break;
	case 97: process97(); break;
	case 98: process98(); break;
	case 99: process99(); break;
	case 100: process100(); break;
	case 101: process101(); break;
	case 102: process102(); break;
	case 103: process103(); break;
	case 104: process104(); break;
	default:error_SNL1();
	}
}
int SNL::priosity(LexType op)
{
	switch (op)
	{
	case END:return 0;
	case LT:return 1;
	case EQ:return 1;
	case PLUS:return 2;
	case MINUS:return 2;
	case TIMES:return 3;
	case DIVIDE:return 3;
	default:return -1;
	}
}