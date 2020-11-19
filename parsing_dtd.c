#include "parsing_dtd.h"


DTDNode* DTDNode_new(DTDNode* parent) //cré new node et met le parent à nul
{
    DTDNode* node = (DTDNode*) malloc(sizeof(DTDNode));
    node->parent = parent;
    node->tag_type = NULL;
    node->tag_name = NULL;
    //  node->inner_text = NULL;
    return node;
}

/*
void DTDNode_free(DTDNode* node)
{
    if (node->tag){
        free(node->tag);
    }
    if (node->inner_text){
        free(node->inner_text);
    }
    free(node);
}
*/

bool DTDDocument_load(DTDDocument* doc, const char* path){
    FILE* fp = fopen(path, "r");
    if (!fp){
        fprintf(stderr, "Could not load file from '%s'\n", path);
        return false;
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

    DTDNode* current_node = NULL;

    while (buffer[i] != '\0'){

        if ((buffer[i] == '<') && (buffer[i+1] == '!')){

            // store[position] = '\0';


            if (!current_node){
                current_node = doc->root;      //si nul, on lui affecte la node root
            }
            else{
                current_node = DTDNode_new(current_node);  //new node is children from node we are currently working on otherwise segmentation fault
            }

            i++; // incrementer pour arriver à la partie à stocker
            while ((buffer[i]) != ' '){
                //     while(buffer[i] != buffer[i+1]){
                //printf("%c\n", buffer[i]);
                store[position++] = buffer[i++];
            }
            store[position] = '\0';
            current_node->tag_type = strdup(store);

            position = 0;
            i++;
            //continue;

            //test
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
                    while ((buffer[i]) != ')'){
                        store[position++] = buffer[i++];
                    }
                    store[position] = '\0';
                    current_node->content = strdup(store);
                    position = 0;
                    i++;
                }
                else{
                    int children_count = 0;
                    while((buffer[i]) != ')'){
                        while (((buffer[i]) != ',') && ((buffer[i]) != ')') && ((buffer[i]) != '+')){
                            store[position++] = buffer[i++];
                        }
                        if (buffer[i] == '+'){
                            *(current_node->several[children_count]) = true;
                            i++;
                        }
                        store[position] = '\0';
                        current_node->children[children_count] = strdup(store);
                        position = 0;
                        if (buffer[i] == ','){
                            i++;
                            children_count++;
                        }
                    }
                }

            }


            /* if ((buffer[i]) == ' '){
                 i++;
                 while ((buffer[i]) != ' '){
                     store[position++] = buffer[i++];
                 }
                 current_node->tag_name = strdup(store);
                 position = 0;

                 if(!current_node){
                     fprintf(stderr, "Texte en dehors de balise");
                     return false;
                 }
             }*/
        }
        else{
            store[position++] = buffer[i++];
        }
    }
    return true;
}
