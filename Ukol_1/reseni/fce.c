#include <stdio.h>
#include "fce.h"

void minimax(int * pole, int delka, int *minimum, int *maximum)
{
	// pole musi mit alespon jeden prvek
	if(delka > 0)
	{
		*minimum = pole[0];
		*maximum = pole[0];
		
		// prvni prvek jsme uz vyresili prirazenimi vyse
		for(int i = 1; i < delka; i++)
		{
			// nastaveni noveho minima
			if(pole[i] < *minimum)
			{
				*minimum = pole[i];
			}
			
			// nastaveni noveho maxima
			if(pole[i] > *maximum)
			{
				*maximum = pole[i];
			}
		}
	}
	else
	{
		printf("minimax error: Pole musi mit alespon jeden prvek!\n");
	}
}

int get_min(int * pole, int delka)
{
	if(delka > 0)
	{
		int tmpMin = pole[0];
		for(int i = 1; i < delka; i++)
		{
			if(pole[i] < tmpMin)
			{
				tmpMin = pole[i];
			}
		}
		return tmpMin;
	}
	else
	{
		printf("minimax error: Pole musi mit alespon jeden prvek!\n");
		return -1;
	}
}

int get_max(int * pole, int delka)
{
	if(delka > 0)
	{
		int tmpMax = pole[0];
		for(int i = 1; i < delka; i++)
		{
			if(pole[i] > tmpMax)
			{
				tmpMax = pole[i];
			}
		}
		return tmpMax;
	}
	else
	{
		printf("minimin error: Pole musi mit alespon jeden prvek!\n");
		return -1;
	}
}

// Reseni pomoci rekurze
double fact(double n)
{
	if (n == 0)
		return 1;
	else
		return(n * fact(n-1));
}

// Reseni pomoci rekurze
int fibonacci(int n)
{
	if ( n == 0 )
		return 0;
	else if ( n == 1 )
		return 1;
	else
		return ( fibonacci(n-1) + fibonacci(n-2) );
}
