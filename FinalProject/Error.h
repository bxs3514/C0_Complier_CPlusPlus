#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Error
{
public:
	Error();
	string error(int);
	void getErrorMes(string);
	~Error();
private:
	static string errorString;
	ofstream f;
};

#endif