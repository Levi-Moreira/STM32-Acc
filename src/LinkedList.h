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
    double value;
    LinkedList *next;
};

LinkedList * newLinkedList();
void printLinkedList(LinkedList *head);
void prependToLinkedList(LinkedList *head, double value);
void appendToLinkedList(LinkedList *head, double value);
void arrayFromLinkedList(LinkedList *head, double *destination, int size);
void removeAllValuesFromLinkedList(LinkedList *head);

#endif /* LINKEDLIST_H_ */
