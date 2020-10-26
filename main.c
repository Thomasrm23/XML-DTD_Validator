#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sys/file.h>
#include <strings.h>
long fileLength(FILE* file);

int main(int argc,char* argv[])
{
    FILE* xmlFile;

    xmlFile = fopen("fichierTest.xml","r");
    if(xmlFile == NULL){
        perror("File cannot be read because");
        exit(-1);
    }

    long fLength = fileLength(xmlFile);
    char fBuffer[fLength];

    fread(fBuffer,fLength,1,xmlFile);

    fclose(xmlFile);
    return 0;
}

long fileLength(FILE* file){
    assert(file != NULL);

    fseek(file,0L,SEEK_END);
    long length = ftell(file);
    fseek(file,0L,SEEK_SET);
    return length;
}
