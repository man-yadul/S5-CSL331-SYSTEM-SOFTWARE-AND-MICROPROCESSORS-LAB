#include <stdio.h>
#include <string.h>

int no_of_files_single_level = 0;
char single_level_root[20];
char single_level_files[40][20];

int no_of_directories_two_level = 0;
int no_of_files_in_directory[20] = {0};
char two_level_root[20];
char two_level_directories[20][20];
char two_level_files[40][40][20];

int level_one_items = 0;
int level_two_items[20] = {0};
char hierarchical_root[20]; 
char level_one[100][20];
char level_two[100][50][20];
char level_three[100][50][20];

void display_single_level()
{
    printf("\nSingle level directory: \n");
    printf("%-30s[root]\n", single_level_root);
    for (int i = 0; i < no_of_files_single_level; i++)
    {   
        if (strcmp(single_level_files[i], "") != 0)
            printf("\t-%-21s[file]\n", single_level_files[i]);
    }
}

void create_file_single_level()
{
    printf("Enter the file name: ");
    scanf("%s", single_level_files[no_of_files_single_level]);
    
    no_of_files_single_level++;

    display_single_level();
}

void delete_file_single_level()
{
    int flag = 0;
    char str[20];

    printf("Enter name of the file (with extension) to be deleted: ");
    scanf("%s", str);

    for (int i = 0; i < no_of_files_single_level; i++)
    {
        if (strcmp(single_level_files[i], str) == 0)
        {
            flag = 1;
            strcpy(single_level_files[i], "");
            no_of_files_single_level--;
        }
    }
    
    if (flag != 1)
        printf("File not found.\n");
    else
    {
        printf("File deleted.\n");    
        display_single_level();    
    }
}

void search_file_single_level()
{
    int flag = 0;
    char str[20];

    printf("Enter name of the file (with extension) to be searched: ");
    scanf("%s", str);

    for (int i = 0; i < no_of_files_single_level; i++)
    {
        if (strcmp(single_level_files[i], str) == 0)
            flag = 1;
    }

    if (flag != 1)
        printf("File not found.\n");
    else
    {
        printf("File found.\n");
        display_single_level();    
    }
}

void single_level()
{
    int ch;

    printf("Enter name of the root directory: ");
    scanf("%s", single_level_root);

    do
    {
        printf("\n\t\tMENU\n");
        printf("1. Create file\t\t2. Delete file\n3. Search file\t\t4. Display files\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1: create_file_single_level();
                    break;
            case 2: delete_file_single_level();
                    break;
            case 3: search_file_single_level();
                    break;
            case 4: display_single_level();
                    break;
            default:
                    break;
        }
    } while (ch >= 1 && ch <= 4);
}

void display_two_level()
{
    printf("\nTwo level directory:\n");
    printf("%-38s[root]\n", two_level_root);
    for (int i = 0; i < no_of_directories_two_level; i++)
    {
        printf("\t-%-29s[directory]\n", two_level_directories[i]);

        for (int j = 0; j < no_of_files_in_directory[i]; j++)
        {
            if (strcmp(two_level_files[i][j], "") != 0)
                printf("\t\t-%-21s[file]\n", two_level_files[i][j]);
        }
    }
}

void create_directory_two_level()
{
    printf("Enter the directory name: ");
    scanf("%s", two_level_directories[no_of_directories_two_level]);
    
    no_of_directories_two_level++;

    display_two_level();
}

void create_file_two_level()
{
    int index, flag = 0;
    char str[20], name[20];

    printf("Enter name of the parent directory: ");
    scanf("%s", str);

    for (int i = 0; i < no_of_directories_two_level; i++)
    {
        if (strcmp(two_level_directories[i], str) == 0)
        {
            flag = 1;
            index = i;
        }
    }
    
    if (flag != 1)
        printf("Parent directory does not exist.\n");
    else
    {
        printf("Enter the file name: ");
        scanf("%s", name);
    
        strcpy(two_level_files[index][no_of_files_in_directory[index]], name);

        no_of_files_in_directory[index]++;
        
        display_two_level();    
    }
}

