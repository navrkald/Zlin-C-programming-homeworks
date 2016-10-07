/*
 * data.c
 *
 *  Created on: 9. 3. 2015
 *      Author: dulik
 */

#include <stdio.h>
#include <string.h>
#include "data.h"
#include "ioutils.h"

void Data_Get(Data_t * data) {
	int eoln_pos=0;
	printf("Zadejte jmeno osoby: ");
    io_utils_get_string(data->jmeno, 255);
    eoln_pos=strcspn(data->jmeno, "\n\r");        /* Najdi pozici konce øádku */
    data->jmeno[eoln_pos]=0;                      /* a "ustøihni" konec øádku */

    printf("Zadejte vek, vahu a vysku (oddelene Enter):\n");
    io_utils_get_double(&data->vek);
    io_utils_get_double(&data->vaha);
    io_utils_get_double(&data->vyska);
}

void Data_Print(Data_t * data) {
    printf("Jmeno=%s, vek=%0.1lf, vaha=%0.1lf, vyska=%0.1lf\n",
            data->jmeno, data->vek, data->vaha, data->vyska);
}

