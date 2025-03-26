/*
Zur Abgabe einen branch `iprg-b09` erstellen und pushen, in dem als einzige Datei die `09ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && ./09ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./09ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"
#include "array.h"

/*
Aufgabe 1:

Gegeben ein linksvollständiger Binärbaum `t`, geben Sie zurück, ob `t` die min-heap Eigenschaft erfüllt.
*/
bool is_min_heap(TreeNode *t) {
    if (t == NULL) return true;         //leerer heap ist ein heap

    if (t->left  && t->item > t->left->item) { //if (child ist nicht <=) dann ist die eigenschaft nicht erfüllt
        return false; 
    }
    if (t->right && t->item > t->right->item) {
        return false; 
    }

    bool l_heap = is_min_heap(t->left);      //rekursion
    bool r_heap = is_min_heap(t->right);
    return l_heap && r_heap;
}

/*
Aufgabe 2:

Gegeben ein Array `arr`, geben Sie den zugehörigen linksvollständigen Binärbaum zurück.
*/

TreeNode* array_to_tree_rec(Array arr, int i){
   if (i >= arr.len) {
        return NULL; 
    }

    TreeNode* next_node = (TreeNode*)malloc(sizeof(TreeNode)); //neuer node wird erstellt und gefüllt
    next_node->item = arr.arr[i];
    next_node->left = NULL;
    next_node->right = NULL;
    
    next_node->left = array_to_tree_rec(arr, 2*i+1);   //berechnungen aus dem tutorium für das finden von kindern im array
    next_node->right = array_to_tree_rec(arr, 2*i+2);
    return next_node;
    }


TreeNode *array_to_tree(Array arr) {
    if (arr.len == 0) {
        return NULL; 
    }
    return array_to_tree_rec(arr, 0);
}
