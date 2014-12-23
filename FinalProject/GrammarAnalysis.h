#ifndef GRAMMARANALYSIS_H
#define GRAMMARANALYSIS_H

#include <iostream>
#include <fstream>
#include "WordAnalysis.h"
using namespace std;

class GrammarAnalysis
{
public:
	GrammarAnalysis();
	~GrammarAnalysis();
protected:

private:
	void init();
	void WriteIntoStateRegion();//д��ÿ����䷶Χ
	void getsym(int);
	void procedure();
	void constInst();
	void constDefi();//��������
	void integer();
	bool declarationHead();//����ͷ��
	void variableInst();
	bool functionDefi();
	void mixStatement();
	void Parameter();
	void ParameterTable();
	void mainFuction();
	void Expression();
	void Term();
	void Factor();
	bool Statement();
	bool assignStatement();
	bool conditionalStatement();
	void Condition();
	bool LoopStatement();
	bool functionCall();
	void valueTable();
	void statementList();
	bool Read();
	bool Write();
	bool Return();

	int no;
	int statementNo;//�����
	string WordList[5];
	int printNo;
	string printString[MAX_LENGTH];
	ifstream in;
	ofstream f;
	Error *error;
	Symbol WordAnaRes;
	WordAnalysis *wordAnalysis;

	int startNo;
	int endNo;
	int stateRegion[MAX_LENGTH][2];
};

#endif