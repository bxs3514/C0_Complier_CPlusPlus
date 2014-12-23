#include "CreateSymbolList.h"

CreateSymbolList::CreateSymbolList()
{
	grammar = new GrammarAnalysis();
	error = new Error();
	init();
	WriteInSymbolList();
}

void CreateSymbolList::init()
{
	int n = -1;
	point = symbolListNo = functionNo = wordNo = blockNo = nowLevel = 0;
	block[0] = 0;
	inWordAna.open("WordAnalysis.txt");
	while(!inWordAna.eof())
	{
		int n1 = n;
		inWordAna>>n>>WordAnaRes[wordNo].type;
		if(n != n1)
		{
			if(WordAnaRes[wordNo].type == "IDSY" || WordAnaRes[wordNo].type == "QUATOSY")
			{
				inWordAna>>WordAnaRes[wordNo].no>>WordAnaRes[wordNo].wordValue>>WordAnaRes[wordNo].integerValue;
			}
			else
			{
				inWordAna>>WordAnaRes[wordNo].no>>WordAnaRes[wordNo].integerValue;
			}
			wordNo++;
		}
		
	}
	inGraAna.open("GrammarAnalysis.txt");
	f.open("SymbolList.txt");
}

//bool CreateSymbolList::CheckReDeclare()
//{
//
//}

//将常量写入符号表
void CreateSymbolList::Constant()
{
	symbolList[symbolListNo].volumn = 0;
	for(int i = grammarAnaWord.startNo; i < grammarAnaWord.endNo; i++)
	{
		if(WordAnaRes[i].type == "IDSY")
		{
			bool ifInsert = true;
			for(int j = block[blockNo]; j <= symbolListNo; j++)
			{
				if(WordAnaRes[i].wordValue == symbolList[j].name)
				{
					ifInsert = false;
					break;
				}
			}

			if(ifInsert)
			{
				symbolList[symbolListNo].name = WordAnaRes[i].wordValue;
				symbolList[symbolListNo].type = "Constant";
				symbolList[symbolListNo].intValue = WordAnaRes[i+2].integerValue;
				symbolList[symbolListNo].parameterType = 1;
				symbolList[symbolListNo].parameter = 0;
				symbolList[symbolListNo].volumn += 4;
				symbolList[symbolListNo].level = nowLevel;
				symbolListNo++;
				i+=2;
			}
			else error->error(40);
		}
	}
}

//将变量写入符号表
void CreateSymbolList::Variable()
{
	symbolList[symbolListNo].volumn = 0;
	for(int i = grammarAnaWord.startNo; i < grammarAnaWord.endNo; i++)
	{
		if(WordAnaRes[i].type == "IDSY")
		{
			bool ifInsert = true;
			for(int j = block[blockNo]; j <= symbolListNo; j++)
			{
				if(WordAnaRes[i].wordValue == symbolList[j].name)
				{
					ifInsert = false;
					break;
				}
			}

			if(ifInsert)
			{
				symbolList[symbolListNo].name = WordAnaRes[i].wordValue;
				symbolList[symbolListNo].type = "Variable";
				symbolList[symbolListNo].parameterType = 1;
				symbolList[symbolListNo].parameter = 0;
				symbolList[symbolListNo].volumn += 4;
				symbolList[symbolListNo].level = nowLevel;
				symbolListNo++;
				i++;
			}
			else error->error(41);
		}
	}
}


void CreateSymbolList::Function()
{
	int paraNum = -1;

	for(int i = grammarAnaWord.startNo; i <= grammarAnaWord.endNo; i++)
	{
		if(WordAnaRes[i].type == "IDSY") paraNum++;
	}
	if(WordAnaRes[grammarAnaWord.startNo].type == "VOIDSY")
		symbolList[symbolListNo].volumn = 4 * paraNum;
	else symbolList[symbolListNo].volumn = 4 * (paraNum + 1);

	for(int i = grammarAnaWord.startNo; i <= grammarAnaWord.endNo; i++)
	{
		if(WordAnaRes[i].type == "IDSY")
		{
			if(WordAnaRes[i+1].type == "LPARSY")
			{
				bool ifInsert = true;
				for(int j = 0; j < symbolListNo; j++)
				{
					if(WordAnaRes[i].wordValue == symbolList[j].name)
					{
						if(symbolList[j].type == "Function")
						{
							if(paraNum == symbolList[j].parameter)
							{
								ifInsert = false;
								break;
							}
						}
						else
						{
							ifInsert = false;
							break;
						}
					}
				}

				if(ifInsert)
				{
					symbolList[symbolListNo].name = WordAnaRes[i].wordValue;
					symbolList[symbolListNo].type = "Function";
					symbolList[symbolListNo].parameterType = -1;
					symbolList[symbolListNo].parameter = paraNum;
					//symbolList[symbolListNo].volumn = 4;
					symbolList[symbolListNo].level = nowLevel - 1;
					funcList[functionNo] = symbolList[symbolListNo];
					symbolListNo++;
					functionNo++;
					i++;
				}
				else error->error(42);
			}
			else
			{
				bool ifInsert = true;
				for(int j = block[blockNo]; j <= symbolListNo; j++)
				{
					if(WordAnaRes[i].wordValue == symbolList[j].name)
					{
						ifInsert = false;
						break;
					}
				}

				if(ifInsert)
				{
					symbolList[symbolListNo].name = WordAnaRes[i].wordValue;
					symbolList[symbolListNo].type = "Variable";
					symbolList[symbolListNo].parameterType = 0;
					symbolList[symbolListNo].parameter = 0;
					symbolList[symbolListNo].volumn = 4;
					symbolList[symbolListNo].level = nowLevel;
					symbolListNo++;
					i++;
				}
				else error->error(43);
			}
		}
	}
}

