#pragma once
#include "common.h"
#include "Morphology.h"
#define S_NTERMINAL     32
#define A_NTERMINAL     33 
#define B_NTERMINAL     34 
#define C_NTERMINAL     35 
#define D_NTERMINAL     36



class grammarAnalysis
{
public:
	int AnalysisStack[ANALYSIS_STACK_LEN];  //������ջ
	int stackTop;   //��ջ����ָ�� 
	char bufferToken[TOKEN_LENGTH];  //�ӻ�������ȡ�����ַ���
	int stackToken;// �ӷ�����ջȡ�����ַ�
    bool  startGrammarAnalysis(const char codeBuffer[]); //��ʼ�﷨����
	Morphology  morphology;             //�ʷ���������ʵ�ִʷ���������
	bool isTerminalCh(int Xcode,int teminalChTable[]);//�ж��Ƿ�Ϊ�ս��ַ�
	bool serachPreMatrix(int Xcode ,int Avalue,int &stackTop); 
	void pushStack(int AnalysisStack[],int &stackTop,int object);
	grammarAnalysis(void);
	~grammarAnalysis(void);
};

