#include "WordAnalysis.h"
#include <Windows.h>

Word WordAnalysis::wordTable[31] = 
{
	{"", 0, ""},
	{"const", 1, "CONSTSY"},
	{"int", 2, "INT_DECLEARSY"},
	{"void",3, "VOIDSY"},
	{"if", 4, "IFSY"},
	{"else",5,"ELSESY"},
	{"while", 6, "WHILESY"},
	{"main", 7, "MAINSY"},
	{"return", 8, "RETURNSY"},
	{"printf", 9, "PRINTFSY"},
	{"scanf", 10, "SCANFSY"},
	//NO.1-10 are reserve words.
	{"identifier", 11, "IDSY"},//NO.11 identifier
	{"integer", 12, "INTSY"},//NO.12 integer
	{"+", 13, "PLUSSY"},
	{"-", 14, "MINUSSY"},
	{"*", 15, "STARSY"},
	{"/", 16, "DIVISY"},
	{"<", 17, "LESSERSY"},
	{"<=", 18, "LESSEY_EQUALSY"},
	{">", 19, "GREETERSY"},
	{">=", 20, "GREETER_EQUALSY"},
	{"!=", 21, "NOT_EQUALSY"},
	{"==", 22, "EQUALSU"},
	//NO.11-22 are calculate operator
	{"(", 23, "LPARSY"},
	{")", 24, "RPARSY"},
	{"{", 25, "BIG_LPARSY"},
	{"}", 26, "BIG_RPARSY"},
	{",", 27, "COMMASY"},
	{";", 28, "SEMISY"},
	{"=", 29, "ASSIGNSY"},
	//NO.23-29 are special operator
	{"\"",30, "QUATOSY"}
	//NO.30 is string operator
};

WordAnalysis::WordAnalysis()
{
	init();
	GetProcedure();
}

WordAnalysis::WordAnalysis(string wholeProcedure)
{
	init();
	this->wholeProcedure = wholeProcedure;
}

void WordAnalysis::GetProcedure()
{
	string a;
	cout << "File name:" << endl;
	cin >> a;
	ifstream in(a);
	//ifstream in("test5.c");
	if(!in.is_open())
		error->error(4);
	while(!in.eof())
	{
		in.getline(buffer,10000);
        wholeProcedure += buffer;
	}
}

void WordAnalysis::init()
{
	f.open("WordAnalysis.txt");
	//f<<"  "<<setiosflags(ios::left)<<setw(20)<<"type"<<'\t'<<"no"<<'\t'<<"wordValue"<<'\t'<<"integerValue"<<endl;
	point = no = numNo = ideNo = 0;
	readPd = new char();
	error = new Error();
	nowString = "";
	wholeProcedure = "";
}

int WordAnalysis::GetChar()
{
	point++;
	if(point < wholeProcedure.length())
		readPd = &wholeProcedure[point];
	else return 0;

	return 1;
}

bool WordAnalysis::isLetter()
{
	if((*readPd > 64 && *readPd < 91) || 
		(*readPd > 96 && *readPd < 123) || *readPd == 95)
	{
		return true;
	}
	else return false;
}

bool WordAnalysis::isBlankSpace()
{
	if((*readPd > 7 && *readPd < 14) || *readPd == 32)
	{
		return true;
	}
	else return false;
}

bool WordAnalysis::isDigit()
{
	if(*readPd > 47 && *readPd < 58)
	{
		return true;
	}
	else return false;
}

bool WordAnalysis::isPlus()
{
	if(*readPd == 43) return true;
	else return false;
}

bool WordAnalysis::isMinus()
{
	if(*readPd == 45) return true;
	else return false;
}

bool WordAnalysis::isStar()
{
	if(*readPd == 42) return true;
	else return false;
}

bool WordAnalysis::isDivi()
{
	if(*readPd == 47) return true;
	else return false;
}

bool WordAnalysis::isExcla()
{
	if(*readPd == 33) return true;
	else return false;
}

bool WordAnalysis::isEqual()
{
	if(*readPd == 61) return true;
	else return false;
}

bool WordAnalysis::isGreater()
{
	if(*readPd == 62) return true;
	else return false;
}

bool WordAnalysis::isLesser()
{
	if(*readPd == 60) return true;
	else return false;
}

bool WordAnalysis::isLpar()
{
	if(*readPd == 40) return true;
	else return false;
}

bool WordAnalysis::isBigLpar()
{
	if(*readPd == 123) return true;
	else return false;
}

bool WordAnalysis::isRpar()
{
	if(*readPd == 41) return true;
	else return false;
}

bool WordAnalysis::isBigRpar()
{
	if(*readPd == 125) return true;
	else return false;
}

bool WordAnalysis::isQuato()
{
	if(*readPd == 34) return true;
	else return false;
}

bool WordAnalysis::isComma()
{
	if(*readPd == 44) return true;
	else return false;
}

bool WordAnalysis::isSemi()
{
	if(*readPd == 59) return true;
	else return false;
}

//Judge if the word is a reserver word.
int WordAnalysis::Reserver()
{
	if(nowString == wordTable[1].name)
	{
		return wordTable[1].no;
	}

	else if(nowString == wordTable[2].name)
	{
		return wordTable[2].no;
	}

	else if(nowString == wordTable[3].name)
	{
		return wordTable[3].no;
	}

	else if(nowString == wordTable[4].name)
	{
		return wordTable[4].no;
	}

	else if(nowString == wordTable[5].name)
	{
		return wordTable[5].no;
	}

	else if(nowString == wordTable[6].name)
	{
		return wordTable[6].no;
	}

	else if(nowString == wordTable[7].name)
	{
		return wordTable[7].no;
	}

	else if(nowString == wordTable[8].name)
	{
		return wordTable[8].no;
	}

	else if(nowString == wordTable[9].name)
	{
		return wordTable[9].no;
	}

	else if(nowString == wordTable[10].name)
	{
		return wordTable[10].no;
	}
	return 0;
}

