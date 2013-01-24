
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int i;
    
    if(isatty((int)fileno(stdin))) {
        printf("stdin is a tty\n");
    }
    
    for(i = 0; i < argc; ++i) {
        printf("argv[%d] : %s\n", i, argv[i]);
    }
    
    return 0;
}
