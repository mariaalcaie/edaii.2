#ifndef SAMPLE_LIB_H
#define SAMPLE_LIB_H

Links* LinksInit();
void add_links(Links *links, int linkId);
//void free_links(Links *links);


DocumentsList* DocumentsListInit();
Document *document_desserialize(char *path);
//Document* get_document_by_id(Links* links, int linkid);
int print_document_list(DocumentsList * list);
void print_document(Document* document);
DocumentsList* load_all_documents(char* dataset);
int count_files(char* dataset);
#endif
