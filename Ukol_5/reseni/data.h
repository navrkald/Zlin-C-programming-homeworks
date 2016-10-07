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
 * Zde je definov�n datov� typ, se kter�m budeme pracovat.
 */
typedef struct {
    char jmeno[255];        /**< jm�no �lov�ka */
    double vek, vaha, vyska; /**< v�k, v�ha, v��ka */
} Data_t;



/************************************************************************/
/** \fn int Data_Cmp(Data_t* d1, Data_t* d2)
 * \brief Porovn� data d1 a d2.
 * \param d1 - ukazatel na prvn� data
 * \param d2 - ukazatel na druh� data
 * \return -1, pokud d1<d2. 0, pokud d1==d2. 1, pokud d1>d2
 */

int Data_Cmp(Data_t* d1, Data_t* d2);


/************************************************************************/
/** \fn int Data_Get(Data_t* data)
 * \brief Z�sk� od u�ivatele hodnoty pro data jednoho uzlu
 * \param data - ukazatel na strukturu data, kterou m� u�ivatel naplnit
 */

void Data_Get(Data_t * data);

/************************************************************************/
/** \fn int Data_Print(Data_t* data)
 * \brief Vytiskne data
 * \param data - ukazatel na strukturu data
 */
void Data_Print(Data_t * data);


#endif /* DATA_H_ */
