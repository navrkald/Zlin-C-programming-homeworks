#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "ioutils.h"
#include "histogram.h"

int main(void)
{
    long box_num = 0;

    printf("Histogram\n");

    Vector_t vector = Vector_Create(10, 10);

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    while (1) {
            printf("Stisknete:\n"
                    "1 pro nacteni noveho souboru\n"
                    "2 pro vypis histogramu\n"
                    "3 pro vymazani obsahu vektoru\n"
                    "cokoli jineho pro konec.\n");
            switch (io_utils_get_char_line()) {
            case '1':
                printf("Vlozte absolutni nebo relativni cestu k souboru:\n");
                char filename[101];
                io_utils_get_string(filename, 100);
                memset(filename + strlen(filename)-1, 0, 1);
                if(Histogram_AnalyzeFile(&vector, filename) != 0) 
                {
                    printf("Nacitani souboru selhalo...\n");
                }
                break;
            case '2':
                printf("Zadejte pocet boxu histogramu:\n");
                io_utils_get_long(&box_num);
                Histogram_Visualize(&vector, box_num);
                break;
            case '3':
                Vector_Clear(&vector);
                break;
            default:
                return 0;
                break;
            }
        };

    return 0;
}

