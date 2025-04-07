#include "inverted_search.h" 

extern char *fname;

int insert_at_last(Wlist **head, data_t *data)
{
    //create node

    Wlist *new = malloc(sizeof(Wlist));
    if(new == NULL)
	    return FAILURE;

    new->file_count = 1;
    strcpy(new->word,data);
    new->Tlink = NULL;
    new->link = NULL;

    update_link_table(&new);

    if(*head == NULL)
    {
	    *head = new;
	    return SUCCESS;
    }

    Wlist *temp = *head;

    while(temp->link)
    {
	    temp = temp->link;
    }

    temp->link = new;
    return SUCCESS;
}


int update_link_table(Wlist **head)
{
    //create node
    Ltable *new = malloc(sizeof(Ltable));

    if(new == NULL)
	    return FAILURE;
        
    new->word_count = 1;
    strcpy(new->file_name,fname);// to get the file name we use global variable.
    new->table_link = NULL;

    (*head)->Tlink = new; // at this point complete node gets created.
    return SUCCESS;
}