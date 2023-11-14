#include "mp3view.h"
#ifndef MP3EDIT_H
#define MP3EDIT_H


typedef struct _Edit
{
    FILE *fptr;
    char *tag;
}Edit;

/* checking argumnests*/
Status check_args(char *argv[],Edit *edit);

/* opening the files */
Status open_file(char *argv[],Edit *edit);

/* editing the files content */
Status do_edit(char *argv[], Edit *edit);

/* swapping the number*/
void swapping(void *size, void *size1);

/* closing the file */
Status file_close(Edit *edit);
#endif
