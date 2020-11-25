#ifndef COMPARING_H_INCLUDED
#define COMPARING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsing_xml.h"
#include "parsing_dtd.h"


#ifndef TRUE
    #define TRUE 1
#endif
#ifndef FALSE
    #define FALSE 0
#endif

int isDTDGood(XMLDocument* doc_xml, DTDDocument* doc_dtd);

#endif // COMPARING_H_INCLUDED
