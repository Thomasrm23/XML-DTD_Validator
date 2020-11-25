#include "parsing_xml.h"
#include "parsing_dtd.h"
#include "comparing.h"


int main(int argc, char**argv){
    XMLDocument doc;
    DTDDocument doc2;
    if ((XMLDocument_load(&doc, "partie2_muliples.xml")) && (DTDDocument_load(&doc2, "partie2_muliples.dtd"))){




        int result = isDTDGood(&doc, &doc2);

        if (result == 1){
            printf("\nDTD OK et XML correct\n");
        }

        XMLDocument_free(&doc);
    }

    return 0;
}
