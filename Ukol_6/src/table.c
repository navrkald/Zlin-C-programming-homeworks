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
	if(table != NULL)
	{
		table->size = size;
		table->count = 0;
		table->delete_contents = deletecontents;
	}
	// Alocate array of pointers to HashTableNode*
	table->buckets = myMalloc(sizeof(HashTableNode*)*table->size);
	// Initialize every element of array to NULL
	for(int i = 0; i < table->size; i++)
	{
		table->buckets[i] = NULL;
	}
}


void HashTable_Destruct(HashTable* table)
{
	myFree(table->buckets);
}


bool HashTable_Insert(HashTable *table, Data_t* key, Data_t* value)
{
	// Get index to array of HashTableNode*
	unsigned int index = hash(table,key);
		
	/* Check if the same key already exist in the table */
	// If there is already node on index
	if(table->buckets[index] != NULL)
	{
		HashTableNode* existingNode = table->buckets[index];	
		// Go throw the list of nodes on the same index
		do
		{
			// Check if in table already exists same key, if yes return FALSE 
			if(Data_Cmp(existingNode->key, key) == 0)
			{
				return false;
			}
			existingNode = existingNode->next;
		}while(existingNode != NULL);
	}
	
	// alocate new node
	HashTableNode* newNode = myMalloc(sizeof(HashTableNode));
	newNode->key = key;
	newNode->value = value;
	
	// Place new node to the beggining of the list
	HashTableNode* tmpNode = table->buckets[index];
	table->buckets[index] = newNode;
	newNode->next = tmpNode;
	table->count++;
	return true;
}


bool HashTable_Delete(HashTable *table, Data_t* key)
{
	// Get index to array of HashTableNode*
	unsigned int index = hash(table,key);
	
	// Search node to delete
	if(table->buckets[index] != NULL)
	{
		HashTableNode* parrentOfExistingNode = table->buckets[index];	
		HashTableNode* existingNode = table->buckets[index];	
		// Go throw the list of nodes on the same index
		do
		{
			// Check if in table already exists same key
			if(Data_Cmp(existingNode->key, key) == 0)
			{ // We found it!
				// Set parrents next to NULL and free the node
				parrentOfExistingNode->next = NULL;
				myFree(existingNode->key);
				if(table->delete_contents) myFree(existingNode->value);
				myFree(existingNode);
				table->count--;
				return true;
			}
			parrentOfExistingNode = existingNode;
			existingNode = existingNode->next;
		}while(existingNode != NULL);
	}
	
	// We did not foud it :(
	return false;
}

Data_t* HashTable_Find(HashTable *table, Data_t* key)
{
	// Get index to array of HashTableNode*
	unsigned int index = hash(table,key);

	// Search node
	if(table->buckets[index] != NULL)
	{
		HashTableNode* existingNode = table->buckets[index];	
		// Go throw the list of nodes on the same index
		do
		{
			// Check if in table already exists same key
			if(Data_Cmp(existingNode->key, key) == 0)
			{ // We found it!
				return existingNode->value;
			}
			existingNode = existingNode->next;
		}while(existingNode != NULL);
	}

	// We did not foud it :(
	return NULL;
}

void HashTable_Clear(HashTable* table)
{
	// go throw array of pointers to HashTableNode* 
	for(int i=0; i < table->size; i++)
	{
		// get pointer to node
		HashTableNode* node = table->buckets[i];
		// Set node in array to NULL
		table->buckets[i] = NULL;
		if(node != NULL)
		{
			HashTableNode* next;
			do
			{
				next = node->next;
				myFree(node->key);
				if(table->delete_contents)
				{
					myFree(node->value);
				}
				myFree(node);
				node = next;
			}while(node != NULL);
			node = NULL;
		}
	}
	table->count = 0;
}

void HashTable_Process(HashTable* table, TableNodeProc proc)
{
	// go throw array of pointers to HashTableNode* 
	for(int i=0; i < table->size; i++)
	{
		// get pointer to node
		HashTableNode* node = table->buckets[i];
		if(node != NULL)
		{
			HashTableNode* next;
			do
			{
				next = node->next;
				// Call process function on node
				proc(node->key, node->value);
				node = next;
			}while(node != NULL);
		}
	}
}

size_t HashTable_Get_Count(HashTable* table)
{
	return table->count;
}


