#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct file
{
	char name[20];
	int no_of_blocks;
	int blocks[20];
}files[20];

// Stores number of total blocks
int total_blocks;
// Stores number of remaining blocks as they are allocated to files
int remaining_blocks;
// Stores the file count
int file_count = 0;
// Stores the block numbers which is used for random selection (contains total blocks, total blocks - 1, ..., 2, 1, 0)
int avail_blcks[500];

void create()
{
    int rand_arr_index, item;

    printf("Enter file name: ");
    scanf("%s", files[file_count].name);

    printf("Enter no. of blocks: ");
    scanf("%d", &files[file_count].no_of_blocks);

    // If nob > remaining blocks available
    if (files[file_count].no_of_blocks > remaining_blocks)
    {
        printf("Not enough blocks available.\n");
        return;
    }
    else
    {
        for (int i = 0; i < files[file_count].no_of_blocks; i++)
        {
            // Generate a random index and use this index to select a block number from avail_blcks[]
            rand_arr_index = rand() % remaining_blocks;
            item = avail_blcks[rand_arr_index];
            // The chosen block number is set to -1 in avail_blcks[] so that it is not chosen again
            avail_blcks[rand_arr_index] = -1;
 
            // Sorting avail_blcks[] (descending) so that -1 is not chosen in next file creation
            for (int a = 0; a < remaining_blocks; a++) 
            {
                for (int b = a + 1; b < remaining_blocks; b++) 
                {
                    if (avail_blcks[a] < avail_blcks[b]) 
                    {
                        int temp = avail_blcks[a];
                        avail_blcks[a] = avail_blcks[b];
                        avail_blcks[b] = temp;
                    }
                }
            }

            files[file_count].blocks[i] = item;
            remaining_blocks--;
        }
    }
}

void display()
{
    printf("%-20s%-20s%-20s\n", "Name of file", "No. of blocks", "Blocks allocated");

    for (int i = 0; i < file_count; i++)
    {
        printf("%-20s%-20d", files[i].name, files[i].no_of_blocks);

        if (files[i].blocks[0] == -1)
            printf("%-20s\n", "Not allocated");
        else
        {
            for (int j = 0; j < files[i].no_of_blocks; j++)
                printf("%d ", files[i].blocks[j]);
            printf("\n");              
        }
    }
}

void main()
{
    int choice;

    srand(time(NULL));

    printf("Enter total no. of blocks: ");
    scanf("%d", &total_blocks);

    remaining_blocks = total_blocks;

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            files[i].blocks[j] = -1;

    // Generating block numbers which is used for random selection (contains total blocks, total blocks - 1, ..., 2, 1, 0)
    for (int i = total_blocks - 1; i >= 0; i--)
        avail_blcks[i] = i;

	do
	{
        printf("\tMENU\n");
        printf("1. Create file\n2. Display files\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: create();
                    file_count++;
                    display();
                    break;
            case 2: display();
                    break;
        }
	} while (choice >= 1 && choice <= 2);
}