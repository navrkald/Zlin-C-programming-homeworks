#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "data.h"
#include "tree.h"
#include <string.h>

void printMenu()
{
    printf(
    "1 - tree_init()\n"
    "2 - tree_clear()\n"
    "3 - tree_insert()\n"
    "4 - tree_delete()\n"
    "5 - tree_find_node()\n"
    "6 - tree_get_node_count()\n"
    "7 - tree_proces()\n"
    "8 - Tree_Get_Max_Width()\n"
    "9 - Test odecteni 2 stromu\n"
    "M - zobraz toto menu\n"
    "K - konec\n"
    "Pro ukonceni stiskni CTRL+D (Linux) nebo CTRL+Z (Windows).\n"
    );
}

void printOption(char c)
{
    if((c >= '1' && c <= '8') || c=='K' || c=='M')
    {
        ;
    }
    else
    {
        printf("Neznama volba: '%c', vypisuji menu.\n",c);
    }
}

void readPassOption(int* passOption)
{
    // Infinite while until user puts correct input
    while(1)
    {
        printf(
            "Pruchod:\n"
            "1 - preorder\n"
            "2 - inorder\n"
            "3 - postorder\n"
            "\n"
        );

        scanf("%d", passOption);
        if(*passOption < 1 || *passOption > 3)
        {
            fprintf(stderr,"Spatna volba, opakujte prisim zadani znovu.\n");
        }
        // Correct option ending infinite loop
        else
            break;
    }

    printf("Vase volba:\n%d\n", *passOption);
}

void readData(Data_t * data)
{
    printf("Zadejte jmeno osoby: ");
    scanf("%254s",data->jmeno);
    #ifdef DEBUG
        printf("name: %s\n", data->name);
    #endif
    printf("Zadejte vek, vahu a vysku (oddelene Enter):\n");
    scanf("%lf", &(data->vek));
    scanf("%lf", &(data->vaha));
    scanf("%lf", &(data->vyska));
    #ifdef DEBUG
        printf("Vek=%0.1lf, vaha=%0.1lf, vyska=%0.1lf\n",data->vek, data->vaha, data->vyska);
    #endif
}

void testOdecteniStromu()
{
    Data_t data1, data2, data3, data4, data5, data6;

    strcpy(data1.jmeno,"Jmeno1");
    data1.vek = 1;
    data1.vaha = 1;
    data1.vyska = 1;

    strcpy(data2.jmeno,"Jmeno2");
    data2.vek = 2;
    data2.vaha = 2;
    data2.vyska = 2;

    strcpy(data3.jmeno,"Jmeno3");
    data3.vek = 3;
    data3.vaha = 3;
    data3.vyska = 3;

    strcpy(data4.jmeno,"Jmeno4");
    data4.vek = 4;
    data4.vaha = 4;
    data4.vyska = 4;

    strcpy(data5.jmeno,"Jmeno5");
    data5.vek = 5;
    data5.vaha = 5;
    data5.vyska = 5;

    strcpy(data6.jmeno,"Jmeno6");
    data6.vek = 6;
    data6.vaha = 6;
    data6.vyska = 6;

    Tree strom1;
    Tree strom2;
    Tree_Init(&strom1);
    Tree_Init(&strom2);

    Tree_Insert(&strom1, &data1);
    Tree_Insert(&strom1, &data2);
    Tree_Insert(&strom1, &data3);
    Tree_Insert(&strom1, &data4);
    Tree_Insert(&strom1, &data6);


    Tree_Insert(&strom2, &data2);
    Tree_Insert(&strom2, &data3);
    Tree_Insert(&strom2, &data4);
    Tree_Insert(&strom2, &data5);

    printf("Strom1: \n\n");
    Tree_Process(strom1,Tree_Print_Node, procINORDER);
    printf("Strom2: \n\n");
    Tree_Process(strom2,Tree_Print_Node, procINORDER);

    Rozdil(&strom1, &strom2);

    printf("Strom1 po odecteni: \n\n");
    Tree_Process(strom1,Tree_Print_Node, procINORDER);
    printf("Strom2: \n\n");
    Tree_Process(strom2,Tree_Print_Node, procINORDER);

}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    printf("Strom v1.0\n");
    printf("----------\n\n");
    Data_t data;
    Tree root;
    Tree tmpNode;
    int passOption;
    printMenu();
    int option;
    bool treeInitialized = false;
    printf("\nVase volba:\n");
    int maxWidthOfTree = 0;
    while ( (option = getchar()) != EOF)
    {
        if(option == '\n')
            continue;

        printOption(option);

        // Check if tree is initialized
        if(!treeInitialized && option != '1')
        {
            fprintf(stderr,"Strom neni inicializovan!\n\n");
            printf("Vase volba:\n");
            continue;
        }

        switch (option)
        {
            case '1':
                Tree_Init(&root);
                printf("Strom byl inicializovan.\n");
                treeInitialized = true;
                break;
            case '2':
                //vycistit strom
                Tree_Clear(&root);
                printf("Obsah stromu byl odstranen.\n");
                break;
            case '3':
                printf("Data uzlu stromu:\n");
                readData(&data);
                Tree_Insert(&root, &data);
                break;
            case '4':
                printf("Zadej mazana data:\n");
                readData(&data);
                Tree_Delete(&root, &data);
                break;
            case '5':
                printf("Zadej hledana data:\n");
                readData(&data);
                tmpNode = Tree_Find_Node(root, &data);
                if(tmpNode != NULL)
                {
                    //http://stackoverflow.com/questions/9053658/correct-format-specifier-to-print-pointer-address
                    printf("Data byla nalezena v uzlu na adrese %p.",(void *)tmpNode);
                }
                else
                {
                    printf("Data nebyla ve strome nalezena.\n");
                }
                break;
            case '6':
                printf("Pocet uzlu stromu: %zu", Tree_Get_Count(root));
                break;
            case '7':
                readPassOption(&passOption);
                Tree_Process(root, Tree_Print_Node, (TreeProcessMode) passOption);
                break;
            case '8':
                maxWidthOfTree = Tree_Get_Max_Width(root);
                printf("Maximální šířka stromu je:%d", maxWidthOfTree);
                break;

            case '9':
                printf("Test odecteni 2 stromu:\n\n");
                printf("\n\nKoncc testu:\n\n");
            case 'K':
                printf("Konec.");
                Tree_Clear(&root);
                return EXIT_SUCCESS;
                break;
            // For 'M' and everithing else print menu!
            case 'M':
            default:
                printMenu();
                break;
        }
        printf("\nVase volba:\n");


    }
    return EXIT_SUCCESS;
}
