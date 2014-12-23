#include "Error.h"

string Error::errorString ="";

string Error::error(int errorNum)
{
	switch(errorNum)
	{
		case 0:
			cout<<"Illegal character.\nError code = 0000"<<endl;
			break;
		case 1:
			cout<<"Identifier Error!Digit is not allowed at the start of an identifier.\nError code = 0001"<<endl;
			break;
		case 2:
			cout<<"Annotation Error!You forget the '*/'!\nError code = 0002"<<endl;
			break;
		case 3:
			cout<<"Lose '\"'!\nError code = 0003"<<endl;
			break;
		case 4:
			cout<<"Error opening file!\nError code = 0004"<<endl;
			break;
		//WordAnalysis error
		case 5:
			cout<<"Lose int declaration in constant declaration.\nError code = 0005"<<endl;
			break;
		case 6:
			cout<<"Lose identifier in constant declaration.\nError code = 0006"<<endl;
			break;
		case 7:
			cout<<"Lose '=' in constant declaration.(You must give a initial vaule to constant!£©\nError code = 0007"<<endl;
			break;
		case 8:
			cout<<"Lose ',' in constant declaration.\nError code = 0008"<<endl;
			break;
		case 9:
			cout<<"Lose ';' in constant declaration.\nError code = 0009"<<endl;
			break;
		case 10:
			cout<<"Lose an integer in constant declaration.\nError code = 0010"<<endl;
			break;
		case 11:
			cout<<"Lose int declaration in declaration head.\nError code = 0011"<<endl;
			break;
		case 12:
			cout<<"Identifier '"+errorString+"' is invaild in variable declaration.\nError code = 0012"<<endl;
			break;
		case 13:
			cout<<"Lose ';'.\nError code = 0013"<<endl;
			break;
		case 14:
			cout<<"Lose int or void in the function declaration.\nError code = 0014"<<endl;
			break;
		case 15:
			cout<<"Lose identifier in the function declaration.\nError code = 0015"<<endl;
			break;
		case 16:
			cout<<"Lose '(' in the function declaration.\nError code = 0016"<<endl;
			break;
		case 17:
			cout<<"Lose ')' in the function declaration.\nError code = 0017"<<endl;
			break;
		case 18:
			cout<<"Lose identify in the fuction parameter table.\nError code = 0018"<<endl;
			break;
		case 19:
			cout<<"Lose int declaration in the fuction parameter table.\nError code = 0019"<<endl;
			break;
		case 21:
			cout<<"Lose '{' in the function.\nError code = 0021"<<endl;
			break;
		case 22:
			cout<<"Lose '}' in the function.\nError code = 0022"<<endl;
			break;
		case 23:
			cout<<"Lose 'main' in main function.\nError code = 0023"<<endl;
			break;
		case 24:
			cout<<"No main function in procedure.\nError code = 0024"<<endl;
			break;
		case 25:
			cout<<"Lose expression in if statement.\nError code = 0025"<<endl;
			break;
		case 26:
			cout<<"Lose ')' in if statement.\nError code = 0026"<<endl;
			break;
		case 27:
			cout<<"Lose a statement in if statement.\nError code = 0027"<<endl;
			break;
		case 28:
			cout<<"Lose relational operator in the condition of if statement.\nError code = 0028"<<endl;
			break;
		case 29:
			cout<<"Condition grammar error in if statement.\nError code = 0029"<<endl;
			break;
		case 30:
			cout<<"Lose '(' in if statement.\nError code = 0030"<<endl;
			break;
		case 31:
			cout<<"Lose '=' in if statement.\nError code = 0031"<<endl;
			break;
		case 32:
			cout<<"Station grammar error in if statement.\nError code = 0032"<<endl;
			break;
		case 33:
			cout<<"Lose '(' in the declaration of loop statement.\nError code = 0033"<<endl;
			break;
		case 34:
			cout<<"Lose ')' in the declaration of loop statement.\nError code = 0034"<<endl;
			break;
		case 35:
			cout<<"Lose statement in the loop statement.\nError code = 0035"<<endl;
			break;
		case 36:
			cout<<"Lose '(' in the write statement.\nError code = 0036"<<endl;
			break;
		case 37:
			cout<<"Lose ',' in the write statement.\nError code = 0037"<<endl;
			break;
		case 38:
			cout<<"Lose ')' in the write statement.\nError code = 0038"<<endl;
			break;
		case 39:
			cout<<"Lose ')' in the return statement.\nError code = 0039"<<endl;
			break;
		case 40:
			cout<<"Re-declarate a constant.\nError code = 0040"<<endl;
			break;
		case 41:
			cout<<"Re-declarate a variable.\nError code = 0041"<<endl;
			break;
		case 42:
			cout<<"Re-declarate a function.\nError code = 0042"<<endl;
			break;
		case 43:
			cout<<"Re-declarate a formal parameter.\nError code = 0043"<<endl;
			break;

		default:
			cout<<"The "<<errorNum<<" error!"<<endl;
			break;
	}
	system("pause");
	exit(1);
}

Error::Error()
{

}

void Error::getErrorMes(string e)
{
	this->errorString = e;
}

Error::~Error()
{

}