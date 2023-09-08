#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // Datei öffnen
    FILE* file;
    file = fopen(argv[1], "r+b");
    if (file == NULL) {
        printf("Error - datei konnte nicht geöffnet werden %s\n", argv[1]);
        return 1;
    }

    fseek(file, 0L, SEEK_END);
    long int fileSize = ftell(file);
    rewind(file);

    unsigned char buffer[fileSize];

    fread(buffer, sizeof(unsigned char), fileSize, file);

    for (long int i = 0; i < fileSize / 2; i++) {
        unsigned char temp = buffer[i];
        buffer[i] = buffer[fileSize - i - 1];
        buffer[fileSize - i - 1] = temp;
    }
    fclose(file);

    file = fopen(argv[1], "w+");
    fwrite(buffer, sizeof(unsigned char), fileSize, file);
    fclose(file);
    return 0;
}

