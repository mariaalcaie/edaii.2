#include "document.h"
#include "sample_lib.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


Document *document_desserialize(char *path) {
    FILE *f = fopen(path, "r");
    assert(f != NULL);
    
    Document *document = (Document *)malloc(sizeof(Document));
    
    char buffer[262144];
    int bufferSize = 262144;
    int bufferIdx = 0;
    char ch;

    // parse id
    while ((ch = fgetc(f)) != '\n') {
        assert(bufferIdx < bufferSize);
        buffer[bufferIdx++] = ch;
    }
    assert(bufferIdx < bufferSize);
    buffer[bufferIdx++] = '\0';
    document->id = atoi(buffer);

    // parse title
    bufferIdx = 0;
    while ((ch = fgetc(f)) != '\n'){
        assert(bufferIdx < bufferSize);
        buffer[bufferIdx++]=ch;
    } assert(bufferIdx<bufferSize);
    buffer[bufferIdx++] = '\0';
    document->title =(char *)malloc(sizeof(char)* bufferIdx);
    strcpy(document->title, buffer);

    // parse body
    char linkBuffer[64];
    int linkBufferSize = 64;
    int linkBufferIdx = 0;
    bool parsingLink = false;
    Links *links = LinksInit();
    
    bufferIdx = 0;
    while ((ch = fgetc(f)) != EOF) {
        assert(bufferIdx < bufferSize);
        buffer[bufferIdx++] = ch;
        if (parsingLink) {
            if (ch == ')') { // end of link
                parsingLink = false;
                assert(linkBufferIdx < linkBufferSize);
                linkBuffer[linkBufferIdx++] = '\0';
                int linkId = atoi(linkBuffer);

                // TODO add to links
                add_links(links, linkId);

                linkBufferIdx = 0;
            } else if (ch != '(') { // skip first parenthesis of the link
                assert(linkBufferIdx < linkBufferSize);
                linkBuffer[linkBufferIdx++] = ch;
            } 
        } else if (ch == ']') { // found beginning of link id, e.g.: [my link text](123)
          parsingLink = true;
        }
    }
    assert(bufferIdx < bufferSize);
    buffer[bufferIdx++] = '\0';
    
    char *body = (char *)malloc(sizeof(char) * bufferIdx);
    strcpy(body, buffer);

    // TODO
    document->body = body;
    document->links = links;

    fclose(f);
    return document;
}
