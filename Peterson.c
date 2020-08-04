//  Dekker-Peterson.c
//  Created by Nada AZ on 4/12/19.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int arr[50000];

int flag[2] = {0, 0};
int turn;

void *asc (void *args)
{
    int i,j,temp;
    flag[0] = 1;
    turn = 1;
    
    while (flag[1] == 1 && turn == 1)
    {
        // busy wait
    }
    
    // critical section
    for (i = 0; i < 50000; i++) //bubble sort
    {
        for (j = 0; j < (50000 - i - 1); j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    for(i=0;i<50000;i++)
    {
        printf("%d \n",arr[i]);
    }
    // critical section
    flag[0] = 0;
}

void *des (void *args)
{
    int i,j,temp;
    
    flag[1] = 1;
    turn = 0;
    
    while (flag[0] == 1 && turn == 0)
    {
        // busy wait
    }
    
    // critical section
    for (i = 0; i < 50000; i++) //bubble sort
    {
        for (j = 0; j < (50000 - i - 1); j++)
        {
            if (arr[j] < arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    for(i=0;i<50000;i++)
    {
        printf("%d \n",arr[i]);
    }
    // critical section
    
    flag[1] = 0;
}

int main()
{
    int i,j,temp,des_flag=1,asc_flag=1;
    
    for (i=0;i<50000;i++)
    {
        arr[i]=rand()% 5000 + 1;
    }
    
    pthread_t t1,t2;
    pthread_create(&t1, NULL, asc, NULL);
    pthread_create(&t2, NULL, des, NULL);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    for (i = 0; i < 50000; i++) //check sort
    {
        for (j = 0; j < (50000 - i - 1); j++)
        {
            if (arr[j]>arr[j+1])
            {
                asc_flag=0;
            }
            if (arr[j]<arr[j+1])
            {
                des_flag=0;
            }
        }
    }
    if(des_flag==0&&asc_flag==1)
        printf("array sorted asc \n");
    else if (des_flag==1&&asc_flag==0)
        printf("array sorted des \n");
    else
        printf("array not sorted \n");
    
    return 0;
}