void delete_file_two_level()
{
    int flag = 0;
    char str[20];

    printf("Enter name of the file (with extension) to be deleted: ");
    scanf("%s", str);

    for (int i = 0; i < no_of_directories_two_level; i++)
    {
        for (int j = 0; j < no_of_files_in_directory[i]; j++)
        {
            if (strcmp(two_level_files[i][j], str) == 0)
            {
                flag = 1;
                strcpy(two_level_files[i][j], "");
                no_of_files_in_directory[i]--;
            }
        }
    }
    
    if (flag != 1)
        printf("File not found.\n");
    else
    {
        printf("File deleted.\n");
        display_two_level();    
    }    
}

void search_file_two_level()
{
    int flag = 0;
    char str[20];

    printf("Enter name of the file (with extension) to be searched: ");
    scanf("%s", str);

    for (int i = 0; i < no_of_directories_two_level; i++)
    {
        for (int j = 0; j < no_of_files_in_directory[i]; j++)
        {
            if (strcmp(two_level_files[i][j], str) == 0)
                flag = 1;
        }
    }

    if (flag != 1)
        printf("File not found.\n");
    else
    {
        printf("File found.\n");
        display_two_level();    
    }    
}

void two_level()
{
    int ch;

    printf("Enter name of the root directory: ");
    scanf("%s", two_level_root);

    do
    {
        printf("\n\t\t\tMENU\n");
        printf("1. Create directory\t2. Create file\t\t3. Delete file\n4. Search file\t\t5. Display files\t6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1: create_directory_two_level();
                    break;
            case 2: create_file_two_level();
                    break;
            case 3: delete_file_two_level();
                    break;
            case 4: search_file_two_level();
                    break;
            case 5: display_two_level();
                    break;
            default:
                    break;
        }
    } while (ch >= 1 && ch <= 5);
}

void display_hierarchical()
{
    int i, j;

    printf("\nHierarchical directory:\n");
    printf("%-63s[root]\n", hierarchical_root);
    for (i = 0; i < level_one_items; i++)
    {
        printf("\t-%-54s[directory]\n", level_one[i]);

        for (j = 0; j < level_two_items[i]; j++)
        {
            if (strchr(level_two[i][j], '.') != NULL)
                printf("\t\t\t-%-38s[file]\n", level_two[i][j]);
            else 
                printf("\t\t\t-%-38s[subdirectory]\n", level_two[i][j]);
            
            if (strcmp(level_three[i][j], "") != 0)
                printf("\t\t\t\t\t\t-%-14s[file]\n", level_three[i][j]);
        }
    }
}

void create_directory_hierarchical()
{
    printf("Enter the directory name: ");
    scanf("%s", level_one[level_one_items]);
    
    level_one_items++;

    display_hierarchical();
}

void create_subdirectory_hierarchical()
{
    int index, flag = 0; 
    char str[20];

    printf("Enter name of the parent directory: ");
    scanf("%s", str);

    for (int i = 0; i < level_one_items; i++)
    {
        if (strcmp(level_one[i], str) == 0)
        {
            flag = 1;
            index = i;
        }
    }
    
    if (flag != 1)
        printf("Parent directory does not exist.\n");
    else
    {
        printf("Enter the subdirectory name: ");
        scanf("%s", str);
    
        strcpy(level_two[index][level_two_items[index]], str);

        level_two_items[index]++;
        
        display_hierarchical();    
    }
}

