#ifndef MP3VIEW_H
#define MP3VIEW_H

#include <stdio.h>
#include "types.h"
#include <string.h>
#include <stdlib.h>


typedef struct _view
{
    char *file_name;
    FILE *fptr;
    int size;
    char name[4];

}View;

OperationType check_operation(char *argv[]);

Status read_and_validate_arg(char *argv[],View *view);

Status do_display(View *view);

Status open_files(View *view);

Status check_tag(View *view);

Status do_display(View *view);

Status read_tag(View *view, FILE *file);

Status swap(void *num, void *num1, int size);

Status song_name(uint size, FILE *file);

Status get_size(View *view);

Status close_file(View *view);
#endif
