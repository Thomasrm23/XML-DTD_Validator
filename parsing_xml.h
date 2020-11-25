#ifndef PARSING_XML_H_INCLUDED
#define PARSING_XML_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TRUE
    #define TRUE 1
#endif
#ifndef FALSE
    #define FALSE 0
#endif



struct XMLAttribute
{
    char* key;
    char* value;
};
typedef struct XMLAttribute XMLAttribute;


struct XMLAttributeList
{
    int heap_size;
    int size;
    XMLAttribute* data;
};
typedef struct XMLAttributeList XMLAttributeList;

struct XMLNodeList
{
    int heap_size;
    int size;
    struct XMLNode** data;
};
typedef struct XMLNodeList XMLNodeList;


// structure pour enregistrer les elements du fichier xml
struct XMLNode
{
    char* tag;
    char* inner_text;
    struct XMLNode* parent;
    XMLAttributeList attributes;
    XMLNodeList children;
};
typedef struct XMLNode XMLNode;

//structure pour le document
struct XMLDocument
{
    XMLNode* root;
    int* child_number;
};
typedef struct XMLDocument XMLDocument;

void XMLNodeList_init(XMLNodeList* list);
void XMLNodeList_add(XMLNodeList* list, struct XMLNode* node);

XMLNode* XMLNode_child(XMLNode* parent, int index);

void XMLAttribute_free(XMLAttribute* attr);

void XMLAttributeList_init(XMLAttributeList* list);
void XMLAttributeList_add(XMLAttributeList* list, XMLAttribute* attr);

XMLNode* XMLNode_new(XMLNode* parent);  //creer une "node" pour nvlle balise xml
void XMLNode_free(XMLNode* node);
int XMLDocument_load(XMLDocument* doc, const char* path);
void XMLDocument_free(XMLDocument* doc);


#endif // PARSING_XML_H_INCLUDED
