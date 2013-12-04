#include "Complier.h"
#include <conio.h>
#include <stdio.h>
#include <math.h>

int main()
{
	Complier complier;
	while(true)
	{
		complier.inputCode();

		complier.startComplier();
	}
	
	getch();
}