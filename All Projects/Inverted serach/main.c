#include "inverted_search.h" 

int main(int argc , char *argv[])
{
    system("clear");

    Wlist *head[27] = { NULL }; 

    if(argc <= 1)
    {
	    printf("Enter the valid nunmber of Command Line Arguments\n");
	    printf("./Flist.exe  file1.txt   file2.txt.....\n");
	    return 0;
    }

   Flist *f_head = NULL;

   file_validation_n_file_list(&f_head, argv);

   if(f_head == NULL)
    {
       printf("No files added to file linked list\n");
       printf("Hence the process got terminated\n");
       return 1;
    }
    printf("\n");
    int choice;
    char ch;

    do
    {
        printf("Select your choice among following options:\n1. Create DATABASE\n2. Display Database\n3. Update DATABASE\n4. Search\n5. Save Database\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create_database(f_head , head);
            printf("\n");
            while(f_head)
            {
                printf("Success : Creation of database for file -> %s\n", f_head -> file_name );
                f_head = f_head -> link;
            }
            break;
        
        case 2:
            display_database(head);
            break;

        case 3:
            update_database(head, &f_head);
            break;

        case 4:
            printf("Enter the word to search : ");
            char word[WORD_SIZE];
            __fpurge(stdin);
            scanf("%s", word);
            int index = ((tolower(word[0])) % 97);
            if(!(index >= 0 && index <= 25))
            {
                index = 26;
            }

            search(head[index], word);
            break;

        case 5:
            save_database(head);
            break;

        default:
            printf("Enter valid choice between 1 to 5, if you want to continue\n");
            break;
        }
        printf("\n");
        printf("Do you want to continue?\nY/y - Continue\nN/n - Discontinue\n");
        printf("\n");
        __fpurge(stdin);
        scanf("%c",&ch);
        printf("\n");
    } while (ch == 'y' || ch == 'Y');
}
