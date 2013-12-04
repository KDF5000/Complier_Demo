/*功能：编译器
*作者：孔德飞 
*时间：2013.9.18
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
	char codeBuffer[CODE_BUTTER_LENGTH]; //存放用户输入代码的缓冲区
	char token[TOKEN_LENGTH];            //从缓冲区中取出的字符串
	//int typeCode;                        //字符串的类型码
	//int tokenPtr   ;			//tokenPtr取出字符串的指针
	int bufferPtr;              //bufferPtr缓冲区的指针
	//Morphology  morphology;             //词法分析器，实现词法分析功能
//	grammarAnalysis grammarAnalysis; //语法分析
	LRGramar lRAnalysi;//  LR语法分析
public:
	void inputCode();                   //用户输入code
	void startComplier();               //开始编译
	static void strToNumber(const char token[],double &outNumber);//将数字字符串转化为数字
};