#include <stdio.h>
#include <stdlib.h>


void bubble_selection(int *v, int size){
    int num, tmp;
    for(int i = 0; i < size; i++){
        num = v[i];
        for(int j = i; j < size; j++){
            if(num > v[j]){
                tmp = v[j];
                v[j] = v[i];
                v[i] = tmp;
                i = -1;
                break;
            }           
            
        }
    }
}

int main(){
    int v[] = {14,3,1,16,7,9,19,200};
    int size = sizeof(v)/sizeof(v[0]);

    bubble_selection(v, size);

    for (int i = 0; i < size; i++) printf("%d ", v[i]);
}