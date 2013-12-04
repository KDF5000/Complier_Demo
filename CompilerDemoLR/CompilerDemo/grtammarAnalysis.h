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
	int AnalysisStack[ANALYSIS_STACK_LEN];  //分析堆栈
	int stackTop;   //堆栈顶部指针 
	char bufferToken[TOKEN_LENGTH];  //从缓冲区中取出的字符串
	int stackToken;// 从分析堆栈取出的字符
    bool  startGrammarAnalysis(const char codeBuffer[]); //开始语法分析
	Morphology  morphology;             //词法分析器，实现词法分析功能
	bool isTerminalCh(int Xcode,int teminalChTable[]);//判断是否为终结字符
	bool serachPreMatrix(int Xcode ,int Avalue,int &stackTop); 
	void pushStack(int AnalysisStack[],int &stackTop,int object);
	grammarAnalysis(void);
	~grammarAnalysis(void);
};

