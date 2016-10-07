/*
 * main.c
 *
 *  Created on: 12.2.2014
 *      Author: dulik
 */

/*
 ============================================================================
 Name        : fce.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "fce.h"
#include "ioutils.h"
#include <ctype.h>
int zadej_pole(int * pole, int delka, int kapacita) {
	int i, ok, hodnota, znak;
    char retezec[255];
	printf("Aktualni obsah pole:\n");
	for (i = 0; i < delka - 1; i++)
		printf("%d, ", pole[i]);
	printf("%d\n"
			"Zadat jine hodnoty? (A/N)\n", pole[i]);
    znak = io_utils_get_char_line();
	if (toupper(znak) == 'A') {
		printf("Zadavejte hodnoty oddelene novym radkem, konec=K:\n");
		for (i = 0; i < kapacita; i++) {
			do {
                io_utils_get_string(retezec, 254);
				if (toupper(retezec[0]) != 'K') {
					ok = sscanf(retezec, "%d", &hodnota);
					if (ok == 1)
						pole[i] = hodnota;
					else
						printf("Nespravny format, zkuste znovu\n");
				} else
					return i;
			} while (ok != 1);
		}
	}
	return delka;

}

int main(void) {
	int pole[1024] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, delka = 10;
	int mini, maxi;
	long x;
	double n;
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	while (1) {
		printf("Stisknete:\n"
				"1 pro minmax\n"
				"2 pro minimum\n"
				"3 pro maximum\n"
				"4 pro faktorial\n"
				"5 pro Fibonacciho posloupnost\n"
				"cokoli jineho pro konec.\n");
		switch (io_utils_get_char_line()) {
		case '1':
			delka = zadej_pole(pole, delka, 1024);
			minimax(pole, delka, &mini, &maxi);
			printf("Minimum=%d, maximum=%d\n", mini, maxi);
			break;
		case '2':
			delka = zadej_pole(pole, delka, 1024);
			printf("Minimum=%d\n", get_min(pole, delka));
			break;
		case '3':
			delka = zadej_pole(pole, delka, 1024);
			printf("Maximum=%d\n", get_max(pole, delka));
			break;
		case '4':
			printf("Vlozte hodnotu N:\n");
            io_utils_get_double(&n);
			if (n<1) printf("Nesmyslne zadani\n");
			printf("Faktorial(%.0lf)=%.0lf\n", n, fact(n));
			break;
		case '5':
			printf("Vlozte hodnotu N:\n");
            io_utils_get_long(&x);
			if (x<2) printf("Nesmyslne zadani\n");
			printf("Fibonacci(%d)=%d\n", (int) x, fibonacci(x));
			break;
		default:
			return EXIT_SUCCESS;
			break;
		}
	};
	return EXIT_SUCCESS;
}

