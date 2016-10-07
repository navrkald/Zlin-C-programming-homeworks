/**
 * @file    vector.h
 * @author  Roman Dosek
 * @date    2/2015
 * @brief   Headers of Vector data structure
 */

#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdint.h>
#include <stdbool.h>

/* Vector structure */
typedef struct {

    uint64_t *items;        /**< Internal pointer to allocated memory */
    uint64_t size;          /**< Number of currently allocated cells */
    uint64_t free_cells;     /**< Number of unused cells inside Vector */
    uint32_t alloc_step;    /**< Number of cells allocated during expanding */
} Vector_t;

/* Public Vector API */
Vector_t Vector_Create(uint64_t initial_size, uint32_t alloc_step);
Vector_t Vector_Copy(Vector_t *original);
void Vector_Clear(Vector_t *vector);
uint64_t Vector_Length(Vector_t *vector);
uint64_t Vector_At(Vector_t *vector, uint64_t position);
bool Vector_Remove(Vector_t *vector, uint64_t position);
void Vector_Append(Vector_t *vector, uint64_t value);
bool Vector_Contains(Vector_t *vector, uint64_t value);
int64_t Vector_IndexOf(Vector_t *vector, uint64_t value, uint64_t from);
void Vector_Fill(Vector_t *vector, uint64_t value, uint64_t start_position, uint64_t end_position);

#endif //__VECTOR_H
