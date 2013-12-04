/*
*功能:实现词法分析功能
*时间：2013.9.28
*作者：孔德飞
*/
#include "common.h"
#pragma once
class Morphology
{
public:
	Morphology(void);
	~Morphology(void);

	//char *keyWordTable[KEYWORD_NUMBER];
	//扫描代码缓冲区,函数返回字符串的代码，字符串或者数字保存在token数组中
	int scaner(const char codeBuffer[],int &startPosition,char token[]); 
	bool isBlank(const char ch);//判断是否为空格等字符
	
	static bool isLetter(const char ch);  //判断输入字符是否为字母
	static bool isDigi(const char ch);    //判断输入字符是否为数字
	int getTypeCode(const char token[]);  //获取字符串对应的code
	bool judgeEe(char ch,const char codeBuffer[],int &startPosition,char token[],int &m);//遇到E/e时进行后面的判断
	void setPreIsOp(bool isPreOP);   //前一个字符串是否为运算符
	int getRowsCout();
	int getColCout();
private:
	bool preIsOp;   //前一个字符串是否为运算符
	int columCount;
	int rowCount;
};

