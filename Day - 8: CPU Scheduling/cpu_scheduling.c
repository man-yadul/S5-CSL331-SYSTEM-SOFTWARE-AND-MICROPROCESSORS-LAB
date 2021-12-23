#include <stdio.h>
 
struct process
{
    int id;
    int at;
    int ct;
    int bt;
    int tt;
    int wt;
    int rt;  
    int priority;
    int poq;  
};
 
int i, j, nop, tq; 
float av_tt, av_wt;
struct process processes[10], temp;
 
void entry()
{
    printf("Enter no. of processes: ");
    scanf("%d", &nop);
 
    for(i = 0; i < nop; i++)
    {
        processes[i].id = i + 1;
 
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &processes[i].at);
 
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &processes[i].bt);
 
        printf("Enter priority of process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }
}
 
void display()
{
    printf("%16s %16s %16s %16s %16s\n", "Process ID", "Arrival time", "Burst time", "Turnaround time", "Waiting time");
 
    for(i = 0; i < nop; i++)
        printf("%16d %16d %16d %16d %16d\n", processes[i].id, processes[i].at, processes[i].bt, processes[i].tt, processes[i].wt);
    
    printf("Average Turnaround time: %.2f", av_tt);
    printf("\nAverage Waiting time: %.2f\n", av_wt);
}
 
void reset()
{
    av_tt = av_wt = 0;
    for(i = 0; i < nop; i++)
    {
        processes[i].ct = 0;
        processes[i].tt = 0;
        processes[i].wt = 0;
        processes[i].rt = processes[i].bt;  
        processes[i].poq = 0; 
    }
}
 
void swap(int i, int j)
{
    temp = processes[i];
    processes[i] = processes[j];
    processes[j] = temp;    
}
 
void sort_by_at()
{
    for(i = 0; i < nop; i++)    
    {
        for(j = i + 1; j < nop; j++)
        {
            if(processes[i].at > processes[j].at)
                swap(i, j);
 
            if(processes[i].at == processes[j].at)
            {
                if(processes[i].id > processes[j].id)
                    swap(i, j);
            }
        }
    }
}
 
void sort_by_pid()
{
    for(i = 0; i < nop; i++)    
    {
        for(j = i + 1; j < nop; j++)
        {
            if(processes[i].id > processes[j].id)
                swap(i, j);
        }
    }
}
 
void sort_by_bt()
{
    for(i = 0; i < nop; i++)    
    {
        for(j = i + 1; j < nop; j++)
        {
            if(processes[i].bt > processes[j].bt)
                swap(i, j);
 
            if(processes[i].bt == processes[j].bt)
            {
                if(processes[i].id > processes[j].id)
                    swap(i, j);
            }
        }
    }
}
 
void sort_by_priority()
{
    for(i = 0; i < nop; i++)    
    {
        for(j = i + 1; j < nop; j++)
        {
            if(processes[i].priority > processes[j].priority)
                swap(i, j);
 
            if(processes[i].priority == processes[j].priority)
            {
                if(processes[i].id > processes[j].id)
                    swap(i, j);
            }
        }
    }
}
 
void fcfs()
{
    av_tt = av_wt = 0.0; 
 
    sort_by_at();    
 
    processes[0].ct = processes[0].at + processes[0].bt; 
    processes[0].tt = processes[0].ct - processes[0].at;
    processes[0].wt = processes[0].tt - processes[0].bt;
 
    av_tt += processes[0].tt;
    av_wt += processes[0].wt;
 
    for(i = 1; i < nop; i++)    
    {
        if(processes[i].at <= processes[i - 1].ct)     
            processes[i].ct = processes[i - 1].ct + processes[i].bt;
        else 
            processes[i].ct = processes[i].at + processes[i].bt;  
 
        processes[i].tt = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tt - processes[i].bt;
 
        av_tt += processes[i].tt;
        av_wt += processes[i].wt;
    }
 
    av_tt /= nop;
    av_wt /= nop;
 
    sort_by_pid();
 
    display();
}
 
void sjf()
{
    int previous_ct, smallest_bt, loc_of_shortest;
    int found_with_early_AT, flag = 0;
    av_tt = av_wt = 0.0; 
 
    for(i = 0; i < nop; i++)   
    {
        if(processes[i].at > 0)
            flag = 1;
    }
 
    if(flag == 1)  
        sort_by_at();
    else 
        sort_by_bt();
 
    processes[0].ct = processes[0].at + processes[0].bt; 
    processes[0].tt = processes[0].ct - processes[0].at;
    processes[0].wt = processes[0].tt - processes[0].bt;
 
    av_tt += processes[0].tt;
    av_wt += processes[0].wt;
 
    for(i = 1; i < nop; i++)    
    {
        previous_ct = processes[i - 1].ct;
        smallest_bt = 100;
        found_with_early_AT = 0; 
 
        for(j = i; j < nop; j++)
        {
            if(processes[j].at <= previous_ct && processes[j].bt < smallest_bt)  
            {
                found_with_early_AT = 1;
                loc_of_shortest = j;
                smallest_bt = processes[j].bt;
            }
 
            if(found_with_early_AT == 0)   
            {
                if(processes[j].at >= previous_ct && processes[j].bt < smallest_bt)
                {
                    loc_of_shortest = j;
                    smallest_bt = processes[j].bt;
                }
            }
        }
       
        if(found_with_early_AT == 1)   
            processes[loc_of_shortest].ct = previous_ct + processes[loc_of_shortest].bt;
        else
            processes[loc_of_shortest].ct = processes[loc_of_shortest].at + processes[loc_of_shortest].bt;
 
        processes[loc_of_shortest].tt = processes[loc_of_shortest].ct - processes[loc_of_shortest].at;
        processes[loc_of_shortest].wt = processes[loc_of_shortest].tt - processes[loc_of_shortest].bt;
 
        swap(loc_of_shortest, i);
 
        av_tt += processes[i].tt;
        av_wt += processes[i].wt;
    }
 
    av_tt /= nop;
    av_wt /= nop;
 
    sort_by_pid();
 
    display();
}
 
