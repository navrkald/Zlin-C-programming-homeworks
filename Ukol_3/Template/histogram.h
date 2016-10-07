#ifndef __HISTOGRAM_H
#define __HISTOGRAM_H

#include "vector.h"

int Histogram_AnalyzeFile(Vector_t *vector, char *filename);
void Histogram_Visualize(Vector_t *vector, uint8_t box_num);

#endif //__HISTOGRAM_H
