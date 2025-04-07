#include "inverted_search.h"

char *fname;

void create_database(Flist *f_head, Wlist *head[])
{
    while(f_head)
    {
	    read_datafile(f_head , head , f_head->file_name);
	    f_head = f_head->link;
    }

}
 
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename)
{

    int flag = 1;
    fname = filename;
    char word[WORD_SIZE];

    FILE *fptr = fopen(filename ,"r");

    while(fscanf(fptr , "%s", word) != EOF)
    {

	    int index = ((tolower(word[0])) % 97);
 
    	if(!(index >= 0 && index <= 25))
        {
	        index = 26;
        }

        flag = 1;
    	if(head[index] !=  NULL)
    	{
    	    Wlist *temp = head[index];

    	    while(temp)
    	    {
    		    if(!strcmp(temp->word , word))
    		    {
    		        update_word_count(&temp , filename);
    		        flag = 0;
                    break;
    		    }
    		temp = temp->link;
    	    }
    	}

    	if(flag == 1)
    	{  
    	    insert_at_last(&head[index] , word);
    	}
    }
}

int update_word_count(Wlist **head, char *file_name)
{
    //.......TODO.............

    //check filenames are same or not 
    // when filenames are same ->  increment word_count
    //when filenames are diff  -> increment file_count , create new Ltable 
    Ltable *temp = (*head)->Tlink;

    while(temp)
    {
        if(strcmp(file_name, temp -> file_name) == 0)
        {
            (temp -> word_count)++;
            return SUCCESS;
        }

        if(temp -> table_link == NULL)
            break;

        temp = temp -> table_link;
    }
    Ltable *new = malloc(sizeof(Ltable));

    if(new == NULL)
	    return FAILURE;

    new->word_count = 1;
    strcpy(new->file_name,file_name); 
    new->table_link = NULL;
    temp -> table_link = new;
    ((*head) ->file_count)++;
    return SUCCESS;
}