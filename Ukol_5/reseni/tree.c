#include <stdio.h>
#include "tree.h"
#include "mymalloc.h"

#define DEBUG

/*!
 * \brief Provede inicializaci stromu před jeho použitím.
 * \param tree Ukazatel na inicializovaný strom
 * \param deletecontents Při mazání uzlu stromu smaž také data uzlu
 */
void Tree_Init(Tree* root)
{
    *root = NULL;
}

void Tree_Dispose_Node(Tree node)
{
    myFree(node);
}

/*!
 * \brief Odstraní všechny listy stromu.
 * \param tree Ukazatel na strom
 */
void Tree_Clear(Tree* root)
{
    // TODO inorder with myfree()

    Tree_Process(*root, Tree_Dispose_Node, procPOSTORDER);
    *root = NULL;
}

TreeNode * Tree_Create_New_Node(Data_t* data)
{
        TreeNode* newNode = (TreeNode* ) myMalloc(sizeof(TreeNode));
        newNode->data = *data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
}

/*!
 * \brief Vytvoří uzel s daty a vloží ho do stromu na správnou pozici.
 * \param tree Ukazatel na strom, kam má být nový uzel vložen
 * \param data Ukazatel na data stromu
 * \return Fce vrátí hodnotu TRUE proběhla-li operace úspěšně. V případě, že se nepodařilo vytvořit
 * nový uzel, nebo strom ji obsahuje uzel se stejnými daty, bude vrácena hondota FALSE.
 */
bool Tree_Insert(Tree* root, Data_t* data)
{
        if(*root == NULL)
        {
            *root = Tree_Create_New_Node(data);
            return true;
        }
        else
        { // tree is not empty
            TreeNode* actNode = *root;
            int compareResult;
            do
            {
                // &(actNode->data) because we need pointer to data
                compareResult = Data_Cmp(data, &(actNode->data));
                // data->name is lesser than &(actNode->data).name (see how does work Data_Cmp function)
                if(compareResult < 0)
                {
                    if(actNode->left == NULL)
                    {
                        actNode->left = Tree_Create_New_Node(data);
                        return true;
                    }
                    else
                    {
                        actNode = actNode->left;
                    }
                }
                // Names are equal
                else if(compareResult == 0)
                {
                    return false;
                }
                // data->name is greater than &(actNode->data).name
                else
                {
                    if(actNode->right == NULL)
                    {
                        actNode->right = Tree_Create_New_Node(data);
                        return true;
                    }
                    else
                    {
                        actNode = actNode->right;
                    }
                }
            // relatively infinite loop (at the end of tree it return TRUE or FALSE)
            }while(1);
        }

        // This should never happen
        return false;
}

/*!
 * \brief Smaže uzel ze stromu obsahující data o dané hodnotě dle příslušných pravidel (viz. přednáška) včetně jeho dat, je-li příznak stromu "deleteContents" roven TRUE.
 * \param tree Ukazatel na strom, odkud má být uzel smazán
 * \param data Ukazatel na data obsažená v mazaném uzlů (může se jednat o jinou instanci Data_tu; důležité je pouze hodnota)
 */
