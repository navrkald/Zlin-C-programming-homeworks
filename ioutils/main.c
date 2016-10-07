#include <stdio.h>
#include "ioutils.h"

int main(void)
{
    /* Simple IOUtils showcase */

    /* Demonstrace načtení řeťezce */
    char hodnota_retezec[21] = {0};
    printf("Zadejte retezec: ");
    io_utils_get_string(hodnota_retezec, 20);
    memset(hodnota_retezec + strlen(hodnota_retezec) - 1, 0, 1);    /* Odstranění \n */
    printf("\n");

    /* Načtení znaku */
    char hodnota_znak;
    printf("Zadejte znak: ");
    io_utils_get_char_line(&hodnota_znak, 20);
    printf("\n");

    /* Načtení longu */
    long hodnota_long;
    printf("Zadejte dlouhé číslo: ");
    io_utils_get_long(&hodnota_long);
    printf("\n");

    /* Načtení doublu */
    double hodnota_double;
    printf("Zadejte hodnotu s desetinnou tečkou: ");
    io_utils_get_double(&hodnota_double);
    printf("\n");

    printf("-------------------\n");
    printf("Načtené hodnoty:\n");
    printf("-------------------\n");
    printf("Retezec: %s\n", hodnota_retezec);
    printf("Znak: %c\n", hodnota_znak);
    printf("Long: %d\n", hodnota_long);
    printf("Double: %f\n", hodnota_double);

    return 0;
}

