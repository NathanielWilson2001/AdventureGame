#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include "LandOfTrebor.c"
#include "LandOfTrebor.h"
#include "simulation.h"
#include <sys/time.h>

sem_t wait;

int numHeroes;
int numLocations;
int numThreads;
/*
 *  Fills a queue with all the heroes so they can be
 *  used to run/fill threads in main using adventure_heroes.lot
 */
void load_queue(Queue* queue1){

    FILE *filepointer = fopen("../../CI/objects/adventure/heroes.lot", "r");
    numHeroes = 0;
    char *name = malloc(40);
    char *skill = malloc(40);
    char *stats = malloc(40);
    double one, two, three, four;
    int scan1, scan2, scan3, scan4;
 



    while(numHeroes != 300) {
        fgets(name, 40, filepointer);
        fgets(skill, 40, filepointer);
        fgets(stats, 40, filepointer);
        sscanf(stats, "%d, %d, %d, %d", &scan1, &scan2, &scan3, &scan4);
        one = (double) scan1;
        two = (double) scan2;
        three = (double) scan3;
        four = (double) scan4;
       
        strtok(name, "\n");
        numHeroes++;
        Hero* hero = initialize_hero(name, skill,  one,  two,  three,  four);
        queue_enqueue(queue1, hero);
    }
    return;
}

/*
 *  Fills the different paths in order from adventure_locations.lot
 */
void load_locations(ArrayList* array){


    FILE *filepointer = fopen("../../CI/objects/adventure/locations.lot", "r");
    numLocations = 0;
    char *name = malloc(60);
    char *stats = malloc(40);
    int one, two, three, four, five;

    while(numLocations != 200) {
        fgets(name, 60, filepointer);
        fgets(stats, 40, filepointer);
        sscanf(stats, "%d, %d, %d, %d, %d", &one, &two, &three, &four, &five);;


        numLocations++;
        Location *location = initialize_location(name, one, two, three, four, five);
        alist_add(array, location);
    }

    return;
}
void print_sorted(ArrayList* alist, FILE* fp) {


    for (int i = 0; i < alist->size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < alist->size; j++) {
            Hero *hero1 = alist->arr[minIndex];
            Hero *hero2 = alist->arr[j];
            double a = hero1->strength;
            double b = hero2->strength;
            if (a > b) {
                minIndex = j;
            }
        }

        int temp = alist->arr[i];
        alist->arr[i] = alist->arr[minIndex];
        alist->arr[minIndex] = temp;
    }
    
    for (int i = 0; i < alist->size; i++) {
        Hero *hero = alist->arr[i];
        if(hero->dead){
            fprintf(fp,"%s %.0f %.0f %.0f %.0f %s\n", hero->name, hero->strength, hero->agility, hero->intelligence, hero->charisma, hero->lastLocation);
        }
        else {


            fprintf(fp, "%s %.0f %.0f %.0f %.0f\n", hero->name, hero->strength, hero->agility, hero->intelligence,
                    hero->charisma);
        }
        }


}
void print_path(ArrayList* alist, FILE* fp) {


    for (int i = 0; i < alist->size; i++) {
        Location *location = alist->arr[i];
        fprintf(fp, "%s Lvl : %d Pow: %d Agili: %d Intell: %d Charm: %.d\n", location->name,
                location->level, location->powerRating, location->subtletyRating, location->strategyRating,
                location->charmRating);
    }
}

void sort_levelOrder(ArrayList* array) {
    for (int i = 0; i < array->size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < array->size; j++) {
            Location *loc1 = array->arr[minIndex];
            Location *loc2 = array->arr[j];
            int a = loc1->level;
            int b = loc2->level;
            if (a > b) {
                minIndex = j;
            }
        }

        int temp = array->arr[i];
        array->arr[i] = array->arr[minIndex];
        array->arr[minIndex] = temp;
    }
}

void sort_powerOrder(ArrayList* array){
    for (int i = 0; i < array->size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < array->size; j++) {
            Location *loc1 = array->arr[minIndex];
            Location *loc2 = array->arr[j];
           double a = loc1->powerRating;
           double b = loc2->powerRating;
            if (a > b) {
                minIndex = j;
            }
        }

        int temp = array->arr[i];
        array->arr[i] = array->arr[minIndex];
        array->arr[minIndex] = temp;
    }
}

