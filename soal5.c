#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int main ()
{
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
}