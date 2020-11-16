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


// structure pour enregistrer les elements du fichier dtd
struct _DTDNode
{
    char* tag_type;
    char* tag_name;
   // char* children;
    char* content;  // contenu
    char* children[10]; // tous les enfants de l'element
    bool* several[10];
    struct _DTDNode* parent;
};
typedef struct _DTDNode DTDNode;

//structure pour le document
struct _DTDDocument
{
    DTDNode* root;
};
typedef struct _DTDDocument DTDDocument;


DTDNode* DTDNode_new(DTDNode* parent);  //creer une "node" pour nvlle balise DTD
//void DTDNode_free(DTDNode* node);
int DTDDocument_load(DTDDocument* doc, const char* path);
void DTDDocument_free(DTDDocument* doc);


#endif // PARSING_DTD_H_INCLUDED