void sort_subtletyOrder(ArrayList* array){
    for (int i = 0; i < array->size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < array->size; j++) {
            Location *loc1 = array->arr[minIndex];
            Location *loc2 = array->arr[j];
            double a = loc1->subtletyRating;
            double b = loc2->subtletyRating;
            if (a > b) {
                minIndex = j;
            }
        }

        int temp = array->arr[i];
       array->arr[i] = array->arr[minIndex];
        array->arr[minIndex] = temp;
    }
}
void sort_strategyOrder(ArrayList* array){
    for (int i = 0; i < array->size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < array->size; j++) {
            Location *loc1 = array->arr[minIndex];
            Location *loc2 = array->arr[j];
            double a = loc1->strategyRating;
            double b = loc2->strategyRating;
            if (a > b) {
                minIndex = j;
            }
        }

        int temp = array->arr[i];
       array->arr[i] = array->arr[minIndex];
        array->arr[minIndex] = temp;
    }
}
void sort_charmOrder(ArrayList* array){
    for (int i = 0; i < array->size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < array->size; j++) {
            Location *loc1 = array->arr[minIndex];
            Location *loc2 = array->arr[j];
            double a = loc1->charmRating;
            double b = loc2->charmRating;
            if (a > b) {
                minIndex = j;
            }
        }

        int temp = array->arr[i];
       array->arr[i] = array->arr[minIndex];
       array->arr[minIndex] = temp;
    }
    
}
int main(int argc, int* argv[]) {

   numThreads = atoi(argv[1]);
   executeAgility();
   sleep(5);
   executeLevel();
   sleep(5);
   executeCharm();
   sleep(5);
   //executeIntelligence();
   sleep(5);
    for(int i = 1; i < 11; i++){
     executePower(i);
     sleep(5);
   }

}

/*
 * Execute Power and record timer
 */
