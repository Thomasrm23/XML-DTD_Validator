#include "comparing.h"



int isDTDGood(XMLDocument* doc_xml, DTDDocument* doc_dtd){
   // if(strcmp(first_dtd->tag_type, "ELEMENT") == 0){      // marche
    XMLNode *classrooms_xml = XMLNode_child(doc_xml->root, 0);

    //for(int i=0; i<classrooms_xml->children.size; i++){
        //XMLNode *childs = XMLNode_child(XMLNode_child(doc_xml->root, 0), 0);
       // printf("  %d is : \"%s\" containing : %s\n", i+1, childs->tag, childs->inner_text);
   // }

    DTDNode *classrooms_dtd = DTDNode_child(doc_dtd->root, 0);
    DTDNode *classroom_dtd = DTDNode_child(doc_dtd->root, 1);
    DTDNode *attr_dtd = DTDNode_child(doc_dtd->root, 2);    // partie2

    //doc_dtd->
    //children.size

    if(strcmp(classrooms_dtd->tag_type, "ELEMENT")){
        printf("Le type de votre element \"%s\" n'est pas defini correctement dans le DTD ms\n",classrooms_dtd->tag_name);
        return 0;
    }

    if (strcmp(classroom_dtd->tag_type, "ELEMENT")){
        printf("Le type de votre element \"%s\" n'est pas defini correctement dans le DTD m\n", classroom_dtd->tag_name);
        return 0;
    }

    if(strcmp(classrooms_dtd->tag_name, classrooms_xml->tag)){
        printf("Le type de votre element \"%s\" n'est pas defini correctement dans le DTD diff\n",classrooms_dtd->tag_name);
        return 0;
    }

    if ((classrooms_xml->children.size > 1) && (classrooms_dtd->several[0] == 0)){
        printf("Le fichier DTD ne permet pas que la balise \"%s\" du fichier xml soit en plusieurs exemplaires.", classrooms_dtd->child[0]);
        return 0;
    }

    if (strcmp(classroom_dtd->content, "PCDATA")){
        printf("Le fichier DTD ne permet pas a la balise \"%s\" du fichier xml de contenir des donees.", classrooms_dtd->child[0]);
        return 0;
    }
/*
    printf("\nTEST ----------:\nXML ------\n");
    printf("tag name is : %s, ", classrooms_xml->tag);
    printf("%d children\n", classrooms_xml->children.size);
*/
    for(int i=0; i<classrooms_xml->children.size; i++){
        XMLNode *childs = XMLNode_child(XMLNode_child(doc_xml->root, 0), i);
        //printf("  %d is : \"%s\" containing : %s   \n", i+1, childs->tag, childs->inner_text);
        if((strcmp(classrooms_dtd->child[0], childs->tag)) || (strcmp(classroom_dtd->tag_name, childs->tag))){
            printf("Le nom de la balise enfant \"%s\" de votre DTD ne correspond pas a la balise enfant numero %d \"%s\" de votre xml.\n",classrooms_dtd->child[0], i+1, childs->tag);
            return 0;
        }
        //XMLNode node = *doc.root;
//partie2

        if (strcmp(attr_dtd->tag_type, "ATTLIST")){
            printf("Le type de votre attribut n'est pas defini correctement dans le DTD.\n");
            return 0;
        }

       // printf("nombre d'attributs: %d  ", childs->attributes.size);
        for(int j=0; j<childs->attributes.size; j++){
            XMLAttribute attr = childs->attributes.data[j];

/*            printf("--%s --> \"%s\"--", attr.key, attr.value);
            printf("\n ici--");
            printf("\n%s  %s\n", attr_dtd->content_info, attr.key);
            printf("---et la");
            printf("----xml: %s\n", attr.key);
            printf("----dtd: %s\n", attr_dtd->attr_name);
            */
            if (strcmp(attr_dtd->attr_name, attr.key)){
         //   if (strcmp(attr_dtd->attr_name, attr.key)){
                printf("L'attribut \"%s\" de votre DTD ne correspond pas a l'attribut \"%s\" de la balise enfant \"%s\" numero %d de votre xml.\n", attr_dtd->attr_name, attr.key, childs->tag, i+1);
                return 0;
            }
           /* if (attr_dtd->content_info == "REQUIRED" && attr.key == 0){
                printf("required...");
                return 0;
            }*/

        }

     //   if (childs->attributes.size == 0 && attr_dtd->content_info == "REQUIRED"){
        if ((childs->attributes.size == 0) && (strcmp(attr_dtd->content_info, "REQUIRED") == 0)){
            printf("\nDans votre xml, la balise \"%s\" ne contient pas d'attribut; votre DTD precise qu'un attribut est requis\n", childs->tag);
            return 0;
        }

    }



    // partie 2

    //XMLNode node = *doc.root;
   /*
    printf("attribtss : \n");
    for(int i=0; i<node.attributes.size; i++){
        XMLAttribute attr = node.attributes.data[i];
        printf(" %s --> \"%s\"\n", attr.key, attr.value);
    }
    */




    // fin partie 2


/*
    printf("\nFin XML ------\n");

    printf("Le type de votre element \"%s\" est defini dans le DTD",classrooms_dtd->tag_name);

    printf("\nDTD ---------\n");
    printf("\nit's an %s named %s, child: \n    %s with %d +\n", classrooms_dtd->tag_type, classrooms_dtd->tag_name, classrooms_dtd->child[0], classrooms_dtd->several[0]);

    printf("\n\nfirst :%s %s %s\n", classrooms_dtd->tag_type, classrooms_dtd->tag_name, classrooms_dtd->child[0]);
    printf("second :%s %s %s\n", classroom_dtd->tag_type, classroom_dtd->tag_name, classroom_dtd->content);
    printf("third :%s %s %s %s %s\n", attr_dtd->tag_type, attr_dtd->tag_name, attr_dtd->attr_name, attr_dtd->content, attr_dtd->content_info);

    //printf("third :%s\n", attr_dtd->tag_name);
    printf("\nFin DTD ---------\n");
*/
    return 1;



    //}

}
