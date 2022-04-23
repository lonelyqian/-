#pragma once
#include <map>
#include <string>
using namespace std;
typedef enum
{
    /*���ǵ��ʷ���*/
    ENDFILE, ERROR,
    /*������*/
    PROGRAM, PROCEDURE, TYPE, VAR, IF,
    THEN, ELSE, FI, WHILE, DO,
    ENDWH, BEGIN, END, READ, WRITE,
    ARRAY, OF, RECORD, RETURN, INTEGER, CHAR,
    /*����*/
    INTEGER_T, CHAR_T,
    /*���ַ��������*/
    ID, INTC, CHARC, INTC_VAL, CHARC_VAL,
    /*�������*/
    ASSIGN, EQ, LT, PLUS, MINUS,
    TIMES, DIVIDE, LPAREN, RPAREN, DOT,//��������OVER
    COLON, SEMI, COMMA, LMIDPAREN, RMIDPAREN,
    UNDERRANGE,

    Program, ProgramHead, ProgramName, DeclarePart,
    TypeDec, TypeDeclaration, TypeDecList, TypeDecMore,
    TypeId, TypeName, BaseType, StructureType,//TypeName��ʵ����Ӧ����TypeDef
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
/*���屣�������ֳ���MAXRESERVEDΪ21*/
#define MAXRESERVED 21
struct Token {
    int line;
    LexType lex;
    string sem;
};