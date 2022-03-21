#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OUT_C_FILENAME ".temp.out.c"

int main(int argc, char* argv[]) {
    if (argc < 0) {
        printf("Except input file\n");
        return 1;
    }
    FILE* bffp = fopen(argv[1], "r");
    if (bffp == NULL) {
        printf("File not found\n");
        return 1;
    }

    fseek(bffp, 0, SEEK_END);
    long length = ftell(bffp);
    char* program = (char*)malloc(sizeof(char) * length);
    fseek(bffp, 0, SEEK_SET);
    fread(program, 1, length, bffp);

    FILE* cfp = fopen(OUT_C_FILENAME, "w");
    char* bfptr = program;
    char* code =
        "#include<stdio.h>\n"
        "char memory[1024];"
        "long cursor = 0;"
        "int main(){";
    fwrite(code, 1, strlen(code), cfp);
    while (length--) {
        switch (*bfptr++) {
            case '>':
                code = "cursor++;";
                break;
            case '<':
                code = "cursor--;";
                break;
            case '+':
                code = "memory[cursor]++;";
                break;
            case '-':
                code = "memory[cursor]--;";
                break;
            case '.':
                code = "putchar(memory[cursor]);";
                break;
            case ',':
                code = "memory[cursor] = getchar();";
                break;
            case '[':
                code = "while(memory[cursor]) {";
                break;
            case ']':
                code = "}";
                break;
            default:
                code = NULL;
        }
        if (code) {
            fwrite(code, 1, strlen(code), cfp);
        }
    }
    fwrite("return 0;\n}", 1, strlen("return 0;\n}"), cfp);

    free(program);
    fclose(bffp);
    fclose(cfp);

    system("gcc -o out " OUT_C_FILENAME);
    remove(OUT_C_FILENAME);
    return 0;
}