#include <stdio.h>
#include "table.h"
#include "ioutils.h"
#include "data.h"
#include "data_cstring.h"
#include "data_person.h"

void menu()
{
	printf("1 - HashTable_Init()\n");
	printf("2 - HashTable_Destruct()\n");
	printf("3 - HashTable_Insert()\n");
	printf("4 - HashTable_Delete()\n");
	printf("5 - HashTable_Find()\n");
	printf("6 - HashTable_Get_Count()\n");
	printf("7 - HashTable_Clear()\n");
	printf("8 - HashTable_Process()\n");
	printf("M - zobraz toto menu\n");
	printf("K - konec\n");

    printf("Pro ukonceni stiskni CTRL+D (Linux) nebo CTRL+Z (Windows).\n\n");
}

void process_table_node( Data_Cstring_t *key, Data_Person_t *value )
{	char strbuf[256];
    printf("Klic: ");
	puts(Data_To_String(key, strbuf));
	printf(" -> Hodnota: ");
	puts(Data_To_String(value, strbuf));
}

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	printf("Hash tabulka\n");
	printf("----------\n\n");


	bool initialized = false;
	char v = ' ';

	HashTable table;
	Data_Cstring_t data_cstring;
	Data_Cstring_Init(&data_cstring, NULL);
	void *key=&data_cstring;

	menu();

	while( !feof(stdin) && v != 'k' && v != 'K' ) {
        printf("Vase volba:\n");

		v = io_utils_get_char_line();

		switch( v ) {
		case '1': {
			if( initialized ) {
                printf("Tabulka je jiz inicializovana!\n");
				break;
			}

            printf("Zadej velikost tabulky (napr. 1000):\n");

			long size;
			io_utils_get_long( &size );

			HashTable_Init( &table, size, true );
            printf("Tabulka byla inicializovana.\n");

			initialized = true;
			break;
		}

		case '2':
			if( !initialized ) {
                printf("Tabulka neni inicializovana!\n");
				break;
			}

			HashTable_Destruct( &table );
            printf("Tabulka byla destruovana.\n");

			initialized = false;
			break;

		case '3': {
			if( !initialized ) {
                printf("Tabulka neni inicializovana!\n");
				break;
			}

            printf("Zadejte klic:\n");
			char strbuf[256];
			io_utils_get_string(strbuf, 256);
            void * key_new = Data_Cstring_New(strbuf);

            //io_utils_get_string(Data_To_String(key_new, NULL), 256);

			printf("Zadejte asociovanou hodnotu:\n"
					"Jmeno: ");
			io_utils_get_string(strbuf, 256);
			double vek, vaha, vyska;
			printf("\nZadejte vek: ");
			io_utils_get_double(&vek);
			printf("\nZadejte vahu: ");
			io_utils_get_double(&vaha);
			printf("\nZadejte vysku: ");
			io_utils_get_double(&vyska);

			void * value_new = Data_Person_New(strbuf, vek,vaha,vyska);

			if( !HashTable_Insert( &table, key_new, value_new ) ) {
                printf("Operace vlozeni se nezdarila (nezadali jste duplikatni klic?).\n");
                Data_Destruct(key_new);
                Data_Destruct(value_new);
			}
			break;
		}

		case '4': {
			if( !initialized ) {
                printf("Tabulka neni inicializovana!\n");
				break;
			}

            printf("Zadejte klic odstranovane polozky:\n");
			io_utils_get_string(Data_To_String(key, NULL), 256);

			if( !HashTable_Delete( &table, key ) )
                printf("Operace odstraneni se nezdarila (polozka s danym klicem pravdepodobne neexistuje).\n");

			break;
		}

		case '5': {
			if( !initialized ) {
                printf("Tabulka neni inicializovana!\n");
				break;
			}

            printf("Zadejte klic hledane polozky:\n");
			io_utils_get_string(Data_To_String(key, NULL), 256);
			Data_Person_t *value = HashTable_Find( &table, key );
			if( value ) {
				puts("Hledana polozka ma hodnotu ");
				puts( Data_To_String(value, NULL ));
			} else
                puts("Hledana polozka nebyla nalezena.\n");

			break;
		}

		case '6':
			if( !initialized ) {
                printf("Tabulka neni inicializovana!\n");
				break;
			}

            printf("Tabulka obsahuje %d polozek.\n", HashTable_Get_Count( &table ));
			break;

		case '7':
			if( !initialized ) {
                printf("Tabulka neni inicializovana!\n");
				break;
			}

			HashTable_Clear( &table );
            printf("Vsechny polozky tabulky byly odstraneny.\n");
			break;

		case '8':
			if( !initialized ) {
                printf("Tabulka neni inicializovana!\n");
				break;
			}

			HashTable_Process( &table, process_table_node );
			break;

		case 'm':
		case 'M':
			menu();
			break;

		case 'k':
		case 'K':
			printf("Konec.\n");
			break;

		default:
            printf("Neznama volba!\n");
			break;
		}

		printf("\n");
	}

	if( initialized ) {
		HashTable_Clear( &table );
		HashTable_Destruct( &table );
	}

	return 0;
}
