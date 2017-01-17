/*
 * LinkedList.c
 *
 *  Created on: 17 de jan de 2017
 *      Author: Alan
 */

#include "LinkedList.h"

LinkedList * newLinkedList() {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    list->value = 0.0;
    list->next = NULL;
    return list;
}

void printLinkedList(LinkedList *head) {
    head = head->next;
    while (head) {
        printf("%lf ", head->value);
        head = head->next;
    }
    printf("\n");
}

void prependToLinkedList(LinkedList *head, double value) {

    if(!head) { return; }

    LinkedList *new = newLinkedList();
    new->value = value;
    new->next = head->next;
    head->next = new;

}

void appendToLinkedList(LinkedList *head, double value) {

    while (head) {
        head = head->next;
    }
    if(!head) { return; }

    LinkedList *new = newLinkedList();
    new->value = value;
    head->next = new;

}

void arrayFromLinkedList(LinkedList *head, double *destination, int size) {

    if(!head) { return; }

    while (head->next && size > 0) {
        head = head->next;
        destination[--size] = head->value;
    }

}

void removeAllValuesFromLinkedList(LinkedList *head) {

    if(!head) { return; }

    LinkedList *current;
    current = head;
    head = head->next;
    current->next = NULL;

    while (head) {
        current = head;
        head = head->next;
        free(current);
    }

}
