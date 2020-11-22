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
* Cr�ation d'un n�ud associ� � une nouvelle balise XML
* @param[in] parent : Le n�ud p�re
* @param[out] node : le nouveau n�ud cr��
*/
XMLNode* XMLNode_new(XMLNode* parent);

/**
* D�sallocation d'un n�ud XML en m�moire
* @param[in] node : Le n�ud � d�saouller
*/
void XMLNode_free(XMLNode* node);

/**
* Chargement d'un document XML
* @param[in] doc : La structure dans lequel les �l�ments du fichiers seront stock�s
* @param[in] path : Le chemin du fichier DTD
* @param[out]  true ou false : Le document a pu �tre charg� ou non
*/
bool XMLDocument_load(XMLDocument* doc, const char* path);

/**
* D�sallocation d'un document XML en m�moire
* @param[in] doc : Le document � d�sallouer
*/
void XMLDocument_free(XMLDocument* doc);

#endif // PARSING_XML_H_INCLUDED
