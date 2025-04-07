#include "inverted_search.h"

void update_database( Wlist *head[], Flist **f_head)
{ 

    char file_name[FNAME_SIZE];

    printf("Enter the file name\n");
    scanf("%s" , file_name);
    int empty;
    empty = isFileEmpty(file_name);
	if(empty == FILE_NOTAVAILABLE)
    {
	    printf("Failure: %s is not available\n" , file_name);
        printf("\t Hence we can't able to add %s file into the file linked list\n", file_name);
	}

    else if(empty == FILE_EMPTY)
	{
        printf("Failure: %s is not having contents in it\n" , file_name);
	    printf("\t Hence we can't able to add %s file into the file linked list\n", file_name);
	}

    else
	{
	    int ret = to_create_list_of_files(f_head , file_name);

	    if(ret == SUCCESS)
	    {
    		printf("Success: Inserted the file %s into file linked list\n" , file_name);
        }

	    else if(ret == REPEATATION)
	    {
    	    printf("Failure: %s file is not added to file linked list as it is repeated\n", file_name);
        }

	    else
	    {
		    printf("Failure\n");
	    }       
    }



    while(*f_head)
    {
	    if(!strcmp((*f_head) -> file_name , file_name))
	    {
	        create_database(*f_head, head);
            printf("Success : Creation of database for file -> %s\n", file_name );
	    }

	    *f_head = (*f_head)->link;
    }
}

