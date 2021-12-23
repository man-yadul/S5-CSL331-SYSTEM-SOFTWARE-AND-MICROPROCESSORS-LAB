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

// Pointer to root directory. The remaining directories are accessed through recursive calls
struct directory *root = NULL;
// Stores location of directory during search
struct directory *dir_location = NULL;
// Stores location of file during search
struct file *file_location = NULL;

void display(struct directory *ptr)
{
    struct directory *temp = ptr;

    while (temp != NULL)
    {
        printf("\nDirectory: %s\n", temp -> dirname);

        if (temp -> dlstart == NULL)
            printf("\tDirectories in %s: Empty\n", temp -> dirname);
        else 
        {
            printf("\tDirectories in %s:\n", temp -> dirname);
            struct directory *dir_ptr = temp -> dlstart;
            while (dir_ptr != NULL)
            {
                printf("\t\t%s\n", dir_ptr -> dirname);
                dir_ptr = dir_ptr -> next; 
            }
        }

        int flag = 0;

        printf("\tFiles in %s: ", temp -> dirname);
        struct file *file_ptr = temp -> flstart;
        while (file_ptr != NULL)
        {
            if (strcmp(file_ptr -> filename, "") != 0)
            {
                printf("\n\t\t%s", file_ptr -> filename);
                flag = 1;
            }
            file_ptr = file_ptr -> next; 
        }
        if (flag != 1)
            printf("Empty\n");
        else 
            printf("\n");

        display(temp -> dlstart);

        temp = temp -> next;
    }
}

struct directory * search_parent(struct directory *ptr, char str[20])
{
    struct directory *temp = ptr;

    while (temp != NULL)
    {
        if (strcmp(str, temp -> dirname) == 0)
            dir_location = temp;
        else
            search_parent(temp -> dlstart, str);

        temp = temp -> next;
    }
}

void create(struct directory *root)
{
    int choice;
    char str[20];

    printf("Enter name of parent directory: ");
    scanf("%s", str);

    /*
    Initialize directory location as NULL
    Search for parent
    If parent is found, directory location becomes a non-NULL value 
    */
    dir_location = NULL;
    search_parent(root, str);

    if (dir_location == NULL)
    {
        printf("Parent directory not found.\n");
        return;
    }
    else
    {
        // Check if current directory does not have any subdirectory list
        if (dir_location -> dlstart == NULL)
        {
            struct directory *newnode = (struct directory *)malloc(sizeof(struct directory));

            printf("Enter name of the new directory: ");
            scanf("%s", str);
            strcpy(newnode -> dirname, str);

            newnode -> flstart = NULL;
            newnode -> dlstart = NULL;
            newnode -> next = NULL;

            dir_location -> dlstart = newnode;
        }
        // Subdirectory list exists, add subdirectory to end of list
        else 
        {
            struct directory *temp;
            temp = dir_location -> dlstart;

            // Check if duplicate directory exists
            while (temp != NULL)
            {
                if (strcmp(str, temp -> dirname) == 0)
                {
                    printf("Directory with similar name found. Directory creation failed.\n");
                    return;
                }
                temp = temp -> next;
            }

            struct directory *newnode = (struct directory *)malloc(sizeof(struct directory));

            printf("Enter name of the new directory: ");
            scanf("%s", str);
            strcpy(newnode -> dirname, str);

            newnode -> flstart = NULL;
            newnode -> dlstart = NULL;
            newnode -> next = NULL;

            temp = dir_location -> dlstart;
            while (temp -> next != NULL)
                temp = temp -> next;

            temp -> next = newnode;
        }
    }
}

void create_file(struct directory *root)
{
    int choice;
    char str[20];

    printf("Enter name of parent directory: ");
    scanf("%s", str);

    /*
    Initialize directory location as NULL
    Search for parent
    If parent is found, directory location becomes a non-NULL value 
    */
    dir_location = NULL;
    search_parent(root, str);

    if (dir_location == NULL)
    {
        printf("Parent directory not found.\n");
        return;
    }
    else
    {
        // Check if current directory does not have any file list
        if (dir_location -> flstart == NULL)
        {
            struct file *newnode = (struct file *)malloc(sizeof(struct file));

            printf("Enter name of the file: ");
            scanf("%s", str);
            strcpy(newnode -> filename, str);
            newnode -> next = NULL;

            dir_location -> flstart = newnode;
        }
        // File list exists, add file to end of list
        else 
        {
            struct file *temp;
            temp = dir_location -> flstart;

            // Check if duplicate file exists
            while (temp != NULL)
            {
                if (strcmp(str, temp -> filename) == 0)
                {
                    printf("File with similar name found. File creation failed.\n");
                    return;
                }
                temp = temp -> next;
            }

            struct file *newnode = (struct file *)malloc(sizeof(struct file));

            printf("Enter name of the file: ");
            scanf("%s", str);
            strcpy(newnode -> filename, str);
            newnode -> next = NULL;

            temp = dir_location -> flstart;
            while (temp -> next != NULL)
                temp = temp -> next;

            temp -> next = newnode;
        }
    }
}

void search_file(struct directory *ptr, char str[20])
{
    struct directory *temp = ptr;

    while (temp != NULL)
    {
        struct file *file_ptr = temp -> flstart;
        while (file_ptr != NULL)
        {
            if (strcmp(file_ptr -> filename, str) == 0)
            {
                printf("File found.\n");
                file_location = file_ptr;
            }
            
            file_ptr = file_ptr -> next; 
        }

        search_file(temp -> dlstart, str);

        temp = temp -> next;
    }
}

void delete_file(struct directory *ptr, char str[20])
{
    file_location = NULL;
    // File location will be a non-NULL value if search is successful
    search_file(ptr, str);

    if (file_location != NULL)
        strcpy(file_location -> filename, "");
    else
        printf("File not found.\n");
}

void main()
{
    int choice;
    char str[20];

    root = (struct directory *)malloc(sizeof(struct directory));

    printf("Enter name of root directory: ");
    scanf("%s", str);
    strcpy(root -> dirname, str);

    root -> flstart = NULL;
    root -> dlstart = NULL;
    root -> next = NULL;

    do
    {
        printf("\n\tMENU\n");
        printf("1. Create directory\n2. Create file\n3. Delete file\n4. Search file\n5. Display files\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: create(root);
                    display(root);
                    break;
            case 2: create_file(root);
                    display(root);
                    break;
            case 3: printf("Enter file name to delete: ");
                    scanf("%s", str);
                    delete_file(root, str);
                    display(root);
                    break;
            case 4: printf("Enter file name to search: ");
                    scanf("%s", str);
                    file_location = NULL;
                    search_file(root, str);
                    if (file_location == NULL)
                        printf("File not found.\n");
                    break;
            case 5: display(root);
                    break;
        }
    } while (choice >= 1 && choice <= 5);
}
