#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file
{
    char filename[20];
    struct file* next;
};

struct directory
{
    char dirname[20];
    struct file* flstart;
    struct directory* dlstart;
    struct directory* next;
};

struct directory *tl_directory = NULL;
char two_level_root[20];

void tl_display()
{
    struct directory *ptr1;
    struct file *ptr2;

    printf("\nTwo level directory:\n");
    printf("%-38s[root]\n", two_level_root);

    ptr1 = tl_directory;

    while (ptr1 != NULL)
    {
        printf("\t-%-29s[directory]\n", ptr1 -> dirname);

        ptr2 = ptr1 -> flstart;

        while (ptr2 != NULL)
        {
            printf("\t\t-%-21s[file]\n", ptr2 -> filename);
            ptr2 = ptr2 -> next;
        }

        ptr1 = ptr1 -> next;
    }
}

void tl_create_directory()
{
    char str[20];

    if (tl_directory == NULL)
    {
        struct directory *newnode = (struct directory *)malloc(sizeof(struct directory));
        newnode -> next = NULL;
        newnode -> dlstart = NULL;
        newnode -> flstart = NULL;

        printf("Enter name of the directory: ");
        scanf("%s", str);

        strcpy(newnode -> dirname, str);

        tl_directory = newnode;

        tl_display();
    }
    else
    {
        struct directory *ptr;
        struct directory *newnode = (struct directory *)malloc(sizeof(struct directory));

        printf("Enter name of the directory: ");
        scanf("%s", str);
        newnode -> next = NULL;
        newnode -> dlstart = NULL;
        newnode -> flstart = NULL;

        ptr = tl_directory;
        while (ptr != NULL)
        {
            if (strcmp(str, ptr -> dirname) == 0)
            {
                printf("Directory with similar name found. Directory creation failed.\n");
                tl_display();
                return;
            }
            ptr = ptr -> next;
        }

        ptr = tl_directory;
        while (ptr -> next != NULL)
            ptr = ptr -> next;

        strcpy(newnode -> dirname, str);
        ptr -> next = newnode;

        printf("New directory created successfully.\n");
        tl_display();
    }
}

void tl_create_file()
{
    int flag = 0;
    char str[20];
    struct directory *ptr1;

    printf("Enter parent directory of file: ");
    scanf("%s", str);

    ptr1 = tl_directory;
    while (ptr1 != NULL)
    {
        if (strcmp(str, ptr1 -> dirname) == 0)
        {
            flag = 1;
            break;
        }
        ptr1 = ptr1 -> next;
    }

    if (flag == 0)
    {
        printf("Parent directory not found.\n");
        return;
    }

    if (ptr1 -> flstart == NULL)
    {
        struct file *newnode = (struct file *)malloc(sizeof(struct file));
        newnode -> next = NULL;

        printf("Enter name of the file: ");
        scanf("%s", str);

        strcpy(newnode -> filename, str);

        ptr1 -> flstart = newnode;

        tl_display();
    }
    else
    {
        struct file *ptr;
        struct file *newnode = (struct file *)malloc(sizeof(struct file));
        newnode -> next = NULL;

        printf("Enter name of the file: ");
        scanf("%s", str);

        ptr = ptr1 -> flstart;
        while (ptr != NULL)
        {
            if (strcmp(str, ptr -> filename) == 0)
            {
                printf("File with similar name found. File creation failed.\n");
                tl_display();
                return;
            }
            ptr = ptr -> next;
        }

        ptr = ptr1 -> flstart;
        while (ptr -> next != NULL)
            ptr = ptr -> next;

        strcpy(newnode -> filename, str);
        ptr -> next = newnode;

        printf("New file created successfully.\n");
        tl_display();
    }
}

void tl_delete()
{
    char filename[20], found = 0;
    struct file *ptr;
    struct file *preptr;
    struct directory *ptr1;

    printf("Enter name of the file to be deleted: ");
    scanf("%s", filename);

    ptr1 = tl_directory;
    while (ptr1 != NULL)
    {
        preptr = ptr = ptr1 -> flstart;

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
            break;

        ptr1 = ptr1 -> next;
    }

    if (found == 1)
    {
        if (ptr == ptr1 -> flstart)
        {
            if (ptr1 -> flstart -> next == NULL)
            {
                ptr1 -> flstart = NULL;
                free(ptr);
            }
            else
            {
                ptr1 -> flstart = ptr -> next;
                free(ptr);
            }
        }
        else
        {
            preptr -> next = ptr -> next;
            free(ptr);
        }
        printf("File %s deleted successfully.\n", filename);
        tl_display();
    }
    else
        printf("File %s not found.\n", filename);
}

void tl_search()
{
    struct file *ptr;
    struct directory *ptr1;
    char str[20];

    printf("Enter name of file to search: ");
    scanf("%s", str);

    if (tl_directory == NULL)
        printf("The root directory is empty.\n");
    else
    {
        ptr1 = tl_directory;

        while (ptr1 != NULL)
        {
            ptr = ptr1 -> flstart;

            while (ptr != NULL)
            {
                if (strcmp(ptr -> filename, str) == 0)
                {
                    printf("File %s found.\n", str);
                    return;
                }
                ptr = ptr -> next;
            }
            ptr1 = ptr1 -> next;
        }

        printf("File %s not found.\n", str);
    }
}

void main()
{
    int choice;

    printf("Enter name of the root directory: ");
    scanf("%s", two_level_root);

    do
    {
        printf("\n\tMENU\n");
        printf("1. Create directory\n2. Create file\n3. Delete file\n4. Search file\n5. Display files\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: tl_create_directory();
                    break;
            case 2: tl_create_file();
                    break;
            case 3: tl_delete();
                    break;
            case 4: tl_search();
                    break;
            case 5: tl_display();
                    break;
        }
    } while (choice >= 1 && choice <= 5);
}
