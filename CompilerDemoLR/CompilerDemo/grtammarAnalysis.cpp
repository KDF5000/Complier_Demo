
#include "grtammarAnalysis.h"
#include <stdio.h>
#include <string.h>
#include "Complier.h"
int teminalChTable[] = {IDENTIFIER,DIGIT,PLUS,SUB,STAR,SLASH,KUOHAO_L,KUOHAO_R};
grammarAnalysis::grammarAnalysis(void)
{
}


grammarAnalysis::~grammarAnalysis(void)
{
}

bool grammarAnalysis::startGrammarAnalysis(const char codeBuffer[])
{

	int returnCode;         //每次识别字符串的code 
	int startPosition = 0;  //每次读出字符的起始位置
	morphology.setPreIsOp(true);//初始化操作符信号
	double num = 0;    //记录scanner扫描到数字的数值
	////////////////////////////////////////////////////////
	do{
		returnCode = morphology.scaner(codeBuffer,startPosition,bufferToken);
		
		if(returnCode == DIGIT)
		{
			Complier::strToNumber(bufferToken,num);
			printf("(%d,%g)\n",returnCode,num);
		}
		else if(returnCode == ERROR)
		{
			printf("('%s')不能有该文法生成！\n",bufferToken);
		}
		else if(returnCode==NOTE)
		{	
			//
		}
		else
		{
			printf("(%d,'%s')\n",returnCode,bufferToken);
		}

	}while(returnCode!=END_JINGHAO);
	////////////////////////////////////////
	startPosition=0;
	returnCode=0;
	stackTop  = 0; //指向栈顶 
	morphology.setPreIsOp(true);
	AnalysisStack[stackTop++] = END_JINGHAO;  //
	AnalysisStack[stackTop] = S_NTERMINAL;//S作为文法的其实字符
	returnCode = morphology.scaner(codeBuffer,startPosition,bufferToken);
	while(returnCode==NOTE)
	{
		returnCode = morphology.scaner(codeBuffer,startPosition,bufferToken);
	}
	//语法分析
	while(true)
	{
		//将栈顶字符取出
		stackToken = AnalysisStack[stackTop--];
		//如果stackToken是非终结符(x属于Vt)
		if(isTerminalCh(stackToken,teminalChTable))
		{
			//X=a
			if(stackToken != returnCode)
			{
				return false;
			}
			else
			{
					do
					{
						returnCode = morphology.scaner(codeBuffer,startPosition,bufferToken);
					}while(returnCode==NOTE);
			}
		}
		else
		{
			//X = '$'
			if(stackToken == END_JINGHAO)
			{
				if(stackToken == returnCode )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			// X！=‘$'
			else
			{
				if(!serachPreMatrix(stackToken,returnCode,stackTop))
				{
					return false;
				}
			}
		}
	}
}
//判断是否为终结符
bool grammarAnalysis::isTerminalCh(int Xcode,int terminalT[])
{
	for(int i=0;i<sizeof(teminalChTable)/sizeof(teminalChTable[0]);i++)
	{
		if(Xcode==teminalChTable[i])
		{
			return true;
		}
	}
	return false;
}
//查找预测矩阵
bool grammarAnalysis::serachPreMatrix(int Xcode ,int Avalue,int &stackTop)
{
	switch(Xcode)
	{
	case S_NTERMINAL:
		switch(Avalue)
		{
		case IDENTIFIER:
		case DIGIT:
		case KUOHAO_L:
			pushStack(AnalysisStack,stackTop,B_NTERMINAL);
			pushStack(AnalysisStack,stackTop,A_NTERMINAL);
			return true;
		default:
			return false;
		}
		break;
	case A_NTERMINAL:
		switch(Avalue)
		{
	    case IDENTIFIER:
		case DIGIT:
		case KUOHAO_L:
			pushStack(AnalysisStack,stackTop,D_NTERMINAL);
			pushStack(AnalysisStack,stackTop,C_NTERMINAL);
			return true;
		default:
			return false;
		}
		break;
	case B_NTERMINAL:
	    switch(Avalue)
		{
	    case PLUS:
			pushStack(AnalysisStack,stackTop,B_NTERMINAL);
			pushStack(AnalysisStack,stackTop,A_NTERMINAL);
			pushStack(AnalysisStack,stackTop,PLUS);
			return true;
		case SUB:
			pushStack(AnalysisStack,stackTop,B_NTERMINAL);
			pushStack(AnalysisStack,stackTop,A_NTERMINAL);
			pushStack(AnalysisStack,stackTop,SUB);
			return true;
		case KUOHAO_R:
		case END_JINGHAO:
			return true;
		default:
			return false;
		}
		break;
	case C_NTERMINAL:
		switch(Avalue)
		{
		case IDENTIFIER:
			pushStack(AnalysisStack,stackTop,IDENTIFIER);
			return true;
		case DIGIT:
			pushStack(AnalysisStack,stackTop,DIGIT);
			return true;
		case KUOHAO_L:
			pushStack(AnalysisStack,stackTop,KUOHAO_R);
			pushStack(AnalysisStack,stackTop,S_NTERMINAL);
			pushStack(AnalysisStack,stackTop,KUOHAO_L);
			return true;
		default:
			return false;
		}
		break;
	case D_NTERMINAL:
		switch(Avalue)
		{
		case PLUS:
		case SUB:
		case KUOHAO_R:
		case END_JINGHAO:
			return true;
		case STAR:
			pushStack(AnalysisStack,stackTop,D_NTERMINAL);
			pushStack(AnalysisStack,stackTop,C_NTERMINAL);
			pushStack(AnalysisStack,stackTop,STAR);
			return true;
		case SLASH:
			pushStack(AnalysisStack,stackTop,D_NTERMINAL);
			pushStack(AnalysisStack,stackTop,C_NTERMINAL);
			pushStack(AnalysisStack,stackTop,SLASH);
			return true;
		default:
			return false;
		}
		break;
	default:
		return false;
	}
}
//
void grammarAnalysis::pushStack(int AnalysisStack[],int &stackTop,int object)
{	
	//缺少判断堆栈是否已满
	AnalysisStack[++stackTop]= object;
}