void CreateSymbolList::FunctionCall()
{
	int paraNum = 1;
	string temp;

	for(int i = grammarAnaWord.startNo; i < grammarAnaWord.endNo; i++)
	{
		if(WordAnaRes[i].type == "LPARSY")
		{
			if(WordAnaRes[i+1].type == "RPARSY")
			{
				paraNum = 0;
				break;
			}
		}
		else if(WordAnaRes[i].type == "COMMASY") paraNum++;
	}

	symbolList[symbolListNo].volumn = 4 * paraNum;

	for(int i = grammarAnaWord.startNo; i < grammarAnaWord.endNo; i++)
	{
		if(WordAnaRes[i].type == "IDSY") 
		{
			if(WordAnaRes[i+1].type == "LPARSY")
			{
				bool isInsert = false;
				for(int j = 0; j < functionNo; j++)
				{
					if(WordAnaRes[i].wordValue == funcList[j].name
							&& paraNum == funcList[j].parameter)
					{
						isInsert = true;
						break;
					}
				}
				if(functionNo == 0) isInsert = true;

				if(isInsert)
				{
					symbolList[symbolListNo].name = WordAnaRes[i].wordValue;
					symbolList[symbolListNo].type = "Function_Call";
					symbolList[symbolListNo].parameterType = -1;
					symbolList[symbolListNo].parameter = paraNum;
					//symbolList[symbolListNo].volumn = 4;
					symbolList[symbolListNo].level = nowLevel;
					symbolListNo++;
					i++;
				}
				else error->error(44);
			}
			else if(WordAnaRes[i].type != "COMMASY")
			{
				temp += 
				/*char temp[100];
				itoa(paraNum,temp,100);*/
				symbolList[symbolListNo].name = symbolList[symbolListNo-1].name + "Call";
				symbolList[symbolListNo].type = "Expression";
				symbolList[symbolListNo].parameterType = 1;
				symbolList[symbolListNo].parameter = 0;
				symbolList[symbolListNo].volumn = 4;
				symbolList[symbolListNo].level = nowLevel;
				symbolListNo++;
				i++;
			} 
		}
		
	}
}

void CreateSymbolList::Main()
{
	int paraNum = 0;

	for(int i = grammarAnaWord.startNo; i <= grammarAnaWord.endNo; i++)
	{
		if(WordAnaRes[i].type == "IDSY") paraNum++;
	}
	if(WordAnaRes[grammarAnaWord.startNo].type == "VOIDSY")
		symbolList[symbolListNo].volumn = 4 * paraNum;
	else symbolList[symbolListNo].volumn = 4 * (paraNum + 1);

	for(int i = grammarAnaWord.startNo; i <= grammarAnaWord.endNo; i++)
	{
		if(WordAnaRes[i].type == "MAINSY")
		{
			symbolList[symbolListNo].name = WordAnaRes[i].wordValue;
			symbolList[symbolListNo].type = "Main";
			symbolList[symbolListNo].parameterType = -1;
			symbolList[symbolListNo].parameter = paraNum;
			symbolList[symbolListNo].level = nowLevel;
			symbolListNo++;
			i++;
		}
		else if(WordAnaRes[i].type == "IDSY")
		{
			bool ifInsert = true;
			for(int j = block[blockNo]; j <= symbolListNo; j++)
			{
				if(WordAnaRes[i].wordValue == symbolList[j].name)
				{
					ifInsert = false;
					break;
				}
			}

			if(ifInsert)
			{
				symbolList[symbolListNo].name = WordAnaRes[i].wordValue;
				symbolList[symbolListNo].type = "Variable";
				symbolList[symbolListNo].parameterType = 0;
				symbolList[symbolListNo].parameter = 0;
				symbolList[symbolListNo].volumn = 4;
				symbolList[symbolListNo].level = nowLevel;
				symbolListNo++;
				i++;
			}
			else error->error(43);
			
		}
	}
}

