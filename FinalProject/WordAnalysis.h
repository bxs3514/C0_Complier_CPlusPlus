#ifndef WORDANALYSIS_H
#define WORDANALYSIS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include "SymbolList.h"
#include "Error.h"
using namespace std;

#define MAX_LENGTH 100000

class WordAnalysis
{
public:
	WordAnalysis();
	WordAnalysis(string);
	void GetProcedure();
	int GetChar();
	void ReturnString(string);
	int Reserver();
	void run();
	int transNum();
	void Analysis();
	//void error(int);
	~WordAnalysis();
	static Word wordTable[31];
protected:
	
private:
	void init();
	void catToken();
	void inputSymbol();
	bool isBlankSpace();//空格，回车，换行
	bool isLetter();
	bool isDigit();
	bool isPlus();
	bool isMinus();
	bool isStar();//*
	bool isDivi();
	bool isExcla();//!
	bool isEqual();//=
	bool isGreater();//>
	bool isLesser();//<
	bool isLpar();//(
	bool isBigLpar();//{
	bool isRpar();//)
	bool isBigRpar();//}
	bool isQuato();//"
	bool isComma();//,
	bool isSemi();//;
	
	char *readPd;
	char buffer[MAX_LENGTH];
	unsigned int point;
	int no;
	int numNo;
	int ideNo;
	string nowString;
	string wholeProcedure;
	ofstream f;
	Symbol symbol[MAX_LENGTH];
	Error *error;
};

#endif