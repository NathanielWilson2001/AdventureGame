#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#ifndef LAB10_SIM_H
#define LAB10_SIM_H

typedef struct _Node {
    void* data;
    struct _Node* next;
    struct _Node* prev;
} Node;

typedef struct _Queue {

    int itemSize;
    char* itemType;
    int size;
    Node* start;
    Node* end;
} Queue;


int numHeroes;
int numLocations;
int numThreads;

void load_queue(Queue*);
void load_locations(ArrayList*);
void sort_levelOrder(ArrayList*);
void sort_powerOrder(ArrayList*);
void sort_subtletyOrder(ArrayList*);
void sort_strategyOrder(ArrayList*);
void sort_charmOrder(ArrayList*);

void execute();
void executePower(int);
void executeAgility();
void executeIntelligence();
void executeCharm();
void executeLevel();

Queue* queue_initialize(int, char*);
bool queue_enqueue(Queue*, void*);
void* queue_dequeue(Queue*);
void* queue_peek(Queue*);
int queue_size(Queue*);
bool queue_contains(Queue*, void*);
bool queue_destroy(Queue*);


#endif //LAB10_SIM_H

