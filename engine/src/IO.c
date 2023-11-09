#include "IO.h"


char* io_read_file(const char* path){
    FILE *fp;
    long size = 0;
    char* sfile;
    
    /* Read File to get size */
    fp = fopen(path, "rb");
    if(fp == NULL) {
        pe_printError("Failed to load file: %s", path);

        return "";
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp)+1;
    fseek(fp, 0L, SEEK_SET);

    /* Read File for Content */
    fp = fopen(path, "r");
    sfile = memset(malloc(size), '\0', size);
    fread(sfile, 1, size-1, fp);
    fclose(fp);
    return sfile;
}


int io_write_file(void *buffer, size_t size, const char* path){
    FILE *fp = fopen(path, "wb");

    if (!fp || ferror(fp)){
        pe_printError("cannot write file: %s", path);
    }
    size_t chunks_written = fwrite(buffer, size, 1, fp);

    fclose(fp);

    if(chunks_written != 1){
        pe_printError("Write error: expected 1 chunk, got the following amount:", chunks_written);
    }


    return 0;
}

void pe_free_mem(void *ptr){
    free(ptr);
}