// This is rewriten algorithm from lesson from Pascal to C see http://vyuka.fai.utb.cz/mod/resource/view.php?id=19702
void Tree_Delete(Tree* root, Data_t* data)
{
    //first we have to find node to del (if exists)
    TreeNode** fathersLeftOrRight = root; // Pointer to father's left or right
    TreeNode* tmpNode = *root;
    bool finded = false;
    int compareResult;
    while(tmpNode != NULL && !finded )
    {
        compareResult = Data_Cmp(data, &(tmpNode->data));

        // data are equal
        if(compareResult == 0)
        {
            finded = true;
        }
        else
        {
            // Ternary operator
            fathersLeftOrRight = (compareResult < 0) ? &(tmpNode->left) : &(tmpNode->right);
            tmpNode = (compareResult < 0) ? tmpNode->left : tmpNode->right;
        }
    }

    // now we know if we find node to delete (tmpNode). If yes so lets delete him
    if(finded)
    {
        #ifdef DEBUG
            printf("Finded!\n");
        #endif
        // If node has no children
        if(tmpNode->left == NULL && tmpNode->right == NULL)
        {
            #ifdef DEBUG
                printf("Deleted node has no children!\n");
            #endif
            myFree(tmpNode);
            // finded node is root so we have to set to NULL root too
            if(fathersLeftOrRight==NULL)
            {
                root = NULL;
            }
            else
            {
                fathersLeftOrRight = NULL;
            }
        }
        // Node has ONE child!
        else if (tmpNode->left == NULL || tmpNode->right == NULL)
        {
            #ifdef DEBUG
                printf("Deleted node has one child!\n");
            #endif
            // If node has only left child
            if(tmpNode->left != NULL)
            {
                *fathersLeftOrRight = tmpNode->left;
            }
            // Node has only right child!
            else
            {
                *fathersLeftOrRight = tmpNode->right;
            }
            myFree(tmpNode);
        }
        /* Most dificult scenario node has both children
            Because it is binary tree (all childs on left side are less
            and all on right side are greater) so we have two options:
                1) Choose the biggest node from left part of subtree = choose
                   THE MOST RIGHT node from LEFT SUBREE
                2) Choose the less node from the right subtree = choose
                   THE MOST LEFT node from the RIGHT SUBTREE
            Why the most right or most left? Because it is binary tree
            * (The less values are on the right part of tree)!*/

        // We will choose option 1
        else
        {
            #ifdef DEBUG
                printf("Deleted node has both children!\n");
            #endif
            TreeNode* tmpLeft = tmpNode->left; // this is root of the left subtree
            // Root of the left subtree has no right son so replace deleted node by tmpLeft
            if(tmpLeft->right == NULL)
            {
                tmpLeft->right = (*fathersLeftOrRight)->right;
                *fathersLeftOrRight = tmpLeft;
                myFree(tmpNode);
            }
            // Right is not NULL so we have to find the most right
            else
            {
                TreeNode* theMostRight = tmpLeft->right;
                TreeNode* fatherOfMostRight = tmpLeft;
                TreeNode* theMostRightRightSon = theMostRight->right;
                while(theMostRightRightSon != NULL)
                {
                    fatherOfMostRight = theMostRight;
                    theMostRight = theMostRight->right;
                    theMostRightRightSon = theMostRight->right;
                }
                // Now the trick, replace data of deleted node with most right
                tmpNode->data = theMostRight->data;
                fatherOfMostRight->right = theMostRight->left;
                // All data is now replaced, so we don't need the most right
                free(theMostRight);
            }
        }
    }
}

/*!
 * \brief Vrátí data uzlu.
 * \param node Ukazatel na data
 * \return Ukazatel na data uložená v uzlu
 */
Data_t* Tree_Get_Data(TreeNode* root)
{
    return &(root->data);
}

/*!
 * \brief Vrátí ukazatel na uzel, který drží daná data.
 * \param tree Ukazatel na strom, ve kterém má být uzel vyhledán
 * \param data Ukazatel na data, která budou hledána
 * \return Fce vrátí ukazatel na uzel držící hledaná data pokud existuje, jinak vrátí NULL
 */
 // This funcion is implemented by recursion search
Tree Tree_Find_Node(Tree root, Data_t* data)
{
    //Data_Cmp(Data_t* d1, Data_t* d2)
    if(root == NULL)
        return NULL;

    int compareResult = Data_Cmp(&(root->data), data);
    if(compareResult == 0)
    {
        return root;
    }
    else if (compareResult > 0)
    {
        return Tree_Find_Node(root->left ,data);
    }
    else // if (compareResult > 0)
    {
        return Tree_Find_Node(root->right, data);
    }

}

