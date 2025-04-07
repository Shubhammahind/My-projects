#include "inverted_search.h" 

int save_database( Wlist *head[])
{
    char file_name[FNAME_SIZE];
    static int flag = 0;
    __fpurge(stdin);
    printf("Enter the file name\n");
    scanf("%s" , file_name);
    const char *dptr = file_name;
    if(flag != 0)
    {
        if(strcmp(file_name,dptr) != 0)
        {
            printf("The previously used backup file is %s, so kindly use that file itself", dptr);
            return 1;
        }
    }

    flag = 1;

    FILE *fptr = fopen(file_name , "w" );

    for(int i = 0; i <27; i++)
    {
	    while(head[i] != NULL)
	    {
	        write_databasefile(head[i] , fptr);
            head[i] = (head[i]) -> link;
	    }
    }

    printf("Database saved\n");
}

void write_databasefile(Wlist *head, FILE *databasefile)
{
    //int index = (head -> word[0]) % 97;
    //int f_count = head -> file_count;
    char word_[WORD_SIZE];
    strcpy(word_, head -> word);
    

    //fprintf(databasefile, "#[%d]\nword is [%s]: file count is %d:\n", index, word_, f_count);
    fprintf(databasefile, "#[%d]\nword is [%s]: file count is %d: ", tolower(head -> word[0]) % 97, word_, head -> file_count);

    Ltable *temp = head -> Tlink;
    while(temp)
    {
        char f_name[FNAME_SIZE];
        strcpy(f_name, temp ->  file_name);
        fprintf(databasefile, " file name is [%s]: word count is [%d]", f_name, temp -> word_count);
        temp = temp -> table_link;
    }
    fprintf(databasefile,"\n");
    //......TODO........
    //    # [index]  word is [  word  ] : file count is [  file_count ] :  file_name  is [  file_name  ]  : word count is [ word_count  ]
}
