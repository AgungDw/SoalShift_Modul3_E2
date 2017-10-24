#include <stdlib>

int kepiting_status, lohan_status;

int status_game; //signal to determine the game. 0 if the game was end

void kepiting_kelaparan()
{
	sleep (20);
	kepiting_status-=10;
	if (kepiting_status<0)
	{
		//give signal to end game
		status_game=0;
	}
}

void lohan_kelaparan()
{
	sleep(10);
	lohan_status-=15;
	if (lohan_kelaparan<0)
	{
		//give signal to end game
		status_game=0;
	}
}

void game()
{
	int menu;
	while (status_game==1)
	{
		printf("Menu:\n 1 untuk memberi makan lohan\n 2 untuk memberi makan kepiting");
		scanf("%d", &menu);
		if (menu==1)
		{
			lohan_status+=10;
			if (lohan_status>100)
			{
				status_game=0;
			}
		}
		if else (menu==2)
		{
			kepiting_status+=10;
			if (kepiting_status>100)
			{
				status_game=0;
			}
		}
	}
}


int main()
{
	status_lohan=status_kepiting=100;
	status_game=1;

}