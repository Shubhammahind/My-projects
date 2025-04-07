#include "inverted_search.h" 

int search( Wlist *head, char *word)
{
    if(head == NULL)
    {
	    printf("Failure: List is empty, search for the word - (%s) is not possible\n", word);
	    return 0;
    }


    while(head)
    {

	    if(!strcmp(head->word , word))
	    {
	        printf("Word %s is present in %d file/s \n" , word , head->file_count);

	        Ltable *Thead = head->Tlink;

	        while(Thead)
	        {
	    	    printf("In file : %s    %d time/s\n " , Thead->file_name , Thead->word_count);
        	    Thead = Thead->table_link;
	        }
	            printf("\n");
	        return 0;
	    }

	    head = head->link;
    }

    printf("Failure: Search for the word - (%s) is not present\n", word);
}