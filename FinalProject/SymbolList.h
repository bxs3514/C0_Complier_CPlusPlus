#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

#include<string>
using namespace std;

struct Word
{
	string name;
	int no;
	string memoryCode;
};

struct Symbol
{
	string type;
	int no;
	int integerValue;
	string wordValue;
};

struct GrammarAnaWord
{
	int no;
	string type;
	int startNo;
	int endNo;
};

typedef struct SymbolList
{
	string name;
	string type;
	int intValue;
	string wordValue;
	int parameterType;//0为形参，1为实参，-1非参数
	int parameter;//参数个数
	int volumn;//大小
	int level;
};

class SymbolListType
{
	~SymbolListType();
};

#endif