#include "parsing_xml.h"
#include "parsing_dtd.h"

int main() {
    XMLDocument doc;
    if (XMLDocument_load(&doc, "test_parse.xml")){
        printf("%s: %s\n", doc.root->tag, doc.root->inner_text);
        XMLDocument_free(&doc);
    }

    DTDDocument doc2;
    if (DTDDocument_load(&doc2, "test_parse.dtd")){
        // printf("%d\n", DTDDocument_load(&doc, "test_parse.xml"));
        printf("%s\n %s\n %s\n %s\n %s\n", doc2.root->tag_type,doc2.root->tag_name, doc2.root->children[0],doc2.root->children[1],doc2.root->children[2]);
        // DTDDocument_free(&doc2);
    }
    return 0;
}
