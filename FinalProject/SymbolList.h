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
	int parameterType;//0Ϊ�βΣ�1Ϊʵ�Σ�-1�ǲ���
	int parameter;//��������
	int volumn;//��С
	int level;
};

class SymbolListType
{
	~SymbolListType();
};

#endif