void CreateSymbolList::Condition()
{
	symbolList[symbolListNo].name = "";
	symbolList[symbolListNo].type = "If";
	symbolList[symbolListNo].parameterType = -1;
	symbolList[symbolListNo].parameter = 0;
	symbolList[symbolListNo].volumn = 0;///
	symbolList[symbolListNo].level = nowLevel;

	for(int i = grammarAnaWord.startNo+2; i <= grammarAnaWord.endNo; i++)
	{
		///here
	}
}

void CreateSymbolList::Loop()
{

}

void CreateSymbolList::Assign()
{

}

void CreateSymbolList::Write()
{

}

void CreateSymbolList::Read()
{

}

void CreateSymbolList::Return()
{

}

//将函数声明写入符号表
void CreateSymbolList::WriteInSymbolList()
{
	int n1 = -1;
	while(!inGraAna.eof())
	{
		inGraAna>>grammarAnaWord.no;
		if(n1 != grammarAnaWord.no)
		{
			n1 = grammarAnaWord.no;
			inGraAna>>grammarAnaWord.type>>grammarAnaWord.startNo>>grammarAnaWord.endNo;

			if(grammarAnaWord.type == "Constant")
			{
				Constant();
			}
			else if(grammarAnaWord.type == "Variable")
			{
				Variable();
			}
			else if(grammarAnaWord.type == "Function")
			{
				nowLevel++;
				blockNo++;
				block[blockNo] = symbolListNo + 1;
				Function();
			}
			else if(grammarAnaWord.type == "Function_End")
			{
				nowLevel--;
			}
			else if(grammarAnaWord.type == "Function_Call")
			{
				FunctionCall();
			}
			else if(grammarAnaWord.type == "Main")
			{
				nowLevel++;
				blockNo++;
				block[blockNo] = symbolListNo + 1;
				Main();
			}
			else if(grammarAnaWord.type == "Main_End")
			{
				nowLevel--;
			}
			else if(grammarAnaWord.type == "Condition")//if//
			{

			}
			else if(grammarAnaWord.type == "Loop")
			{

			}
			else if(grammarAnaWord.type == "Assign")
			{

			}
			else if(grammarAnaWord.type == "Write")
			{

			}
			else if(grammarAnaWord.type == "Read")
			{

			}
			else if(grammarAnaWord.type == "Return")
			{

			}
			else
			{

			}
		}
	}
	f<<"No"<<"\t"<<"Name"<<"\t  "<<setiosflags(ios::left)<<setw(10)<<"Type"<<"  \t"<<setiosflags(ios::left)<<setw(15)
		<<"IntValue"<<"\t"<<"WordValue"<<"\t"<<"parameter"<<"\t"<<setiosflags(ios::left)
		<<setw(20)<<"ParameterType"<<"\t"<<"Level"<<endl;
	for(int i = 0; i < symbolListNo; i++)
	{
		f<<i<<"\t"<<symbolList[i].name<<"\t\t"<<
			setiosflags(ios::left)<<setw(15)<<symbolList[i].type<<"\t"
			<<setiosflags(ios::left)<<setw(15)<<symbolList[i].intValue<<"\t"
			<<symbolList[i].wordValue<<"\t"<<symbolList[i].parameter<<"\t\t\t"
			<<setiosflags(ios::left)<<setw(10)<<symbolList[i].parameterType<<"\t"
			<<setiosflags(ios::left)<<setw(18)<<symbolList[i].volumn<<"\t"<<symbolList[i].level<<endl;
	}
	f<<endl;
	for(int i = 0; i <= blockNo; i++)
	{
		f<<i<<"\t"<<block[i]<<"\t"<<funcList[i].name<<"\t"<<funcList[i].parameter<<endl;
	}
}


void CreateSymbolList::test()
{
	//for(int i = 0; i < wordNo; i++)
		//cout<<i<<" "<<setiosflags(ios::left)<<setw(20)<<WordAnaRes[i].type<<'\t'<<WordAnaRes[i].no<<'\t'<<WordAnaRes[i].wordValue<<'\t'<<'\t'<<WordAnaRes[i].integerValue<<endl;
	//system("pause");
}

CreateSymbolList::~CreateSymbolList()
{
	delete grammar;
	delete error;
	inWordAna.close();
	inGraAna.close();
	f.close();
}