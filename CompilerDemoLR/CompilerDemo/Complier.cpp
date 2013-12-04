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

//�û�����
void Complier::inputCode()
{
	printf("��������Ҫ�����Ĵ���(��#��������)��\n");
	char lineCode[80];
	bufferPtr = 0;
	//�ж��Ƿ�����#
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
			   printf("���Ѿ�����#������#����Ĵ��뽫�����з���\n");
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
//����
void Complier::startComplier()
{
	int startPosition = 0;
	int returnCode;
	//�����������������
	printf("%s\n",codeBuffer);
	//�ʷ�����

	//�﷨����
	if(lRAnalysi.startGrammarAnalysis(codeBuffer))
	{
		printf("�﷨������ȷ\n");
	}else
	{
		printf("�﷨��������\n");
		printf("error:row:%d\n",lRAnalysi.morphology.getRowsCout());
	}
}

//�������ַ���ת��Ϊ����
void Complier::strToNumber(const char token[],double &outNumber)
{
	outNumber = 0;
	bool dotFlag = false; //����'.'
	bool eFlag = false; //����E/e
	bool signFlag = false; //+��-�ı�
	double Decimal = 0;//С��
	double ENumber = 0;//��
	bool   biggerZero = true; //�Ƿ����0 
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
	//���С��0��ȡ��
	if(!biggerZero)
	{
		outNumber = 0 - outNumber;
	}
}