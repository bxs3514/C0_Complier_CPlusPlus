#include "GrammarAnalysis.h"

GrammarAnalysis::GrammarAnalysis()
{
	init();
	in.open("WordAnalysis.txt");
	if(!in.is_open())
		error->error(4);
	error = new Error();
	wordAnalysis = new WordAnalysis();
	wordAnalysis -> run();
	f.open("GrammarAnalysis.txt");

	procedure();
	//system("pause");
}

void GrammarAnalysis::init()
{
	printNo = statementNo = startNo = 0;
}

void GrammarAnalysis::WriteIntoStateRegion()
{
	endNo = no;
	stateRegion[statementNo][0] = startNo;
	stateRegion[statementNo][1] = endNo;
}

//Get symbol from the result of word analysis
void GrammarAnalysis::getsym(int readNum)
{
	for(int i = 0; i < 5; i++) WordList[i] = "";
	if(in.eof())
	{
		for(int i = 0; i < 5; i++) WordList[i] = "";
		return;
	}
	else
	{
		for(int i = 0; i < readNum; i++)
		{
			int n1 = no;
			in>>no>>WordAnaRes.type;
			if(no != n1)
			{
				if(WordAnaRes.type == "IDSY" || WordAnaRes.type == "QUATOSY")
				{
					//if(WordAnaRes.wordValue != "")
						in>>WordAnaRes.no>>WordAnaRes.wordValue>>WordAnaRes.integerValue;
					//else
						//in>>WordAnaRes.no>>WordAnaRes.integerValue;
				}
				else
				{
					in>>WordAnaRes.no>>WordAnaRes.integerValue;
					WordAnaRes.wordValue = "";
				}
				WordList[i] = WordAnaRes.type;
				//cout<<WordList[i]<<endl;
			}
		}
		
	}
}


//������ ::=  ��������˵�����֣�����������˵�����֣��������������岿�֣�������������
void GrammarAnalysis::procedure()
{
	getsym(1);
	constInst();
	variableInst();
	while(functionDefi());
	mainFuction();
}
//������˵�����֣�  ::=  const ���������壾��,���������壾��;
void GrammarAnalysis::constInst()
{
	//while(WordList[0] != "SEMISY")  getsym(1);
	if(WordList[0] == "CONSTSY")
	{
		startNo = no;
		getsym(1);
		//if(WordList[0] == "INT_DECLEARSY")
		//{
		if(WordList[0] == "INT_DECLEARSY")
			getsym(1);

		constDefi();
		while(WordList[0] == "COMMASY")
		{
			if(WordList[0] != "COMMASY")
			{
				error->error(8);
				break;
			}
			getsym(1);
			constDefi();
		}

		if(WordList[0] != "SEMISY") error->error(9);
		else
		{
			WriteIntoStateRegion();
			cout<<"This is a constant."<<endl;
			f<<statementNo<<"\tConstant\t"<<startNo<<"\t"<<endNo<<endl;
			//startNo = endNo + 1;
			statementNo++;
			getsym(1);
		}

		//}
		//else error->error(5);
	}
}
//���������壾  ::=  ����ʶ��������������
void GrammarAnalysis::constDefi()
{
	if(WordList[0] == "IDSY")
	{
		getsym(1);
		if(WordList[0] == "ASSIGNSY")
		{
			getsym(1);
			integer();
		}
		else error->error(7);
	}
	else error->error(6);
	//getsym(2);
}
//�������� ::=  �������������������֣��������֣�������
void GrammarAnalysis::integer()
{
	if(WordList[0] != "INTSY")
		 error->error(10);
	getsym(1);
	while(WordList[0] == "PLUSSY" || WordList[0] == "MINUSSY")
	{
		getsym(1);
		if(WordList[0] == "INTSY") getsym(1);
		else error->error(10);
	}
}
//������ͷ���� ::=  int������ʶ���� 
bool GrammarAnalysis::declarationHead()
{
	if(WordList[0] == "INT_DECLEARSY")
	{
		startNo = no;
		getsym(1);
		if(WordList[0] == "IDSY")
		{
			
		}
		else if(WordList[0] == "MAINSY") return false;
		else error->error(12);

		getsym(1);
		return true;
	}
	else if(WordList[0] == "IDSY")
		error->error(11);
	return false;
}

