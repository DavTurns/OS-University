#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void deleteElement(int array[], int size, int k) {
    int pid;

    if ((pid = fork()) == -1) {
        printf("fork error");
    }
    
    if (pid == 0) {

        //find minimum
        int index = 0;
        int minelem = 100000;

        for (int i = 0; i < size; i++) {
            if (array[i] < minelem) {
                index = i;
                minelem = array[i];
            }
        }

        if (k == 1) {
            printf("%d", array[index]);
            return;
        }

        //delete index by shifting
        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }

        size--;
        k--;

        deleteElement(array, size, k);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Falsche Anzahl Argumente");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Datei");
        return 1;
    }

    char line[100];// Annahme: Eine Zeile ist maximal 100 Zeichen lang
    fgets(line, sizeof(line), file);
    fclose(file);

    int array[100];
    int count = 0;

    char *token = strtok(line, ",");
    while (token != NULL) {
        array[count] = atoi(token);
        count++;
        token = strtok(NULL, ",");
    }

    int k = atoi(argv[2]);

    deleteElement(array, count, k);

}
