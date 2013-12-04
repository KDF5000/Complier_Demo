
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

	int returnCode;         //ÿ��ʶ���ַ�����code 
	int startPosition = 0;  //ÿ�ζ����ַ�����ʼλ��
	morphology.setPreIsOp(true);//��ʼ���������ź�
	double num = 0;    //��¼scannerɨ�赽���ֵ���ֵ
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
			printf("('%s')�����и��ķ����ɣ�\n",bufferToken);
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
	stackTop  = 0; //ָ��ջ�� 
	morphology.setPreIsOp(true);
	AnalysisStack[stackTop++] = END_JINGHAO;  //
	AnalysisStack[stackTop] = S_NTERMINAL;//S��Ϊ�ķ�����ʵ�ַ�
	returnCode = morphology.scaner(codeBuffer,startPosition,bufferToken);
	while(returnCode==NOTE)
	{
		returnCode = morphology.scaner(codeBuffer,startPosition,bufferToken);
	}
	//�﷨����
	while(true)
	{
		//��ջ���ַ�ȡ��
		stackToken = AnalysisStack[stackTop--];
		//���stackToken�Ƿ��ս��(x����Vt)
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
			// X��=��$'
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
//�ж��Ƿ�Ϊ�ս��
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
//����Ԥ�����
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
	//ȱ���ж϶�ջ�Ƿ�����
	AnalysisStack[++stackTop]= object;
}