void  executePower(int threadNum){

    ArrayList* powerPath  = alist_initialize(100, sizeof(Location*), "location");
    ArrayList* powerPath_alive = alist_initialize(100, sizeof(Hero*), "hero");
    ArrayList* powerPath_dead = alist_initialize(100, sizeof(Hero*), "hero");
    load_locations(powerPath);
    sort_powerOrder(powerPath);


    Queue *power = queue_initialize(sizeof(Hero*), "heroes");
    load_queue(power);


        struct timeval start, end;
        gettimeofday(&start, NULL);
        pthread_t threads[threadNum];
        Args args[threadNum];

        FILE *fd = fopen("Power_dead.txt", "w");
        FILE *fa = fopen("Power_alive.txt", "w");

        for (int i = 0; i < threadNum; i++) {

            Hero *hero = queue_dequeue(power);
            args[i].hero = hero;
            args[i].path = powerPath;
            args[i].is_complete = false;
            args[i].aliveFile = powerPath_alive;
            args[i].deathFile = powerPath_dead;
            pthread_create(&threads[i], NULL, attemptLocation, &args[i]);
            numHeroes--;

        }
        int index = 0;
        while (queue_size(power) > 0) {

            if (args[index].is_complete == true) {
                pthread_join(threads[index], NULL);
                numHeroes--;

                Hero *hero = queue_dequeue(power);
                //  printf("%s",hero->name );
                args[index].hero = hero;
                args[index].path = powerPath;
                args[index].is_complete = false;
                args[index].aliveFile = powerPath_alive;
                args[index].deathFile = powerPath_dead;
                pthread_create(&threads[index], NULL, attemptLocation, &args[index]);
            }
            index = (index + 1) % threadNum;
        }

        for (int i = 0; i < threadNum; i++) {
            pthread_join(threads[i], NULL);
        }

        print_sorted(powerPath_dead, fd);
        print_sorted(powerPath_alive, fa);
        gettimeofday(&end, NULL);

        /*
         *  Run time calculation using gettimeofday()
         *  Source learned from:
         *  https://www.techiedelight.com/find-execution-time-c-program/
         */
        long micros = (((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);

        printf("Run time for powerPath: %d threads is %d microseconds\n", threadNum, micros);
	queue_destroy(power);
return;	

}
/*
 * Executes Subtlety/Agility Path
 */
void executeAgility(){
 ArrayList* subtletyPath =  alist_initialize(100, sizeof(Location*), "location");
 ArrayList* subtletyPath_alive = alist_initialize(100, sizeof(Hero*), "hero");
 ArrayList*  subtletyPath_dead = alist_initialize(100, sizeof(Hero*), "hero");
    load_locations(subtletyPath);
    sort_subtletyOrder(subtletyPath);

    Queue *agility = queue_initialize(sizeof(Hero*), "heroes");
    load_queue(agility);


        pthread_t threads[numThreads];
        Args args[numThreads];

        FILE *fd = fopen("Agility_dead.txt", "w");
        FILE *fa = fopen("Agility_alive.txt", "w");

        for (int i = 0; i < numThreads; i++) {

            Hero *hero = queue_dequeue(agility);
            args[i].hero = hero;
            args[i].path = subtletyPath;
            args[i].is_complete = false;
            args[i].aliveFile =  subtletyPath_alive;
            args[i].deathFile =  subtletyPath_dead;
            pthread_create(&threads[i], NULL, attemptLocation, &args[i]);
            numHeroes--;

        }
        int index = 0;
        while (queue_size(agility) > 0) {

            if (args[index].is_complete == true) {
                pthread_join(threads[index], NULL);
                numHeroes--;

                Hero *hero = queue_dequeue(agility);
                args[index].hero = hero;
                args[index].path = subtletyPath;
                args[index].is_complete = false;
                args[index].aliveFile =  subtletyPath_alive;
                args[index].deathFile =  subtletyPath_dead;
                pthread_create(&threads[index], NULL, attemptLocation, &args[index]);
            }
            index = (index + 1) % numThreads;
        }

        for (int i = 0; i < numThreads; i++) {
            pthread_join(threads[i], NULL);
        }

        print_sorted(subtletyPath_dead, fd);
        print_sorted(subtletyPath_alive, fa);
	return;
}
/*
 * Executes Intelligence/Strategy Path
 */
void executeIntelligence() {
    ArrayList* strategyPath  = alist_initialize(100, sizeof(Location*), "location");
    ArrayList* strategyPath_alive = alist_initialize(100, sizeof(Hero *), "hero");
    ArrayList* strategyPath_dead = alist_initialize(100, sizeof(Hero *), "hero");

    load_locations(strategyPath);
    sort_strategyOrder(strategyPath);
    
    Queue *intelligence = queue_initialize(sizeof(Hero*), "heroes");
    load_queue(intelligence);

    FILE *fd = fopen("Intelligence_dead.txt", "w");
    FILE *fa = fopen("Intelligence_alive.txt", "w");

    pthread_t threads[numThreads];
    Args args[numThreads];


    for (int i = 0; i < numThreads; i++) {

        Hero *hero = queue_dequeue(intelligence);
        args[i].hero = hero;
        args[i].path = strategyPath;
        args[i].is_complete = false;
        args[i].aliveFile = strategyPath_alive;
        args[i].deathFile = strategyPath_dead;
        pthread_create(&threads[i], NULL, attemptLocation, &args[i]);
        numHeroes--;

    }
    int index = 0;
    while (queue_size(intelligence) > 0) {

        if (args[index].is_complete == true) {
            pthread_join(threads[index], NULL);
            numHeroes--;

            Hero *hero = queue_dequeue(intelligence);
            args[index].hero = hero;
            args[index].path = strategyPath;
            args[index].is_complete = false;
            args[index].aliveFile = strategyPath_alive;
            args[index].deathFile = strategyPath_dead;
            pthread_create(&threads[index], NULL, attemptLocation, &args[index]);
        }
        index = (index + 1) % numThreads;
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }



    print_sorted(strategyPath_dead, fd);
    print_sorted(strategyPath_alive, fa);
	return;

}
/*
 * Executes charm Path
 */
void executeCharm(){
    ArrayList* charmPath  = alist_initialize(100, sizeof(Location*), "location");
    ArrayList*  charmPath_alive = alist_initialize(100, sizeof(Hero*), "hero");
    ArrayList* charmPath_dead = alist_initialize(100, sizeof(Hero*), "hero");
    load_locations(charmPath);
    sort_charmOrder(charmPath);

    Queue *charm = queue_initialize(sizeof(Hero*), "heroes");
    load_queue(charm);


    FILE *fd = fopen("Charm_dead.txt", "w");
    FILE *fa = fopen("Charm_alive.txt", "w");


    pthread_t threads[numThreads];
    Args args[numThreads];


    for (int i = 0; i < numThreads; i++) {

        Hero *hero = queue_dequeue(charm);
        args[i].hero = hero;
        args[i].path = charmPath;
        args[i].is_complete = false;
        args[i].aliveFile = charmPath_alive;
        args[i].deathFile = charmPath_dead;
        pthread_create(&threads[i], NULL, attemptLocation, &args[i]);
        numHeroes--;

    }
    int index = 0;
    while (queue_size(charm) > 0) {

        if (args[index].is_complete == true) {
            pthread_join(threads[index], NULL);
            numHeroes--;

            Hero *hero = queue_dequeue(charm);
            args[index].hero = hero;
            args[index].path = charmPath;
            args[index].is_complete = false;
            args[index].aliveFile = charmPath_alive;
            args[index].deathFile = charmPath_dead;
            pthread_create(&threads[index], NULL, attemptLocation, &args[index]);
        }
        index = (index + 1) % numThreads;
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    print_sorted(charmPath_dead, fd);
    print_sorted(charmPath_alive, fa);
	return;
}
/*
 * Executes Level Path
 */
void executeLevel(){
    ArrayList*  levelPath = alist_initialize(100, sizeof(Location*), "location");
    ArrayList*  levelPath_alive = alist_initialize(100, sizeof(Hero*), "hero");
    ArrayList* levelPath_dead = alist_initialize(100, sizeof(Hero*), "hero");
    load_locations(levelPath);
    sort_levelOrder(levelPath);

    Queue *level = queue_initialize(sizeof(Hero*), "heroes");
    load_queue(level);

    FILE *fd = fopen("Level_dead.txt", "w");
    FILE *fa = fopen("Level_alive.txt", "w");


    pthread_t threads[numThreads];
    Args args[numThreads];


    for (int i = 0; i < numThreads; i++) {

        Hero *hero = queue_dequeue(level);
        args[i].hero = hero;
        args[i].path = levelPath;
        args[i].is_complete = false;
        args[i].aliveFile = levelPath_alive;
        args[i].deathFile = levelPath_dead;
        pthread_create(&threads[i], NULL, attemptLocation, &args[i]);
        numHeroes--;

    }
    int index = 0;
    while (queue_size(level) > 0) {

        if (args[index].is_complete == true) {
            pthread_join(threads[index], NULL);
            numHeroes--;

            Hero *hero = queue_dequeue(level);
            args[index].hero = hero;
            args[index].path = levelPath;
            args[index].is_complete = false;
            args[index].aliveFile = levelPath_alive;
            args[index].deathFile = levelPath_dead;
            pthread_create(&threads[index], NULL, attemptLocation, &args[index]);
        }
        index = (index + 1) % numThreads;
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }



    print_sorted(levelPath_dead, fd);
    print_sorted(levelPath_alive, fa);

return;
}
Queue* queue_initialize(int dataSize, char* dataType){


    Queue* q = malloc(sizeof(*q));

    q->itemSize = dataSize;
    q->itemType = malloc(sizeof(dataType));
    q->itemType = dataType;
    q->start = malloc(dataSize);
    q->size = 0;
    return q;

}

bool queue_enqueue(Queue* q, void* data){
    if( q == NULL){
        return false;
    }
    Hero* op = data;
    Node *newNode = malloc(sizeof(*newNode));
    newNode->data = malloc(sizeof(*op));
    memcpy(newNode->data, data, sizeof(*op));

    if(q->size == 0){
        q->start = newNode;
        q->start->next = NULL;
        q->size++;
        return true;
    }
    newNode->next = q->start;
    q->start = newNode;
    q->size++;
    return true;
}

void* queue_dequeue(Queue* q) {

    if( q == NULL && q->start == NULL){
        return NULL;
    }


    Node* secondtoLast = malloc(sizeof(Node));
    Node* firstNode = malloc(sizeof(Node));
    firstNode = q->start;
    void* output;
    if(firstNode == NULL){
        return NULL;
    }
    if(q->size == 1){
        q->size--;
        output = firstNode->data;
        q->start = NULL;
        return output;
    }
    int count = 0;
    while(firstNode->next != NULL){
        count ++;
        secondtoLast = firstNode;
        firstNode = firstNode->next;
        if(count == q->size){
            break;
        }
    }
    q->size--;
    secondtoLast->next = NULL;
    output = firstNode->data;
    return output;
}

void* queue_peek(Queue* q){
    if( q == NULL || q->start == NULL){
        return NULL;
    }

    Node *currentNode = q->start;
    int counter = 0;
    while(true){
        if(currentNode == NULL){
            return NULL;
        }
        if(counter == q->size - 1 ){
            return currentNode->data;
        }
        currentNode = currentNode->next;
        counter++;
    }
    return q->start->data;
}

int queue_size(Queue* q){
    if( q == NULL){
        return -1;
    }
    return q->size;
}

bool queue_contains(Queue* q, void* data){
    if(q == NULL || data == NULL){
        return false;
    }

    Node *currentNode = q->start;
    int counter = 0;
    while(true){
        if(currentNode == NULL){
            return NULL;
        }
        if(currentNode->data == data || strcmp(currentNode->data, data) == 0){
            return true;
        }
        if(counter == q->size - 1){
            return false;
        }
        currentNode = currentNode->next;
        counter++;
    }

}

bool queue_destroy(Queue* q){
    if( q == NULL){
        return false;
    }
    q = NULL;
    free(q);
    return true;

}