/*!
 * \brief Spočítá všechny uzly stromu.
 * \param tree Ukazatel na strom
 * \return Fce vrátí počet uzlů stromu
 */
size_t Tree_Get_Count(Tree root)
{
        size_t size = 0;
        if(root != NULL)
            size = 1 + Tree_Get_Count(root->left) + Tree_Get_Count(root->right);
        return size;
}

void Tree_Print_Node(Tree node)
{
    Data_Print(&(node->data));

    printf(" | L->");
    if (node->left == NULL)
        printf("NULL\n");
    else
        Data_Print(&(node->left->data));

    printf(" | R->");
    if (node->right == NULL)
        printf("NULL\n");
    else
        Data_Print(&(node->right->data));
}

/*!
 * \brief Zpracuje každý uzel stromu pomocí funkce specifikované ukazatelem "proc". Průchod stromem
 * může být trojí: PREORDER, INORDER a POSTORDER.
 * \param tree Ukazatel na strom jehož uzly mají být zpracovány
 * \param proc Ukazatel na callback funkci pro zpracování uzlu
 * \param mode Typ průchodu stromem (viz. výčtový typ TreeProcessMode)
 * \sa TreeProcessMode
 */
void Tree_Process(Tree root, TreeNodeProc proc, TreeProcessMode mode)
{
    if(root == NULL)
        return;

    if(mode == procPREORDER) 	proc(root);
    Tree_Process(root->left, proc, mode);
    if(mode == procINORDER)	proc(root);
    Tree_Process(root->right, proc, mode);
    if(mode == procPOSTORDER) proc(root);
}

// http://articles.leetcode.com/2010/04/maximum-height-of-binary-tree.html
// Rekurzivni metoda na spocitani maximalni hloubky stromu
int Tree_Get_Max_Height(Tree node)
{
    if(node == NULL)
        return 0;

    int leftHeight = Tree_Get_Max_Height(node->left);
    int rightHeight = Tree_Get_Max_Height(node->right);
    return (leftHeight > rightHeight) ? leftHeight +1 : rightHeight +1;
}

// http://www.geeksforgeeks.org/maximum-width-of-a-binary-tree/
// Vrati hloubku v danem levelu stromu
// Postupne se zanorujeme, snizujeme o jednicku level, az narazime na level
// ktery hledame tj. level == 1 a v tu chvili vratime 1
int Tree_Get_Width(Tree node, int level)
{
    if(node == NULL)
    {
        return 0;
    }

    if(level == 1)
        return 1;

    else if (level > 1)
    {
        // Zde se vše jedničky zase zbírají
        return Tree_Get_Width(node->left, level -1) + Tree_Get_Width(node->right, level -1);
    }
    else
        return 0;
}

// http://www.geeksforgeeks.org/maximum-width-of-a-binary-tree/
int Tree_Get_Max_Width(Tree node)
{
    int maxWidth = 0;
    int width;
    int h = Tree_Get_Max_Height(node);
    #ifdef DEBUG
        printf("Maximalni hloubka je %d\n", h);
    #endif
    for(int i=1; i <= h; i++)
    {
        width = Tree_Get_Width(node, i);
        #ifdef DEBUG
            printf("Sirka na levelu %d je %d\n", i, width);
        #endif
        if(width > maxWidth)
            maxWidth = width;
    }

    return maxWidth;
}

void Rozdil(Tree* tree1, Tree* tree2)
{
    if(*tree1 == NULL)
        return;

    // Rekurzivně procházím strom pomocí průchodu postorder
    Rozdil(&((*tree1)->left), tree2);
    Rozdil(&((*tree1)->right), tree2);
    TreeNode* tmpNode =  Tree_Find_Node(*tree2, &((*tree1)->data));
    if(tmpNode != NULL)
    {   //data existují ve stromu 2, takže je smažu ze stromu1
        Tree_Delete(tree1, &((*tree1)->data));
    }
}
