#ifndef LIST_H
#define LIST_H
#include <stdbool.h>
#include "data.h"
/*!
 * \file list.h
 * \brief Hlavi�kov� soubor modulu ADT Line�rn� seznam
 *
 * Zde najdete kompletn� implementaci ADT line�rn� seznam - tj. definici datov�ch
 * typ� a metod, kter� s nimi pracuj�
 */

//typedef enum {false, true} bool; /* pro ANSI C si nadefinujeme bool */


/************************************************************************/
/** \struct List_Node_s
 * Zde je definov�n jeden prvek line�rn�ho seznamu.
 *
 * \var typedef List_Node_s List_Node_t
 * \var typedef List_Node_t * List_Node_Ptr_t
 */
typedef struct List_Node_s
{	Data_t data;                /**< datov� ��st prvku */
	struct List_Node_s * next; /**<	ukazatel na dal�� prvek */
} List_Node_t;

typedef List_Node_t * List_Node_Ptr_t;

/************************************************************************/
/** \struct List_t
 * Zde je definov�n seznam jako ukazatel na prvn� a ukazatel na aktivn� prvek.
 */
typedef struct {
	List_Node_t *  first;					/**< ukazatel na prvn� prvek seznamu */
	List_Node_t *  active;					/**< ukazatel na aktivn� prvek seznamu */
} List_t;


/************************************************************************/
/** \fn void ListInit(List_t* list)
 * \brief Provede inicializaci seznamu p�ed jeho prvn�m pou�it�m.
 * \param list - seznam, kter� se m� inicializovat
 *
 *	Inicializace spo��v� v napln�n� ukazatel� \link List_t#first list->first \endlink a
 *	\link List_t#active list->active \endlink nulov�mi ukazateli
 */
void List_Init(List_t * list);

/************************************************************************/
/** \fn void InsertFirst(List_t* list, Data_t data)
 * \brief Vytvo�� nov� prvek a vlo�� jej na za��tek seznamu.
 * \param list - seznam, do kter�ho se m� nov� prvek vkl�dat
 * \param data - data, kter� maj� b�t obsahem nov�ho prvn�ho prvku
 *
 *	Vytvo�� nov� prvek s datovou ��st� "data" a vlo�� jej na za��tek seznamu "list"
 */
void List_Insert_First(List_t* list, Data_t data);

/************************************************************************/
/** \fn void First(List_t* list)
 * \brief Nastav� ukazatel aktivn�ho prvku na 1. prvek.
 * \param list - seznam, se kter�m m� b�t tato operace provedena
 *
 *	Nastav� \link List_t#active list->active \endlink na hodnotu
 *	\link List_t#first list->first \endlink
 */
void List_First(List_t* list);

/************************************************************************/
/** \fn Data_t CopyFirst(List_t list)
 * \brief Vr�t� data 1. prvku seznamu
 * \param list - seznam, se kter�m m� b�t tato operace provedena
 */
Data_t List_Copy_First(List_t list);

/************************************************************************/
/** \fn void DeleteFirst(List_t* list)
 * \brief Ru�� prvn� prvek seznamu.
 * \param list - seznam, se kter�m m� b�t tato operace provedena
 *
 *   Pokud byl prvn� prvek z�rove� aktivn�m prvkem, aktivita se ztr�c�.
 *   Pokud byl seznam pr�zdn�, nic se ned�je.
 */
void List_Delete_First(List_t* list);

/************************************************************************/
/** \fn void PostDelete(List_t* list)
 * \brief Ru�� prvn� prvek seznamu za aktivn�m prvkem.
 * \param list - seznam, se kter�m m� b�t tato operace provedena
 *
 *   Pokud nebyl seznam aktivn�, nic se ned�je.
 *   Pokud byl seznam pr�zdn�, nic se ned�je.
 */
void List_Post_Delete(List_t* list);

/************************************************************************/
/** \fn void PostInsert(List_t* list, Data_t data)
 * \brief Vlo�� nov� prvek za aktivn� prvek seznamu.
 * \param list - seznam, do kter�ho se m� nov� prvek vkl�dat
 * \param data - data, kter� maj� b�t obsahem nov�ho prvku
 *
 *	Vytvo�� nov� prvek s datovou ��st� "data" a vlo�� jej za aktivn� prvek
 *  seznamu "list". Pokud nebyl seznam aktivn�, ned�l� nic.
 */
void List_Post_Insert(List_t* list, Data_t data);


/************************************************************************/
/** \fn Data_t LCopy(List_t list)
 * \brief Vr�t� data aktivn�ho prvku seznamu
 * \param list - seznam, se kter�m m� b�t tato operace provedena
 *
 * Pokud seznam nen� aktivn�, vol� se procedura Error.
 */
Data_t List_Copy(List_t list);

/************************************************************************/
/** \fn void Actualize(List_t* list, Data_t data)
 * \brief P�ep�e obsah aktivn� polo�ky nov�mi daty.
 * \param list - seznam, do kter�ho se m� nov� prvek vkl�dat
 * \param data - data, kter� maj� b�t obsahem nov�ho prvku
 *
 *  Pokud nen� seznam aktivn�, ned�l� nic.
 */
void List_Actualize(List_t* list, Data_t data);


/************************************************************************/
/** \fn void LSucc(List_t* list)
 * \brief Posune aktivitu na n�sleduj�c� prvek seznamu.
 * \param list - seznam, se kter�m m� b�t tato operace provedena
 *
 *  Pokud nen� ��dn� prvek aktivn�, ned�l� nic.
 */
void List_Succ(List_t* list);

/************************************************************************/
/** \fn bool Active(List_t list)
 * \brief Je-li seznam aktivn�, vrac� true
 * \param list - seznam, se kter�m m� b�t tato operace provedena
 */
bool List_Is_Active(List_t list);

#endif
