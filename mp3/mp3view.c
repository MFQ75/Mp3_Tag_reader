#include "mp3view.h"

OperationType check_operation(char *argv[])
{
    if(strcmp(argv[1],"--help")==0)
    {
	return e_help;
    }
    else if(strcmp(argv[1],"-v")==0)
    {
	return e_view;
    }
    else if(strcmp(argv[1],"-e")==0)
    {
	return e_edit;
    }
    else
	return e_error;
}

Status read_and_validate_arg(char *argv[],View *view)
{
    if(strcmp(strstr(argv[2],"."),".mp3")==0)
    {
	view->file_name = argv[2];
	return e_success;
    }
    return e_failure;
}

Status open_files(View *view)
{
    view->fptr = fopen(view->file_name,"r");

    if(view->fptr == NULL)
    {
	perror("fopen");
	return e_failure;
    }
    return e_success;
}

Status check_tag(View *view)
{
    char ch[3];
    fread(ch,1,3,view->fptr);
    if(strcmp(ch,"ID3")==0)
	return e_success;
}

Status do_display(View *view)
{
    fseek(view->fptr,10,SEEK_SET);
    if(read_tag(view,view->fptr) == e_success)
    {
	if(strcmp(view->name,"TIT2") == 0 )
	{
	    get_size(view);
	    printf("%-15s %-10s","TITLE",":");
	    if(song_name(view->size,view->fptr) == e_success)
	    {
		if(read_tag(view,view->fptr) == e_success)
		{
		    if(strcmp(view->name,"TPE1") == 0 )
		    {
			get_size(view);
			printf("%-15s %-10s","ARTIST",":");
			if(song_name(view->size,view->fptr) == e_success)
			{
			    if(read_tag(view,view->fptr) == e_success)
			    {
				if(strcmp(view->name,"TALB") == 0 )
				{
				    get_size(view);
				    printf("%-15s %-10s","ALBUM",":" );
				    if(song_name(view->size,view->fptr) == e_success)
				    {
					if(read_tag(view,view->fptr) == e_success)
					{
					    if(strcmp(view->name,"TYER") == 0 )
					    {
						get_size(view);
						printf("%-15s %-10s","YEAR", ":");
						if(song_name(view->size,view->fptr) == e_success)
						{
						    if(read_tag(view,view->fptr) == e_success)
						    {
							if(strcmp(view->name,"TCON") == 0 )
							{
							    get_size(view);
							    printf("%-15s %-10s","MUSIC",":");
							    if(song_name(view->size,view->fptr) == e_success)
							    {
								if(read_tag(view,view->fptr) == e_success)
								{
								    if(strcmp(view->name,"COMM") == 0 )
								    {
									get_size(view);
									printf("%-15s %-10s","COMMENT",":");
									if(song_name(view->size,view->fptr) == e_success)
									{
									    return e_success;
									}
								    }
								    else
									printf("COMM tag not found\n");
								}
							    }
							}
							else
							    printf("TCON tag not found\n");
						    }
						}
					    }
					    else
						printf("TYER tag not found\n");
					}
				    }
				}
				else
				    printf("TALB tag not found\n");
			    }
			}	
		    }
		    else
			printf("TPE1 tag not found\n");
		}
	    }
	}
	else
	    printf("TIT2 tag not found\n");
    }
}

Status song_name(uint size, FILE *file)
{
    char ch[size];
    fseek(file, 3, SEEK_CUR);
    fread(ch,1,size-1,file);

    printf("%s\n",ch);
    return e_success;
}

Status read_tag(View *view, FILE *file)
{
    fread(view->name,1,4,file);
    return e_success;
}

Status get_size(View *view)
{
    int size,size1;
    fread(&size, 1, 4,view->fptr);
    swap(&size,&size1,sizeof(int));
    view->size = size1;

}

Status swap(void *num, void *num1,int size)
{
    for(int i=0; i<size; i++)
    {
	*(char *)(num1 + i) = *(char *) (num + (size-1-i));
    }
}

Status close_file(View *view)
{
    fclose(view->fptr);
	return e_success;
}
