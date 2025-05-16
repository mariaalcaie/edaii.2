#ifndef DOCUMENT_H
#define DOCUMENT_H

typedef struct Document{
    char *title;
    int id;
    struct Links *links;
    float relevance;
    char *body;
    struct Document* next; 
}Document;

typedef struct DocumentsList{
    struct Document* head;
}DocumentsList;

typedef struct Link{
    int linkid; //del document linkejat
    struct Link* next;
}Link;

typedef struct Links{   //Llista de tots els links que hi ha al 
    struct Link *head; 
}Links;

#endif