/**
 * \file    ioutils.c
 * \author  Tomáš Dulík
 * \date    16.2.2012
 * \brief   Miniknihovna pro načítání vstupu
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ioutils.h"

/**
 * @brief   Načte řetězec ze standartního vstupu o maximální délce specifikované parametrem nebo dokud nenarazí na
 *          znak konce řádku (\n).
 *          Pokud se nepodaří nic načíst a funkce narazí na EOF(konec souboru), funkce zavolá
 *          exit(), který ukončí vykonávání programu.
 * @param   line    Ukazatel na textové pole, kam je vstup načten.
 * @param   len     Maximální délka načteného vstupu.
 */
void io_utils_get_string(char * line, int len) {
	if (fgets(line, len, stdin)==NULL) {
		printf("Konec souboru, koncime.\n");
		exit(EXIT_SUCCESS);
	}
#ifdef ECHO
	printf("%s", line);
#endif
}

/**
 * @brief Načte jeden znak ze standartního vstupu.
 * @return Vrací načtený znak.
 */
char io_utils_get_char_line() {
	char line[255];
	io_utils_get_string(line, 255);
	return line[0];
}

/**
 * @brief   Načte hodnotu typu long ze standartního vstupu.
 * @param   val     Ukazatel na proměnnou typu long kam je uložen načtený výsledek.
 * @return
 */
int io_utils_get_long(long * val) {
	long hodnota;
	int ok;
	char line[255];
	do {
		io_utils_get_string(line, 255);
		ok = sscanf(line, "%ld", &hodnota);
		if (ok != 1)
			printf("Nespravny format, zkuste znovu\n");
	} while (ok != 1);
	*val = hodnota;
	return 1;
}

/**
 * @brief   Načte hodnotu typu double ze standartního vstupu.
 * @param   val     Ukazatel na proměnnou typu double kam je uložen načtený výsledek.
 * @return
 */
int io_utils_get_double(double * val) {
	double hodnota;
	int ok;
	char line[255];
	do {
		io_utils_get_string(line, 255);
		ok = sscanf(line, "%lf", &hodnota);
		if (ok != 1)
			printf("Nespravny format, zkuste znovu\n");
	} while (ok != 1);
	*val = hodnota;
	return 1;
}

/**
 * @brief Vyčistí jeden řádek vstupu.
 */
void io_utils_clear_stdin()
{
	while(fgetc(stdin) != '\n');
}
