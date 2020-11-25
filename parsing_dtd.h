#ifndef PARSING_DTD_H_INCLUDED
#define PARSING_DTD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TRUE
    #define TRUE 1
#endif
#ifndef FALSE
    #define FALSE 0
#endif

struct NodeList
{
    int heap_size;
    int size;
    struct Node** data;
};
typedef struct NodeList DTDNodeList;

// structure pour enregistrer les elements du fichier dtd
struct Node
{
    char* tag_type;
    char* tag_name;
    char* attr_name;
    char* content;
    char* content_info;
    char* child[10]; // tous les enfants de l'element
    int* several[10];   //leur + associer
    struct Node* parent;
    DTDNodeList children;

};
typedef struct Node DTDNode;

struct Document
{
    DTDNode* root;
};
typedef struct Document DTDDocument;

void DTDNodeList_init(DTDNodeList* list);
void DTDNodeList_add(DTDNodeList* list, struct Node* node);

DTDNode* DTDNode_child(DTDNode* parent, int index);

DTDNode* DTDNode_new(DTDNode* parent);  //creer une "node" pour nvlle balise DTD
void DTDNode_free(DTDNode* node);
int DTDDocument_load(DTDDocument* doc, const char* path);
void DTDDocument_free(DTDDocument* doc);


#endif // PARSING_DTD_H_INCLUDED
