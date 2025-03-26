/*
Zur Abgabe einen branch `iprg-b05` erstellen und pushen, in dem als einzige Datei die `05ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./05ex_test.o
*/

#include "search_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Die Definition von Bäumen bzw. Knoten finden Sie in `./search_tree.h`
*/

/*
Aufgabe 1:

Ändern Sie alle im Baum `t` gespeicherten Werte auf `x`.
*/
void search_tree_boringify(TreeNode *t, uint16_t x) {
    if (t==NULL){       ////abbruchsbedingung, sonst " error: all paths through this function will call itself"
        return;                
    }

    t->item = x;
    search_tree_boringify(t->left, x);
    search_tree_boringify(t->right, x);
}

/*
Aufgabe 2:
Geben Sie die größte Zahl im Suchbaum `t` zurück, welche echt kleiner als `x` ist.
Falls keine solche Zahl existiert, geben Sie stattdessen `x` zurück. Die Laufzeit Ihrer Lösung soll
proportional zur Höhe des Baumes sein, aber unabhängig von der Gesamtzahl an Knoten. 
*/
uint16_t search_tree_get_less_than(TreeNode *t, uint16_t x) {   

  if (t==NULL){
    return x;
  }

  TreeNode* y = t;
  uint16_t max = x;

    while(y != NULL){
        if(y->item >= x){
            y = y->left;
        
        } else if(y->item < x){     
            max = y->item;
            y = y->right;
        } 

        }
        return max;
   
}
