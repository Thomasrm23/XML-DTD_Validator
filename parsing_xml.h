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

XMLNode* XMLNode_new(XMLNode* parent);  //creer une "node" pour nvlle balise xml
void XMLNode_free(XMLNode* node);

//structure pour le document
struct _XMLDocument
{
    XMLNode* root;
};

typedef struct _XMLDocument XMLDocument;

int XMLDocument_load(XMLDocument* doc, const char* path);
void XMLDocument_free(XMLDocument* doc);

XMLNode* XMLNode_new(XMLNode* parent)
{
    XMLNode* node = (XMLNode*) malloc(sizeof(XMLNode));
    node->parent = parent;
    node->tag = NULL;
    node->inner_text = NULL;
    return node;
}

//good
void XMLNode_free(XMLNode* node)
{
    if (node->tag){
        free(node->tag);
    }
    if (node->inner_text){
        free(node->inner_text);
    }
    free(node);


}

int XMLDocument_load(XMLDocument* doc, const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Could not load file from '%s'\n", path);
        return FALSE;
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);     // obtenir la taille du fichier
    fseek(file, 0, SEEK_SET);

    char* buf = (char*) malloc(sizeof(char) * size + 1);
    fread(buf, 1, size, file);      //stocker le contenu du fichier dans buf
    fclose(file);
    buf[size] = '\0';

    doc->root = XMLNode_new(NULL);  //root node qui n'a pas de parent

    char lex[256];  //stocker les caracteres
    int lexi = 0;
    int i = 0;

    XMLNode* curr_node = NULL;  //

    while (buf[i] != '\0')      //lecture du buffer du fichier
    {
        if (buf[i] == '<') {    //debut de balise

            lex[lexi] = '\0';

            // Inner text
            if (lexi > 0) {     // deja du texte
                if (!curr_node) {   // mais pas de balise avant...
                    fprintf(stderr, "Text outside of document\n");
                    return FALSE;
                }

                curr_node->inner_text = strdup(lex);  //affecter le contenu du texte à l'élément inner_text
                lexi = 0;
            }

            // End of node
            if (buf[i + 1] == '/') {
                i += 2;  //passer au premier caractere de balise fermante
                while (buf[i] != '>'){
                    lex[lexi++] = buf[i++];  // stockage du nom de balise
                }
                lex[lexi] = '\0';

                if (!curr_node) {  // verifier
                    fprintf(stderr, "Already at the root\n");
                    return FALSE;
                }

                if (strcmp(curr_node->tag, lex)) {
                    fprintf(stderr, "Mismatched tags (%s != %s)\n", curr_node->tag, lex);
                    return FALSE;
                }

                curr_node = curr_node->parent; //see what is it, to return to the parent osrt of
                i++;
                continue;
            }
            //set current node
            if (!curr_node){
                curr_node = doc->root;      //si nul, on lui affecte la node root
            }
            else{
                curr_node = XMLNode_new(curr_node);  //new node is children from node we are currently working on otherwise segmentation fault
            }

            // Get tag name
            i++; // incrementation de la position dans le buf
            while (buf[i] != '>'){
                lex[lexi++] = buf[i++]; //on stocke dans lex le nom de la balise
            }
            lex[lexi] = '\0';
            curr_node->tag = strdup(lex); //nom de la balise stocké dans la node en cours de traitement
            // strdup fait une copy sans avoir a allouer

            // Reset lexer
            lexi = 0;
            i++;
            continue;
        } else {
            lex[lexi++] = buf[i++];  //continuer à incrementer
        }
    }

    return TRUE;
}

//good
void XMLDocument_free(XMLDocument* doc)
{
    XMLNode_free(doc->root);
}




#endif // PARSING_XML_H_INCLUDED