void WordAnalysis::catToken()
{
	nowString = nowString + *readPd;
}


int WordAnalysis::transNum()
{
	if(nowString[0] == 34) nowString.erase(0,1);
	int n = nowString.length();
	int tempNum = 0;

	for(int i = 0; i < n; i++)
	{
		int ten = 1;
		for(int j = 1; j < n - i; j++)
			ten *= 10;
		tempNum += (nowString[i] - '0') * ten;
	}
	return tempNum;
}

void WordAnalysis::inputSymbol()
{
	int n = symbol[no].no;
	symbol[no].type = wordTable[n].memoryCode;
	if(n == 11)
		symbol[no].wordValue = nowString;
	else if (n == 12)
		symbol[no].integerValue = transNum();
	else if (n == 30)
		symbol[no].wordValue = nowString;

	f<<no<<" "<<setiosflags(ios::left)<<setw(20)<<symbol[no].type<<'\t'<<symbol[no].no<<'\t'<<symbol[no].wordValue<<'\t'<<'\t'<<symbol[no].integerValue<<endl;
	no++;
}

void WordAnalysis::Analysis()
{
	readPd = &wholeProcedure[point];

	while(point < wholeProcedure.length())
	{
		if(isBlankSpace())
		{
			GetChar();
			continue;
		}
		else if(isLetter())
		{
			while(isLetter()||isDigit())
			{
				catToken();
				if(GetChar() == 0) break;
			}
			
			int isReserve = Reserver();
			if(isReserve == 0)
			{
				symbol[no].no = 11;
				inputSymbol();
				//identifier[ideNo] = nowString;
				//ideNo++;
			}
			else
			{
				symbol[no].no = wordTable[isReserve].no;
				inputSymbol();
			}
			//no++;
			nowString = "";

			point--;
		}
		else if(isDigit())
		{
			while(isDigit())
			{
				catToken();
				if(GetChar() == 0) break;
			}
			if(isLetter())
			{
				error->error(1);
			}
			else
			{
				symbol[no].no = 12;
				inputSymbol();
				//integer[numNo] = transNum();
				//numNo++;
			}
			//no++;
			nowString = "";

			point--;
		}
		else if(isPlus())
		{
			symbol[no].no = 13;
			inputSymbol();
		}
		else if(isMinus())
		{
			symbol[no].no = 14;
			inputSymbol();
		}
		else if(isStar())
		{
			symbol[no].no = 15;
			inputSymbol();
		}
		else if(isDivi())
		{
			GetChar();
			if(isStar())
			{
				do
				{
					if(GetChar() == 0) error->error(2);
				}while(!isStar());
				GetChar();
				if(!isDivi()) error->error(2);
			}
			else if(isDivi())
			{
				while(*readPd != '\n')
				{
					if(GetChar() == 0) break;
				}
			}
			else
			{
				point--;
				symbol[no].no = 16;
				inputSymbol();
			}
		}
		else if(isExcla())
		{
			GetChar();
			if(isEqual())
			{
				symbol[no].no = 21;
				inputSymbol();
			}
			else
			{
				error->error(0);
			}
		}
		else if(isEqual())
		{
			GetChar();
			if(isEqual())
			{
				symbol[no].no = 22;
				inputSymbol();
			}
			else
			{
				symbol[no].no = 29;
				inputSymbol();
				point--;
			}
		}
		else if(isGreater())
		{
			GetChar();
			if(isEqual())
			{
				symbol[no].no = 20;
				inputSymbol();
			}
			else
			{
				symbol[no].no = 19;
				inputSymbol();
				point--;
			}
			
		}
		else if(isLesser())
		{
			GetChar();
			if(isEqual())
			{
				symbol[no].no = 18;
				inputSymbol();
			}
			else
			{
				symbol[no].no = 17;
				inputSymbol();
				point--;
			}
		}
		else if(isLpar())
		{
			symbol[no].no = 23;
			inputSymbol();
		}
		else if(isBigLpar())
		{
			symbol[no].no = 25;
			inputSymbol();
		}
		else if(isRpar())
		{
			symbol[no].no = 24;
			inputSymbol();
		}
		else if(isBigRpar())
		{
			symbol[no].no = 26;
			inputSymbol();
		}
		else if(isQuato())
		{
			//GetChar();
			do
			{
				catToken();
				if(GetChar() == 0) error->error(3);
			}while(!isQuato());
			symbol[no].no = 30;
			inputSymbol();
		}
		else if(isComma())
		{
			symbol[no].no = 27;
			inputSymbol();
		}
		else if(isSemi())
		{
			symbol[no].no = 28;
			inputSymbol();
		}
		else error->error(0);

		GetChar();
	}
}

void WordAnalysis::run()
{
	Analysis();
	/*cout<<"Symbol: "<<endl;
	cout<<setiosflags(ios::left)<<setw(20)<<"type"<<'\t'<<"no"<<'\t'<<"wordValue"<<'\t'<<"integerValue"<<endl;
	for(int i = 0; i < no; i++)
	{
		cout<<i<<" "<<setiosflags(ios::left)<<setw(20)<<symbol[i].type<<'\t'<<symbol[i].no<<'\t'<<symbol[i].wordValue<<'\t'<<'\t'<<symbol[i].integerValue<<endl;
	}*/

	//system("pause");
}


WordAnalysis::~WordAnalysis()
{
	f.close();
	delete readPd;
}