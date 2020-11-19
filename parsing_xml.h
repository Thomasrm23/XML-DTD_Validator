#ifndef PARSING_XML_H_INCLUDED
#define PARSING_XML_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
#ifndef TRUE
    #define TRUE 1
#endif
#ifndef FALSE
    #define FALSE 0
#endif
*/

// structure pour enregistrer les elements du fichier xml
struct _XMLNode
{
    char* tag;
    char* inner_text;
    struct _XMLNode* parent;
    //  XMLAttributeList attributes;
    //  XMLNodeList children;
};
typedef struct _XMLNode XMLNode;

//structure pour le document
struct _XMLDocument
{
    XMLNode* root;
};

typedef struct _XMLDocument XMLDocument;


XMLNode* XMLNode_new(XMLNode* parent);  //creer une "node" pour nvlle balise xml
void XMLNode_free(XMLNode* node);
void XMLNode_free(XMLNode* node);
bool XMLDocument_load(XMLDocument* doc, const char* path);
void XMLDocument_free(XMLDocument* doc);

#endif // PARSING_XML_H_INCLUDED
