#include"inverted_search.h" 

void file_validation_n_file_list(Flist **f_head, char *argv[])
{

    int i = 1 , empty;
    while(argv[i] != NULL)
    {
	    empty = isFileEmpty(argv[i]);
    	if(empty == FILE_NOTAVAILABLE)
	    {
	        printf("Failure: %s is not available\n" , argv[i]);
    	    printf("\t Hence we can't able to add %s file into the file linked list\n", argv[i]);
	        i++;
	        continue;
    	}

	    else if(empty == FILE_EMPTY)
    	{
    	    printf("Failure: %s is not having contents in it\n" , argv[i]);
    	    printf("\t Hence we can't able to add %s file into the file linked list\n", argv[i]);
    	    i++;
    	    continue;
    	}

    	else
    	{
    	    int ret = to_create_list_of_files(f_head , argv[i]);

    	    if(ret == SUCCESS)
    	    {
        		printf("Success: Inserted the file %s into file linked list\n" , argv[i]);
	        }

    	    else if(ret == REPEATATION)
    	    {
        	    printf("Failure: %s file is not added to file linked list as it is repeated\n", argv[i]);
	        }

    	    else
    	    {
    		    printf("Failure\n");
    	    }

	        i++;
	        continue;        

	    }
    }

}

int isFileEmpty(char *filename)
{
    FILE *fptr = fopen(filename , "r" );
    if(fptr == NULL)
    {
	    if(errno == ENOENT)
	    {
	        return FILE_NOTAVAILABLE;
	    }
    }

    fseek(fptr , 0 , SEEK_END);

    if(ftell(fptr) == 0)
    {
	    return FILE_EMPTY;
    }

}

int to_create_list_of_files(Flist **f_head, char *name)
{
    if (*f_head != NULL) 
    {
        Flist *find_dup = *f_head;
        
        // Traverse the list to find a duplicate file name
        while (find_dup != NULL) // <- this condition look crful it traverse upto last node and go inside loop and do operation , and it is coorect , but you write f_head -> link != NULL it travser upto last NULL or not and this not requirment. we also check last node filed (name).
        {
            if (strcmp(find_dup->file_name, name) == 0) {
                // Duplicate found
                return REPEATATION;
            }
            find_dup = find_dup->link;
        }
    }

    Flist *new = malloc(sizeof(Flist));
    if(new == NULL)
    {
        return FAILURE;
    }

    strcpy(new -> file_name, name); //*name. This will give you the first character of the string, not the full string itself.
    new -> link = NULL;

    if(*f_head == NULL)
    {
        *f_head = new;
        return SUCCESS;
    }



    Flist *temp = *f_head;

    while(temp -> link != NULL)
    {
        temp = temp -> link;
    }

    temp -> link = new;

    return SUCCESS;
    

}