#include <stdio.h>

void single_level()
{
    int i, no_of_files;
    char root[20];
    char files[20][20];

    printf("Enter name of the root directory: ");
    scanf("%s", root);

    printf("Enter the number of files in root: ");
    scanf("%d", &no_of_files);

    for (i = 0; i < no_of_files; i++)
    {
        printf("Enter the file name %d: ", i + 1);
        scanf("%s", files[i]);
    }

    printf("\nSingle level directory: \n");
    printf("%-30s[root]\n", root);
    for (i = 0; i < no_of_files; i++)
        printf("\t-%-21s[file]\n", files[i]);
}

void two_level()
{
    int no_of_directories, no_of_files, no_of_files_in_directory[20];
    char root[20], directories[20][20], files[20][20][20];

    printf("Enter name of the root directory: ");
    scanf("%s", root);

    printf("Enter the number of directories in root: ");
    scanf("%d", &no_of_directories);

    for (int i = 0; i < no_of_directories; i++)
    {
        printf("\nEnter the name of directory %d: ", i + 1);
        scanf("%s", directories[i]);

        printf("Enter the number of files in directory %s: ", directories[i]);
        scanf("%d", &no_of_files_in_directory[i]);
    
        for (int j = 0; j < no_of_files_in_directory[i]; j++)
        {
            printf("Enter the file name %d: ", j + 1);
            scanf("%s", files[i][j]);
        }
    }

    printf("\nTwo level directory:\n");
    printf("%-38s[root]\n", root);
    for (int i = 0; i < no_of_directories; i++)
    {
        printf("\t-%-29s[directory]\n", &directories[i]);

        for (int j = 0; j < no_of_files_in_directory[i]; j++)
            printf("\t\t-%-21s[file]\n", files[i][j]);
    }
}

void hierarchical()
{
    int no_of_directories, no_of_files, no_of_subdirectories[20], no_of_files_in_subdirectory[20];
    char root[20], directories[20][20], subdirectories[20][20][20], files[20][20][20];

    printf("Enter name of the root directory: ");
    scanf("%s", root);

    printf("Enter the number of directories in root: ");
    scanf("%d", &no_of_directories);

    for (int i = 0; i < no_of_directories; i++)
    {
        printf("\nEnter the name of directory %d: ", i + 1);
        scanf("%s", directories[i]);

        printf("Enter the number of subdirectories in directory %s: ", directories[i]);
        scanf("%d", &no_of_subdirectories[i]);

        for (int j = 0; j < no_of_subdirectories[i]; j++)
        {
            printf("Enter the names of subdirectory %d: ", j + 1);
            scanf("%s", subdirectories[i][j]);
        }

        printf("Enter the number of files in the last subdirectory %s of directory %s: ", subdirectories[i][no_of_subdirectories[i] - 1], directories[i]);
        scanf("%d", &no_of_files_in_subdirectory[i]);
    
        for (int j = 0; j < no_of_files_in_subdirectory[i]; j++)
        {
            printf("Enter the file name %d: ", j + 1);
            scanf("%s", files[i][j]);
        }
    }

    printf("\nHierarchical directory:\n");
    printf("%-38s[root]\n", root);
    for (int i = 0; i < no_of_directories; i++)
    {
        printf("\t-%-29s[directory]\n", &directories[i]);

        for (int j = 0; j < no_of_subdirectories[i]; j++)
            printf("\t\t-%-21s[subdirectory]\n", subdirectories[i][j]);

        for (int j = 0; j < no_of_files_in_subdirectory[i]; j++)
            printf("\t\t\t-%-13s[file]\n", files[i][j]);
    }
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