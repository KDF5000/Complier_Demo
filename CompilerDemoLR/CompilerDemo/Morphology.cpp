#include "Morphology.h"
#include <string.h>
//�ؼ��ֱ�
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
	//��token�������
	memset(token,0,sizeof(token));
	int m = 0; //token��ָ��
	char preCh;
	char ch = codeBuffer[startPosition++];
	columCount++;
	//ȷ����һ���ַ����ǿո��Ʊ�������еȷ���
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
	
	//�жϵ�һ���ַ������ͣ�����״̬ת��ͼȷ���ַ���
	//����һ���ַ�����ĸ
	if(isLetter(ch))
	{
		//����״̬ͼȷ���ַ���
		while(isLetter(ch) || isDigi(ch) )
		{
			token[m++] = ch;
			ch = codeBuffer[startPosition++];
			columCount++;
		}
		token[m] = '\0';//��token�ַ���ĩβ��ӽ�����
		//��������ĸ�������ֵ��ַ��Żػ�����
		startPosition--;

		//�ж�ȡ�õ��ַ�����������
		int stringCode = getTypeCode(token);
		preIsOp = false;
		return stringCode;
	}
	//���Ϊ��+��,'-'�Ż���������
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
			//�����E/e
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
			//����� ��.��
			if(ch == '.')
			{
				//������治������,��'.'�Żػ�����
				token[m++] = ch;
				ch = codeBuffer[startPosition++];
				//���E/e���治�����֣���E���·Żػ�����
				if(!isDigi(ch))
				{
					startPosition--;
					columCount--;
					token[m] = '\0';
					//�����������ʹa
					preIsOp = false;
					return ERROR;
				}
				//���������
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
		//ȥ��<>
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
	//���Ϊ�����ַ�#
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
//�ж��Ƿ�Ϊ�ո��Ʊ�������е��ַ�
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
//�ж��ַ��Ƿ�Ϊ��ĸ
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
//�ж��ַ��Ƿ�Ϊ����
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
//��ȡ�ƶ��ַ����������룬����Ϊ������ֵ����
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

//����E/eʱ���к�����ж�
bool Morphology::judgeEe(char ch,const char codeBuffer[],int &startPosition,char token[],int &m)
{
	token[m++] = ch;
	ch = codeBuffer[startPosition++];
	//���E/e���治�����֣���E���·Żػ�����
	if(ch == '+' || ch == '-')
	{
		token[m++] = ch;
		ch = codeBuffer[startPosition++];
		if(!isDigi(ch))
		{
			token[m] = '\0';
			//�����������ʹa
			return false;
		}
	}
	else
	{
		if(!isDigi(ch))
		{
			token[--m] = '\0';
			//�����������ʹa
			return false;
		}
	}
	//�����ѧ������E������ķ�
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

//��ȡ��ǰ��
int Morphology::getColCout()
{
	return this->columCount;
}
//��ȡ��ǰ����
int Morphology::getRowsCout()
{
	return this->rowCount;
}