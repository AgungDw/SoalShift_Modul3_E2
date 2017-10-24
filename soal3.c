#include <stdlib>

int kepiting_status, lohan_status;

void kepiting_kelaparan()
{
	sleep (20);
	kepiting_status-=10;
	if (kepiting_status<0)
	{
		//give signal to end game
	}
}

void lohan_kelaparan()
{
	sleep(10);
	lohan_status-=15;
	if (lohan_kelaparan<0)
	{
		//give signal to end game
	}
}


int main()
{
	status_lohan=status_kepiting=100;

}