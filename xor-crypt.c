#include <stdio.h>      // printf(), fseek(), ftell(), perror(), fopen(), fgetc(), fprintf(), fclose()
#include <unistd.h>     // execve()
#include <sys/stat.h>   // chmod()
#include <stdlib.h>     // exit(), size_t
#include <string.h>     // strcmp()

#define XOR_BYTE 0x6F   // key to XOR

void xorFile (char *infile, char *outline) {
    FILE *source_f;
    FILE *output_f;
    char ch;
    // size_t size;

    source_f = fopen(infile, "rb+");
    if (!source_f) perror("Error opening source_f");
    else {

        // fseek(source_f, 0, SEEK_END);
        // size = ftell(source_f);
        // printf("File size: %zu bytes\n", size); 
        // fseek(source_f, 0, SEEK_SET);
        
        output_f = fopen(outline, "wb+");
        if (!output_f) perror("Error opening output_f");
        else {
            while ((ch = fgetc(source_f)) != EOF) {
                fprintf(output_f, "%c", ch ^ XOR_BYTE);
            }
            fclose(output_f);
        }
    }
    fclose(source_f);
}
 

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [IN FILE] [OUT FILE]\n", argv[0]);
        exit(1);
    } else {
        xorFile(argv[1], argv[2]);
    }

    return 0;
}
