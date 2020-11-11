#include "parsing_xml.h"

int main(){
    XMLDocument doc;
    if (XMLDocument_load(&doc, "test_parse.xml")){
        printf("%s: %s\n", doc.root->tag, doc.root->inner_text);
        XMLDocument_free(&doc);
    }
//    else
//        printf("no");
    return 0;
}