//������˵�����֣� ::=  ������ͷ������������ʶ��������
void GrammarAnalysis::variableInst()
{
	//while(WordList[0] != "SEMISY")  getsym(1);
	if(declarationHead())
	{
		while(WordList[0] == "COMMASY")
		{
			getsym(1);
			if(WordList[0] != "IDSY") 
			{
				error->getErrorMes((wordAnalysis->wordTable[WordAnaRes.no]).name);
				error->error(12);
			}
			
			getsym(1);
		}
		if(WordList[0] == "LPARSY")
			return;
		if(WordList[0] != "SEMISY") error->error(13);
		else
		{
			WriteIntoStateRegion();
			cout<<"This is the variable instruction."<<endl;
			f<<statementNo<<"\tVariable\t"<<startNo<<"\t"<<endNo<<endl;
			//startNo = endNo + 1;
			statementNo++;
			getsym(1);
		}
	}
}
//���������岿�֣� ::=  ��������ͷ������void ����ʶ����������������������䣾
bool GrammarAnalysis::functionDefi()
{
	bool ifFun = false;
	//while(WordList[0] != "SEMISY")  getsym(1);
	if(WordList[1] == "")
	{
		if(WordList[0] == "INT_DECLEARSY")
		{
			if(declarationHead()) ifFun = true;
			else return false;
		}
		else if(WordList[0] == "VOIDSY")
		{
			startNo = no;
			getsym(1);
			if(WordList[0] == "IDSY")
			{
				ifFun = true;
				getsym(1);
			}
			else if(WordList[0] == "MAINSY") return false;
			else error->error(15);
		}
		else if(WordList[0] == "LPARSY") ifFun = true;
		else if(WordList[0] == "MAINSY") return false;
		else error->error(14);
	}
	else
	{
		if((WordList[0] == "INT_DECLEARSY" && WordList[1] == "IDSY")
		||WordList[0] == "VOIDSY" && WordList[1] == "IDSY")
		{
			startNo = no;
			ifFun = true;
			getsym(1);
		}
		else return false;
	}

	if(ifFun)
	{
		Parameter();
		
		WriteIntoStateRegion();
		cout<<"This is the declaration of a function"<<endl;
		f<<statementNo<<"\tFunction\t"<<startNo<<"\t"<<endNo-1<<endl;
		//startNo = endNo + 1;
		statementNo++;
		mixStatement();

		endNo = no;
		cout<<"This is the end of function."<<endl;
		f<<statementNo<<"\tFunction_End\t"<<endNo<<"\t"<<endNo<<endl;
		statementNo++;
		getsym(2);
		return true;
	}

}

//�������� ::=  ��(������������)��
void GrammarAnalysis::Parameter()
{
	if(WordList[0] == "LPARSY")
	{
		getsym(1);
		ParameterTable();
		if(WordList[0] != "RPARSY")
			error->error(17);
		else
			getsym(1);
	}
	else error->error(16);
	
}

//�������� ::=  int ����ʶ��������int ����ʶ����} | ��
void GrammarAnalysis::ParameterTable()
{
	if(WordList[0] == "INT_DECLEARSY")
	{
		getsym(1);
		if(WordList[0] == "IDSY")
		{
			getsym(1);
			while(WordList[0] == "COMMASY")
			{
				getsym(2);
				if(WordList[0] == "INT_DECLEARSY")
				{
					if(WordList[1] == "IDSY")
						getsym(1);
					else error->error(18);
				}
				else error->error(19);
			}
		}
		else error->error(18);
	}
}

//��������䣾 ::=  ��{����������˵�����֣�����������˵�����֣�����������У���}��
void GrammarAnalysis::mixStatement()
{
	if(WordList[0] == "BIG_LPARSY")
	{
		getsym(1);
		if(WordList[0] != "IDSY")
		{
			constInst();
			variableInst();
		}
		statementList();
		if(WordList[0] != "BIG_RPARSY") 
			error->error(22);
	}
	else error->error(21);
}

