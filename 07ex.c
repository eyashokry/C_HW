/*
Zur Abgabe einen branch `iprg-b07` erstellen und pushen, in dem als einzige Datei die `07ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && ./07ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./07ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void merge(uint8_t* arr, int left, int middle, int right){
    for(int i = left; i<right; i++){            //selection sort
        uint8_t kleinstes = arr[left]; 
        kleinstes = arr[i];
        int index = i;
       
        for(int j = i+1; j<right;j++){
            if(arr[j]<kleinstes){
                kleinstes = arr[j];
                index = j;
            }

        }
        uint8_t temp = arr[i];
        arr[i] = kleinstes;
        arr[index] = temp;
    }
}


/*
Aufgabe 1:
Bringen Sie die Tests zum durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void sort_it(Visualizer *v, uint8_t *arr, size_t len) {
    visualizer_append_array(v, arr);                //iterativer merge sort
    int step = 1; 
    while (step<len){
        int left = 0;
        while(left<= len-step){
        int middle = left+step;
        int right = left+2*step;
        merge(arr,left, middle, right);
        left = left+2*step; 
        visualizer_append_array(v, arr);
        }
    step = step*2;
    }
}
