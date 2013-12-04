#include "Complier.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
Complier::Complier(void)
{
	memset(codeBuffer,0,sizeof(codeBuffer));
	memset(token,0,sizeof(token));
	bufferPtr = 0;
}


Complier::~Complier(void)
{
}

//用户输入
void Complier::inputCode()
{
	printf("请输入您要分析的代码(以#结束输入)：\n");
	char lineCode[80];
	bufferPtr = 0;
	//判断是否输入#
	do
	{
	   memset(lineCode,0,sizeof(lineCode));
	   gets(lineCode);
	   for(int i=0;i<strlen(lineCode);i++)
	   {
		   if(lineCode[i]=='#')
		   {
			   codeBuffer[bufferPtr++]=lineCode[i];
			   codeBuffer[bufferPtr++] = '\0';
			   printf("您已经输入#，而且#后面的代码将不进行分析\n");
			   return;
		   }
		   else
		   {
			    codeBuffer[bufferPtr++]=lineCode[i];
		   }
	   }
	   codeBuffer[bufferPtr++] = '\n';
	}while(lineCode[0]!='#');
}
//编译
void Complier::startComplier()
{
	int startPosition = 0;
	int returnCode;
	//先输出缓冲区的内容
	printf("%s\n",codeBuffer);
	//词法分析

	//语法分析
	if(lRAnalysi.startGrammarAnalysis(codeBuffer))
	{
		printf("语法分析正确\n");
	}else
	{
		printf("语法分析错误\n");
		printf("error:row:%d\n",lRAnalysi.morphology.getRowsCout());
	}
}

//将数字字符串转化为数字
void Complier::strToNumber(const char token[],double &outNumber)
{
	outNumber = 0;
	bool dotFlag = false; //遇到'.'
	bool eFlag = false; //遇到E/e
	bool signFlag = false; //+，-的标
	double Decimal = 0;//小数
	double ENumber = 0;//幂
	bool   biggerZero = true; //是否大于0 
	double m = 1;
	char ch;
	for(int i=0;i<strlen(token);i++)
	{	
		ch = token[i];
		if(i==0)
		{
			if(ch=='+')
			{
				biggerZero = true;
				continue;
			}
			else if(ch == '-')
			{
				biggerZero = false;
				continue;
			}
			else{
				biggerZero = true;
			}
		}
		if(ch =='.')
		{
			dotFlag = true;
		}
	    if(ch =='e' || ch =='E')
		{
			eFlag = true;
			dotFlag = false;
			m = 1;
		}
		if(Morphology::isDigi(ch))
		{
			
			if(eFlag == true)
			{
				if(dotFlag == true)
				{
					m = m/10;
					ENumber = ENumber + (ch - '0')*m;
				}
				else
				{
					ENumber = ENumber * 10 + ch - '0';
				}
			}
			else
			{
				if(dotFlag == true)
				{
					m = m/10;
					outNumber = outNumber + (ch - '0')*m;

				}
				else
				{
					outNumber = outNumber * 10 + ch - '0';
				}
			}
		}
		if(ch == '-')
		{
			signFlag = true;
		}
	}
	if(signFlag == true)
	{
		outNumber = outNumber * pow(10,(0-ENumber));
	}
	else
	{
		outNumber = outNumber * pow(10,ENumber);
	}
	//如果小于0就取反
	if(!biggerZero)
	{
		outNumber = 0 - outNumber;
	}
}