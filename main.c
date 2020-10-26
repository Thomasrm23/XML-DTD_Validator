#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* xmlFile;
    xmlFile = fopen("dtdTest.xml","r");
    if(xmlFile == NULL){
        perror("File cannot be read because");
        exit(-1);
    }

    fclose(xmlFile);
    return 0;
}
