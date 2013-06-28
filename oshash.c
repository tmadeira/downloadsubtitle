#include <stdio.h>
#include <stdlib.h>

void usage(char *name) {
    printf("Usage: %s <file>\n", name);
    exit(1);
}

int main(int argc, char *argv[]) {
    unsigned long long buf[16384], c = 0;
    FILE *in;
    int i;
    if (argc != 2) {
        usage(argv[0]);
    }
    in = fopen(argv[1], "rb");
    if (in == NULL) {
        usage(argv[0]);
    }
    fread(buf, 8192, 8, in);
    fseek(in, -65536, SEEK_END);
    fread(&buf[8192], 8192, 8, in);
    for (i = 0; i < 16384; i++) {
        c+= buf[i];
    }
    c+= ftell(in);
    fclose(in);
    printf("%016llx\n", c);
    return 0;
}

