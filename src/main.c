#include <stdio.h>

#define IN 1
#define OUT 0
#define SAW_SLA 2
#define SAW_AST 3
#define COM_AST 4
#define COM_SLA 5
#define COM_NO 6

int main(int argc, char *argv[])
{
    if(argc == 1){
        printf("Please enter a File\n");
        return 1;
    }

    FILE *pF = fopen(argv[1], "r+");
    if(pF != NULL){
        printf("File opened successfully\n");
    } else {
        printf("File couldn't be opened\n");
        return 2;
    }
    FILE *pTemp = fopen("temp.txt", "w");

    int kind = COM_NO; 
    int state = OUT;
    int c;
    while((c = getc(pF)) != EOF){
        switch(state){
            case OUT:
                if(c == '/'){ 
                    state = SAW_SLA;
                } else {
                    putc(c, pTemp);
                }
                break;

            case IN:
                if(c == '*' && kind == COM_AST) state = SAW_AST;
                if(c == '\n' && kind == COM_SLA) {
                    kind = COM_NO;
                    state = OUT;
                }
                break;

            case SAW_SLA:
                if(c == '*'){
                    kind = COM_AST;
                    state = IN;
                } else if(c == '/'){
                    kind = COM_SLA;
                    state = IN;
                } else {
                    putc('/', pTemp);
                    if(c == '/') {
                        state = SAW_SLA;
                    } else {
                        putc(c, pTemp);
                        state = OUT;
                    }
                }
                break;

            case SAW_AST:
                if(c == '/') {
                    kind = COM_NO;
                    state = OUT;
                } else if(c == '*'){
                    state = SAW_AST;
                } else {
                    state = IN;
                }
                break;
        }
    }

    fclose(pF);
    fclose(pTemp);

    return 0;
}
