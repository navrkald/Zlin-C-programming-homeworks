#include "histogram.h"
#include "vector.h"
#include "string.h"
#include "stdio.h"
#include "stdbool.h"

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
  
}
