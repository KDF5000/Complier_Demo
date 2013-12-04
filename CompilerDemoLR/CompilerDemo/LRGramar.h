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
	//��ʼ�����﷨������
	bool  startGrammarAnalysis(const char codeBuffer[]); //��ʼ�﷨����
	Morphology morphology;  //�ʷ�������
private:
	int statusStack[STACK_MAX_LENGTH];     //ת̫״̬ջ
	int charStack[STACK_MAX_LENGTH];      //stack of characters
	int statusStackPtr;  //״̬ջ��ָ��
	int charStackPtr;   //�ַ�ջ��ָ��
	int popChar;   //�Ӷ�ջ��pop�����ַ�������
	char bufferToken[TOKEN_LENGTH];  //�ӻ�������ȡ�����ַ���

	qQuad  QuadHead[100];  //��Ԫʽ����
	int quadCount; //��¼��Ԫʽ������λ��
	int nextq;     //��¼��һ����Ԫʽ���
	int trueChainHead;//��¼����������

	int falseChain[100];//�����Ҫ�Ĳ���ļ�
	int falseChainPtr;

	char variableBuffer[100][20];//��ű��������߱�ʾ����ջ
	int variableBufferPtr;//��ű��������߱�ʾ����ջ��ָ��

	char lastOp[100][3];  //��Ų�����ջ
	int OpPtr;//ptr to the stack of op

	int doTrue[10];      //��¼do..whileѭ����do������׵�ַ
	int doTruePtr;


	int tempCount; //��ʱ�����ĸ���
	void push(int stack[],int &topPtr,int value);//ѹջ ������valueΪѹ��ָ��topPtrΪջ��ָ��
	void pop(int stack[],int &topPtr,int &token);//��ջ������tokenΪȡ����ֵ��topPtrΪջ��ָ��
	int mapPosition(int charA);//charAΪ��������ַ�������ӳ�䵽LR�������Ӧ���±�ֵ
	bool isTransferStatus(const int actionStatus);        //�ж��Ƿ�Ϊת��״̬
	bool isGuiYueStatus(const int actionStatus);  //�ж��Ƿ�Ϊ��Լ״̬
	bool doGuiYue(const int ruleNum);                 //����ruleNum��������й�Լ
	void popStackN(int stack[],int &topPtr,int numbers);//��ָ����ջ��pop��ָ������������
	bool doRules(int LeftChar,int rightNumbers); //ִ�й���
	void backPatch(int &chainHead,int nextq);//����
	void emit(char op[],char arg1[],char arg2[],char result[]);//����һ����Ԫʽ
	char* newTemp(); //����һ���µı���
	void printQuad();//��ӡ��Ԫ�����
};

