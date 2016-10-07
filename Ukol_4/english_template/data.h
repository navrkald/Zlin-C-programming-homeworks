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
 * Here is the definition of type we are going to work with
 */
typedef struct {
    char name[255];        	/**< Person's name */
    double age, weight, height;	/**< age, weight, height */
} Data_t;

/************************************************************************/
/** \fn int Data_Get(Data_t* data)
 * \brief Získá od uživatele hodnoty pro data jednoho uzlu seznamu
 * \brief Gains values for data of one node from the user
 * \param data - pointer to data structure that is supposed to be filled by user
 */

void Data_Get(Data_t * data);
void Data_Print(Data_t * data);


#endif /* DATA_H_ */
