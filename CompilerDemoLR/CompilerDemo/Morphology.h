/*
*����:ʵ�ִʷ���������
*ʱ�䣺2013.9.28
*���ߣ��׵·�
*/
#include "common.h"
#pragma once
class Morphology
{
public:
	Morphology(void);
	~Morphology(void);

	//char *keyWordTable[KEYWORD_NUMBER];
	//ɨ����뻺����,���������ַ����Ĵ��룬�ַ����������ֱ�����token������
	int scaner(const char codeBuffer[],int &startPosition,char token[]); 
	bool isBlank(const char ch);//�ж��Ƿ�Ϊ�ո���ַ�
	
	static bool isLetter(const char ch);  //�ж������ַ��Ƿ�Ϊ��ĸ
	static bool isDigi(const char ch);    //�ж������ַ��Ƿ�Ϊ����
	int getTypeCode(const char token[]);  //��ȡ�ַ�����Ӧ��code
	bool judgeEe(char ch,const char codeBuffer[],int &startPosition,char token[],int &m);//����E/eʱ���к�����ж�
	void setPreIsOp(bool isPreOP);   //ǰһ���ַ����Ƿ�Ϊ�����
	int getRowsCout();
	int getColCout();
private:
	bool preIsOp;   //ǰһ���ַ����Ƿ�Ϊ�����
	int columCount;
	int rowCount;
};

