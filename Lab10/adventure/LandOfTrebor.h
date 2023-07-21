#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef LAB10_THELANDOFTREBOR_H
#define LAB10_THELANDOFTREBOR_H

typedef struct _AList {
    void** arr;
    int size;
    int maxSize;
    int itemSize;
    char* type;
} ArrayList;

typedef struct _Hero{
    char* name;
    char* class;
    int dead;
    char* lastLocation;
    char* primaryAttribute;
    float primarAttLevel;
    float strength;
    float agility;
    float intelligence;
    float charisma;
    int level;

} Hero;


typedef struct _Location{

    char* name;
    void** fallenHeros;
    int numDeaths;
    int level;
    int powerRating;
    int subtletyRating;
    int strategyRating;
    int charmRating;
    int inProgress;
} Location;

typedef struct _Args {
    Hero *hero;
    ArrayList* path;
    ArrayList* deathFile;
    ArrayList* aliveFile;
    bool is_complete;
} Args;

Hero* initialize_hero(char*, char*, double, double, double, double);
Location* initialize_location(char*, int, double, double, double, double);

void attemptLocation(void*);

int compareAttributes_Location_Hero(Hero*, Location*);

void levelUp(Hero*);
void failure(Hero*, Location*);


ArrayList* alist_initialize(int, int, char*);
bool alist_add(ArrayList*, void*);
bool alist_add_at(ArrayList*, int, void*);
void alist_clear(ArrayList*);
void* alist_get(ArrayList*, int);
int alist_index_of(ArrayList*, void*);
void* alist_remove(ArrayList*, int);
bool alist_destroy(ArrayList*);
bool _alist_resize(ArrayList*);
#endif //LAB10_THELANDOFTREBOR_H
