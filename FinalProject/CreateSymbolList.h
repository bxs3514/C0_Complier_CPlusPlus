#ifndef CREATESYMBOLLIST_H
#define CREATESYMBOLLIST_H

#include <iostream>
#include <fstream>
#include <string>
#include "Error.h"
#include "SymbolList.h"
#include "GrammarAnalysis.h"
using namespace std;

#define MAX_LENGTH 100000

class CreateSymbolList
{
public:
	CreateSymbolList();
	void test();
	~CreateSymbolList();
protected:

private:
	void init();
	void WriteInSymbolList();
	void Constant();
	void Variable();
	void Function();
	void FunctionCall();
	void Main();
	void Condition();
	void Loop();
	void Assign();
	void Write();
	void Read();
	void Return();
	//bool CheckReDeclare();

	int point;
	int symbolListNo;
	int functionNo;
	int wordNo;
	int blockNo;
	int block[MAX_LENGTH];
	int nowLevel;
	Symbol WordAnaRes[MAX_LENGTH];
	GrammarAnaWord grammarAnaWord;
	SymbolList symbolList[MAX_LENGTH];
	SymbolList funcList[MAX_LENGTH];//函数表，相当于符号表的字表
	ifstream inWordAna;//读入词法分析结果
	ifstream inGraAna;//读入语法分析结果
	ofstream f;//写入符号表

	GrammarAnalysis *grammar;
	Error *error;
};

#endif