//���������� ::=  ( void ��int ) main ����������������䣾
void GrammarAnalysis::mainFuction()
{
	//while(WordList[0] != "SEMISY")  getsym(1);
	startNo = no - 1;
	if(WordList[0] == "INT_DECLEARSY" || WordList[0] == "VOIDSY")
	{
		if(WordList[1] == "MAINSY")
		{
			getsym(1);
			Parameter();
			
			WriteIntoStateRegion();
			cout<<"This is the declaration of the main function."<<endl;
			f<<statementNo<<"\tMain\t"<<startNo<<"\t"<<endNo-1<<endl;
			//startNo = endNo + 1;
			statementNo++;
			mixStatement();

			endNo = no;
			cout<<"This is the end of main function."<<endl;
			f<<statementNo<<"\tMain_End\t"<<endNo<<"\t"<<endNo<<endl;
			statementNo++;
			getsym(1);
		}
		else error->error(23);
	}
	else if(WordList[0] == "MAINSY" && WordList[1] == "")
	{
		//startNo = no - 1;
		getsym(1);
		Parameter();
		
		WriteIntoStateRegion();
		cout<<"This is the declaration of the main function."<<endl;
		f<<statementNo<<"\tMain\t"<<startNo<<"\t"<<endNo - 1<<endl;
		//startNo = endNo + 1;
		statementNo++;
		mixStatement();

		endNo = no;
		cout<<"This is the end of main function."<<endl;
		f<<statementNo<<"\tMain_End\t"<<endNo<<"\t"<<endNo<<endl;
		statementNo++;
		getsym(1);
	}
	else 
	{
		if(WordList[0] == "BIG_RPARSY") error->error(24);

		if(WordList[0] != "INT_DECLEARSY" && WordList[0] != "VOIDSY") error->error(14);
		else error->error(23);
	}

}

//�����ʽ�� ::=  ������������������ӷ�������������
void GrammarAnalysis::Expression()
{
	if(WordList[0] == "PLUSSY" || WordList[0] == "MINUSSY")
		getsym(1);
	Term();
	while(WordList[0] == "PLUSSY" || WordList[0] == "MINUSSY")
	{
		getsym(1);
		Term();
	}

	//getsym(1);
}

//��� ::=  �����ӣ�{���˷�������������ӣ�}
void GrammarAnalysis::Term()
{
	Factor();
	while(WordList[0] == "STARSY" || WordList[0] == "DIVISY")
	{
		getsym(1);
		Factor();
	}
}

//�����ӣ� ::=  ����ʶ�����������������ʽ��������������������������������䣾
void GrammarAnalysis::Factor()
{
	if(WordList[0] == "INTSY")
	{
		getsym(1);
		return;
	}
	else if(WordList[0] == "LPARSY")
	{
		getsym(1);
		Expression();
		if(WordList[0] == "RPARSY")
		{
			getsym(1);
			return;
		}
		else error->error(26);
	}
	else if(WordList[0] == "IDSY")
	{
		getsym(1);
		//if(WordAnaRes.no > 12 && WordAnaRes.no <23) return;
		if(WordList[0] == "LPARSY")
			functionCall();
		return;
	}
	else error->error(29);
}

/*����䣾::=& nbsp; ��������䣾����ѭ����䣾����{��<�������>��}����������������䣾;������ֵ��䣾; | <�������>;
��������䣾;����д��䣾;�����գ�*/
bool GrammarAnalysis::Statement()
{
	//�ж��Ƿ��﷨��ȷ�������ж��Ƿ��Ǹ����
	if(WordList[0] == "BIG_RPARSY") return false;
	else if(conditionalStatement()) return true;
	else if(LoopStatement()) return true;

	else if(WordList[0] == "BIG_LPARSY")
	{
		getsym(1);
		statementList();
		if(WordList[0] != "BIG_RPARSY") error->error(22);
		else 
		{
			getsym(1);
			return true;
		}
	}
	else if(functionCall()) return true;
	else if(assignStatement()) return true;
	else if(Return()) return true;
	else if(Read()) return true;
	else if(Write()) return true;
	else 
	{
		if(WordList[0] == "SEMISY")
		{
			getsym(1);
			return false;
		}
		else error->error(32);
		
	}
}

//����ֵ��䣾 ::=  ����ʶ�����������ʽ��;
bool GrammarAnalysis::assignStatement()
{
	if(WordList[0] == "IDSY")
	{
		startNo = no - 1;
		if(WordList[1] == "ASSIGNSY")
		{
			getsym(1);
			Expression();
			if(WordList[0] == "SEMISY")
			{
				WriteIntoStateRegion();
				cout<<"This is a assign statement."<<endl;
				f<<statementNo<<"\tAssign\t"<<startNo<<"\t"<<endNo<<endl;
				//startNo = endNo + 1;
				statementNo++;
				getsym(1);
				return true;
			}
			else error->error(13);
		}
		else
		{
			getsym(1);
			if(WordList[0] == "ASSIGNSY")
			{
				getsym(1);
				Expression();
				if(WordList[0] == "SEMISY")
				{
					WriteIntoStateRegion();
					cout<<"This is a assign statement."<<endl;
					f<<statementNo<<"\tAssign\t"<<startNo<<"\t"<<endNo<<endl;
					//startNo = endNo + 1;
					statementNo++;
					getsym(1);
					return true;
				}
				else error->error(13);
			}
			else error->error(31);
		}
	}
	return false;
}

