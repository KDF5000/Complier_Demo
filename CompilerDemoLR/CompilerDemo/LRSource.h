#define  STATUS_NUM          62    //状态总数
#define  TERMINAL_CHAR_NUM   24    //终止符个数
#define  NOT_TERMINAL_NUM    19    //非终止符个数
#define  STACK_MAX_LENGTH    500    //堆栈最大长度
#define  ACC                 100    //接受信号
#define  LAST_STATUS         61     //最后一个状态号
#define  ERROR_STATUS        -1    //错误状态号
#define  MAX_LENGTH          10
/*      
0    A`->A        | 6	 D->S    	  | 12	 S->T B     |	18	 P->ZH   |  24	 V-> /UV    |  30	 Y->>
1	 A->main()B   | 7	 D->W      	  | 13	 W-> NQ     |	19	 H->+ZH  |	25	 U->ID   	|  31	 Y->>=
2	 B->{C}       | 8	 F->ID=P   	  | 14	 K->do      | 	20	 H-> -ZH |	26	 U->num		|  32	 Y->==
3	 C->D;C       | 9	 G->if Q   	  | 15	 L->KB      | 	21	 H->ε	 |	27	 U->(P)  	|  33	 Y->!=
4	 C->ε        | 10	 S->G B   	  | 16	 N-> Lwhile | 	22	 Z->UV   |	28	 Y-><    	|  34	 V->ε
5	 D->F		  | 11	 T->G B else  | 17	 Q->PYP     |   23	 V->*UV  |	29	 Y-><=      |  */
/*规约时候对应的规则编号  +61*/
#define  R0     62       
#define  R1 	63
#define  R2 	64
#define  R3 	65
#define  R4 	66
#define  R5 	67
#define  R6 	68
#define  R7 	69
#define  R8 	70
#define  R9 	71
#define  R10	72
#define  R11	73
#define  R12	74
#define  R13	75
#define  R14	76
#define  R15	77
#define  R16	78
#define  R17	79
#define  R18	80
#define  R19	81
#define  R20	82
#define  R21	83
#define  R22	84
#define  R23	85
#define  R24	86
#define  R25	87
#define  R26	88
#define  R27	89
#define  R28	90
#define  R29	91
#define  R30	92
#define  R31	93
#define  R32	94
#define  R33	95
#define  R34	96
//非终结符
#define A_NTERMINAL    0
#define B_NTERMINAL	   1
#define C_NTERMINAL	   2
#define D_NTERMINAL	   3
#define F_NTERMINAL	   4
#define G_NTERMINAL	   5
#define H_NTERMINAL	   6
#define K_NTERMINAL	   7
#define L_NTERMINAL	   8
#define N_NTERMINAL	   9
#define P_NTERMINAL	   10
#define Q_NTERMINAL	   11
#define S_NTERMINAL	   12
#define T_NTERMINAL	   13
#define U_NTERMINAL	   14
#define V_NTERMINAL	   15
#define W_NTERMINAL	   16
#define Y_NTERMINAL	   17
#define Z_NTERMINAL	   18

typedef struct QUAD{
	char op[MAX_LENGTH];
	char argv1[MAX_LENGTH];
	char argv2[MAX_LENGTH];
	char result[MAX_LENGTH];
}qQuad;

















