#include <stdio.h>
#include "sort.h"

void print(int data[], int length){
    printf("after sort: \n");
    for(int i=0;i<length;++i){
        if(i>0){
            printf(" ");
        }
        printf("%d", data[i]);
    }
    printf("\n");
}


int main(int argc, char** argv){
    int data_size;
    printf("input the data size: ");
    scanf("%d", &data_size);
    int data[data_size];
    for(int i=0;i<data_size;++i){
        printf("The %dth number is: ",i+1);
        scanf("%d", &data[i]);
    }
    int sort_mode;
    printf("input the sort algorithm: ");
    scanf("%d", &sort_mode);
    if(sort_mode==1){
        insert_sort<int>(data, data_size);
    }else if(sort_mode==2){
        shell_sort<int>(data, data_size);
    }else if(sort_mode==3){
        select_sort<int>(data, data_size);
    }else if(sort_mode==4){
        heap_sort<int>(data, data_size);
    }else if(sort_mode==5){
        bubble_sort<int>(data, data_size);
    }

    print(data, data_size);
    return 0;
}