//��������䣾 ::=  if������������������������䣾��else����䣾��
bool GrammarAnalysis::conditionalStatement()
{
	if(WordList[0] == "IFSY")
	{
		startNo = no;
		getsym(1);
		if(WordList[0] == "LPARSY")
		{
			getsym(1);
			Condition();
			if(WordList[0] == "RPARSY") 
			{
				WriteIntoStateRegion();
				cout<<"This is the condition(if) statement."<<endl;
				f<<statementNo<<"\tCondition\t"<<startNo<<"\t"<<endNo<<endl;
				//startNo = endNo + 1;
				statementNo++;
				getsym(1);
				if(Statement())
				{
					if(WordList[0] == "ELSESY")
					{
						/*endNo = no;
						f<<statementNo<<"\tElse\t"<<endNo<<"\t"<<endNo<<endl;
						statementNo++;*/
						getsym(1);
						if(!Statement()) error->error(27);
						else
						{
							endNo = no;
							cout<<"This is the end of condition(if) statement."<<endl;
							f<<statementNo<<"\tEndif\t"<<endNo-1<<"\t"<<endNo-1<<endl;
							statementNo++;
							return true;
						}
					}
					else
					{
						endNo = no;
						cout<<"This is the end of condition(if) statement."<<endl;
						f<<statementNo<<"\tEndif\t"<<endNo-1<<"\t"<<endNo-1<<endl;
						statementNo++;
						return true;
					}
					
				}
				else error->error(27);
			}
			else error->error(26);
		}
		else error->error(25);
	}
	return false;
}

//�������� ::=  �����ʽ������ϵ������������ʽ���������ʽ��
void GrammarAnalysis::Condition()
{
	Expression();
	if(WordList[0] == "RPARSY") return;//�޲�������
	if(WordAnaRes.no > 16 && WordAnaRes.no < 23)
	{
		getsym(1);
		Expression();
	}
	
	else error->error(28);
}

//��ѭ����䣾 ::=  while������������������������䣾
bool GrammarAnalysis::LoopStatement()
{
	if(WordList[0] == "WHILESY")
	{
		startNo = no;
		getsym(1);
		if(WordList[0] == "LPARSY")
		{
			getsym(1);
			Condition();
			if(WordList[0] == "RPARSY")
			{
				WriteIntoStateRegion();
				cout<<"This is a loop statement."<<endl;
				f<<statementNo<<"\tLoop\t"<<startNo<<"\t"<<endNo<<endl;
				//startNo = endNo + 1;
				statementNo++;
				getsym(1);
				if(Statement())
				{
					endNo = no;
					cout<<"This is the end of loop statement."<<endl;
					f<<statementNo<<"\tEndLoop\t"<<endNo-1<<"\t"<<endNo-1<<endl;
					statementNo++;
					return true;
				}
				else error->error(35);
			}
			else error->error(34);
		}
		else error->error(33);
	}
	else return false;
}

//������������䣾 ::=  ����ʶ������������ֵ������������
bool GrammarAnalysis::functionCall()
{
	if(WordList[0] == "IDSY")
	{
		startNo = no;
		getsym(1);
		if(WordList[0] == "LPARSY")
		{
			getsym(1);
			if(WordList[0] != "RPARSY")
				valueTable();

			if(WordList[0] == "RPARSY")//valueTable��ɺ����ж�')'
			{
				WriteIntoStateRegion();
				getsym(1);
				cout<<"This is the function call."<<endl;
				f<<statementNo<<"\tFunction_Call\t"<<startNo<<"\t"<<endNo<<endl;
				statementNo++;
				return true;
			}
			else
			{
				error->error(26);
				//return false;
			}
		}
		else if(WordList[0] == "ASSIGNSY")
		{
			WordList[0] = "IDSY";
			WordList[1] = "ASSIGNSY";
			if(assignStatement())
				return true;//��Statement��������
			return false;//�����﷨
		}
		else error->error(30);
	}
	//else error->error(0);//
	return false;
}

