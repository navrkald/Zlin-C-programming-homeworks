/**
 * @file    vector.h
 * @author  Karel Jurkovic
 * @date    6/2015
 * @brief   Implementation of Vector structure
 */
#include<stdio.h>
#include "vector.h"
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>


// How to print uint64_t: http://stackoverflow.com/questions/9225567/how-to-print-a-int64-t-type-in-c

/**
 * @brief   Vytvoří Vector s počáteční velikostí speicifikovanou parametrem
 * @param   initial_size    počáteční velikost Vectoru
 * @param   alloc_step      Určuje, po jak velkých blocích se přialokovává paměť
 * @return  Vrací strukturu popisující Vector
 */
Vector_t Vector_Create(uint64_t initial_size, uint32_t alloc_step)
{
	Vector_t vector;
	vector.size = initial_size;
	vector.free_cells = initial_size;
	vector.alloc_step = alloc_step;
	vector.items = NULL;
	
	// Pokud je co naalokovat
	if(initial_size > 0)
	{
		// Alokace pameti a test jestli se neco naalokovalo
		if((vector.items = (uint64_t *) malloc(sizeof(uint64_t)*initial_size)) == NULL)
		{
			fprintf(stderr, "Not enough memmory, exiting program!");
			exit(EXIT_FAILURE);
		}
	}
	return vector;
}

/**
 * @brief   Přidá novou hodnotu na konec Vectoru
 * @param   vector  Ukazatel na Vector
 * @param   value   Vkládaná hodnota
 */
void Vector_Append(Vector_t *vector, uint64_t value)
{
	// Pokud nejsou zadne volne bunky musime naalokovat dalsi
	if(vector->free_cells == 0)
	{
		uint64_t newVectorSize = vector->size + vector->alloc_step;
		uint64_t * newPointer = (uint64_t*) realloc(vector->items, sizeof(uint64_t) * (newVectorSize));
		
		// Pokud se nam nepodarilo prealokovat, tak dealokujeme puvodni pamet a zkoncime program
		if(newPointer == NULL)
		{
			free(vector->items);
			fprintf(stderr, "Unsuccefull realocate memory!");
			exit(EXIT_FAILURE);
		}
		else
		{
			vector->size = newVectorSize;
			vector->items = newPointer;
			vector->free_cells = vector->alloc_step;
		}
	}
	
	// Pridame prvek na konec
	vector->items[vector->size - vector->free_cells] = value;
	vector->free_cells--;
}

/**
 * @brief   Vrací aktuální délku Vectoru
 * @param   vector  Ukazatel na Vector
 * @return  Aktuální délka Vectoru
 */
uint64_t Vector_Length(const Vector_t *vector)
{
	return vector->size - vector->free_cells;
}

/**
 * @brief   Vytvoří samostatnou kopii Vectoru
 * @param   original    Ukazatel na kopírovaný Vector
 * @return  Vrací strukturu popisující zkopírovaný Vector
 */
Vector_t Vector_Copy(const Vector_t *original)
{
	// vytvorime prazdny vektor
	Vector_t vectorCopy = Vector_Create(original->size, original->alloc_step);
	
	// Nakopirujeme hodnoty
	uint64_t itemCount = Vector_Length(original);
	for(uint64_t i = 0; i < itemCount; i++)
	{
		Vector_Append(&vectorCopy, original->items[i]);
	}
	return vectorCopy;
}

/**
 * @brief   Uvolni pamet vektoru a nastavi jeho velikost na 0
 * @param   vector  Ukazatel na Vector
 */
void Vector_Clear(Vector_t *vector)
{
	free(vector->items);
	vector->size = 0;
	vector->free_cells = 0;
	
}

/**
 * @brief   Navrací hodnotu Vectoru na vybraném umístění
 * @param   vector      Ukazatel na Vector
 * @param   position    Pozice v rámci Vectoru
 * @return  Vrací nalezenou hodnotu nebo 0
 */
