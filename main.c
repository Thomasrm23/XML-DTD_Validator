#include <stdio.h>
#include "parsing_xml.h"
#include "parsing_dtd.h"

/**
* Vérification de la présence d'un tag XML dans le DTD
* @param[in] xmlTag : Le tag présent dans le fichier XML
* @param[in] dtdTag : Le tag présent dans le fichier DTD
* @param[out] boolean : Le tag XML est présent dans le DTD ou non
*/
bool isInDTD(char* xmlTag,char* dtdTag){
    if (strcmp(xmlTag,dtdTag) == 0){
        printf("Le tag %s est defini dans le DTD.",xmlTag);
        return true;
    }
    else{
        printf("Le tag %s n'est pas defini dans le DTD.",xmlTag);
        return false;
    }
}

int main() {
    XMLDocument doc;
    char* xmlTag = NULL;
    if (XMLDocument_load(&doc, "test_parse.xml")){
      // printf("%s: %s\n", doc.root->tag, doc.root->inner_text);
       xmlTag = doc.root->tag;
    }

    DTDDocument doc2;
    char* dtdTag = NULL;
    if (DTDDocument_load(&doc2, "test_parse.dtd")){
        // printf("%d\n", DTDDocument_load(&doc, "test_parse.xml"));
        dtdTag = doc2.root->tag_name;
        // printf("%s\n %s\n %s\n %s\n %s\n", doc2.root->tag_type,doc2.root->tag_name, doc2.root->children[0],doc2.root->children[1],doc2.root->children[2]);

    }

    isInDTD(xmlTag,dtdTag);

   // doc.root->;
    XMLDocument_free(&doc);
    // DTDDocument_free(&doc2);
    return 0;
}
