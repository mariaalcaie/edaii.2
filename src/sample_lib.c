#include "document.h"
#include "sample_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


Links* LinksInit(){
    Links *links = (Links*)malloc(sizeof(Links));
    links->head = NULL;
    return links;
}

DocumentsList* DocumentsListInit(){
    DocumentsList *list = (DocumentsList*)malloc(sizeof(DocumentsList));
    list->head = NULL;
    return list;
}


void add_links(Links* links, int id){
    Link *newLink = (Link*)malloc(sizeof(Link));
    newLink->linkid = id;
    newLink->next = links->head;
    links->head = newLink;
    //Si el posem al davant no cal que cada cop es comprovi si hi ha head
    //i a partir d'allà mirar la primera posició NULL. Més eficaç
}


DocumentsList* load_all_documents(char* dataset){
    printf("entra a la funció");
    DocumentsList *list = (DocumentsList *)malloc(sizeof(DocumentsList));
    int files = count_files(dataset);
    printf("count_files fet");
    for (int i= 0; i >= files; i++){
        char* path = malloc(200);
        snprintf(path,200, "%s%d.txt", dataset, i);
        printf("ha passat per guardar a path");
        Document* document = document_desserialize(path);
        document->next = list->head;
        list->head = document;
        free(path);
    }return list;
}

//FALT ACABAR FUNCIÓ, AIXÒ NOOO CONTA LA QUANTITAT DE DOCS QUE TE UN DATASET
int count_files(char* path){
    int count = 0;
    FILE *f = fopen(path, "r");
    while(f != NULL){
        count++;
    }fclose(f);
    return count;
}

int print_document_list(DocumentsList* list){
    int index = 0;
    Document* document = list->head;
    printf("Documents List:\n");
    while (document != NULL) {
        printf("(%d). %s\n", index, document->title);
        printf("---\n");
        printf("%.150s", document->body);
        if (strlen(document->body) > 150){
        printf("...\n");
        }
        printf("---\n");
        printf("relevance score: %.2f\n", document->relevance);
        printf("\n");
        document = document->next;
        index++;
    } return index-1;  
}

void print_document(Document* document){
    if (document == NULL){
        printf("Invalid document\n");
        return;
    }
    printf("\nID\n %d\n", document->id);
    printf("\nTITLE\n %s\n", document->title);
    printf("\nRELEVANCE SCORE\n %.2f\n", document->relevance);
    printf("\nBODY\n %s", document->body);
    printf("\n------------------------------\n");
}
