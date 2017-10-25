#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

long weapon_ammount[6];
char weapon_name [6][10];
int new_socket;

void listener(void * arg)
{
    char input[100];
    char name[10];
    char temp[10];
    long ammount;
    int itterator=0;
    char* ptr;
    while (1)
    {
        valread = read( new_socket , input, 100);    
        while(input[itterator]!=' ')
        {
            itterator++;            
        }
        strncpy(input, name, itterator);
        name[itterator]='\0';

        temp=strchr(input, ' ');
        ammount=strtol(temp, ptr, 10);
        
        for (itterator=0; itterator<6; itterator++)
        {
            if (strcmp (weapon_name[itterator],name)==0)
            {
                weapon_ammount[itterator]+=ammount;
            }
        }

    }
    
}


int main ()
{
	int server_fd, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char input[10];
    //MP4A1, PM2-V1, SPR-3, SS2-V5, SPG1-V3,​ ​ dan​​ ​ MINE
    strcpy(weapon_name[0], "MP4A1");
    strcpy(weapon_name[1], "PM2-V1");
    strcpy(weapon_name[2], "SPR-3");
    strcpy(weapon_name[3], "SS2-V5");
    strcpy(weapon_name[4], "SPG1-V3");
    strcpy(weapon_name[5], "MINE");
    weapon_ammount[0]=weapon_ammount[1]=weapon_ammount[2]=
    weapon_ammount[3]=weapon_ammount[4]=weapon_ammount[5]=0;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    pthread_t tid[1];
    int err;
    err=pthread_create(&(tid[0]),NULL,&listener,NULL);//crating thread for listening
	if(err!=0)//cek error
	{
		printf("\n can't create thread : [%s]",strerror(err));
	}

    int opt;
    int itterator;
    while (1)
    {
    	printf("1 untuk lihat stok senjata\n2 untuk tambah stok senjata");	
    	scanf("%d", &opt);
        if (opt==1)
        {
            for (itterator=0; itterator<6; itterator++)
            {
                printf("%s %d\n", weapon_name[itterator], weapon_ammount[itterator]);
            }
        }
        else if (opt==2)
        {
            scanf("%s %d", input, opt);
            for (itterator=0; itterator<6; itterator++)
            {
                if (strcmp (weapon_name[itterator],input)==0)
                {
                    weapon_ammount[itterator]+=opt;
                }
            }
        }
        else 
        {
            input salah;
        }
    }
    
    return 0;
}