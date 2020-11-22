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

/**
* Création d'un nœud associé à une nouvelle balise XML
* @param[in] parent : Le nœud père
* @param[out] node : le nouveau nœud créé
*/
XMLNode* XMLNode_new(XMLNode* parent);

/**
* Désallocation d'un nœud XML en mémoire
* @param[in] node : Le nœud à désaouller
*/
void XMLNode_free(XMLNode* node);

/**
* Chargement d'un document XML
* @param[in] doc : La structure dans lequel les éléments du fichiers seront stockés
* @param[in] path : Le chemin du fichier DTD
* @param[out]  true ou false : Le document a pu être chargé ou non
*/
bool XMLDocument_load(XMLDocument* doc, const char* path);

/**
* Désallocation d'un document XML en mémoire
* @param[in] doc : Le document à désallouer
*/
void XMLDocument_free(XMLDocument* doc);

#endif // PARSING_XML_H_INCLUDED
