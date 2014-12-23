//#include "GrammarAnalysis.h"
#include "CreateSymbolList.h"

int main()
{
	/*WordAnalysis *wordAnalysis = new WordAnalysis();
	wordAnalysis->run();
	system("pause");*/
	//GrammarAnalysis *grammar = new GrammarAnalysis();
	
	while (1) 
	{
		CreateSymbolList *create = new CreateSymbolList();
		create->test();
		//delete(create);
	}
}