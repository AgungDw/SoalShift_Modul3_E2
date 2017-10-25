#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <algorithm>
using namespace std;

pthread_t tid[500];
int n[500],size,mulai=0,i;
long long hasil[500];

void *hitung_fak(void *arg){
  int a =i;
  ++mulai;
  int z;
  long long hasil_temp=1;
  for(z=2;z<=n[a];z++)hasil_temp*=(long long)z;
  //printf("Hasil %d! = %lld\n",a,hasil);
  hasil[a]=hasil_temp;
  return NULL;
}
int main(){
  memset(hasil,-1,500);

  int j=0,k=0,l=0,len,err;
  char trap[11],input[1000],temp[500][10];
  scanf("%s",&trap);
  getchar();
  gets(input);
  len=strlen(input);
  for(i=0;i<len;i++){
    if(input[i]==' '){
      n[l]=atoi(temp[j]);
      ++j;
      k=0;
      ++l;
    }
    else{
      temp[j][k]=input[i];
      ++k;
    }
  }
  n[l]=atoi(temp[j]);
  sort(n,n+j+1);
  
  for(i=0;i<=j;i++){
    err=pthread_create(&(tid[i]),NULL,&hitung_fak,NULL);
    if(err!=0){
      printf("Program error. Please restart the program\n");
      return -1;
    }
    while(mulai<=i);
  }
  int x=0;
  while (hasil[x]!=-1)
  {
    printf("Hasil %d! = %lld\n",n[x],hasil[x]);
    x+=1;
  }
  return 0;
}
