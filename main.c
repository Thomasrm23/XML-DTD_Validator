#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/* Librairies potentiellement utiles
#include <cytpe.h>
 */

long filelength(FILE* file);


int main(int argc,char* argv[]){
    FILE* xmlFile;

    xmlFile = fopen("fichierTest.xml","r");
    if(xmlFile == NULL){
        perror("File cannot be read because");
        exit(1);
    }

    long fLength = filelength(xmlFile);
    char* fBuffer = (char *)malloc(fLength * sizeof(char*));
    fread(fBuffer,fLength,1,xmlFile);

    printf("%s\n",fBuffer);
    fclose(xmlFile);
    return 0;
}

long filelength(FILE* file){
    assert(file != NULL);

    fseek(file,0L,SEEK_END);
    long length = ftell(file);
    fseek(file,0L,SEEK_SET);
    return length;
}
