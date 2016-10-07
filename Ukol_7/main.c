#include <stdio.h>
#include <string.h>

//#define DEBUG

// TODO print help
void printHelp()
{
	printf("This is help!");
}

typedef enum
{
	start = 0,
	single_quote,
	backslash1,
	backslash2,
	string_literal,
	slash,
	line_comment,
	multiline_comment,
	star
} TState;

#define BACK_SLASH '\\'
#define SLASH '/'
#define DOUBLE_QUOTE '"'
#define SINGLE_QUOTE '\''
#define STAR '*'
#define END_OF_LINE '\n'

FILE * openFile(char* filename, char* openFlags)
{
    FILE * file = fopen (filename,openFlags);
    if(file == NULL)
    {
        fprintf(stderr ,"Can not open input file: %s.", filename);
        fclose (file);
    }
    return file;
}

int main(int argc/*number of commmandline arguments*/, char* argv[]/* Array of string commmandline arguments */)
{
    FILE * inFile = stdin;
    FILE * outFile = stdout;
	
	//
	// Command line parameters processing.
	//
    // Note: First argument argv[0] is alwais name of executable
	if(argc == 2)
	{// One param - name of input file 
        inFile = openFile(argv[1], "r");
	}
	else if(argc == 3)
	{// Two params - name of input file and name of output file

        inFile = openFile(argv[1], "r");
        outFile = openFile(argv[2], "w");
	}
	else if(argc > 3)
	{// Wrong number of params
        fprintf(stderr, "Wrong number of input parametrs. (You entered %d params, including name of binary)!", argc);
		return -1;
	}

    if(inFile == NULL || outFile == NULL) return -1;
	
    int c; ///< one char from input
    TState state = start; ///< variable holding state in finite machine
	while((c = fgetc(inFile)) != EOF)
	{
		switch(state)
		{
			case start:
			{
				if(c == SINGLE_QUOTE) 
				{
					state = single_quote;
					fputc ( c , outFile );
				}
				else if(c == SLASH)
				{
					state = slash;
				} 
				else if(c == DOUBLE_QUOTE)
				{
					state = string_literal;
					fputc ( c , outFile );
				}
				else
				{
					fputc ( c , outFile );
				} 
				break;
			}
			
			case single_quote:
			{
				if(c == BACK_SLASH) state = backslash1;
				else if (c == SINGLE_QUOTE) state = start;
				fputc ( c , outFile );
				break;
			}
			case backslash1:
			{
				state = single_quote;
				fputc ( c , outFile );
                break;
			}
			case string_literal:
			{
                if(c == DOUBLE_QUOTE)
                    state = start;
                else if(c == BACK_SLASH)
                    state = backslash2;
				fputc ( c , outFile );
				break;
			}
			case backslash2:
			{
				state = string_literal;
				fputc ( c , outFile );
                break;
			}
			case slash:
			{
				if(c == SLASH) state = line_comment;
				else if(c == STAR) state = multiline_comment;
				else
				{
					fputc ( SLASH , outFile );
					fputc ( c , outFile );
				}
				break;
			}
			case line_comment:
			{
				if(c == END_OF_LINE) 
				{
					state = start;
					fputc ( c , outFile );
				}
				break;
			}
			case multiline_comment:
			{
				if (c == STAR) state = star;
				break;
			}
			case star:
			{
				if(c == SLASH) state = start;
				else state = multiline_comment;
				break;
			}
#ifdef DEBUG
            fflush(outFile);
#endif
		} // end switch
	} // end while

    fclose (inFile);
    fclose (outFile);

	return 0;
}

