#include "table.h"
#include "mymalloc.h"
#include "data.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#define DEBUG
////////////////////////////////////////////////////////////////////////////////
// pomocné funkce

unsigned int hash(HashTable* table, Data_t* key)
{
	return Data_Hash(key) % table->size;
}


////////////////////////////////////////////////////////////////////////////////

// operace nad tabulkou

void HashTable_Init(HashTable* table, size_t size, bool deletecontents)
{
/** TODO: Doplnte kod */
}


void HashTable_Destruct(HashTable* table)
{
/** TODO: Doplnte kod */
}


bool HashTable_Insert(HashTable *table, Data_t* key, Data_t* value)
{
/** TODO: Doplnte kod */
}


bool HashTable_Delete(HashTable *table, Data_t* key)
{
/** TODO: Doplnte kod */
}

Data_t* HashTable_Find(HashTable *table, Data_t* key)
{
/** TODO: Doplnte kod */
}

void HashTable_Clear(HashTable* table)
{
/** TODO: Doplnte kod */
}

void HashTable_Process(HashTable* table, TableNodeProc proc)
{
/** TODO: Doplnte kod */
}

size_t HashTable_Get_Count(HashTable* table)
{
/** TODO: Doplnte kod */
}


