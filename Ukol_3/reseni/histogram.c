#include "histogram.h"
#include "vector.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/**
 * @brief   Otevře soubor s daným názvem a pro každý řádek obsažený v souboru spočítá jeho délku. Tuto délku následně uloží
 *          jako další položku do vektoru.
 *
 * @param   vector      Ukazatel na vektor
 * @param   filename    Název otevíraného souboru
 * @return  Vrací 0 pokud vše proběhlo v pořádku, jinak chybový kód.
 */
int Histogram_AnalyzeFile(Vector_t *vector, char *filename)
{
	printf("Opening.. %s\n", filename);
	FILE* file = fopen(filename,"r"); // read mode

	if( file == NULL )
	{
		fprintf(stdout, "Error while opening the file %s. (errno=%d)\n", filename, errno);
		return EXIT_FAILURE;
	}

	// It needs to be int because fgetc return's int
	int charter;
	uint64_t lineLenth = 0;
	// read file until its end (EOF= End of the File).
	do
	{
		charter = fgetc( file );
		if(charter == '\n' || charter == EOF)
		{
			// Don't save empty lines
			if(lineLenth != 0)
			{
				Vector_Append(vector, lineLenth);
				lineLenth = 0;
			}

		} 
		else
		{
			lineLenth++;
		}
	}
	while(charter != EOF);
	return EXIT_SUCCESS;
}

/**
 * @brief   Vypočítá a zobrazí tabulku četností délek řádků, dle aktuálního obsahu předaného vektoru. Pro výpočet velikostí jednotlivých "boxů"
 *          využívá rovnici ((max-min)/box_num) + 1. Je tedy nutné nejdříve vyhledat maximum a minimum délek řádků, následně vytvořit boxy
 *          (buďto pomocí dynamické alokace nebo VLAs) a poté projít vektor záznam po záznamu a pro odpovídající rozsah inkrementovat daný
 *          box.
 *
 * @param   vector  Ukazatel na vektor
 * @param   box_num Počet boxů
 */
void Histogram_Visualize(Vector_t *vector, uint8_t box_num)
{
  uint64_t min = Vector_Min(vector);
  uint64_t max = Vector_Max(vector);
  uint64_t boxWidth = ((max - min) / box_num) + 1;
  // Create array of histogram filled with zeros
  uint64_t histogram[box_num];
  memset(histogram, 0, sizeof histogram);
  uint64_t itemCount =  Vector_Length(vector);
	uint64_t value;
	
	// Count histogram
  for(uint64_t i = 0; i < itemCount; i++)
  {
		value = Vector_At(vector, i);
		//printf("%" PRIu64 "\n", value);
		// Increase value of cell in histogram. (Count of index is done by integer division)
		if(value != 0)
			histogram[(value - 1) / boxWidth]++;
	}
	Print_Histogram(histogram, box_num, min, max, boxWidth);
}

void Print_Histogram(uint64_t histogram[], uint8_t box_num, uint64_t min, uint64_t max, uint64_t boxWidth)
{
	printf("Min: %" PRIu64 "\n", min);
	printf("Max: %" PRIu64 "\n", max);
	printf("Histogram....\n"); 
	printf("[From]\t\t\t\t\t[To]\t\t\t\t\t[Count]\n");
	uint64_t from;
	uint64_t to = boxWidth;
	for(uint8_t i = 0; i < box_num; i++)
	{
		from = (i*boxWidth) + 1;
		to = boxWidth * (i+1);
		printf("%" PRIu64 "\t\t\t\t\t%" PRIu64 "\t\t\t\t\t\t%" PRIu64 "\n", from, to, histogram[i]);
	}
}
