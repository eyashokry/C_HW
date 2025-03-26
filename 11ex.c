/*
Zur Abgabe einen branch `iprg-b11` erstellen und pushen, in dem als einzige Datei die `11ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 11ex_test.c -o 11ex_test.o -lm && ./11ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 11ex_test.c -o 11ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./11ex_test.o
*/

#include "height_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

size_t height_or_zero(HeightTreeNode *t) {
    if (t == NULL) {
        return 0;
    } else {
        return t->height;
    }
}

/*
Aufgabe 1a:

Führen Sie eine Linksrotation auf dem gegebenen Baum durch, und geben Sie einen Pointer auf
die Wurzel des neuen Baumes zurück.
Der Baum ist nichtleer, und die Wurzel hat einen nichtleeren rechten Teilbaum.

Denken Sie daran, auch die Höhen und die Elternpointer anzupassen.

Die Baumausgabe im Terminal enthält in jedem Knoten erst das Item, dann die Höhe, und zuletzt
das Item des Elternkotens (oder NULL für die Wurzel).

Die Baumausgabe nimmt den zurückgegebenen Knoten als Wurzel. Sollte die Baumausgabe komplett
überraschend aussehen, könnte das gut an einer falsch zurückgegebenen Wurzel liegen.
*/

//ternary-operator und Makro
#define MAX(a, b)((a>b) ? (a) : (b)) 

HeightTreeNode *rotate_left(HeightTreeNode *t) {

    HeightTreeNode * s = t->right; 
    HeightTreeNode * r = s->left; 
    t->right = r; 
    s->left = t; 
    s->parent = t->parent; 
    t->parent = s; 
    if (r != NULL){
    r->parent = t; 
    }

    // Höhe berechnen
    t->height = MAX(height_or_zero(t->left), height_or_zero(t->right)) + 1;
    s->height = MAX(height_or_zero(s->left), height_or_zero(s->right)) + 1;

    return s;
}

/*
Die vier möglichen Sequenzen von Rotationen, um einen Beinahe-AVL-Baum in einen AVL-Baum zu überführen.
*/
typedef enum Rotations_ {
    Left, /* eine Linksrotation */
    Right, /* eine Rechtsrotation */
    DoubleRotationLeftRight, /* Doppelrotation: erst Linksrotation, dann Rechtsrotation */
    DoubleRotationRightLeft, /* Doppelrotation: erst Rechtsrotation, dann Linksrotation */
} Rotations;

/*
Aufgabe 2:

Gegeben ein Beinahe-AVL-Baum mit korrekten Höhenwerten, geben Sie zurück, welche Rotationen ihn zu einem AVL-Baum machen.
*/



Rotations determine_rotations(HeightTreeNode *t) {

    HeightTreeNode *s = t->left;
    HeightTreeNode *u = t->right;

    int t_l_height = height_or_zero(t->left);
    int t_r_height = height_or_zero(t->right);
  
    int b = t_l_height  -  t_r_height;

    if (b<=-2) {                                  // rechte seite ist länger
        if (u->left && (!u->right || u->left->height>u->right->height)) {
            return DoubleRotationRightLeft;
        } else {
            return Left; 
        }
    } else if (b>=2) {                         // linke Seite ist länger
        if (s->right && (!s->left || s->right->height>s->left->height)) {
            return DoubleRotationLeftRight; 
        } else {
            return Right; 
        }
    }

    return -1;
}

 
