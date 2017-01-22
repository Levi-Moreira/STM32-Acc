/*
 * LinkedList.h
 *
 *  Created on: 17 de jan de 2017
 *      Author: Alan
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList LinkedList;

struct LinkedList {
    float value;
    LinkedList *next;
};

LinkedList * newLinkedList();
void printLinkedList(LinkedList *head);
void prependToLinkedList(LinkedList *head, float value);
void appendToLinkedList(LinkedList *head, float value);
void arrayFromLinkedList(LinkedList *head, float *destination, int size);
void freeLinkedList(LinkedList *head);

#endif /* LINKEDLIST_H_ */
