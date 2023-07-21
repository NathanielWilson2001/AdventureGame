#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "LandOfTrebor.h"
#include "simulation.h"

sem_t locationInprogress;
int numHeroes;
int extraPlace; 
//Hero initialize
Hero* initialize_hero(char* inName, char* inClass, double inStrength, double inAgility, double inIntelligence, double inCharisma){

    Hero* hero = malloc(sizeof(*hero));
    hero->name  = malloc(strlen(inName) + 1);
    strcpy(hero->name, inName);
    hero->class = malloc(strlen(inClass) + 1);
    strcpy(hero->class, inClass);
    hero->level = 0;
    hero->dead = 0;

    hero->primaryAttribute = malloc(sizeof(char));
    int maxAtt = 0;
    hero->strength = inStrength;
    hero->primaryAttribute = "s";
    hero->primarAttLevel = 0;

    hero->agility = inAgility;
    if(inAgility >  hero->primarAttLevel ){
        hero->primaryAttribute = "a";
        hero->primarAttLevel  = inAgility;
    }

    hero->intelligence = inIntelligence;
    if(inIntelligence >  hero->primarAttLevel ){
        hero->primaryAttribute = "a";
        hero->primarAttLevel  = inIntelligence;
    }

    hero->charisma = inCharisma;
    if(inCharisma >  hero->primarAttLevel ){
        hero->primaryAttribute = "c";
        hero->primarAttLevel  = inCharisma;
    }

    return hero;
}

//Location Initialize
Location* initialize_location(char* inName, int levelRating, double inpowerRating, double insubtletyRating, double instrategyRating, double incharmRating){

    Location* location = malloc(sizeof(*location));
    location->name  = malloc(strlen(inName) + 1);
    strcpy(location->name, inName);

    location->level = levelRating;
    location->fallenHeros = malloc(sizeof(*location->fallenHeros));

    location->powerRating = inpowerRating;
    location->subtletyRating = insubtletyRating;
    location->strategyRating = instrategyRating;
    location->charmRating = incharmRating;
    location->numDeaths = 0;
    location->inProgress = 0;
    return location;
}
/* Hero tries to see if they can complete a location
 * 
 */
void attemptLocation(void* arguments){
    Args* args = arguments;
    Hero* hero = args->hero;
    ArrayList* path = args->path;
    ArrayList* dead = args->deathFile;
    ArrayList* alive = args->aliveFile;
  

    Location *location = path->arr[hero->level];

    if(hero == NULL || location == NULL){
        return;
    }
    
   
    while(hero->level != 200) {
        location = path->arr[hero->level];
        // Wait until location is no longer in progress
        if (location->inProgress == 1) {

         return attemptLocation(arguments);
	 
        }
        if (compareAttributes_Location_Hero(hero,location)) {
            levelUp(hero);
            location->inProgress = 0;

        }
        else {
            break;

        }
    }
    if (hero->level >= 200) {
        alist_add(alive, hero);
        args->is_complete = true;
        return;
    }
    alist_add(dead, hero);
    failure(hero, location);
    location->inProgress = 0;
    hero->dead = 1;
    hero->lastLocation = malloc(strlen(location->name));
    strncpy( hero->lastLocation,location->name,strlen(location->name));
    strtok(hero->lastLocation, "\n");
    args->is_complete = true;
    return;
}

/* Compare Hero stats with location stats
 *  returns 0 if fails, returns 1 if it passes
 */
int compareAttributes_Location_Hero(Hero* hero, Location* location){

    if(hero == NULL || location == NULL){
        return 0;
    }

    location->inProgress = 1;
    if(hero->strength >= location->powerRating){
        return 1;
    }
    if(hero->agility >= location->subtletyRating){
        return 1;
    }
    if(hero->intelligence >= location->strategyRating){
        return 1;
    }
    if(hero->charisma >= location->charmRating){
        return 1;
    }

    return 0;
}

/* Increases a hero's stats and level after a successful mission
 */
