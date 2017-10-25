#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <algorithm>

pthread_t tid[500];
char baris[10000],temp[500][100];
FILE *book;
int jumlah[500],selesai=0,i,j;
void *cari_nama(void *arg){
	int I=i,x,y,len=strlen(baris),len2=strlen(temp[I]);
	for(x=0;x<len;x++){
		for(y=0;y<len2;y++){
			if(baris[x+y]!=temp[I][y])break;
		}
		if(y==len2){
			++jumlah[I];
		}
	}
	++selesai;
	return NULL;
}

int main(){
	memset(jumlah,0,500);
	int k=0,l=0,len,err,n[1000];
	char trap[11],input[1000];
	book=fopen("Novel.txt","r");
	scanf("%s",&trap);
	getchar();
	scanf("%[^\n]s",&input);
	getchar();
	fscanf(book,"%[^\n]s",&baris);
	len=strlen(input);
	for(i=0;i<len;i++){
		if(input[i]==' '){
			++j;
			k=0;
			++l;
		}
		else{
			temp[j][k]=input[i];
			++k;
		}
	}
	for(i=0;i<=j;i++){
		err=pthread_create(&(tid[i]),NULL,&cari_nama,NULL);
		if(err!=0){
			printf("Program error. Please restart the program\n");
			return -1;
		}
		while(selesai<=i);
	}
	for(i=0;i<=j;i++){
		printf("%s : %d\n",temp[i],jumlah[i]);
	}
	return 0;
}
