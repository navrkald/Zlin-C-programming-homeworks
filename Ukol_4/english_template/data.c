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
	printf("Enter person's name: ");
    io_utils_get_string(data->name, 255);
    eoln_pos=strcspn(data->name, "\n\r");        /* Finds position of end of line */
    data->name[eoln_pos]=0;                      /* and "cut" end of line character */

    printf("Enter age, weight and height(separated by Enter):\n");
    io_utils_get_double(&data->age);
    io_utils_get_double(&data->weight);
    io_utils_get_double(&data->height);
}

void Data_Print(Data_t * data) {
    printf("Name=%s, age=%0.1lf, weight=%0.1lf, height=%0.1lf\n",
            data->name, data->age, data->weight, data->height);
}

