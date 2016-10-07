#include "list.h"
#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h>

void List_Init(List_t * list)
{
	list->first = NULL;
	list->active = NULL;
}

/************************************************************************/
/** \fn void InsertFirst(List_t* list, Data_t data)
 * \brief Creates new item and inserts it to the start of the list
 * \param list - used list
 * \param data - data that are supposed to be inside created item
 *
 *	Creates new item with data part data and inserts it to start of the list
 */
void List_Insert_First(List_t* list, Data_t data)
{
	List_Node_t* newNode = myMalloc(sizeof(List_Node_t));
	newNode->data = data;
	newNode->next = list->first;
	list->first = newNode;
}

/************************************************************************/
/** \fn void First(List_t* list)
 * \brief Sets pointer to active item to the first item
 * \param list - used list
 *
 *	Sets \link List_t#active list->active \endlink to value
 *	\link List_t#first list->first \endlink
 */
void List_First(List_t* list)
{
	list->active = list->first;
}

/************************************************************************/
/** \fn Data_t CopyFirst(List_t list)
 * \brief Returns the data of first item of list
 * \param list - used list
 */
Data_t List_Copy_First(List_t list)
{
	if (list.first != NULL)
		return list.first->data;
	else
	{
		fprintf(stderr, "Fatal error: List_Copy_First - empty list!");
		exit(EXIT_FAILURE);
	}
}

/************************************************************************/
/** \fn void DeleteFirst(List_t* list)
 * \brief Removes the first item inside the list
 * \param list - used list
 *
 *	 If the first item was active, the activity is lost
 *   If the list was empty, nothing is done
 */
void List_Delete_First(List_t* list)
{
	if(list->first != NULL)
	{
		// Get first item
		List_Node_t* nodeToDel = list->first;
		
		// Get rid of ative node
		if(list->active == nodeToDel)
			list->active = NULL;
		
		// Set new first item
		list->first = nodeToDel->next;
		
		// Delete old first
		myFree(nodeToDel);
	}
}

/************************************************************************/
/** \fn void PostDelete(List_t* list)
 * \brief Removes the item after active one
 * \param list - used list
 *
 *   If the list was not active, no action.
 *   If the list was empty, no action.
 */
void List_Post_Delete(List_t* list)
{
	// Is some item active?
	if(List_Is_Active(*list))
	{
		List_Node_t* nodeToDel;
		// If is something to delete
		if(( nodeToDel = list->active->next) != NULL)
		{
			// Set new ancessor
			list->active->next = nodeToDel->next;
			// Free nodeToDel
			myFree(nodeToDel);
		}
	}
}

/************************************************************************/
/** \fn void PostInsert(List_t* list, Data_t data)
 * \brief Insert the new item after the active one.
 * \param list - used list
 * \param data - data content of the new item
 *
 *	Creates new item with data part "data" and inserts it after the active item of the list
 *  "list". If list was not active, nothing is performed.
 */
void List_Post_Insert(List_t* list, Data_t data)
{
	// Is some item active?
	if(List_Is_Active(*list))
	{
		List_Node_t* newNode = myMalloc(sizeof(List_Node_t));
		newNode->data = data;
		newNode->next = list->active->next;
		list->active->next = newNode;
	}
}


/************************************************************************/
/** \fn Data_t LCopy(List_t list)
 * \brief Returns data of the active item.
 * \param list - used list
 *
 * If the list was not active, calls Error procedure.
 */
Data_t List_Copy(List_t list)
{
		if (List_Is_Active(list))
		{
			return list.active->data;
		}
		else
		{
			fprintf(stderr, "Fatal error: List_Copy - there is no active item!");
			exit(EXIT_FAILURE);
		}
}

/************************************************************************/
/** \fn void Actualize(List_t* list, Data_t data)
 * \brief Owerwrites the data content of active item with new data.
 * \param list - used list
 * \param data - new data of item
 *
 *  If the list is not active, nothing is performed.
 */
void List_Actualize(List_t* list, Data_t data)
{
		if(List_Is_Active(*list))
		{
			list->active->data = data;
		}
}


/************************************************************************/
/** \fn void LSucc(List_t* list)
 * \brief Shifts activity to the next item inside the list.
 * \param list - used list
 *
 *  If there is no active item, nothing is performed.
 */
void List_Succ(List_t* list)
{
		if(List_Is_Active(*list))
		{
			list->active = list->active->next;
		}
}

/************************************************************************/
/** \fn bool Active(List_t list)
 * \brief If the list is active, returns true; else false.
 * \param list - used list
 */
bool List_Is_Active(List_t list)
{
	return list.active != NULL;
}

/************************************************************************/
/** \fn void printNode(List_Node_t* node);
 * \brief Print one node
 * \param node
 */
void printNode(List_Node_t* node)
{
		if(node == NULL)
			printf("NULL\n");
		else
			Data_Print(&(node->data));
}


/************************************************************************/
/** \fn void printList(List_t list);
 * \brief Print content of the list.
 * \param list - used list
 */
void printList(List_t list)
{
	printf("Aktivni polozka:\n");
	printNode(list.active);
	printf("Obsah seznamu:\n");
	int index = 1;
	List_Node_t* node = list.first;
	while(node != NULL)
	{
		printf("%d. prvek: ", index);
		printNode(node);
		index++;
		node = node->next;
	}
	printf("\n");
}


