#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

double rtc()
{
        struct timeval time;
        gettimeofday(&time,NULL);
        return ( (double)(time.tv_sec*1000000+time.tv_usec)/1000000 );
}

int cmpfunc(const void* a, const void* b){
    return (*(int*)a-*(int*)b);
}


int divisores_1(int n){
   return 1;
}

int divisores_2(int n){
    int x = n%10;
    if(x%2 == 0) {
       return 1;
    }
     else{
        return 0;
    }
}

int divisores_3(int n){
    int result = 0;
while(n > 0){
    result += n%10;
    n = n /10;
    
}
if(result % 3 == 0)
return  1;
 else{
        return 0;
    }
}

int divisores_4(int n){
    int x = n%100;
    if(x%4 == 0) {
       return 1;
    }
     else{
        return 0;
    }

}

int divisores_5(int n){
    int x = n%10;
    if(x == 0 || x == 5) {
       return 1;
    }
     else{
        return 0;
    }

}

int divisores_6(int n){
    if(divisores_2(n) == 1 && divisores_3(n) == 1) {
       return 1;
    }
     else{
        return 0;
    }

}

int divisores_7(int n){
    if(n%7 == 0) {
       return 1;
    }
     else{
        return 0;
    }

}

int divisores_8(int n){
    if(n%8==0) {
       return 1;
    }
     else{
        return 0;
    }

}

int divisores_9(int n){
    int result = 0;
while(n > 0){
    result += n%10;
    n = n /10;
    
}
if(result % 9 == 0 && divisores_3(n) == 1){
    return  1;
}
 else{
        return 0;
    }
}

int divisores_10(int n){
    int x = n%10;
    if(x == 0) {
       return 1;
    }
    else{
        return 0;
    }
} 
    int divisores_more(int n, int i){
            if(n%i==0 )
            {
                return 1;
            }
            else
            {
                return 0;
            }    
}


void arraydivisores(int n){
    int a [100000];
    int result = 0;
    double x = sqrt(n);
    int i=1;
   // for (int i = 1; i < x; i++)
    //{

    if(divisores_1(n) == 1 && i <= x){
        a[result++] = i;
        if(x !=i)
            a[result++]=n;
        
    }
    i++;
    if(divisores_2(n) == 1 && i <= x){
            a[result++] = i;
            if(x !=i)
            a[result++]=n/i;
            
    }
    i++;

    if(divisores_3(n) == 1 && i <= x){
        a[result++] = i;
        if(x !=i)
            a[result++]=n/i;
        
    }
    i++;

    if(divisores_4(n) == 1 && i <= x ){
        a[result++] = i;
        if(x !=i)
            a[result++]=n/i;
        
    }
    i++;

    if(divisores_5(n) == 1 && i <= x){
    a[result++] = i;
    if(x !=i)
            a[result++]=n/i;
    
    }
    i++;

    if(divisores_6(n) == 1  && i <= x){
    a[result++] = i;
    if(x !=i)
            a[result++]=n/i;
    
    }
    i++;

    if(divisores_7(n) == 1 && i <= x){
    a[result++] = i;
    if(x !=i)
        a[result++]=n/i;
    
    }
    i++;

    if(divisores_8(n) == 1 && i <= x){
    a[result++] = i;
    if(x !=i)
            a[result++]=n/i;
    
    }
    i++;
        
    if(divisores_9(n) == 1 && i <= x){
    a[result++] = i;
    if(x !=i)
            a[result++]=n/i;
    
    }
    i++;

    if(divisores_10(n) == 1 && i <= x){
    a[result++] = i;
    if(x !=i)
            a[result++]=n/i;
    }
    i++;
    
    for (int j = 11; j <= x; j++)
    {
    if(divisores_more(n,j) ==1){
    a[result++] = j;
    if(x !=j)
            a[result++]=n/j;
    }
    i++;
   }  

    qsort(a,result,sizeof(int),cmpfunc);
    printf("factors: %d",result);
    for (int j = 0; j < result; j++)
    {
      printf("%d ", a[j]) ;  
    }
    
}

int main (int argc, char *argv[]){
    
        int n = atoi(argv[1]);
        double elapsed, rtc();
        elapsed=rtc();

        for (int i = 0; i < 1; i++)
        {

             arraydivisores(n);
        }
        
        
        elapsed=rtc()-elapsed;
        

        printf( "  \n Elapsed time: Loop time = %.12f  \n",	elapsed );

        exit (0);

}

