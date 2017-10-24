#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>

int main (void)
{
	
	char input[256];
	gets(input);
	if (strncmp(input, "./cari", 5));
	int itterator;
	itterator= strlen(input);
	int leng=itterator;
	int temp=leng;
	char passer [50];
	int i=0;
	pthread_t tid[10];
	for (itterator-=1; itterator>5;itterator--)
	{
		if(input[itterator] == ' '&&itterator!=leng)
		{
			int x=itterator+1;
			int y=0;
			for (x; x<temp; x++)
			{
				passer[y]=input[x];
				y++;
			}
			passer[y]='\0';
			temp=itterator;
			//printf("%s\n", passer);
			pthread_create(&tid[i], NULL, finder, (void *)x);
			i++;
		}
	}
}
