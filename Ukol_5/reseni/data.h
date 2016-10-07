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
/** \fn int Data_Cmp(Data_t* d1, Data_t* d2)
 * \brief Porovná data d1 a d2.
 * \param d1 - ukazatel na první data
 * \param d2 - ukazatel na druhá data
 * \return -1, pokud d1<d2. 0, pokud d1==d2. 1, pokud d1>d2
 */

int Data_Cmp(Data_t* d1, Data_t* d2);


/************************************************************************/
/** \fn int Data_Get(Data_t* data)
 * \brief Získá od uživatele hodnoty pro data jednoho uzlu
 * \param data - ukazatel na strukturu data, kterou má uživatel naplnit
 */

void Data_Get(Data_t * data);

/************************************************************************/
/** \fn int Data_Print(Data_t* data)
 * \brief Vytiskne data
 * \param data - ukazatel na strukturu data
 */
void Data_Print(Data_t * data);


#endif /* DATA_H_ */