//��ֵ������ ::=  �����ʽ�����������ʽ���������գ�
void GrammarAnalysis::valueTable()
{
	Expression();

	while(WordList[0] == "COMMASY")
	{
		getsym(1);
		Expression();
	}
}

//��������У� ::=  ����䣾������䣾��
void GrammarAnalysis::statementList()
{
	while(Statement());
}

//������䣾 ::=  scanf��(������ʶ����������
bool GrammarAnalysis::Read()
{
	if(WordList[0] == "SCANFSY")
	{
		startNo = no;
		getsym(4);
		if(WordList[0] == "LPARSY")
		{
			if(WordList[1] == "IDSY")
			{
				if(WordList[2] == "RPARSY")
				{
					if(WordList[3] == "SEMISY")
					{
						WriteIntoStateRegion();
						cout<<"This is a read statement."<<endl;
						f<<statementNo<<"\tRead\t"<<startNo<<"\t"<<endNo<<endl;
						//startNo = endNo + 1;
						statementNo++;
						getsym(1);
						return true;
					}
					else error->error(13);
				}
				else error->error(0);
			}
			else error->error(0);
		}
		else error->error(0);
	}
	return false;
}

//��д��䣾 ::=  printf��(��[<�ַ���>,][�����ʽ ��]������
bool GrammarAnalysis::Write()
{
	if(WordList[0] == "PRINTFSY")
	{
		startNo = no;
		getsym(1);
		if(WordList[0] == "LPARSY")
		{
			getsym(1);
			if(WordList[0] == "QUATOSY")
			{
				printNo++;
				printString[printNo] = WordAnaRes.wordValue.erase(0,1);//�������"ȥ��
				getsym(1);
				if(WordList[0] == "COMMASY")
				{
					getsym(1);
					Expression();
					if(WordList[0] == "RPARSY")
					{
						WriteIntoStateRegion();
						cout<<"This is a write statement."<<endl;
						f<<statementNo<<"\tWrite\t"<<startNo<<"\t"<<endNo<<endl;
						//startNo = endNo + 1;
						statementNo++;
						getsym(1);
						if(WordList[0] == "SEMISY") getsym(1);
						return true;
					}
					else error->error(38);
				}
				else error->error(37);
			}
			else if(WordList[0] == "RPARSY") 
			{
				WriteIntoStateRegion();
				cout<<"This is a write statement."<<endl;
				f<<statementNo<<"\tWrite\t"<<startNo<<"\t"<<endNo<<endl;
				//startNo = endNo + 1;
				statementNo++;
				getsym(1);
				return true;
			}
			else 
			{
				Expression();
				if(WordList[0] == "RPARSY")
				{
					WriteIntoStateRegion();
					cout<<"This is a write statement."<<endl;
					f<<statementNo<<"\tWrite\t"<<startNo<<"\t"<<endNo<<endl;
					//startNo = endNo + 1;
					//statementNo++;
					getsym(1);
					if(WordList[0] == "SEMISY") getsym(1);
					return true;
				}
			}
		}
		else error->error(36);
	}
	else return false;
}

//��������䣾 ::=  return [ ��(�������ʽ����)�� ] 
bool GrammarAnalysis::Return()
{
	if(WordList[0] == "RETURNSY")
	{
		startNo = no;
		getsym(1);
		if(WordList[0] == "LPARSY")
		{
			getsym(1);
			Expression();

			if(WordList[0] == "RPARSY")
			{
				WriteIntoStateRegion();
				cout<<"This is a return statement."<<endl;
				f<<statementNo<<"\tReturn\t"<<startNo<<"\t"<<endNo<<endl;
				//startNo = endNo + 1;
				statementNo++;
				getsym(1);
				return true;
			}
			else error->error(39);
		}
		else
		{
			WriteIntoStateRegion();
			cout<<"This is a return statement."<<endl;
			f<<statementNo<<"\tReturn\t"<<startNo<<"\t"<<startNo<<endl;
			//startNo = endNo + 1;
			statementNo++;
			return true;
		}
	}
	else return false;
}

GrammarAnalysis::~GrammarAnalysis()
{
	in.close();
	f.close();
	delete error;
	delete wordAnalysis;
}