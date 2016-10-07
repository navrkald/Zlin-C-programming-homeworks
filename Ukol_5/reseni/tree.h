#ifndef _TREE_H_
#define _TREE_H_

#include <stdbool.h>
#include <stdlib.h>

#include "data.h"

////////////////////////////////////////////////////////////////////////////////
// definice datových struktur

/*!
 * \brief Datová struktura listu stromu.
 */
typedef struct _TreeNode {
    Data_t  data;				/**< Data listu stromu */
    struct _TreeNode * left;	/**< Ukazatel na levý list stromu */
    struct _TreeNode * right;	/**< Ukazatel na pravý list stromu */
} TreeNode;

/*!
 * \brief Datová struktura stromu.
 */
typedef TreeNode * Tree;

/*!
 * \brief Způsob průchodu stromem.
 */
typedef enum _TreeProcessMode {
    procPREORDER = 1,		/**< Data uzlu jsou zpracována před oběma jeho listy (= uzly budou zpracovány od kořene k listům) */
    procINORDER = 2,		/**< Nejprve zpracuj levý list, poté data a poté pravý list (= uzly budou zpracovány v seřazeném pořadí) */
    procPOSTORDER = 3		/**< Data uzlu jsou zpracována až po obou jeho listech (= uzly budou zpracovány od listů ke kořeni) */
} TreeProcessMode;

/*!
 * \brief Callback funkce pro zpracování uzlu při průchodu stromem.
 * \param Ukazetel na rodičovský strom zpracovávaného uzlu
 * \param Ukazatel na zpracovávaný uzel
 */
typedef void (*TreeNodeProc)(Tree node);

////////////////////////////////////////////////////////////////////////////////
// operace nad stromem

/*!
 * \brief Provede inicializaci stromu před jeho použitím.
 * \param tree Ukazatel na inicializovaný strom
 * \param deletecontents Při mazání uzlu stromu smaž také data uzlu
 */
void Tree_Init(Tree* root);

/*!
 * \brief Odstraní všechny listy stromu.
 * \param tree Ukazatel na strom
 */
void Tree_Clear(Tree* root);

/*!
 * \brief Vytvoří uzel s daty a vloží ho do stromu na správnou pozici.
 * \param tree Ukazatel na strom, kam má být nový uzel vložen
 * \param data Ukazatel na data stromu
 * \return Fce vrátí hodnotu TRUE proběhla-li operace úspěšně. V případě, že se nepodařilo vytvořit
 * nový uzel, nebo strom ji obsahuje uzel se stejnými daty, bude vrácena hondota FALSE.
 */
bool Tree_Insert(Tree* root, Data_t* data);

/*!
 * \brief Smaže uzel ze stromu obsahující data o dané hodnotě dle příslušných pravidel (viz. přednáška) včetně jeho dat, je-li příznak stromu "deleteContents" roven TRUE.
 * \param tree Ukazatel na strom, odkud má být uzel smazán
 * \param data Ukazatel na data obsažená v mazaném uzlů (může se jednat o jinou instanci Data_tu; důležité je pouze hodnota)
 */
void Tree_Delete(Tree* root, Data_t* data);

/*!
 * \brief Vrátí data uzlu.
 * \param node Ukazatel na data
 * \return Ukazatel na data uložená v uzlu
 */
Data_t* Tree_Get_Data(TreeNode* root);

/*!
 * \brief Vrátí ukazatel na uzel, který drží daná data.
 * \param tree Ukazatel na strom, ve kterém má být uzel vyhledán
 * \param data Ukazatel na data, která budou hledána
 * \return Fce vrátí ukazatel na uzel držící hledaná data pokud existuje, jinak vrátí NULL
 */
Tree Tree_Find_Node(Tree root, Data_t* data);

/*!
 * \brief Spočítá všechny uzly stromu.
 * \param tree Ukazatel na strom
 * \return Fce vrátí počet uzlů stromu
 */
size_t Tree_Get_Count(Tree root);

/*!
 * \brief Zpracuje každý uzel stromu pomocí funkce specifikované ukazatelem "proc". Průchod stromem
 * může být trojí: PREORDER, INORDER a POSTORDER.
 * \param tree Ukazatel na strom jehož uzly mají být zpracovány
 * \param proc Ukazatel na callback funkci pro zpracování uzlu
 * \param mode Typ průchodu stromem (viz. výčtový typ TreeProcessMode)
 * \sa TreeProcessMode
 */
void Tree_Process(Tree root, TreeNodeProc proc, TreeProcessMode mode);

TreeNode * Tree_Create_New_Node(Data_t* data);
void Tree_Dispose_Node(Tree node);
void Tree_Print_Node(Tree node);

int Tree_Get_Max_Height(Tree node);
int Tree_Get_Width(Tree node, int level);
int Tree_Get_Max_Width(Tree node);
void Rozdil(Tree* tree1, Tree* tree2);

#endif //_TREE_H_
