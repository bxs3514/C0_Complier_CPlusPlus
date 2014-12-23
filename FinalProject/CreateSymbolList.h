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
	SymbolList funcList[MAX_LENGTH];//�������൱�ڷ��ű���ֱ�
	ifstream inWordAna;//����ʷ��������
	ifstream inGraAna;//�����﷨�������
	ofstream f;//д����ű�

	GrammarAnalysis *grammar;
	Error *error;
};

#endif