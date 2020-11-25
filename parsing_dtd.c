#include "parsing_dtd.h"


void DTDNodeList_init(DTDNodeList* list)
{
    list->heap_size = 1;
    list->size = 0;
    list->data = (DTDNode**) malloc(sizeof(DTDNode*) * list->heap_size);
}

void DTDNodeList_add(DTDNodeList* list, DTDNode* node)
{
    while (list->size >= list->heap_size) {
        list->heap_size *= 2;
        list->data = (DTDNode**) realloc(list->data, sizeof(DTDNode*) * list->heap_size);
    }

    list->data[list->size++] = node;
}

DTDNode* DTDNode_child(DTDNode* parent, int index)
{
    return parent->children.data[index];
}

DTDNode* DTDNode_new(DTDNode* parent) //cré new node et met le parent à nul
{
    DTDNode* node = (DTDNode*) malloc(sizeof(DTDNode));
    node->parent = parent;
    node->tag_type = NULL;
    node->tag_name = NULL;
    node->attr_name = NULL;
    node->content = NULL;
    node->content_info = NULL;
    node->several[0] = NULL;
    DTDNodeList_init(&node->children);
    if (parent)
        DTDNodeList_add(&parent->children, node);
    return node;
}


void DTDNode_free(DTDNode* node)
{
    if (node->tag_type){
        free(node->tag_type);
    }
    if (node->tag_name){
        free(node->tag_name);
    }
    if (node->attr_name){
        free(node->attr_name);
    }
    if (node->content){
        free(node->content);
    }
    if (node->content_info){
        free(node->content_info);
    }
    free(node);
}


int DTDDocument_load(DTDDocument* doc, const char* path){
    FILE* fp = fopen(path, "r");
    if (!fp){
        fprintf(stderr, "Le fichier n'a pas pu etre charge au chemin '%s'\n", path);
        return FALSE;
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = (char*) malloc(sizeof(char) * size + 1);
    fread(buffer, 1, size, fp);
    fclose(fp);
    buffer[size] = '\0';

    doc->root = DTDNode_new(NULL);

    char store[256];
    char position = 0;
    int i = 0;

    DTDNode* current_node = doc->root;

    while (buffer[i] != '\0'){

        if (buffer[i] == '<'){
            if(buffer[i+1] != '!'){
                fprintf(stderr, "Dans votre DTD, vous avez oublie le '!' apres le chevron ouvrant.\n");
                return FALSE;
            }
            store[position] = '\0';


            //declaration du dtd

            if (buffer[i+2] == 'D') {
                i += 2;
                while (buffer[i] != ' ' && buffer[i] != '['){
                    store[position++] = buffer[i++];
                }
                store[position] = '\0';

             //   i += 2;

                // balise de declaration
                if (strcmp(store, "DOCTYPE") == 0) {
                    while ((buffer[i] != '[') && (buffer[i+1] != '<')){
                        i++;
                    }
                    if (buffer[i] != '['){
                        fprintf(stderr, "Mauvaise declaration du DTD, il manque le '['\n");
                        return FALSE;
                    }
                    i++;
                    position = 0;
                    continue;
                }else{
                    fprintf(stderr, "Mauvaise declaration du DTD\n");
                    return FALSE;
                }
            }

            current_node = DTDNode_new(current_node);  //new node is children from node we are currently working on otherwise segmentation fault

            position = 0;
            i += 2; // incrementer pour arriver à la partie à stocker apres le +

            while ((buffer[i]) != ' '){
                store[position++] = buffer[i++];
            }
            store[position] = '\0';
            current_node->tag_type = strdup(store);

            if (strcmp(current_node->tag_type, "ELEMENT") == 0){

                position = 0;
                i++;

                while ((buffer[i]) != ' '){
                    store[position++] = buffer[i++];
                }
                store[position] = '\0';
                current_node->tag_name = strdup(store);

                position = 0;
                i++;

                if ((buffer[i]) == '('){
                    i++;

                    if ((buffer[i]) == '#'){
                            i++;
                        while ((buffer[i] != ')') && (buffer[i] != '>')){
                            store[position++] = buffer[i++];
                        }
                        store[position] = '\0';
                        current_node->content = strdup(store);

                        //i++;
                        if ((buffer[i]) != ')'){
                            fprintf(stderr, "Dans votre DTD, une ')' manque\n");
                            return FALSE;
                        }
                        i++;
                        if ((buffer[i]) != '>'){
                            fprintf(stderr, "Dans votre DTD, le chevron fermant de la balise \"%s\" manque\n", current_node->tag_name);
                            return FALSE;
                        }
                        current_node = current_node->parent;
                        position = 0;
                        i++;
                        continue;

                    }
                    else{
                        int children_count = 0;
                        while((buffer[i] != ')') && (buffer[i] != '>')){
                            while (((buffer[i]) != ',') && ((buffer[i]) != ')') && ((buffer[i]) != '+')){
                                store[position++] = buffer[i++];
                            }
                            if (buffer[i] == '+'){
                                current_node->several[children_count] = 1;
                                i++;
                            }
                            store[position] = '\0';
                            current_node->child[children_count] = strdup(store);
                            position = 0;
                            if (buffer[i] == ','){
                                i++;
                                children_count++;
                            }
                        }
                        if ((buffer[i]) != ')'){
                            fprintf(stderr, "Dans votre DTD, une ')' manque\n");
                            return FALSE;
                        }

                        i++;
                        if ((buffer[i]) != '>'){
                            fprintf(stderr, "Balise fermante manquante ou mal placee dans votre DTD, pour la balise \"%s\"\n", current_node->tag_name);
                            return FALSE;
                        }
                        current_node = current_node->parent;
                        position = 0;
                        i++;
                        continue;

                    }

                }else{
                    fprintf(stderr, "Dans votre DTD, une '(' manque\n");
                    return FALSE;
                }
            }
            else if (strcmp(current_node->tag_type, "ATTLIST") == 0){
                position = 0;
                i++;

                while ((buffer[i]) != ' '){
                    store[position++] = buffer[i++];
                }
                store[position] = '\0';
                current_node->tag_name = strdup(store);

                position = 0;
                i++;

                while ((buffer[i]) != ' '){
                    store[position++] = buffer[i++];
                }
                store[position] = '\0';
                current_node->attr_name = strdup(store);

                position = 0;
                i++;

                while ((buffer[i]) != ' '){
                    store[position++] = buffer[i++];
                }
                store[position] = '\0';
                current_node->content = strdup(store);

                position = 0;
                i++;

                if ((buffer[i]) != '#'){
                    fprintf(stderr, "Precisez si votre attribut \"%s\" doit contenir quelque chose ou verifiez sa syntaxe\n", current_node->attr_name);
                    return FALSE;
                }
                i++;
                while ((buffer[i]) != '>'){
                    store[position++] = buffer[i++];
                }
                store[position] = '\0';
                current_node->content_info = strdup(store);

                if ((buffer[i]) != '>'){
                    fprintf(stderr, "Balise fermante manquante ou mal placee dans votre DTD, pour l'attribut \"%s\" de la balise  \n", current_node->attr_name, current_node->tag_name);
                    return FALSE;
                }
                current_node = current_node->parent;

                i++;
                continue;

            }
            else{
                fprintf(stderr, "Le type de votre element est mal defini dans votre DTD.\n");
                return FALSE;
            }

        }
        else{
            store[position++] = buffer[i++];
        }
    }
    return TRUE;
}

