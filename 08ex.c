/*
Zur Abgabe einen branch `iprg-b08` erstellen und pushen, in dem als einzige Datei die `08ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./08ex_test.o
*/

#include "sphinx.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:

Da spaziert man entspannt durch Theben, und plötzlich kommt eine Sphinx angeflogen
und spricht: "Ich habe mir ein Array überlegt, das aus beliebig vielen Nullen gefolgt von
beliebig vielen Einsen besteht. Du darfst mich nach dem Wert an 1 + log2(n) (aufgerundet)
vielen Positionen fragen. Und wenn du mir danach nicht sagen kannst, wo die erste Eins
steht, dann fresse ich dich. Falls es keine Eins gibt, dann hätte ich gerne die Länge
des Arrays als Antwort".

Geben Sie den Index der ersten Eins zurück, oder die Arraylänge, falls es keine Eins gibt.
Um den Wert an Position `i` zu erfragen, rufen Sie `sphinx_ask(s, i)` auf. Aber Achtung:
Wenn Sie diese Funktion mehr als 1 + log2(n) (aufgerundet) mal aufrufen, stürzt das Programm
fehlerhaft ab.
*/
size_t zero_one_sphinx(Sphinx *s, size_t n) {
    int links = 0; 
    int rechts = n - 1;
    int first = n;                  //im falle keiner 1 

    while (links <= rechts) {
        int mitte = links + (rechts-links)/2;
        uint16_t antwort = sphinx_ask(s, mitte);
        if (antwort == 1) {
            first = mitte;  
            rechts = mitte - 1;     //falls es noch eine linkere 1 gibt
        } else {
            links = mitte + 1;   
        }
    }

    return first;
}
