/*���ܣ�������
*���ߣ��׵·� 
*ʱ�䣺2013.9.18
*/  
//#include "Morphology.h"
//#include "grtammarAnalysis.h"
#include "LRGramar.h"
#pragma once
class Complier
{
public:
	Complier(void);
	~Complier(void);
	char codeBuffer[CODE_BUTTER_LENGTH]; //����û��������Ļ�����
	char token[TOKEN_LENGTH];            //�ӻ�������ȡ�����ַ���
	//int typeCode;                        //�ַ�����������
	//int tokenPtr   ;			//tokenPtrȡ���ַ�����ָ��
	int bufferPtr;              //bufferPtr��������ָ��
	//Morphology  morphology;             //�ʷ���������ʵ�ִʷ���������
//	grammarAnalysis grammarAnalysis; //�﷨����
	LRGramar lRAnalysi;//  LR�﷨����
public:
	void inputCode();                   //�û�����code
	void startComplier();               //��ʼ����
	static void strToNumber(const char token[],double &outNumber);//�������ַ���ת��Ϊ����
};