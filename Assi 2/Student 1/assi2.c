//190001003
//Anikeit Sethi

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/ipc.h>

#include <sys/shm.h>

#include<unistd.h>

#include<stdlib.h>

#include<string.h>

#include<stdio.h>



void merge(int arr[], int low, int high){

    int temp[10],i,m,k,l,mid;

    l=low;

    i=low;

    mid=(low+high)/2;

    m=mid+1;

    while((high>=m)&&(l<=mid)){

        if(arr[m]>=arr[l]){

            temp[i]=arr[l];

            l++;

        }

        else{

            temp[i]=arr[m];

            m++;

        }

        i++;

    }

    if(l>mid){

        for(k=m;k<=high;k++){

            temp[i]=arr[k];

            i++;

        }

    }

    else{

        for(k=l;k<=mid;k++){

            temp[i]=arr[k];

            i++;

        }

    }



    for(k=low;k<=high;k++){

        arr[k]=temp[k];

    }

}



void quicksort(int x[],int first,int last){

    int pivot,j,temp,i;

    if(first<last){

        pivot=first;

        i=first;

        j=last;

        while(i<j){

            while(x[i]<=x[pivot]&&i<last) i++;

            while(x[j]>x[pivot]) j--;

            if(i<j){

                temp=x[i];

                x[i]=x[j];

                x[j]=temp;

            }

        }

        temp=x[pivot];

        x[pivot]=x[j];

        x[j]=temp;

        quicksort(x,first,j-1);

        quicksort(x,j+1,last);

    }

}



int main(){

    key_t key = 5656;

    int shmid = shmget(key, 40, 0666|IPC_CREAT);

    int* arr = (int*)shmat(shmid, NULL, 0);

    

    printf("Enter 10 elements in array: ");

    for(int i=0; i<10; i++) scanf("%d", &arr[i]);

    int child1; 

    if(child1=fork())

    {

        wait(NULL);

        int child2;

        if(child2=fork())

        {

            wait(NULL);

            merge(arr, 0, 9);

            printf("Sorted Array: ");

            for(int i=0; i<10; i++) printf("%d ",arr[i]);

            printf("\n");

        }

        else

        {

            quicksort(arr, 5, 9);

            printf("B: \n"); //sorted elements from second child

            for(int i=5; i<10; i++) printf("%d ", arr[i]);

            printf("\n");

        }

    }

    else

    {

        quicksort(arr, 0, 4);

        printf("A: \n");//sorted elements from First child

        for(int i=0; i<5; i++) printf("%d ", arr[i]);

        printf("\n");

    }

    shmdt(arr);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;

}



