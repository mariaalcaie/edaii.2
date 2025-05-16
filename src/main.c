#include "document.h"
#include "sample_lib.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


void createaleak() {
  char *foo = malloc(20 * sizeof(char));
  printf("Allocated leaking string: %s", foo);
}

int main() {
  char path[250];
  // uncomment and run "make v" to see how valgrind detects memory leaks
  // createaleak();


  // Load all documents from the dataset directory---
  printf("Write the path: \n");
  scanf("%s", path);
  printf("\nescanejat\n");
  
  DocumentsList* list = load_all_documents(path);
  printf("\ncreació de list\n");
  print_document_list(list);
  
  
  
  //Document *document = document_desserialize("./datasets/wikipedia12/2.txt");
  //if(!document){
    //printf("OIII");
    //return 1;
  //}
  
  //if(document==NULL){
    //printf("Eppp");
    //return 1;
  //}
  //printf("%d\n", document->id);
  //printf("%s\n", document->title);
  //printf("%s\n", document->body);

  return 0;
}