int finished_execution()
{
    for(i = 0; i < nop; i++)
    {
        if(processes[i].rt != 0)
            return 0;
    }
 
    return 1;
}
 
void round_robin()
{
    int smallest_position, count = 0, first_in_queue, clock = 0, position = 1;  
    av_tt = av_wt = 0.0; 
 
    printf("\nEnter time quantum: "); 
    scanf("%d", &tq);
 
    for(i = 0; i < nop; i++)    
        processes[i].rt = processes[i].bt;
            
    sort_by_at();
 
    while(finished_execution() == 0)
    {
        for(i = 0; i < nop; i++)
        {
            if(processes[i].at == clock)
                processes[i].poq = position++;
        }
 
        if(count == tq)
        {
            count = 0;
            processes[first_in_queue].poq = position++;
        }
 
        for(i = 0, smallest_position = 100; i < nop; i++)
        {
            if(processes[i].poq < smallest_position && processes[i].poq != 0 && processes[i].rt != 0)
            {
                first_in_queue = i;
                smallest_position = processes[i].poq;
            }
        }
 
        clock++;
        processes[first_in_queue].rt--;
        count++;
 
        if(processes[first_in_queue].rt == 0)
        {
            count = 0;
 
            processes[first_in_queue].poq = 0;
            processes[first_in_queue].ct = clock;
            processes[first_in_queue].tt = processes[first_in_queue].ct - processes[first_in_queue].at;
            processes[first_in_queue].wt = processes[first_in_queue].tt - processes[first_in_queue].bt;
 
            av_tt += processes[first_in_queue].tt;
            av_wt += processes[first_in_queue].wt;
        }
    }
 
    av_tt /= nop;
    av_wt /= nop;
 
    sort_by_pid();
 
    display();
}
 
void priority()
{
    int previous_ct, highest_priority, loc_of_highest;
    int found_with_early_AT, flag = 0;
    av_tt = av_wt = 0.0; 
 
    for(i = 0; i < nop; i++)    
    {
        if(processes[i].at > 0)
            flag = 1;
    }
 
    if(flag == 1)   
        sort_by_at();
    else 
        sort_by_priority();
 
    processes[0].ct = processes[0].at + processes[0].bt; 
    processes[0].tt = processes[0].ct - processes[0].at;
    processes[0].wt = processes[0].tt - processes[0].bt;
 
    av_tt += processes[0].tt;
    av_wt += processes[0].wt;
 
    for(i = 1; i < nop; i++)   
    {
        previous_ct = processes[i - 1].ct;
        highest_priority = 20;
        found_with_early_AT = 0; 
 
        for(j = i; j < nop; j++)    
        {
            if(processes[j].at <= previous_ct && processes[j].priority < highest_priority)   
            {
                found_with_early_AT = 1;
                loc_of_highest = j;
                highest_priority = processes[j].priority;
            }
 
            if(found_with_early_AT == 0)    
            {
                if(processes[j].at >= previous_ct && processes[j].priority < highest_priority)
                {
                    loc_of_highest = j;
                    highest_priority = processes[j].priority;
                }
            }
        }
       
        if(found_with_early_AT == 1)    
            processes[loc_of_highest].ct = previous_ct + processes[loc_of_highest].bt;
        else
            processes[loc_of_highest].ct = processes[loc_of_highest].at + processes[loc_of_highest].bt;
 
        processes[loc_of_highest].tt = processes[loc_of_highest].ct - processes[loc_of_highest].at;
        processes[loc_of_highest].wt = processes[loc_of_highest].tt - processes[loc_of_highest].bt;
 
        swap(loc_of_highest, i);
 
        av_tt += processes[i].tt;
        av_wt += processes[i].wt;
    }
 
    av_tt /= nop;
    av_wt /= nop;
 
    sort_by_pid();
 
    display();
}
 
void main()
{
    int ch;
 
    entry();
 
    do 
    {
        printf("\n\t\tMENU");
        printf("\n1. FCFS\t\t2. SJF\t\t3. Priority\n4. Round Robin\t5. Entry\t6. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);
 
        switch(ch)
        {
            case 1: fcfs();
                    reset();
                    break;
 
            case 2: sjf();
                    reset();
                    break;
 
            case 3: priority();
                    reset();
                    break;
 
            case 4: round_robin();
                    reset();
                    break;

            case 5: reset();
                    entry();
                    break;
        }
    } while(ch >= 1 && ch <= 5);
}
