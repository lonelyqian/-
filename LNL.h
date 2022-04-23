#pragma once
#include <map>
#include <string>
using namespace std;
typedef enum
{
    /*薄记单词符号*/
    ENDFILE, ERROR,
    /*保留字*/
    PROGRAM, PROCEDURE, TYPE, VAR, IF,
    THEN, ELSE, FI, WHILE, DO,
    ENDWH, BEGIN, END, READ, WRITE,
    ARRAY, OF, RECORD, RETURN, INTEGER, CHAR,
    /*类型*/
    INTEGER_T, CHAR_T,
    /*多字符单词序号*/
    ID, INTC, CHARC, INTC_VAL, CHARC_VAL,
    /*特殊符号*/
    ASSIGN, EQ, LT, PLUS, MINUS,
    TIMES, DIVIDE, LPAREN, RPAREN, DOT,//÷书上是OVER
    COLON, SEMI, COMMA, LMIDPAREN, RMIDPAREN,
    UNDERRANGE,

    Program, ProgramHead, ProgramName, DeclarePart,
    TypeDec, TypeDeclaration, TypeDecList, TypeDecMore,
    TypeId, TypeName, BaseType, StructureType,//TypeName其实真正应该是TypeDef
    ArrayType, Low, Top, RecType,
    FieldDecList, FieldDecMore, IdList, IdMore,
    VarDec, VarDeclaration, VarDecList, VarDecMore,
    VarIdList, VarIdMore, ProcDec, ProcDeclaration,
    ProcDecMore, ProcName, ParamList, ParamDecList,
    ParamMore, Param, FormList, FidMore,
    ProcDecPart, ProcBody, ProgramBody, StmList,
    StmMore, Stm, AssCall, AssignmentRest,
    ConditionalStm, StmL, LoopStm, InputStm,
    InVar, OutputStm, ReturnStm, CallStmRest,
    ActParamList, ActParamMore, RelExp, OtherRelE,
    Exp, OtherTerm, Term, OtherFactor,
    Factor, Variable, VariMore, FieldVar,
    FieldVarMore, CmpOp, AddOp, MultOp
}LexType;

map<LexType, string> lexName = { {PROGRAM, "PROGRAM"},
                                  {TYPE, "TYPE"},
                                  {VAR, "VAR"},
                                  {PROCEDURE, "PROCEDURE"},
                                  {BEGIN, "BEGIN"},
                                  {END, "END"},
                                  {ARRAY, "ARRAY"},
                                  {OF, "OF"},
                                  {RECORD, "RECORD"},
                                  {IF, "IF"},
                                  {THEN, "THEN"},
                                  {ELSE, "ELSE"},
                                  {FI, "FI"},
                                  {WHILE, "WHILE"},
                                  {DO, "DO"},
                                  {ENDWH, "ENDWH"},
                                  {READ, "READ"},
                                  {WRITE, "WRITE"},
                                  {RETURN, "RETURN"},
                                  {INTEGER, "INTEGER"},
                                  {CHAR, "CHAR"},
                                  {ID, "ID"},
                                  {INTC, "INTC"},
                                  {CHARC, "CHAR"},
                                  {ASSIGN, "ASSIGN"},
                                  {EQ, "EQ"},
                                  {LT, "LT"},
                                  {PLUS, "PLUS"},
                                  {MINUS, "MINUS"},
                                  {TIMES, "TIMES"},
                                  {DIVIDE, "DIVIDE"},
                                  {LPAREN, "LPAREN"},
                                  {RPAREN, "RPAREN"},
                                  {DOT, "DOT"},
                                  {COLON, "COLON"},
                                  {SEMI, "SEMI"},
                                  {COMMA, "COMMA"},
                                  {LMIDPAREN, "LMIDPAREN"},
                                  {RMIDPAREN, "RMIDPAREN"},
                                  {UNDERRANGE, "UNDERRANGE"},
                                  {ENDFILE, "EOF"},
                                  {ERROR, "ERROR"} };
/*定义保留字数字常量MAXRESERVED为21*/
#define MAXRESERVED 21
struct Token {
    int line;
    LexType lex;
    string sem;
};