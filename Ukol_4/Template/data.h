/*
 * data.h
 *
 *  Created on: 9. 3. 2015
 *      Author: dulik
 */

#ifndef DATA_H_
#define DATA_H_

/************************************************************************/
/** \struct Data_t
 * Zde je definován datový typ, se kterým budeme pracovat.
 */
typedef struct {
    char jmeno[255];        /**< jméno èlovìka */
    double vek, vaha, vyska; /**< vìk, váha, výška */
} Data_t;

/************************************************************************/
/** \fn int Data_Get(Data_t* data)
 * \brief Získá od uživatele hodnoty pro data jednoho uzlu seznamu
 * \param data - ukazatel na strukturu data, kterou má uživatel naplnit
 */

void Data_Get(Data_t * data);
void Data_Print(Data_t * data);


#endif /* DATA_H_ */
