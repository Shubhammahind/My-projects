#include "inverted_search.h" 
void display_database( Wlist *head[] )
{
	printf("-------------------------------------------------------------------------------------------------------------------\n");
    printf("[index]	       [word]	     file_count file/s	   File: File_name	word_count\n");
	printf("-------------------------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < 27; i++)
    {
		if(head[i] != NULL)
		{
	    	print_word_count(head[i]);
		}
    }
	printf("\n-------------------------------------------------------------------------------------------------------------------\n");

}

int print_word_count(Wlist *head)
{
    //traverse through Wlist till last node

    while(head != NULL)
    {
		int index = 0;
		index = ((tolower(head->word[0])) % 97);
		if(!(index >= 0 && index <= 25))
		{
			index = 26;
		}

	printf("  [%2d]   %10s    %10d file/s   " , index , head->word , head->file_count);
	Ltable *Thead = head->Tlink;

	//traverse through Ltable list

	while(Thead)
	{
	    printf("        File: %6s             %d  " , Thead->file_name , Thead->word_count);
	    Thead = Thead->table_link;
	}
	printf("\n");

	head = head->link;
    }
}
	