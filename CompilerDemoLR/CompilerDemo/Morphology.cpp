#include "Morphology.h"
#include <string.h>
//关键字表
#ifndef KEYWORDTABLE
#define KEYWORDTABLE    
char *keyWordTable[KEYWORD_NUMBER] = {"main","if","else","do","while"};
#endif

Morphology::Morphology(void)
{
	 preIsOp = true;
	 columCount = 0;
	 rowCount = 1;
}


Morphology::~Morphology(void)
{
}

void Morphology::setPreIsOp(bool isPreOp)
{
	preIsOp = true;
}
int Morphology::scaner(const char codeBuffer[],int &startPosition,char token[])
{
	//将token数组清空
	memset(token,0,sizeof(token));
	int m = 0; //token的指针
	char preCh;
	char ch = codeBuffer[startPosition++];
	columCount++;
	//确保第一个字符不是空格，制表符，换行等符号
	while(isBlank(ch))
	{
		if(ch=='\n')
		{
			rowCount++;
			columCount=0;
		}
		ch = codeBuffer[startPosition++];
		columCount++;
	}
	
	//判断第一个字符的类型，根据状态转换图确定字符串
	//若第一个字符是字母
	if(isLetter(ch))
	{
		//根据状态图确定字符串
		while(isLetter(ch) || isDigi(ch) )
		{
			token[m++] = ch;
			ch = codeBuffer[startPosition++];
			columCount++;
		}
		token[m] = '\0';//在token字符串末尾添加结束符
		//将不是字母或者数字的字符放回缓冲区
		startPosition--;

		//判断取得的字符串的类型码
		int stringCode = getTypeCode(token);
		preIsOp = false;
		return stringCode;
	}
	//如果为‘+’,'-'号或者是数字
	else if(ch=='+' || ch == '-'|| isDigi(ch))
	{
		
		if(isDigi(ch))
		{
			preIsOp=true;
		}
		else
		{
			preCh = ch;
			token[m++]= ch;
			ch = codeBuffer[startPosition++];
			columCount++;
		}

		if(isDigi(ch)&&preIsOp==true)
		{
			while(isDigi(ch))
			{
				token[m++] = ch;
				ch = codeBuffer[startPosition++];
				columCount++;
			}
			//如果是E/e
			if(ch == 'E' || ch == 'e')
			{
				if(!judgeEe(ch,codeBuffer,startPosition,token,m))
				{
					preIsOp = false;
					startPosition--;
					columCount--;
					return ERROR;
				}
				preIsOp = false;
				startPosition--;
				columCount--;
				return DIGIT;
			}
			//如果是 ’.’
			if(ch == '.')
			{
				//如果后面不是数字,则将'.'放回缓冲区
				token[m++] = ch;
				ch = codeBuffer[startPosition++];
				//如果E/e后面不是数字，则将E重新放回缓冲区
				if(!isDigi(ch))
				{
					startPosition--;
					columCount--;
					token[m] = '\0';
					//返回数字类型碼
					preIsOp = false;
					return ERROR;
				}
				//如果是数字
				while(isDigi(ch))
				{
					token[m++] = ch;
					ch = codeBuffer[startPosition++];
					columCount++;
				}
				//
				if(ch == 'E' || ch == 'e')
				{
					if(!judgeEe(ch,codeBuffer,startPosition,token,m))
					{
						preIsOp = false;
						startPosition--;
						columCount--;
						return ERROR;
					}
				}
				token[m] = '\0';
				startPosition--;
				columCount--;
				preIsOp = false;
				return DIGIT;
			}
			token[m] = '\0';
			startPosition--;
			columCount--;
			preIsOp = false;
			return DIGIT;
		}
		else
		{
			if(preCh=='+')
			{
				token[m] = '\0';
				startPosition--;
				columCount--;
				preIsOp=true;
				return PLUS;				
			}
			else
			{
				token[m] = '\0';
				startPosition--;
				columCount--;
				preIsOp=true;
				return SUB;
			}

		}
	}
	//*
	else if(ch == '*')
	{
		token[m++] = '*';
		token[m] = '\0';
		preIsOp=true;
		return STAR;
	}
	//'/'
	else if(ch == '/')
	{
		bool endNode= false;
		char nextCh;
		token[m++] = '/';
		ch = codeBuffer[startPosition++];
		columCount++;
		if(ch=='*')
		{
			token[m++]= ch;
			while(!endNode)
			{
				ch = codeBuffer[startPosition++];
				if(ch=='#')
				{
					startPosition--;
					return ERROR;
				}
				nextCh = codeBuffer[startPosition];
				if(ch=='*' && nextCh=='/')
				{
					token[m++]= ch;
					token[m++]= nextCh;
					startPosition++;
					columCount++;
					endNode = true;
				}
				else
				{
					token[m++]= ch;
				}
			}
			//startPosition--;
			token[m] = '\0';
			return NOTE;
		}
		else
		{
			startPosition--;
			columCount--;
			token[m] = '\0';
			preIsOp=true;
			return SLASH;
		}
		
	}
	else if(ch == '=')
	{
		token[m++] = ch;
		ch = codeBuffer[startPosition++];
		if(ch == '=')
		{
			token[m++] = ch;
			token[m] = '\0';
			return DOUBLE_EQUAL;
		}
		token[m] = '\0';
		startPosition--;
		preIsOp = true;
		return EQUAL;
	}
	else if(ch == '!')
	{
		token[m++] = ch;
		ch = codeBuffer[startPosition++];
		if(ch == '=')
		{
			token[m++] = ch;
			token[m] = '\0';
			return MAOHAO_DENGHAO;
		}
		startPosition--;
		token[m] = '\0';
		return MAOHAO;
	}
	//':' ,':='
	/*else if(ch == ':')
	{
		token[m++] = ch;
		ch = codeBuffer[startPosition++];
		if(ch == '=')
		{
			token[m++] = ch;
			token[m] = '\0';
			return MAOHAO_DENGHAO;
		}
		startPosition--;
		token[m] = '\0';
		return MAOHAO;
	}*/
	//'<', '<>,'<='
	else if(ch == '<')
	{
		token[m++] = ch;
		ch = codeBuffer[startPosition++];
		//去除<>
		/*if(ch == '>')
		{
			token[m++] = ch ;
			token[m] = '\0';
			return SMALL_BIGGER;
		}*/
		if(ch == '=')
		{
			token[m++] = ch ;
			token[m] = '\0';
			return SMALLER_EQUAL;
		}
		startPosition--;
		token[m] = '\0';
		return SMALLER;
	}
	// '>'
	else if(ch == '>')
	{
		token[m++] = ch;
		ch = codeBuffer[startPosition++];
		if(ch == '=')
		{
			token[m++] = ch ;
			token[m] = '\0';
			return BIGGER_EQUAL;
		}
		startPosition--;
		token[m] = '\0';
		return BIGGER;
	}
	// ';'
	else if(ch == ';')
	{
		token[m++] = ch;
		token[m] = '\0';
		return FENHAO;
	}
	else if(ch == '(')
	{
		token[m++] = ch;
		token[m] = '\0';
		preIsOp=true;
		return KUOHAO_L;
	}
	else if(ch == ')')
	{
		token[m++] = ch;
		token[m] = '\0';
		preIsOp=false;
		return KUOHAO_R;
	}
	else if(ch == '{')
	{
		token[m++] = ch;
		token[m] = '\0';
		preIsOp=false;
		return BIG_KUOHAOL;
	}
	else if(ch == '}')
	{
		token[m++] = ch;
		token[m] = '\0';
		preIsOp=false;
		return BIG_KUOHAOR;
	}
	//如果为结束字符#
	else if(ch =='#')
	{
		token[m++] = '#';
		token[m] = '\0';
		return END_JINGHAO;
	}
	token[m++] = ch;
	token[m] = '\0';
	return ERROR;
}
//判断是否为空格，制表符，换行等字符
bool Morphology::isBlank(const char ch)
{
	if(ch==' '|| ch=='\n'|| ch=='\t')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//判断字符是否为字母
bool Morphology::isLetter(const char ch)
{
	if((ch >= 'A' && ch <= 'Z') || ((ch >= 'a' && ch <= 'z')) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
//判断字符是否为数字
bool Morphology::isDigi(const char ch)
{
	if(ch>='0' && ch<='9')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//获取制定字符串的类型码，病作为含函数值返回
int Morphology::getTypeCode(const char token[])
{
	for(int n=0;n<KEYWORD_NUMBER;n++)
	{
		if(strcmp(token,keyWordTable[n])==0)
		{
			return (n+17);
		}
	}
	return IDENTIFIER;
}

//遇到E/e时进行后面的判断
bool Morphology::judgeEe(char ch,const char codeBuffer[],int &startPosition,char token[],int &m)
{
	token[m++] = ch;
	ch = codeBuffer[startPosition++];
	//如果E/e后面不是数字，则将E重新放回缓冲区
	if(ch == '+' || ch == '-')
	{
		token[m++] = ch;
		ch = codeBuffer[startPosition++];
		if(!isDigi(ch))
		{
			token[m] = '\0';
			//返回数字类型碼
			return false;
		}
	}
	else
	{
		if(!isDigi(ch))
		{
			token[--m] = '\0';
			//返回数字类型碼
			return false;
		}
	}
	//进入科学计数法E后面的文法
	while(isDigi(ch))
	{
		token[m++] = ch;
		ch = codeBuffer[startPosition++];
	}
	if(ch=='.')
	{
		token[m++] = ch;
		ch = codeBuffer[startPosition++];
		if(!isDigi(ch))
		{
			token[m] = '\0';
			return false;
		}
		else
		{
			while(isDigi(ch))
			{
				token[m++] = ch;
				ch = codeBuffer[startPosition++];
			}
			token[m] = '\0';
			return true;
		}
	}
	else
	{
		return true;
	}
}

//获取当前列
int Morphology::getColCout()
{
	return this->columCount;
}
//获取当前行数
int Morphology::getRowsCout()
{
	return this->rowCount;
}