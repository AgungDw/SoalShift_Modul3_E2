#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main ()
{
    char weapon_name[6][10];
    key_t key = 1234;
    int *weapon_ammount[6];
    int itterator;
    int input_amm;
    int opt;
    for (itterator=0; itterator<6;itterator++)
    {
        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        weapon_ammount[itterator] = shmat(shmid, NULL, 0);
        key+=1;
    }
    
    char input[10];
    //MP4A1, PM2-V1, SPR-3, SS2-V5, SPG1-V3,​ ​ dan​​ ​ MINE
    strcpy(weapon_name[0], "MP4A1");
    strcpy(weapon_name[1], "PM2-V1");
    strcpy(weapon_name[2], "SPR-3");
    strcpy(weapon_name[3], "SS2-V5");
    strcpy(weapon_name[4], "SPG1-V3");
    strcpy(weapon_name[5], "MINE");
    *weapon_ammount[0]=0;
    *weapon_ammount[1]=0;
    *weapon_ammount[2]=0;
    *weapon_ammount[3]=0;
    *weapon_ammount[4]=0;
    *weapon_ammount[5]=0;
    int is_weapon_true=1;
    while (1)
    {
    	printf("1 untuk lihat stok senjata\n2 untuk beli senjata\n");	
    	scanf("%d", &opt);
        if (opt==1)
        {
            for (itterator=0; itterator<6; itterator++)
            {
                if (&weapon_ammount[itterator]>0) printf("%s %d\n", weapon_name[itterator], *weapon_ammount[itterator]);
            }
        }
        else if (opt==2)
        {
        	is_weapon_true=0;
            scanf("%s %d", input,&input_amm);
            for (itterator=0; itterator<6; itterator++)
            {
                if (strcmp (weapon_name[itterator],input)==0)
                {
                    *weapon_ammount[itterator]-=input_amm;
                    is_weapon_true=1;
                }
            }
            if (is_weapon_true==0) printf("Salah nama senjata?\n");
        }
        else 
        {
            printf("input salah");
        }
    }
    
    return 0;
}