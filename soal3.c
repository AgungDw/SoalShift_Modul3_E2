#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>

int kepiting_status, lohan_status;

int status_game; //signal to determine the game. 0 if the game was end

void *kepiting_kelaparan(void *arg)
{
	while (status_game==1) //as long as the game is running the crab will continue to starve
	{
		sleep (20);
		kepiting_status-=10;
		if (kepiting_status<=0)
		{
		//give signal to end game
			status_game=0;
		}	
	}
	return 0;
}

void *lohan_kelaparan(void *arg)
{
	while (status_game==1)
	{
		sleep(10);
		lohan_status-=15;
		if (lohan_kelaparan<=0)
		{
		//give signal to end game, and end its misery
		status_game=0;
		}	
	}
	return 0;
}

void *game(void *arg)
{
	int menu;
	while (status_game==1)
	{
		printf("Menu:\n 1 untuk memberi makan lohan\n 2 untuk memberi makan kepiting\n");
		scanf("%d", &menu);
		if (menu==1)
		{
			lohan_status+=10;
			if (lohan_status>100)
			{
				status_game=0;
			}
		}
		else if (menu==2)
		{
			kepiting_status+=10;
			if (kepiting_status>100)
			{
				status_game=0;
			}
		}
	}
	printf("You lose\n");
	return 0;
}


int main(void)
{
	lohan_status=kepiting_status=100;
	status_game=1;
	int err;
	pthread_t tid[3];
	err=pthread_create(&(tid[0]),NULL,&game,NULL);//crating thread for game function
	if(err!=0)//cek error
	{
		printf("\n can't create thread : [%s]",strerror(err));
	}

	err=pthread_create(&(tid[1]),NULL,&lohan_kelaparan,NULL);//crating thread for lohan function
	if(err!=0)//cek error
	{
		printf("\n can't create thread : [%s]",strerror(err));
	}

	err=pthread_create(&(tid[2]),NULL,&kepiting_kelaparan,NULL);//crating thread for kepiting function
	if(err!=0)//cek error
	{
		printf("\n can't create thread : [%s]",strerror(err));
	}

	pthread_join(tid[0],NULL); //just join to 0 because 0 is the controler of the game;
}