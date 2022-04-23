#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file
{
    char filename[20];
    struct file* next;
};

struct file* slds = NULL;
char single_level_root[20];

void sl_display()
{
    struct file *ptr;
    ptr = slds;

    if (slds == NULL)
        printf("The root directory is empty.\n");
    else
    {
        printf("\n%-30s[root]\n", single_level_root);
        while (ptr != NULL)
        {
            printf("\t-%-21s[file]\n", ptr -> filename);
            ptr = ptr -> next;
        }
    }
}

void sl_create()
{
    char str[20];

    if (slds == NULL)
    {
        struct file *newnode = (struct file *)malloc(sizeof(struct file));
        newnode -> next = NULL;

        printf("Enter name of the file: ");
        scanf("%s", str);

        strcpy(newnode -> filename, str);

        slds = newnode;

        sl_display();
    }
    else
    {
        struct file *ptr;
        struct file *newnode = (struct file *)malloc(sizeof(struct file));
        newnode -> next = NULL;

        printf("Enter name of the file: ");
        scanf("%s", str);

        ptr = slds;
        while (ptr != NULL)
        {
            if (strcmp(str, ptr -> filename) == 0)
            {
                printf("File with similar name found. File creation failed.\n");
                sl_display();
                return;
            }
            ptr = ptr -> next;
        }

        ptr = slds;
        while (ptr -> next != NULL)
            ptr = ptr -> next;

        strcpy(newnode -> filename, str);
        ptr -> next = newnode;

        printf("New file created successfully.\n");
        sl_display();
    }
}

void sl_delete()
{
    if (slds == NULL)
        printf("There are no files to delete.\n");
    else
    {
        char filename[20], found = 0;
        struct file *ptr;
        struct file *preptr;

        printf("Enter name of the file to be deleted: ");
        scanf("%s", filename);

        ptr = slds;
        preptr = slds;

        while (ptr != NULL)
        {
            if (strcmp(ptr -> filename, filename) == 0)
            {
                found = 1;
                break;
            }
            preptr = ptr;
            ptr = ptr -> next;
        }

        if (found == 1)
        {
            if (ptr == slds)
            {
                if (slds -> next == NULL)
                {
                    slds = NULL;
                    free(ptr);
                }
                else
                {
                    slds = ptr -> next;
                    free(ptr);
                }
            }
            else
            {
                preptr -> next = ptr -> next;
                free(ptr);
            }
            printf("File %s deleted successfully.\n", filename);
            sl_display();
        }
        else
            printf("File %s not found.\n", filename);
    }
}

void sl_search()
{
    struct file *ptr;
    char str[20];
    int found = 0;

    printf("Enter name of file to search: ");
    scanf("%s", str);

    if (slds == NULL)
        printf("The root directory is empty.\n");
    else
    {
        ptr = slds;
        while (ptr != NULL)
        {
            if (strcmp(str, ptr -> filename) == 0)
            {
                printf("File found.\n");
                sl_display();
                return;
            }
            ptr = ptr -> next;
        }

        printf("File not found.\n");
    }
}

void main()
{
    int choice;

    printf("\nEnter name of the root directory: ");
    scanf("%s", single_level_root);
    printf("\nRoot directory %s created.", single_level_root);

    do
    {
        printf("\n\n\tMENU\n1. Create file\n2. Delete file\n3. Search file\n4. Display files\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: sl_create();
                    break;
            case 2: sl_delete();
                    break;
            case 3: sl_search();
                    break;
            case 4: sl_display();
                    break;
        }
    } while (choice >= 1 && choice <= 4);
}
