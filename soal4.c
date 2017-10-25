#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_t tid[500];
int n[500],size,selesai=0,i;

void  * hitung_fak (void* arg)
{
	int z;
	long long hasil=1;
	for(z=2;z<=n[i];z++)hasil*=(long long)z;
	printf("Hasil %d! = %lld\n",n[i],hasil);
	++selesai;
	return NULL;
}

int main ()
{
	int j=0,k=0,l=0,len,err;
	char trap[11],input[1000],temp[500][10];
	scanf("%s",trap);
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
	int x,y, key;
	for (x = 1; x <= j; x++)
   	{
       key = n[x];
       y = x-1;
       while (y >= 0 && n[y] > key)
       {
           n[y+1] = n[y];
           y = y-1;
       }
       n[y+1] = key;
   	}

   	for(i=0;i<=j;i++){
		err=pthread_create(&(tid[i]),NULL,&hitung_fak,NULL);
		if(err!=0){
			printf("Program error. Please restart the program\n");
			return -1;
		}
		while(selesai<=i);
	}
	return 0;
}