uint64_t Vector_At(const Vector_t *vector, uint64_t position)
{
	if(Vector_Length(vector) >= position)
	{
		return vector->items[position];
	}
	else
	{
		fprintf(stderr, "ERROR: Can not get item! (Out of range Vector_t!)");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief   Odstraní prvek na vybrané pozici
 * @param   vector      Ukazatel na Vector
 * @param   position    Pozice v rámci Vectoru
 * @return  Vrací true pokud byla pozice uvnitř rozsahu
 */
bool Vector_Remove(Vector_t *vector, uint64_t position)
{
	uint64_t itemCount = Vector_Length(vector);
	// Kontrola mezi vektoru
	if(itemCount > position)
	{
		// Posunuti zbyle casti vektoru o jedna do leva
		for(uint64_t i = position + 1; i < itemCount; i++)
		{
			vector->items[i -1] = vector->items[i];
		}
		vector->free_cells++;
	}
	else
	{
		fprintf(stderr, "ERROR: Can not remove item! (Out of range Vector_t)");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief   Hledá pozici prvku s danou hodnotou ve Vectoru
 * @param   vector  Ukazatel na Vector
 * @param   value   Hledaná hodnota
 * @param   from    Pozice od které se začíná hledat
 * @return  Vrací pozici prvku pokud je nalezen, jinak -1
 */
int64_t Vector_IndexOf(const Vector_t *vector, uint64_t value, uint64_t from)
{
	int64_t indexOf = -1;
	uint64_t itemCount = Vector_Length(vector);
	// Kontrola mezi vektoru
	if(itemCount > from)
	{
		for(uint64_t i = from; i < itemCount; i++)
		{
			// Pokud jsme nasli prvek nastavime indexOf a ukoncime prohledavani
			if(vector->items[i] == value)
			{
				indexOf = i;
				break;
			}
		}
	}
	else
	{
		fprintf(stderr, "ERROR: Can not get index of item using from %" PRIu64 "! (Out of range Vector_t)", from);
		exit(EXIT_FAILURE);
	}
	
	return indexOf;
}

/**
 * @brief   Funkce slouží k zjištění, jestli se někde ve Vectoru nachází daná hodnota
 * @param   vector  Ukazatel na Vector
 * @param   value   Hledaná hodnota
 * @return  Vrací true pokud je hodnota nalezena, jinak false
 */
bool Vector_Contains(const Vector_t *vector, uint64_t value)
{
	uint64_t firstIndex = 0;
	uint64_t notFoundIndexOf = -1;
	// We can use function Vector_IndexOf(vector, value, firstIndex).
	// If the function does'nt retrun -1 so vector contains item
	return notFoundIndexOf != Vector_IndexOf(vector, value, firstIndex);
}


/**
 * @brief   Vyplní část vektoru zadanou rozsahem nějakou hodnotou
 * #note    Bonusová funkce pro aktivní studenty
 * @param   vector          Ukazatel na Vector
 * @param   value           Nastavovaná hodnota
 * @param   start_position  Počáteční pozice
 * @param   end_position    Konečná pozice
 */
void Vector_Fill(Vector_t *vector, uint64_t value, uint64_t start_position, uint64_t end_position)
{
	uint64_t itemCount = Vector_Length(vector);
	if(start_position > itemCount +1)
	{
		fprintf(stderr,"ERROR: start_position=%" PRIu64 " item count=%" PRIu64 " don't know what to fill between!",itemCount, start_position);
		exit(EXIT_FAILURE);
	}
	
	if(start_position > end_position)
	{
		fprintf(stderr, "ERROR: Can not fill vector! Start_position > endposition!");
		exit(EXIT_FAILURE);
	}
	
	// Pokud je konecna pozice vetsi nez naalokovana velikost vektoru musime vektor zvetsit
	// (vector->size + 1 je, protože indexujeme od 0)
	if(end_position >  vector->size + 1)
	{
		uint64_t * newPointer = (uint64_t*) realloc(vector->items, sizeof(uint64_t) * end_position);
		
		// Pokud se nam nepodarilo prealokovat, tak dealokujeme puvodni pamet a zkoncime program
		if(newPointer == NULL)
		{
			free(vector->items);
			fprintf(stderr, "Unsuccefull realocate memory!");
			exit(EXIT_FAILURE);
		}
	}
	
	// Nyni muzeme vyplnovat vektor
	for(uint64_t i = start_position; i <= end_position; i++)
	{
		vector->items[i] = value;
	}
}

/***************************************************
 *  Tyto funkce jsou nutne pro ukol 3 (Histogram)
 * *************************************************/

uint64_t Vector_Max(const Vector_t* vector)
{
	uint64_t itemCount = Vector_Length(vector);
	if(itemCount > 0)
	{
		uint64_t max = vector->items[0];
		for(uint64_t i = 1; i < itemCount; i++)
		{
			if(vector->items[i] > max)
			{
				max = vector->items[i];
			}
		}
		return max;
	}
	else
	{
		fprintf(stderr, "Can't get maximum of empty vector!");
		exit(EXIT_FAILURE);
	}
}

uint64_t Vector_Min(const Vector_t* vector)
{
	uint64_t itemCount = Vector_Length(vector);
	if(itemCount > 0)
	{
		uint64_t min = vector->items[0];
		for(uint64_t i = 1; i < itemCount; i++)
		{
			if(vector->items[i] < min)
			{
				min = vector->items[i];
			}
		}
		return min;
	}
	else
	{
		fprintf(stderr, "Can't get minimum of empty vector!");
		exit(EXIT_FAILURE);
	}
}
