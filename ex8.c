#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int num;
    int rdmnum = (rand() % (100 - 0 + 1)) + 0;
    FILE *fptr;
    fptr = fopen("/home/bassaget/Desktop/Travail/algo struc 1/alea.nb","r+");
    if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }    
    printf("Enter num: ");
    scanf("%d",&num);
    for(int x = 0; x < num; x++){
        fprintf(fptr,"%d ",num);

    }
   
    fclose(fptr);

    return 0;
}
