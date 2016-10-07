#ifndef __HISTOGRAM_H
#define __HISTOGRAM_H

#include "vector.h"

int Histogram_AnalyzeFile(Vector_t *vector, char *filename);
void Histogram_Visualize(Vector_t *vector, uint8_t box_num);
void Print_Histogram(uint64_t histogram[], uint8_t box_num, uint64_t min, uint64_t max, uint64_t boxWidth);
#endif //__HISTOGRAM_H
