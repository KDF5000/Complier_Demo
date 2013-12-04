#pragma once
#include "LRSource.h"
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "common.h"
#include "Morphology.h"
class LRGramar
{
public:
	LRGramar(void);
	~LRGramar(void);
	//开始进行语法分析；
	bool  startGrammarAnalysis(const char codeBuffer[]); //开始语法分析
	Morphology morphology;  //词法分析器
private:
	int statusStack[STACK_MAX_LENGTH];     //转太状态栈
	int charStack[STACK_MAX_LENGTH];      //stack of characters
	int statusStackPtr;  //状态栈顶指针
	int charStackPtr;   //字符栈顶指针
	int popChar;   //从堆栈中pop出的字符缓冲区
	char bufferToken[TOKEN_LENGTH];  //从缓冲区中取出的字符串

	qQuad  QuadHead[100];  //四元式数组
	int quadCount; //记录四元式数组存放位置
	int nextq;     //记录下一个四元式标号
	int trueChainHead;//记录真链的链首

	int falseChain[100];//存放需要的补充的假
	int falseChainPtr;

	char variableBuffer[100][20];//存放变量名或者标示符的栈
	int variableBufferPtr;//存放变量名或者标示符的栈的指针

	char lastOp[100][3];  //存放操作符栈
	int OpPtr;//ptr to the stack of op

	int doTrue[10];      //记录do..while循环中do后面的首地址
	int doTruePtr;


	int tempCount; //临时变量的个数
	void push(int stack[],int &topPtr,int value);//压栈 操作，value为压入指，topPtr为栈顶指针
	void pop(int stack[],int &topPtr,int &token);//出栈操作，token为取出的值，topPtr为栈顶指针
	int mapPosition(int charA);//charA为读入的中字符，将其映射到LR分析表对应的下标值
	bool isTransferStatus(const int actionStatus);        //判断是否为转移状态
	bool isGuiYueStatus(const int actionStatus);  //判断是否为规约状态
	bool doGuiYue(const int ruleNum);                 //按照ruleNum条规则进行规约
	void popStackN(int stack[],int &topPtr,int numbers);//从指定堆栈中pop出指定个数的数据
	bool doRules(int LeftChar,int rightNumbers); //执行规则
	void backPatch(int &chainHead,int nextq);//回填
	void emit(char op[],char arg1[],char arg2[],char result[]);//产生一个四元式
	char* newTemp(); //创建一个新的变量
	void printQuad();//打印四元组队列
};

