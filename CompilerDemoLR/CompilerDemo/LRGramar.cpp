/************************************************************************/
/* 功能：LR语法分析器i，同时生成中间代码
* 作者：孔德飞
* 时间：2013.11.4
/************************************************************************/
#include "LRGramar.h"
#include "Complier.h"
int ActionTable[][TERMINAL_CHAR_NUM]=
{
	        /*ID ,num , +  , -  , *  , /  , =  , >  ,>=  , <  ,<=  ,==  ,!=  , (  , )  , {  , }  ,main,if  ,else, do ,while, ;  , #  */
/*0 */      {-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,2   ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*1 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,ACC },
/*2 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,3   ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*3 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,4   ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*4 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,6   ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*5 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,R1  },
/*6 */		{12  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R4  ,-1  ,15  ,-1  ,19  ,-1   ,-1  ,-1  },
/*7 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,20  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*8 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,21  ,-1  },
/*9 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R5  ,-1  },
/*10 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R6  ,-1  },
/*11 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R7  ,-1  },
/*12 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,22  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*13 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,6   ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*14 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,6   ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*15 */		{29  ,30  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,31  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*16 */		{29  ,30  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,31  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*17 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,33   ,-1  ,-1  },
/*18 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,6   ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*19 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R14 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*20 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R2  ,-1  ,R2   ,R2  ,R2  },
/*21 */		{12  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R4  ,-1  ,15  ,-1  ,19  ,-1   ,-1  ,-1  },
/*22 */		{29  ,30  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,31  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*23 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,37  ,-1  ,-1   ,R10 ,-1  },
/*24 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R12 ,-1  },
/*25 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R9  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*26 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,41  ,42  ,39  ,40  ,43  ,44  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*27 */		{-1  ,-1  ,46  ,47  ,-1  ,-1  ,-1  ,R21 ,R21 ,R21 ,R21 ,R21 ,R21 ,-1  ,-1  ,R21 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R21 ,-1  },
/*28 */		{-1  ,-1  ,R34 ,R34 ,49  ,50  ,-1  ,R34 ,R34 ,R34 ,R34 ,R34 ,R34 ,-1  ,-1  ,R34 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R34 ,-1  },
/*29 */		{-1  ,-1  ,R25 ,R25 ,R25 ,R25 ,-1  ,R25 ,R25 ,R25 ,R25 ,R25 ,-1  ,-1  ,-1  ,R25 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R25 ,-1  },
/*30 */		{-1  ,-1  ,R26 ,R26 ,R26 ,R26 ,-1  ,R26 ,R26 ,R26 ,R26 ,R26 ,-1  ,-1  ,-1  ,R26 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R26 ,-1  },
/*31 */		{29  ,30  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,31  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*32 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R13  ,-1  },
/*33 */		{R16 ,R16 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R16 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*34 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R15  ,-1  ,-1  },
/*35 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R3  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*36 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R8  ,-1  },
/*37 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R11 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*38 */		{29  ,30  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,31  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*39 */		{R28 ,R28 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R28 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*40 */		{R29 ,R29 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R29 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*41 */		{R30 ,R30 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R30 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*42 */		{R31 ,R31 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R31 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*43 */		{R32 ,R32 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R32 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*44 */		{R33 ,R33 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R33 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*45 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R18 ,R18 ,R18 ,R18 ,R18 ,R18 ,-1  ,-1  ,R18 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R18 ,-1  },
/*46 */		{29  ,30  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,31  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*47 */		{29  ,30  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,31  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*48 */		{-1  ,-1  ,R22 ,R22 ,-1  ,-1  ,-1  ,R22 ,R22 ,R22 ,R22 ,R22 ,R22 ,-1  ,-1  ,R22 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R22 ,-1  },
/*49 */		{29  ,30  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,31  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*50 */		{29  ,30  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,31  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*51 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,57  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*52 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R17 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R17 ,-1  },
/*53 */		{-1  ,-1  ,46  ,47  ,-1  ,-1  ,-1  ,R21 ,R21 ,R21 ,R21 ,R21 ,R21 ,-1  ,-1  ,R21 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R21 ,-1  },
/*54 */		{-1  ,-1  ,46  ,47  ,-1  ,-1  ,-1  ,R21 ,R21 ,R21 ,R21 ,R21 ,R21 ,-1  ,-1  ,R21 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R21 ,-1  },
/*55 */		{-1  ,-1  ,R34 ,R34 ,49  ,50  ,-1  ,R34 ,R34 ,R34 ,R34 ,R34 ,R34 ,-1  ,-1  ,R34 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R34 ,-1  },
/*56 */		{-1  ,-1  ,R34 ,R34 ,49  ,50  ,-1  ,R34 ,R34 ,R34 ,R34 ,R34 ,R34 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R34 ,-1  },
/*57 */		{-1  ,-1  ,-1  ,-1  ,R27 ,R27 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,-1  ,-1  },
/*58 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R19 ,R19 ,R19 ,R19 ,R19 ,R19 ,-1  ,-1  ,R19 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R19 ,-1  },
/*59 */		{-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,R20 ,R20 ,R20 ,R20 ,R20 ,R20 ,-1  ,-1  ,R20 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R20 ,-1  },
/*60 */		{-1  ,-1  ,R23 ,R23 ,-1  ,-1  ,-1  ,R23 ,R23 ,R23 ,R23 ,R23 ,R23 ,-1  ,-1  ,R23 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R23 ,-1  },
/*61 */		{-1  ,-1  ,R24 ,R24 ,-1  ,-1  ,-1  ,R24 ,R24 ,R24 ,R24 ,R24 ,R24 ,-1  ,-1  ,R24 ,-1  ,-1  ,-1  ,-1  ,-1  ,-1   ,R24 ,-1  }
};
int GotoTable[STATUS_NUM][NOT_TERMINAL_NUM]=
{
				/* A  B	 C	 D	 F	 G	 H	 K	 L	 N	 P	 Q	 S	 T	 U	 V	 W	 Y	 Z*/
	/*0 */ 		{1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*1 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*2 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*3 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*4 */		{-1	,5	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*5 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*6 */		{-1	,-1	,7	,8	,9	,13	,-1	,18	,17	,16	,-1	,-1	,10	,14	,-1	,-1	,11	,-1	,-1},
	/*7 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*8 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*9 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*10 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*11 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*12 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*13 */		{-1	,23	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*14 */		{-1	,24	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*15 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,26	,25	,-1	,-1	,28	,-1	,-1	,-1	,27},
	/*16 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,26	,32	,-1	,-1	,28	,-1	,-1	,-1	,27},
	/*17 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*18 */		{-1	,34	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*19 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*20 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*21 */		{-1	,-1	,35	,8	,9	,13	,-1	,18	,17	,16	,-1	,-1	,10	,14	,-1	,-1	,11	,-1	,-1},
	/*22 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,36	,-1	,-1	,-1	,28	,-1	,-1	,-1	,27},
	/*23 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*24 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*25 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*26 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,38	,-1},
	/*27 */		{-1	,-1	,-1	,-1	,-1	,-1	,45	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*28 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,48	,-1	,-1	,-1},
	/*29 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*30 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*31 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,51	,-1	,-1	,-1	,28	,-1	,-1	,-1	,27},
	/*32 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*33 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*34 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*35 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*36 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*37 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*38 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,52	,-1	,-1	,-1	,28	,-1	,-1	,-1	,27},
	/*39 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*40 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*41 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*42 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*43 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*44 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*45 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*46 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,28	,-1	,-1	,-1	,53},
	/*47 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,28	,-1	,-1	,-1	,54},
	/*48 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*49 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,55	,-1	,-1	,-1	,-1},
	/*50 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,56	,-1	,-1	,-1	,-1},
	/*51 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1 ,-1	,-1	,-1	,-1},
	/*52 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*53 */		{-1	,-1	,-1	,-1	,-1	,-1	,58	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*54 */		{-1	,-1	,-1	,-1	,-1	,-1	,59	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*55 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,60	,-1	,-1	,-1},
	/*56 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,61	,-1	,-1	,-1},
	/*57 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*58 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*59 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*60 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1},
	/*61 */		{-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1}
};
LRGramar::LRGramar(void)
{
	memset(statusStack,0,STACK_MAX_LENGTH);
	memset(charStack,0,STACK_MAX_LENGTH);
	for(int i=0;i<100;i++)
	{
		memset(variableBuffer[i],0,20);
		memset(lastOp[i],0,3);
		memset(QuadHead[i].argv1,0,MAX_LENGTH);
		memset(QuadHead[i].argv2,0,MAX_LENGTH);
		memset(QuadHead[i].op,0,MAX_LENGTH);
		memset(QuadHead[i].result,0,MAX_LENGTH);

	}
}


LRGramar::~LRGramar(void)
{
}


bool LRGramar::startGrammarAnalysis(const char codeBuffer[])
{
	int returnCode;         //每次识别字符串的code 
	int startPosition = 0;  //每次读出字符的起始位置
	int charA;             //每次从输入串中读出的字符保存到a
	int statusTopStack;   //栈顶状态

	
	morphology.setPreIsOp(true);//初始化操作符信号
	double num = 0;    //记录scanner扫描到数字的数值
	////////////////////////////////////////////////////////
	/*do{
		returnCode = morphology.scaner(codeBuffer,startPosition,bufferToken);

		if(returnCode == DIGIT)
		{
			Complier::strToNumber(bufferToken,num);
			printf("(%d,%g)\n",returnCode,num);
		}
		else if(returnCode == ERROR)
		{
			printf("('%s')不能有该文法生成！\n",bufferToken);
		}
		else if(returnCode==NOTE)
		{	
			//
		}
		else
		{
			printf("(%d,'%s')\n",returnCode,bufferToken);
		}

	}while(returnCode!=END_JINGHAO);*/
	//初始化相关堆栈
	quadCount = 0; //记录四元式数组存放位置
	nextq = 1;     //记录下一个四元式标号
	trueChainHead = 0;//记录回填真链的链首
	variableBufferPtr = -1;//存放变量名或者标示符的栈的指针
	OpPtr = -1;//ptr to the stack of op
	tempCount = 0;
	startPosition = 0;  //每次读出字符的起始位置
	statusStackPtr = -1;
	charStackPtr = -1;
	doTruePtr = -1;
    falseChainPtr = -1;
	push(statusStack,statusStackPtr,0); //将0状态压入堆栈
	push(charStack,charStackPtr,END_JINGHAO);
	charA = morphology.scaner(codeBuffer,startPosition,bufferToken);  //将字符串读入a
	if(charA==DIGIT || charA == IDENTIFIER)//如果为数字或者标示符及时保存
	{
		strcpy(variableBuffer[++variableBufferPtr],bufferToken);
	}
	statusTopStack = statusStack[statusStackPtr];         //栈顶状态
	int actionStatus = ActionTable[statusTopStack][mapPosition(charA)] ;
	while(actionStatus != ACC)
	{
		//如果是转移状态
		if(isTransferStatus(actionStatus))
		{
			//将状态和a压入堆栈
			push(statusStack,statusStackPtr,actionStatus);
			push(charStack,charStackPtr,charA);
			//读取下一个字符a
			do{
			   charA = morphology.scaner(codeBuffer,startPosition,bufferToken);  //将字符串读入a
			   if(charA==DIGIT || charA == IDENTIFIER)//如果为数字或者标示符及时保存
			   {
				   strcpy(variableBuffer[++variableBufferPtr],bufferToken);
			   }
			}while(charA==NOTE);
		}
		//如果是规约状态
		else if(isGuiYueStatus(actionStatus))
		{
			//用actionStatus所对应的规则（A->a）规约，并将|a|个状态和|a|个输入符号退栈，
			//当前栈顶状态为S，将A和GOTO[S][A]=S`进栈
			if(!doGuiYue(actionStatus))  //如果规约失败返回错误
			{
				return false;
			}
		}
		//some status else
		else
		{
			//error
			return false;
		}
		statusTopStack = statusStack[statusStackPtr];         //栈顶状态
		actionStatus = ActionTable[statusTopStack][mapPosition(charA)] ;
	}
	printf("---------------------------------------------------\n");
	printQuad();
	return true;
}
//压栈操作
void LRGramar::push(int stack[],int &topPtr,int value)
{
	//判断是否为栈顶
	{
		;
	}
	stack[++topPtr] = value;
}

//出栈操作
void LRGramar::pop(int stack[],int &topPtr,int &token)
{
	//判断是否为栈底
	{
		;
	}
	token = stack[topPtr--];
}

//坐标映射函数
int LRGramar::mapPosition(int charA)
{
	return charA;
}
//判断是否为转移状态
bool LRGramar::isTransferStatus(const int actionStatus)
{
	if(actionStatus > ERROR_STATUS && actionStatus<= LAST_STATUS )
	{
		return true;
	}
	else
	{
		return false;
	}
}
//判断是否是规约状态
bool LRGramar::isGuiYueStatus(const int actionStatus)
{
	if(actionStatus>=R0 && actionStatus <= R34)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*      
0    A`->A        | 6	 D->S    	  | 12	 S->T B     |	18	 P->ZH   |  24	 V-> /UV    |  30	 Y->>
1	 A->main()B   | 7	 D->W      	  | 13	 W-> NQ     |	19	 H->+ZH  |	25	 U->ID   	|  31	 Y->>=
2	 B->{C}       | 8	 F->ID=P   	  | 14	 K->do      | 	20	 H-> -ZH |	26	 U->num		|  32	 Y->==
3	 C->D;C       | 9	 G->if Q   	  | 15	 L->KB      | 	21	 H->ε	 |	27	 U->(P)  	|  33	 Y->!=
4	 C->ε        | 10	 S->G B   	  | 16	 N-> Lwhile | 	22	 Z->UV   |	28	 Y-><    	|  34	 V->ε
5	 D->F		  | 11	 T->G B else  | 17	 Q->PYP     |   23	 V->*UV  |	29	 Y-><=      |  */


//进行规约的操作
bool LRGramar::doGuiYue(const int ruleNum)
{
	switch(ruleNum)
	{
	case  R1:
		//执行进出站等相关操作
		if(!doRules(A_NTERMINAL,4))
		{
			return false;
		}
		break;
	case R2:
		if(!doRules(B_NTERMINAL,3))
		{
			return false;
		}
		break;
	case R3:
		if(!doRules(C_NTERMINAL,3))
		{
			return false;
		}
		break;
	case R4:
		if(!doRules(C_NTERMINAL,0))
		{
			return false;
		}
		break;
	case R5:
		if(!doRules(D_NTERMINAL,1))
		{
			return false;
		}
		break;
	case R6:
	case R7:
		if(!doRules(D_NTERMINAL,1))
		{
			return false;
		}
		else
		{
			
		}
		break;
	case R8:
		if(!doRules(F_NTERMINAL,3))
		{
			return false;
		}
		else
		{
			//堆栈是先进先出
			int argP = variableBufferPtr--; 
			int resultPtr = variableBufferPtr--;
			emit("=",variableBuffer[argP]," ",variableBuffer[resultPtr]);
		}
		break;
	case R9:
		if(!doRules(G_NTERMINAL,2))
		{
			return false;
		}
		else
		{
			backPatch(trueChainHead,nextq);  //回填真链头
		}
		break;
	case R10:
		if(!doRules(S_NTERMINAL,2))
		{
			return false;
		}
		else
		{
			backPatch(falseChain[falseChainPtr--],nextq);
		}
		break;
	case R11:
		if(!doRules(T_NTERMINAL,3))
		{
			return false;
		}
		else
		{
			
			emit("goto","","","0");
			backPatch(falseChain[falseChainPtr--],nextq);
			falseChain[++falseChainPtr] = nextq-1;
		}
		break;
	case R12:
		if(!doRules(S_NTERMINAL,2))
		{
			return false;
		}
		backPatch(falseChain[falseChainPtr--],nextq);
		break;
	case R13:
		if(!doRules(W_NTERMINAL,2))
		{
			return false;
		}
		else
		{
			backPatch(trueChainHead,doTrue[doTruePtr--]);
			backPatch(falseChain[falseChainPtr--],nextq);
		}
		break;
	case R14:
		if(!doRules(K_NTERMINAL,1))
		{
			return false;
		}
		doTrue[++doTruePtr] = nextq;//保存do后面的地址
		break;
	case R15:
		if(!doRules(L_NTERMINAL,2))
		{
			return false;
		}
		break;
	case R16:
		if(!doRules(N_NTERMINAL,2))
		{
			return false;
		}
		break;
	case R17:
		if(!doRules(Q_NTERMINAL,3))
		{
			return false;
		}
		else
		{
			trueChainHead = nextq;
			falseChain[++falseChainPtr]=nextq+1;
			char temp[10];
			int arg2 = variableBufferPtr--;
			int arg1 = variableBufferPtr--;
			sprintf(temp,"%s%s%s",variableBuffer[arg1],lastOp[OpPtr--],variableBuffer[arg2]);
			emit("if",temp,"goto","0");
			emit("goto","","","0");	

		}
		break;
	case R18:
		if(!doRules(P_NTERMINAL,2))
		{
			return false;
		}
		else
		{
			if(strcmp(variableBuffer[variableBufferPtr],"null")!=0)
			{
				char *pPlace = newTemp();
				emit(lastOp[OpPtr--],variableBuffer[variableBufferPtr--],variableBuffer[variableBufferPtr--],pPlace);
				strcpy(variableBuffer[++variableBufferPtr],pPlace);
			}
			else{
				variableBufferPtr--;
			}
		}
		break;
	case R19:
		if(!doRules(H_NTERMINAL,3))
		{
			return false;
		}
		else
		{
			if(strcmp(variableBuffer[variableBufferPtr],"null")!=0)
			{
				char *hPlace = newTemp();
				emit(lastOp[OpPtr--],variableBuffer[variableBufferPtr--],variableBuffer[variableBufferPtr--],hPlace);
				strcpy(variableBuffer[++variableBufferPtr],hPlace);
			}
			else{
				variableBufferPtr--;
			}
			strcpy(lastOp[++OpPtr],"+");
		}
		break;
	case R20:
		if(!doRules(H_NTERMINAL,3))
		{
			return false;
		}
		else
		{
			if(strcmp(variableBuffer[variableBufferPtr],"null")!=0)
			{
				char *hPlace = newTemp();
			    emit(lastOp[OpPtr--],variableBuffer[variableBufferPtr--],variableBuffer[variableBufferPtr--],hPlace);
			    strcpy(variableBuffer[++variableBufferPtr],hPlace);
			}
			else
			{
				variableBufferPtr--;
			}
			strcpy(lastOp[++OpPtr],"-");
		}
		break;
	case R21:
		if(!doRules(H_NTERMINAL,0))
		{
			return false;
		}
		else
		{
			strcpy(variableBuffer[++variableBufferPtr],"null");
		}
		break;
	case R22:
		if(!doRules(Z_NTERMINAL,2))
		{
			return false;
		}
		else
		{
			if(strcmp(variableBuffer[variableBufferPtr],"null")!=0)
			{
				char *zPlace = newTemp();
				emit(lastOp[OpPtr--],variableBuffer[variableBufferPtr--],variableBuffer[variableBufferPtr--],zPlace);
				strcpy(variableBuffer[++variableBufferPtr],zPlace);
			}
			else
			{
				variableBufferPtr--;
			}
		}
		break;
	case R23:
		if(!doRules(V_NTERMINAL,3))
		{
			return false;
		}
		else
		{
			if(strcmp(variableBuffer[variableBufferPtr],"null")!=0)
			{
				char *vPlace = newTemp();
				emit(lastOp[--OpPtr],variableBuffer[variableBufferPtr--],variableBuffer[variableBufferPtr--],vPlace);
				strcpy(variableBuffer[++variableBufferPtr],vPlace);
			}
			else
			{
				variableBufferPtr--;
			}
			strcpy(lastOp[++OpPtr] ,"*");
		}
		break;
	case R24:
		if(!doRules(V_NTERMINAL,3))
		{
			return false;
		}
		else
		{
			if(strcmp(variableBuffer[variableBufferPtr],"null")!=0)
			{
				char *vPlace = newTemp();
				emit(lastOp[--OpPtr],variableBuffer[variableBufferPtr--],variableBuffer[variableBufferPtr--],vPlace);
				strcpy(variableBuffer[++variableBufferPtr],vPlace);
			}
			else
			{
				variableBufferPtr--;
			}
			strcpy(lastOp[++OpPtr] ,"/");
		}
		break;
	case R25:
	case R26:
		if(!doRules(U_NTERMINAL,1))
		{
			return false;
		}
		break;
	case R27:
		if(!doRules(U_NTERMINAL,3))
		{
			return false;
		}
		break;
	case R28:
		strcpy(lastOp[++OpPtr],"<");
		if(!doRules(Y_NTERMINAL,1))
		{
			return false;
		}
		break;
	case R29:
		if(!doRules(Y_NTERMINAL,1))
		{
			return false;
		}
	    strcpy(lastOp[++OpPtr],"<=");
		break;
	case R30:
		if(!doRules(Y_NTERMINAL,1))
		{
			return false;
		}
		strcpy(lastOp[++OpPtr],">");
		break;
	case R31:
		if(!doRules(Y_NTERMINAL,1))
		{
			return false;
		}
		strcpy(lastOp[++OpPtr],">=");
		break;
	case R32:
		if(!doRules(Y_NTERMINAL,1))
		{
			return false;
		}
		strcpy(lastOp[++OpPtr],"==");
		break;
	case R33:
		if(!doRules(Y_NTERMINAL,1))
		{
			return false;
		}
		strcpy(lastOp[++OpPtr],"!=");
		break;
	case R34:
		if(!doRules(V_NTERMINAL,0))
		{
			return false;
		}
		else
		{
			strcpy(variableBuffer[++variableBufferPtr],"null");
		}
		break;
	default:
		return false;
	}
	return true;
}

void LRGramar::popStackN(int stack[],int &topPtr,int numbers)
{
	int i=0;
	int popChar;
	for(;i<numbers;i++)
	{
		pop(stack,topPtr,popChar);
	}
}

bool LRGramar::doRules(int LeftChar,int rightNumbers)
{
	int topStatus;//记录栈顶状态
	int gotoStatus;//记录goto状态
	//将|a|长度字符出栈
	popStackN(charStack,charStackPtr,rightNumbers);
	//将规则左侧入站
	push(charStack,charStackPtr,LeftChar);
	//将|a|长度状态出栈
	popStackN(statusStack,statusStackPtr,rightNumbers);
	topStatus = statusStack[statusStackPtr];//此时栈顶状态
	gotoStatus = GotoTable[topStatus][LeftChar];
	if(gotoStatus == ERROR_STATUS)
	{
		return false;
	}
	else
	{
		push(statusStack,statusStackPtr,gotoStatus);
		return true;
	}
}
//回填函数
void LRGramar::backPatch(int &chainHead,int nextq)
{
	if(chainHead ==0)
	{
		return;
	}
	int lastQuad = chainHead ;//记录回填链节点上一个
	do
	{
		int temp = atoi(QuadHead[lastQuad].result);
		itoa(nextq,QuadHead[lastQuad].result,10);
		lastQuad = temp;
	}while(lastQuad!=0);
	chainHead = 0;
}

void LRGramar::emit(char op[],char arg1[],char arg2[],char result[])
{
	++quadCount;
	strcpy(QuadHead[quadCount].op,op);
	strcpy(QuadHead[quadCount].argv1,arg1);
	strcpy(QuadHead[quadCount].argv2,arg2);
	strcpy(QuadHead[quadCount].result,result);
	//printf("%d:%s = %s %s %s\n",nextq,result,arg1,op,arg2);
	nextq++;
}
//新产生一个变量
char * LRGramar::newTemp()
{
	char *temp = (char *)malloc(sizeof(char)*8);//
	sprintf(temp,"T%d\0",tempCount++);
	return temp;
}

void LRGramar::printQuad()
{
	for(int i=1;i<=quadCount;i++)
	{
		printf("%d: (%s, %s, %s, %s )\n",i,QuadHead[i].op,QuadHead[i].argv1,QuadHead[i].argv2,QuadHead[i].result);
	}
}
