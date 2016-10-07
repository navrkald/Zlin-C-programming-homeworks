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
/** \fn int Data_Get(Data_t* data)
 * \brief Z�sk� od u�ivatele hodnoty pro data jednoho uzlu seznamu
 * \param data - ukazatel na strukturu data, kterou m� u�ivatel naplnit
 */

void Data_Get(Data_t * data);
void Data_Print(Data_t * data);


#endif /* DATA_H_ */
