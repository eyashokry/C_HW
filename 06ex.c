/*
Zur Abgabe einen branch `iprg-b06` erstellen und pushen, in dem als einzige Datei die `06ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && ./06ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
clang -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./06ex_test.o
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
In dieser Aufgabe arbeiten wir mit doppelt verketteten Listen, identisch zu denen von Blatt 04.

Das folgende Struct ist ein Node in einer doppelt verketteten Liste.
Dieses Struct dient als Implementierungsdetail.
Wer von außen mit einer DoublyLinkedList arbeitet,
bekommt Nodes nie direkt zu sehen.
*/
typedef struct Node {
    /* Der Datenwert, der in der Node gespeichert ist. */
    int data;
    /* Pointer auf die vorige Node, oder NULL, falls es keine vorige Node gibt. */
    struct Node *prev;
    /* Pointer auf die nächste Node, oder NULL, falls es keine vorige Node gibt. */
    struct Node *next;
} Node;

/* Eine doppelt verkettete Liste. */
typedef struct {
    /* Pointer auf die erste Node der Liste. */
    Node *head;
    /* Pointer auf die letzte Node der Liste. */
    Node *tail;
    /* Anzahl der Nodes in der Liste. */
    size_t size;
} DoublyLinkedList;

/*
Aufgabe 1: Sortieren

Sortieren Sie die gegebene Liste aufsteigend. Es kommen keine doppelten Datenwerte vor.
*/
void sort_list(DoublyLinkedList *list) {
    Node* current_node;
    Node* next_node;
    bool sortiertNoch = true;

    while(sortiertNoch == true) {
        current_node = list->head;
        sortiertNoch = false;           //sonst nicht ausführbar

        while (current_node != NULL && current_node->next != NULL) {
            next_node = current_node->next;

            if (current_node->data > next_node->data) {
                if (current_node->prev != NULL) {   //cN ist nicht head -> pN kann auf nN zeigen
                    current_node->prev->next = next_node;  
                }
                if (next_node->next != NULL) {      //nN ist nicht tail -> cN wird auf nN gesetzt (tausch)
                    next_node->next->prev = current_node;
                }

                current_node->next = next_node->next;
                next_node->next = current_node;
                next_node->prev = current_node->prev;
                current_node->prev = next_node;

                if (next_node->prev == NULL) {      //cN ist 1. listenelement
                    list->head = next_node;
                }
                if (current_node->next == NULL) {   //cN letztes listenelement -> cN wird tail 
                    list->tail = current_node;
                }

                sortiertNoch = true;  
            }
            current_node = current_node->next;
        }
    }  

    return;
}