void levelUp(Hero* hero){

    // checks if primAtt has already been increased
    int primAtt = 0;

    if(hero == NULL){
        return;
    }

    hero->level+= 1;

    if(hero->strength == hero->primarAttLevel){
        hero->strength += .35;
        hero->primarAttLevel += .35;
        primAtt = 1;
    }
    else{
        hero->strength += .25;
    }
    if( primAtt == 0 && hero->agility == hero->primarAttLevel){
        hero->agility += .35;
        hero->primarAttLevel += .35;
        primAtt = 1;
    }
    else{
        hero->agility += .25;
    }
    if( primAtt == 0 && hero->intelligence == hero->primarAttLevel){
        hero->intelligence += .35;
        hero->primarAttLevel += .35;
        primAtt = 1;
    }
    else{
        hero->intelligence += .25;
    }
    if( primAtt == 0 && hero->charisma == hero->primarAttLevel){
        hero->charisma += .35;
        hero->primarAttLevel += .35;
        primAtt = 1;
    }
    else{
        hero->charisma += .25;
    }
}

/* Failure to complete a mission
 * Hero is added to the locations fallenHero's list and the number of fallen heros at the location increases
 */
void failure(Hero* hero, Location* location) {

    if(hero == NULL || location == NULL){
        return;
    }
    location->fallenHeros[location->numDeaths] = malloc(strlen(hero->name) + 1);
    strcpy(location->fallenHeros[location->numDeaths], hero->name);
    location->numDeaths++;
    return;

}



ArrayList* alist_initialize(int maxSize , int itemSize, char* arrayType){

    struct  _AList *arrayList;

    arrayList = malloc(sizeof(*arrayList));

    arrayList->maxSize = maxSize;
    arrayList->itemSize = itemSize;
    arrayList->type = malloc(sizeof(arrayType));
    strcpy(arrayList->type, arrayType);
    arrayList->arr = malloc(sizeof(*arrayList->arr) * maxSize);
    arrayList->size = 0;
    return arrayList;
}

bool alist_add(ArrayList* list, void* elementPointer){

    if(list == NULL){
        return  false;
    }
    if(list->maxSize - 1 <= list->size){
        _alist_resize(list);
    }

    list->arr[list->size] = malloc(sizeof(*elementPointer));
    list->arr[list->size] = elementPointer;

    list->size++;
    return true;

}
bool alist_add_at(ArrayList* list, int index, void* elementPointer){

    if(list == NULL || elementPointer == NULL){
        return  false;
    }
    int size = list->size;
    void* temp = malloc( list->itemSize);
    void* temp2 = malloc( list->itemSize);

    if(index = list->size){
        memcpy(list->arr[index], elementPointer, list->itemSize);
        list->size++;
        return true;
    }
    temp =  list->arr[index];
    list->arr[index] = elementPointer;

    for (int i = index + 1; i <= size; i++) {

        temp2 = list->arr[i];
        list->arr[i] = temp;
        temp = temp2;
    }
    return true;

}

void alist_clear(ArrayList* list){

    if(&list == NULL){
        return;
    }

    int size = list->size;
    for(int i = 0; i < list->size - 1; i++){
        free(list->arr[i]);
    }
    list->size = 0;
}

void* alist_get(ArrayList* list, int index){

    if(&list == NULL || index > list->size){
        return NULL;
    }

    return list->arr[index];
}

int alist_index_of(ArrayList* list, void* elementPointer){

    if(list == NULL || elementPointer == NULL){
        return -1;
    }
    for(int i = 0; i <= list->size; i++){
        if(list->type == "string") {
            if ( strcmp(list->arr[i], (char *) elementPointer)) {
                return i;
            }
        }
        else{
            if(list->arr[i] == elementPointer){
                return i;
            }
        }
    }
    return -1;
}

void* alist_remove(ArrayList* list, int index){

    if(&list == NULL || &index == NULL || index > list->size - 1){
        return NULL;
    }
    void* temp = list->arr[index];
    for(int i = index; i < list->size - 1; i++) {

        list->arr[i] =  list->arr[i + 1];
    }
    list->arr[list->size] = NULL;
    list->size--;
    return temp;



}

bool alist_destroy(ArrayList* list){
    if(&list == NULL){
        return false;
    }
    alist_clear(list);
    free(list->arr);
    return true;
}

bool _alist_resize(ArrayList* list){
    if(list->size == list->maxSize){
        list->arr = realloc(list->arr,list->maxSize * 2 * sizeof(*list->arr));
        list->maxSize = list->maxSize * 2;
        return true;
    }
    return false;
}
