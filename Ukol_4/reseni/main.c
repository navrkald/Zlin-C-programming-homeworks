#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "data.h"
#include "ioutils.h"

#define DEBUG

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
	if((c >= '0' && c <= '9') || c=='A' || c=='M')
	{
		printf("Vase volba=%c\n", c);
	}
	else
	{
		printf("Neznama volba: '%c', vypisuji menu.\n",c);
	}
}

int main(void) 
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

	printMenu();
    char option;
	Data_t data;
	List_t list;
	List_Init(&list);
    while (  !feof(stdin))
	{

        option = io_utils_get_char_line();

		printOption(option);
		switch (option) 
		{
			case '0':
				printf("Init - Provede inizializaci seznamu pred jeho prvnim pouzitim\n");
				List_Init(&list);
				break;
			case '1':
				printf("Actualize - Prepise obsah aktivni polozky novymi daty\n");
				if(List_Is_Active(list))
				{
                    Data_Get(&data);
					List_Actualize(&list, data);
				}
				else
				{
					fprintf(stderr, "Warning: List_Actualize - in list not active member, do nothing. (First use List_First.)\n");
				}
				break;
			case '2':
				printf("Insert_First - vlozeni nove polozky na 1. misto seznamu\n");
                Data_Get(&data);
				List_Insert_First(&list, data);
				break;
			case '3':
				printf("First - nastaveni aktivni polozky na 1.prvek\n");
				List_First(&list);
				break;
			case '4':
				printf("Copy_First - Vypis 1.prvku seznamu\n");
				if(list.first != NULL)
				{
					data = List_Copy_First(list);
					Data_Print(&data);
				}
				else
				{
					fprintf(stderr, "Warning: Copy_First - empty list, do nothing. (First use Insert_First.)\n");
				}
				break;
			case '5':
				printf("Delete_First - vymaz  1.prvek\n");
				if(list.first != NULL)
				{
					List_Delete_First(&list);
				}
				else
				{
					fprintf(stderr, "Warning: Delete_First - empty list, do nothing. (First use Insert_First.)\n");
				}
				break;
			case '6':
				printf("Post_Delete - vymaz prvek za aktivnim prvkem\n");
				if(List_Is_Active(list))
				{
					List_Post_Delete(&list);
				}
				else
				{
					fprintf(stderr, "Warning: List_Post_Delete - in list not active member, do nothing. (First use List_First.)\n");
				}
				break;
			case '7':
				printf("Post_Insert - vloz novy prvek za aktivni prvek\n");
				if(List_Is_Active(list))
				{
                    Data_Get(&data);
					List_Post_Insert(&list, data);
				}
				else
				{
					fprintf(stderr, "Warning: List_Post_Insert - in list not active member, do nothing. (First use List_First.)\n");
				}
				break;
			case '8':
				printf("Copy - ziskani hodnoty aktivniho prvku\n");
				if(List_Is_Active(list))
				{
					data = List_Copy(list);
					Data_Print(&data);
				}
				else
				{
					fprintf(stderr, "Warning: Copy - in list not active member, do nothing. (First use List_First.)\n");
				}
				break;
			case '9':
				printf("Succ - posuv ukazatel aktivniho prvku na dalsi prvek\n");
				List_Succ(&list);
				break;
			case 'A':
				printf("Is_Active - zjisteni, zda je seznam aktivni\n");
				printf("Is_Active=%s\n",List_Is_Active(list) ? "true" : "false");
				break;
			// For 'M' and everithing else print menu! 
			case 'M':
			default:
				printMenu();
				break;
		}
		printList(list);
		printf("\n"
					 "Zadejte znak 0-A, EOF(tj. CTRL+Z nebo CTRL+D)=Konec, M=Menu:\n"
					 "************************************************************\n");
		
	}
	return EXIT_SUCCESS;
}
