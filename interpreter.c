#include <stdio.h>
#include <stdlib.h>
int cursor = 0;
char* memory = NULL;
void exec(int length, char* src) {
    char c;
    int pc = -1;
    int jumpbackPos = 0;

    while (1) {
        c = src[++pc];
        if (pc == length || pc < 0) {
            break;
        }

        switch (c) {
            case '>':
                cursor++;
                break;
            case '<':
                cursor--;
                break;
            case '+':
                memory[cursor]++;
                break;
            case '-':
                memory[cursor]--;
                break;
            case '.':
                printf("%c", memory[cursor]);
                break;
            case ',':
                memory[cursor] = getchar();
                while (c = getchar(), c == '\r' || c == '\n')
                    ;

            case '[':
                jumpbackPos = pc - 1;
                if (memory[cursor] == 0) {
                    long temppc = pc;
                    while (src[pc++] != ']')
                        ;
                    return exec(length - pc, src + pc);
                }
                break;
            case ']':
                pc = jumpbackPos;
                break;
            default:;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 0) {
        printf("Except input file\n");
        return 1;
    }
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    char* src = (char*)malloc(sizeof(char) * length);
    fseek(fp, 0, SEEK_SET);
    fread(src, 1, length, fp);

    memory = (char*)malloc(sizeof(char) * 1024);
    exec(length, src);

    free(src);
    fclose(fp);
    return 0;
}