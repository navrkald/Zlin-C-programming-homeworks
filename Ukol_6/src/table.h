
#ifndef _TABLE_H_
#define _TABLE_H_

#include "data.h"
#include <stdbool.h>
#include <stddef.h>

////////////////////////////////////////////////////////////////////////////////
// datové struktury

/*!
 * \brief Položka tabulky.
 */
typedef struct _HashTableNode {
	Data_t *key;					/*< Klíč položky */
	Data_t *value;					/*< Hodnota položky */
	struct _HashTableNode *next;	/*< Ukazatel na další položku se stejným indexem */
} HashTableNode;

/*!
 * \brief Hash tabulka.
 */
typedef struct _HashTable {
	bool delete_contents;			/*< Je-li příznak nastaven na TRUE, bude při mazání položky tabulky odstraněna také hodnota (klíč bude odstraněn vdy) */
	HashTableNode **buckets;		/*< Položky tabulky (pole ukazatelů na položky = na počáteční
									* uzel seznamu položek se stejným hash-em ) */
	size_t size;					/*< Velikost (počet položek) pole buckets  */
	size_t count;					/*< Počet položek, uložených v hash tabulce */

} HashTable;

/*!
 * \brief Callback funkce pro zpracování položky tabulky.
 * \param key Klíč položky
 * \param value Hodnota položky
 */
typedef void (*TableNodeProc)(Data_t *key, Data_t *value);

////////////////////////////////////////////////////////////////////////////////
// pomocné funkce

/*!
 * \brief Vypočte index v tabulce na základě hodnoty zadaného klíče.
 * Index je vypočítán jako součet hodnot bytů v klíči modulo rozměr tabulky
 * kde každý byte v hodnotě klíče je navíc rotován o počet bitů daných jeho pozicí,
 * tj. byte na pozici 0 o 0 bitů, byte na pozici 1 o 1 bit, atd. Počet bytů v hodnotě klíče je
 * sizeof(T) kde T je datový typ klíče pro všechny typy kromě vtSTRING, nebo strlen(data)
 * pro vtSTRING.
 * \param table Ukazatel na tabulku
 * \param key Klíč
 * \return Vypočtený index
 */
unsigned int hash(HashTable *table, Data_t *key);



////////////////////////////////////////////////////////////////////////////////
// operace nad tabulkou

/*!
 * \brief Inicializuje tabulku (vytvoří pole ukazatelů na položky tabulky) a nastaví
 * velikost tabulky. Kadý prvek pole předtavuje počáteční uzel seznamu synonym (položek z jejichž
 * unikátního klíče vypočetla hash funkce neunikátní index).
 * \param table Ukazatel na inicializovanou tabulku
 * \param size Požadovaná velikost tabulky
 * \param deletecontents Je-li argument nastaven na TRUE, bude při mazání položky tabulky odstraněna také hodnota (klíč bude odstraněn vdy)
 */
void HashTable_Init(HashTable *table, size_t size, bool deletecontents);

/*!
 * \brief Destruuje tabulku (uvolní pole ukazatelů na tabulku a nastaví její velikost na nulu.
 * \param table Ukazatel na destruovanou tabulku
 */
void HashTable_Destruct(HashTable *table);

/*!
 * \brief Vytvoří novou položku a vloží ji do tabulky (na počátek seznamu synonym
 * ležícím na indexu spočteném pomocí hash funkce). Pokud bude předán duplicitní (v
 * tabulce již použitý) index, operace vložení nebude provedena.
 * \param table	Ukazatel na tabulku
 * \param key Ukazatel na klíč položky
 * \param value Ukazatel na hodnotu položky
 * \return Vrátí TRUE byla-li položka vložena do tabulky, jinak FALSE
 */
bool HashTable_Insert(HashTable *table, Data_t *key, Data_t *value);

/*!
 * \brief Odstraní položku identifikovanou klíčem z tabulky. Pokud taková položka neexistuje,
 * nic se neprovede.
 * \param table Ukazatel na tabulku
 * \param key Ukazatel na klíč položky
 * \return Vrátí TRUE byla-li položka odstraněna, jinak FALSE.
 */
bool HashTable_Delete(HashTable *table, Data_t *key);

/*!
 * \brief Vrátí hodnotu položky v tabulce identifikované jejím klíčem.
 * \param table Ukazatel na tabulku
 * \param key Ukazatel na klíč položky
 * \return Vrátí adresu hodnoty klíče pokud byla položka nalezena, jinak NULL
 */
Data_t* HashTable_Find(HashTable *table, Data_t *key);

/*!
 * \brief Vrátí počet položek v tabulce.
 * \param table Ukazatel na tabulku
 * \return Počet položek
 */
size_t HashTable_Get_Count(HashTable *table);

/*!
 * \brief Odstraní všechny položky z tabulky.
 * \param table Ukazatel na tabulku
 */
void HashTable_Clear(HashTable *table);

/*!
 * \brief Zpracuje všechny položky v tabulce pomocí funkce "proc".
 * \param table Ukazatel na tabulku
 * \param proc Ukazatel na callback funkci typu TableNodeProc
 */
void HashTable_Process(HashTable *table, TableNodeProc proc );


#endif //_TABLE_H_
