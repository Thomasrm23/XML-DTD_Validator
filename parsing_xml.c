#include "parsing_xml.h"



void XMLAttribute_free(XMLAttribute* attr)
{
    free(attr->key);
    free(attr->value);
}

void XMLAttributeList_init(XMLAttributeList* list)
{
    list->heap_size = 1;
    list->size = 0;
    list->data = (XMLAttribute*) malloc(sizeof(XMLAttribute) * list->heap_size);
}

void XMLAttributeList_add(XMLAttributeList* list, XMLAttribute* attr)
{
    while (list->size >= list->heap_size) {     // augmenter la taille du tableau
        list->heap_size *= 2;
        list->data = (XMLAttribute*) realloc(list->data, sizeof(XMLAttribute) * list->heap_size);
    }

    list->data[list->size++] = *attr;
}

void XMLNodeList_init(XMLNodeList* list)
{
    list->heap_size = 1;
    list->size = 0;
    list->data = (XMLNode**) malloc(sizeof(XMLNode*) * list->heap_size);
}

void XMLNodeList_add(XMLNodeList* list, XMLNode* node)
{
    while (list->size >= list->heap_size) {
        list->heap_size *= 2;
        list->data = (XMLNode**) realloc(list->data, sizeof(XMLNode*) * list->heap_size);
    }

    list->data[list->size++] = node;
}

XMLNode* XMLNode_new(XMLNode* parent)
{
    XMLNode* node = (XMLNode*) malloc(sizeof(XMLNode));
    node->parent = parent;
    node->tag = NULL;
    node->inner_text = NULL;
    XMLAttributeList_init(&node->attributes);
    XMLNodeList_init(&node->children);
    if (parent)                     //s'i y a un parent, on ajoute
        XMLNodeList_add(&parent->children, node);
    return node;
}

void XMLNode_free(XMLNode* node)
{
    if (node->tag){
        free(node->tag);
    }
    if (node->inner_text){
        free(node->inner_text);
    }
    for (int i = 0; i < node->attributes.size; i++)
        XMLAttribute_free(&node->attributes.data[i]);
    free(node);
}

XMLNode* XMLNode_child(XMLNode* parent, int index)
{
    return parent->children.data[index];
}

int XMLDocument_load(XMLDocument* doc, const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Le fichier n'a pas pu etre charge au chemin '%s'\n", path);
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

    char store[256];  //stocker les caracteres
    int position = 0;
    int i = 0;

    XMLNode* curr_node = doc->root;  //

    while (buf[i] != '\0')      //lecture du buffer du fichier
    {
        if (buf[i] == '<') {    //debut de balise

            store[position] = '\0';

            // test interieur
            if (position > 0) {     // deja du texte
                if (!curr_node) {   // mais pas de balise avant...
                    fprintf(stderr, "Text outside of document\n");
                    return FALSE;
                }

                curr_node->inner_text = strdup(store);  //affecter le contenu du texte à l'élément inner_text
                position = 0;
            }

            // fin de node
            if (buf[i + 1] == '/') {
                i += 2;     //passer au premier caractere de balise fermante
                while (buf[i] != '>'){
                    store[position++] = buf[i++];  // stockage du nom de balise
                }
                store[position] = '\0';

                if (!curr_node) {  // verifier que ce ne soit pas null
                    fprintf(stderr, "Deja a la racine\n");
                    return FALSE;
                }

                if (strcmp(curr_node->tag, store)) {
                    fprintf(stderr, "Dans votre xml, nom de balises differents pour : %s et %s\n", curr_node->tag, store);
                    return FALSE;
                }

                curr_node = curr_node->parent; //see what is it, to return to the parent sort of
                i++;
                continue;
            }

            //declaration du fichier xml
            if (buf[i+1] == '?') {
                while (buf[i] != ' ' && buf[i] != '>'){
                    store[position++] = buf[i++];
                }
                store[position] = '\0';

                if (strcmp(store, "<?xml") == 0) {
                    while (buf[i] != '>'){
                        i++;
                    }
                    i++;
                    position = 0;
                    continue;
                }else{
                    fprintf(stderr, "Mauvaise declaration du xml\n");
                    return FALSE;
                }
            }

            //initialiser le node sur lequel on travaille
            curr_node = XMLNode_new(curr_node);


            i++; // incrementation de la position dans le buf
            XMLAttribute curr_attr = {0, 0};

            while (buf[i] != '>'){

                store[position++] = buf[i++]; //on stocke dans store le nom de la balise

                //traitements pour les attributs
                //nom de balise
                if (buf[i] == ' ' && !curr_node->tag) {
                    store[position] = '\0';
                    curr_node->tag = strdup(store);
                    position = 0;
                    i++;
                    continue;
                }

                // gerer les espaces
                if (store[position-1] == ' ') {
                    position--;
                    continue;

                }

                //clé
                if (buf[i] == '=') {
                    store[position] = '\0';
                    curr_attr.key = strdup(store);
                    position = 0;
                    continue;
                }

                //valeur
                if (buf[i] == '"') {
                    if (!curr_attr.key) {
                        fprintf(stderr, "Valeur n'a pas d'attributs\n");
                        return FALSE;
                    }

                    position = 0;
                    i++;

                    while (buf[i] != '"')
                        store[position++] = buf[i++];
                    store[position] = '\0';
                    curr_attr.value = strdup(store);
                    XMLAttributeList_add(&curr_node->attributes, &curr_attr);

                    curr_attr.key = NULL;
                    curr_attr.value = NULL;
                    position = 0;
                    i++;
                    continue;
                }
            }

            store[position] = '\0';
            if (!curr_node->tag){
                curr_node->tag = strdup(store); //nom de la balise stocké dans la node en cours de traitement
                // strdup fait une copy sans avoir a allouer
            }

            position = 0;
            i++;
            continue;
        } else {
            store[position++] = buf[i++];  //continuer à incrementer
        }
    }

    return TRUE;
}

//good
void XMLDocument_free(XMLDocument* doc)
{
    XMLNode_free(doc->root);
}