void create_file_hierarchical()
{
    int index, i_index, j_index, flag1 = 0, flag2 = 0;
    char str[20], name[20];

    printf("Enter name of the parent directory (level 1 or level 2): ");
    scanf("%s", str);

    // Search in main directories
    for (int i = 0; i < level_one_items; i++)
    {
        if (strcmp(level_one[i], str) == 0)
        {
            flag1 = 1;
            index = i;
        }
    }

    // If not found in main directory, search in sub directories
    if (flag1 != 1)
    {
        for (int i = 0; i < level_one_items; i++)
        {
            for (int j = 0; j < level_two_items[i]; j++)
            {
                if (strcmp(level_two[i][j], str) == 0)
                {
                    flag2 = 1;
                    i_index = i;
                    j_index = j;
                }
            }
        }
    }
    
    if (flag1 == 0 && flag2 == 0)
        printf("Parent directory does not exist.\n");
    else if (flag1 == 1 && flag2 == 0)
    {
        printf("Enter the file name: ");
        scanf("%s", name);
    
        strcpy(level_two[index][level_two_items[index]], name);

        level_two_items[index]++;
        
        display_hierarchical();    
    }
    else 
    {
        printf("Enter the file name: ");
        scanf("%s", name);
    
        strcpy(level_three[i_index][j_index], name);

        display_hierarchical();    
    }
}

void delete_file_hierarchical()
{
    int flag = 0;
    char str[20];

    printf("Enter name of the file (with extension) to be deleted: ");
    scanf("%s", str);

    for (int i = 0; i < level_one_items; i++)
    {
        for (int j = 0; j < level_two_items[i]; j++)
        {
            if (strcmp(level_two[i][j], str) == 0)
            {
                flag = 1;
                strcpy(level_two[i][j], "");
                level_two_items[i]--;
            }

            if (strcmp(level_three[i][j], str) == 0)
            {
                flag = 1;
                strcpy(level_three[i][j], "");
            }
        }
    }

    if (flag != 1)
        printf("File not found.\n");
    else
    {
        printf("File deleted.\n");
        display_hierarchical();    
    }    
}

void search_file_hierarchical()
{
    int flag = 0;
    char str[20];

    printf("Enter name of the file (with extension) to be searched: ");
    scanf("%s", str);

    for (int i = 0; i < level_one_items; i++)
    {
        for (int j = 0; j < level_two_items[i]; j++)
        {
            if (strcmp(level_two[i][j], str) == 0)
            {
                flag = 1;
                strcpy(level_two[i][j], "");
                level_two_items[i]--;
            }

            if (strcmp(level_three[i][j], str) == 0)
            {
                flag = 1;
                strcpy(level_three[i][j], "");
            }
        }
    }

    if (flag != 1)
        printf("File not found.\n");
    else
    {
        printf("File found.\n");
        display_hierarchical();    
    }    
}

/*
Root
    -Level 1 (directories only)
        -Level 2 (subdirectories & files of Level 1 directories)
            -Level 3 (only files of Level 2 subdirectories)
*/
void hierarchical()
{
    int ch;

    printf("Enter name of the root directory: ");
    scanf("%s", hierarchical_root);

    do
    {
        printf("\n\t\t\t\tMENU\n");
        printf("1. Create directory\t2. Create subdirectory\t\t3. Create file\n4. Delete file\t\t5. Search file\t\t\t6. Display files\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1: create_directory_hierarchical();
                    break;
            case 2: create_subdirectory_hierarchical();
                    break;
            case 3: create_file_hierarchical();
                    break;
            case 4: delete_file_hierarchical();
                    break;
            case 5: search_file_hierarchical();
                    break;
            case 6: display_hierarchical();
                    break;
            default:
                    break;
        }
    } while (ch >= 1 && ch <= 6);
}

void main()
{
    int ch;

    do
    {
        printf("\n\n\t\tMENU\n");
        printf("1. Single level\t\t2. Two level\n3. Hierarchical\t\t4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1: single_level();
                    break;
            case 2: two_level();
                    break;
            case 3: hierarchical();
                    break;
        }
    } while (ch >= 1 && ch <= 3);
}
