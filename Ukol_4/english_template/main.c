#include <stdio.h>
#include "ioutils.h"

#define DEBUG 1

void printMenu()
{
	printf(
		"List test program\n"
		"Zadejte pismeno 0-A pro jednu z nasledujicich cinnosti:\n"
		"0: Init,\n"
		"1: Actualize,\n"
		"2: Insert_First,\n"
		"3: First,\n"
		"4: Copy_First,\n"
		"5: Delete_First,\n"
		"6: Post_Delete,\n"
		"7: Post_Insert,\n"
		"8: Copy,\n"
		"9: Succ,\n"
		"A: Is_Active,\n"
		"M: Vypis menu\n"
		"CTRL+Z (Win) nebo CTRL+D (Unix): Konec programu\n"
	);
}

void printOption(char c)
{
	if((c <= '0' && c >= '9') || c=='A' || c=='M')
	{
		printf("Vase volba=%c\n", c);
	}
	else
	{
		printf("Neznama volba, vypisuji menu.\n");
	}
}

int main(void) 
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char option;
	char name[255];
	long age;
	long weight;
	long height;
	while ( ((int)(option = getc(in))) != EOF) 
	{
		printOption(char c);
		switch (option) 
		{
			case '0':
				break;
			case '1':
				break;
			case '2':
				printf("Insert_First - vlozeni nove polozky na 1. misto seznamu\n");
				scanf("Zadejte jmeno osoby: %s",&name);
				#if DEBUG
					printf("name:%s\n", name);
				#fi
				printf("Zadejte vek, vahu a vysku (oddelene Enter):");
				io_utils_get_long(&age);
				io_utils_get_long(&weight);
				io_utils_get_long(&height);
				#if DEBUG 
					printf("Vek=%l, vaha=%l, vyska=%l\n",age, weight, height);
				#fi
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				break;
			case 'M':
			default:
				printMenu();
				break;
		}
		printf("\n"
					 "Zadejte znak 0-A, EOF(tj. CTRL+Z nebo CTRL+D)=Konec, M=Menu:\n"
					 "************************************************************\n");
		
	}
	return EXIT_SUCCESS;
}
List test program
Zadejte pismeno 0-A pro jednu z nasledujicich cinnosti:
