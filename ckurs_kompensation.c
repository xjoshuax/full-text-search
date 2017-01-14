/* ==== KOMPENSATION ABGABE ====
 * Kompensationsaufgabe
 * Abgabe von: Joshua Asar
 * =============================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_MATCH 200 // maximale Anzahl auszugebender Matches
#define MAX_STRING 255 // Maximale Wortlänge

/*** Datenstrukturen ***/
// QElement wird von Queue benutzt
typedef struct QElement QElement;
typedef struct Queue Queue;
int a = 0;
int *matchcount = &a;


struct QElement {
    // HIER Code einfügen
    // * Datenstruktur implementieren
    char* data;
    QElement* next; 
};

struct Queue {
    // HIER Code einfügen
    // * Datenstruktur implementieren
    QElement* front;
    QElement* rear;
};

// Queue initialisieren
Queue* init_queue() {
    // HIER Code einfügen
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Speicher der Qeue freigeben
void queue_freigeben(Queue *queue) {
    // HIER Code einfügen
    free(queue);
};

// Füge string als QElement am Ende der Queue an
void enqueue(Queue *queue, char* string){
    // HIER Code einfügen
    QElement *temp = (QElement*)malloc(sizeof(QElement));
    temp->data = string;
    temp->next = NULL;

    // Prüfen ob Queue leer ist
    if (queue->front == NULL && queue->rear == NULL){
        queue->front = queue->rear = temp;
    }
    queue->rear->next = temp;
    queue->rear = temp;

}

// Lösche das erste QElement der Queue
void dequeue (Queue *queue) {
    // HIER Code einfügen

    QElement *temp = queue->front;
    if (queue->front == NULL) return;
    if (queue->front == queue->rear){
        queue->front = queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }
    free(temp);

}

// Debug Ausgabe für Queue
void queue_ausgeben(Queue *queue) {
    // HIER Code einfügen

    QElement* temp = queue->front;
    while(temp != NULL) {
        printf("%s ", temp->data);
        temp = temp->next;
    }
    printf("\n");

}

// Vergleiche Inhalte zweier Queues bis zur Länge
int match(Queue *suchphrase, Queue *queue) {
    // HIER Code einfügen
    QElement *temp1 = (QElement*)malloc(sizeof(QElement));
    QElement *temp2 = (QElement*)malloc(sizeof(QElement));

    if( queue->front == NULL && suchphrase->front == NULL)
        return(2);

    temp1 = queue->front;
    temp2 = suchphrase->front;

    
    while( temp1 != NULL && temp2 != NULL)
    {

        if(strcmp(temp1->data, temp2->data) != 0){
            //printf("Sorry, no match!");
            return(1); 
        }

        temp1 = temp1->next;
        temp2 = temp2->next;

        }

        if( temp1 == NULL && temp2 == NULL){
            //printf("It's a MATCH!");
            (*matchcount)++;
            free(temp1);
            free(temp2);
            return(0); 

        } 
        else {
            printf("Queues sind nicht gleich lang");
            free(temp1);
            free(temp2);
            return(1); 
        }


}


int main(int argc, char** argv) {
    // Parameter einlesen
    if (argc < 3)
    {
        printf("Nutzung: %s <Dateiname> <Wort1> <Wort2> ...\n", argv[0]);
        return 1;
    }

    // HIER Code einfügen
    // * Initialisiere Queues
    Queue* suchphrase = init_queue();

    // * Fülle die Queue der Suchphrase
    //   Tipp: Die Elemente findest du bei argv[2] bis argv[argc]
    for (int i = 2; i < argc; i++){
        enqueue(suchphrase, argv[i]);
    }


    // * Überpüfe mit queue_ausgeben ob du es korrekt eingelesen hast.
    //printf("Suchphrase: ");
    //queue_ausgeben(suchphrase);

    // HIER Code einfügen
    // * Wörter aus Datei mit enqueue in die Queue befördern bis Queue voll ist.
    // Datei öffnen

    Queue* eingabe = init_queue();
    
    FILE *fp;
    
    char str[255];


     /* opening file for reading */
     fp = fopen(argv[1] , "r");


     if(fp == NULL) {
       printf("Error opening file");
     }

    for (int i = 2; i < argc; i++){

        fscanf(fp, "%s", str);

        enqueue(eingabe, strdup(str));
    }

    //printf("Initial queue: ");
    //queue_ausgeben(eingabe);
    
 

    // * Von da an mit enqueue und dequeue Wörter in die Queue lesen und Queues
    //   vergleichen
    int wordcount = 1; 

    if(match(eingabe, suchphrase)==0){
        printf("%d. Treffer beginnend bei Wort Nr. %d\n", *matchcount, wordcount);
    }

    while((fscanf(fp, "%s", str))!= EOF){


        dequeue(eingabe);
        //fscanf(fp, "%s", str);
        enqueue(eingabe, strdup(str));
        wordcount++;

        // printf(" //// %d <<< Next queue: ", wordcount);
        // queue_ausgeben(eingabe);
        //match(eingabe, suchphrase);
        if(match(eingabe, suchphrase)==0){
            printf("%d. Treffer beginnend bei Wort Nr. %d\n", *matchcount, wordcount);
        }
    }
    printf("===> %d Treffer\n", *matchcount);


    fclose(fp);


    // * Gebe die Positionen der gefundenen Phrase im Text an, in dem du die Wörter des
    //   Text von 1 an hochzählst. Die Position der Phrase ist identisch mit der Position
    //   des ersten Wortes der Phrase.

    // HIER Speicher der Queues freigeben

    queue_freigeben(suchphrase);
    queue_freigeben(eingabe);

    // * Überprüfe mit valgrind ob alles freigeben wird.
}