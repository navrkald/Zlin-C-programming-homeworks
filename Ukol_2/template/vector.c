/**
 * @file    vector.h
 * @author  Roman Dosek
 * @date    2/2015
 * @brief   Implementation of Vector structure
 */

#include "vector.h"
#include <stdlib.h>
#include <assert.h>

/**
 * @brief   Vytvoří Vector s počáteční velikostí speicifikovanou parametrem
 * @param   initial_size    počáteční velikost Vectoru
 * @param   alloc_step      Určuje, po jak velkých blocích se přialokovává paměť
 * @return  Vrací strukturu popisující Vector
 */
Vector_t Vector_Create(uint64_t initial_size, uint32_t alloc_step)
{

}

/**
 * @brief   Vytvoří samostatnou kopii Vectoru
 * @param   original    Ukazatel na kopírovaný Vector
 * @return  Vrací strukturu popisující zkopírovaný Vector
 */
Vector_t Vector_Copy(Vector_t *original)
{

}

/**
 * @brief   Vymaže obsah Vectoru a nastaví jeho velikost na 0
 * @param   vector  Ukazatel na Vector
 */
void Vector_Clear(Vector_t *vector)
{

}

/**
 * @brief   Vrací aktuální délku Vectoru
 * @param   vector  Ukazatel na Vector
 * @return  Aktuální délka Vectoru
 */
uint64_t Vector_Length(Vector_t *vector)
{
}

/**
 * @brief   Navrací hodnotu Vectoru na vybraném umístění
 * @param   vector      Ukazatel na Vector
 * @param   position    Pozice v rámci Vectoru
 * @return  Vrací nalezenou hodnotu nebo 0
 */
uint64_t Vector_At(Vector_t *vector, uint64_t position)
{
}

/**
 * @brief   Odstraní prvek na vybrané pozici
 * @param   vector      Ukazatel na Vector
 * @param   position    Pozice v rámci Vectoru
 * @return  Vrací true pokud byla pozice uvnitř rozsahu
 */
bool Vector_Remove(Vector_t *vector, uint64_t position)
{
}

/**
 * @brief   Přidá novou hodnotu na konec Vectoru
 * @param   vector  Ukazatel na Vector
 * @param   value   Vkládaná hodnota
 */
void Vector_Append(Vector_t *vector, uint64_t value)
{
}

/**
 * @brief   Funkce slouží k zjištění, jestli se někde ve Vectoru nachází daná hodnota
 * @param   vector  Ukazatel na Vector
 * @param   value   Hledaná hodnota
 * @return  Vrací true pokud je hodnota nalezena, jinak false
 */
bool Vector_Contains(Vector_t *vector, uint64_t value)
{
}

/**
 * @brief   Hledá pozici prvku s danou hodnotou ve Vectoru
 * @param   vector  Ukazatel na Vector
 * @param   value   Hledaná hodnota
 * @param   from    Pozice od které se začíná hledat
 * @return  Vrací pozici prvku pokud je nalezen, jinak -1
 */
int64_t Vector_IndexOf(Vector_t *vector, uint64_t value, uint64_t from)
{

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

}
