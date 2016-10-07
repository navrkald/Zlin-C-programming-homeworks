#ifndef LIST_H
#define LIST_H
#include <stdbool.h>
#include "data.h"
/*!
 * \file list.h
 * \brief Header file for ADT Linked List module
 *
 * Here you can find the complete implementation of Linked List ADT - definition of data
 * types and methods, which works with it
 */

//typedef enum {false, true} bool; /* pro ANSI C si nadefinujeme bool */


/************************************************************************/
/** \struct List_Node_s
 * Here is the definition of single node of linked list .
 *
 * \var typedef List_Node_s List_Node_t
 * \var typedef List_Node_t * List_Node_Ptr_t
 */
typedef struct List_Node_s
{	Data_t data;                /**< data part of item */
	struct List_Node_s * next; /**<	pointer to the next item */
} List_Node_t;

typedef List_Node_t * List_Node_Ptr_t;

/************************************************************************/
/** \struct List_t
 * Here the list is defined as a pointer to the first and active item.
 */
typedef struct {
	List_Node_t *  first;					/**< pointer to the first item of list */
	List_Node_t *  active;					/**< pointer to the active item of list */
} List_t;


/************************************************************************/
/** \fn void ListInit(List_t* list)
 * \brief Initializes the list before the first use.
 * \param list - pointer to list to be initializeds
 *
 *	List is initialized by setting pointers \link List_t#first list->first \endlink and
 *	\link List_t#active list->active \endlink to NULL.
 */
void List_Init(List_t * list);

/************************************************************************/
/** \fn void InsertFirst(List_t* list, Data_t data)
 * \brief Creates new item and inserts it to the start of the list
 * \param list - used list
 * \param data - data that are supposed to be inside created item
 *
 *	Creates new item with data part data and inserts it to start of the list
 */
void List_Insert_First(List_t* list, Data_t data);

/************************************************************************/
/** \fn void First(List_t* list)
 * \brief Sets pointer to active item to the first item
 * \param list - used list
 *
 *	Sets \link List_t#active list->active \endlink to value
 *	\link List_t#first list->first \endlink
 */
void List_First(List_t* list);

/************************************************************************/
/** \fn Data_t CopyFirst(List_t list)
 * \brief Returns the data of first item of list
 * \param list - used list
 */
Data_t List_Copy_First(List_t list);

/************************************************************************/
/** \fn void DeleteFirst(List_t* list)
 * \brief Removes the first item inside the list
 * \param list - used list
 *
 *	 If the first item was active, the activity is lost
 *   If the list was empty, nothing is done
 */
void List_Delete_First(List_t* list);

/************************************************************************/
/** \fn void PostDelete(List_t* list)
 * \brief Removes the item after active one
 * \param list - used list
 *
 *   If the list was not active, no action.
 *   If the list was empty, no action.
 */
void List_Post_Delete(List_t* list);

/************************************************************************/
/** \fn void PostInsert(List_t* list, Data_t data)
 * \brief Insert the new item after the active one.
 * \param list - used list
 * \param data - data content of the new item
 *
 *	Creates new item with data part "data" and inserts it after the active item of the list
 *  "list". If list was not active, nothing is performed.
 */
void List_Post_Insert(List_t* list, Data_t data);


/************************************************************************/
/** \fn Data_t LCopy(List_t list)
 * \brief Returns data of the active item.
 * \param list - used list
 *
 * If the list was not active, calls Error procedure.
 */
Data_t List_Copy(List_t list);

/************************************************************************/
/** \fn void Actualize(List_t* list, Data_t data)
 * \brief Owerwrites the data content of active item with new data.
 * \param list - used list
 * \param data - new data of item
 *
 *  If the list is not active, nothing is performed.
 */
void List_Actualize(List_t* list, Data_t data);


/************************************************************************/
/** \fn void LSucc(List_t* list)
 * \brief Shifts activity to the next item inside the list.
 * \param list - used list
 *
 *  If there is no active item, nothing is performed.
 */
void List_Succ(List_t* list);

/************************************************************************/
/** \fn bool Active(List_t list)
 * \brief If the list is active, returns true; else false.
 * \param list - used list
 */
bool List_Is_Active(List_t list);

/************************************************************************/
/** \fn void printNode(List_Node_t* node);
 * \brief Print one node
 * \param node
 */
void printNode(List_Node_t* node);

/************************************************************************/
/** \fn void printList(List_t list);
 * \brief Print content of the list.
 * \param list - used list
 */
void printList(List_t list);
#endif
