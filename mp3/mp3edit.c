#include "mp3edit.h"

Status check_args(char *argv[],Edit *edit)
{
    if(strcmp(argv[2],"-t")==0)
	edit->tag = "TIT2";
    else if(strcmp(argv[2],"-a")==0)
	edit->tag = "TPE1";
    else if(strcmp(argv[2],"-A")==0)
	edit->tag = "TALB";
    else if(strcmp(argv[2],"-y")==0)
	edit->tag = "TYER";
    else if(strcmp(argv[2],"-m")==0)
	edit->tag = "TCON";
    else if(strcmp(argv[2],"-c")==0)
	edit->tag = "COMM";
    else 
	return e_failure;

    return e_success;
}

Status open_file(char *argv[], Edit *edit)
{
    if(strcmp(strstr(argv[4],"."),".mp3") == 0)
    {
	edit->fptr = fopen(argv[4],"r+");
	return e_success;
    }
    else
	return e_failure;

}

Status do_edit(char *argv[], Edit *edit)
{
    fseek(edit->fptr,10,SEEK_SET);
    for(int i=0; i<6; i++)
    {
	char ch[4];
	fread(ch,1,4,edit->fptr);
	int size,size1;

	fread(&size,1,4,edit->fptr);

	swapping(&size, &size1);
	char c[size1];
	fseek(edit->fptr,3,SEEK_CUR);
	if(strcmp(ch,edit->tag) !=0 )
	{
	    fseek(edit->fptr,size1-1,SEEK_CUR);
	}
	else
	{
	    strcpy(c,argv[3]);
	    fwrite(c,1,size1 -1,edit->fptr);
	    return e_success;
	}
    }
}

void swapping(void *size, void *size1)
{
    for(int i=0; i<4; i++)
    {
	*(char *)(size1+i) = *(char *)(size + (4-i-1));
    }
}

Status file_close(Edit *edit)
{
    fclose(edit->fptr);
    return e_success;
}
