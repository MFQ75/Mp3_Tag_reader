#include "mp3view.h"
#include "mp3edit.h"

int main(int argc, char *argv[])
{
    //checking the arguments
    if(argc < 2)
    {
        printf("\n------------------------------Selected view details------------------------------\n\n");
	printf("ERROR : ./a.out : Inavlid arguments\n");
	printf("USAGE :\n");
	printf("To view please pass like : ./a.out -v mp3filename\n");
	printf("To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
	printf("To get help like : ./a.out --help\n");
	printf("---------------------------------------------------------------------------------\n\n");
	return 0;
    }
    //checking the switch case by using function call
    switch(check_operation(argv))
    {
	//help menu
	case e_help : printf("\n----------------------------------Help Menu--------------------------------------\n\n");
	              printf("1. -v -> to view mp3 file contents\n");
		      printf("2. -e -> to edit mp3 file contents\n");
		      printf("         2.1. -t -> to edit song title\n");
		      printf("         2.2. -a -> to edit artist name\n");
		      printf("         2.3. -A -> to edit album name\n");
		      printf("         2.4. -y -> to edit year\n");
		      printf("         2.5. -m -> to edit content\n");
		      printf("         2.1. -c -> to edit comment\n");
	              printf("---------------------------------------------------------------------------------\n\n");
		      break;
	//view menu
	case e_view : View view;
		      if(read_and_validate_arg(argv, &view) == e_failure)
		      {
			  printf("Error : 3rd argument not valid\n");
			  printf("Usage : filename.mp3\n");
		      }
		      else
		      {
			  if(open_files(&view)==e_success)
			  {
			      if(check_tag(&view) == e_success)
			      {
				  printf("\n------------------------------Selected view details------------------------------\n\n");
	                          printf("\n---------------------------------------------------------------------------------\n");
	                          printf("                       MP3 Tag reader and editor for ID3v2                       \n");
	                          printf("---------------------------------------------------------------------------------\n\n");
				  if(do_display(&view) == e_success)
				  {
				      
	                          printf("\n---------------------------------------------------------------------------------\n\n");
				  printf("-------------------------Detail displayed successfully---------------------------\n\n");
				  close_file(&view);

				  }
			      }
			      else
				  printf("ID3 tag file npt found\n");
			  }
		      } 
		      break;
        //edit menu
	case e_edit : if(argc < 4)
		      {
			  printf("Error : Please pass the valid arguments\n");
			  printf("Usage : ./a.out -e -t/-a/-A/-y/m/-c filename.mp3\n"); 
		      } 
		      else
		      {
			  Edit edit;
			  if(check_args(argv, &edit) == e_success)
			  {
			      if(open_file(argv, &edit) == e_success)
			      {
				  do_edit(argv,&edit);
				  if(file_close(&edit) == e_success)
				  {
				      printf("Content Edit Successfull\n");
				  }
				  
			      }
			      else
			          printf("Error : File name Should be .mp3 file\n");
			  }
			  else
			  {
			      printf("Error : 3rd argument not valid\n");
			      printf("Usage : -t/-a/-A/-y/-m/-c\n");
			  }
		      }
		      break;
	default     : printf("ERROR : 2nd agument invalid\n");
		      printf("USAGE : -e/-d/--help\n");
    }


    return 0;
}

