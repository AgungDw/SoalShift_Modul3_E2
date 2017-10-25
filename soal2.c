#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int index_tebakan[4],pasang_terakhir,skor1=0,skor2=0;
bool turn=0,lubang1[16],lubang2[16],hitung=0;
pthread_t tid;

void *hitung_nilai_tebak(void *arg){
	int i;
    if(!turn)
        for(i=0;i<4;i++){
            if(lubang1[index_tebakan[i]]==0)++skor1;
            else ++skor2;
        }
    else
        for(i=0;i<4;i++){
            if(lubang2[index_tebakan[i]])++skor2;
            else ++skor1;
        }
    hitung=1;
    return NULL;
}
int main()
{
	memset(lubang1,0,16);
	memset(lubang2,0,16);
    char player1[100],player2[100];
    int ranjau1=0,ranjau2=0,input_ranjau,err,index_ranjau,i;
    printf("Input nama player 1: ");
    scanf("%s",&player1);
    printf("Input nama player 2: ");
    scanf("%s",player2);
    printf("Game Dimulai!\n");
    while(1){
        hitung=0;
        if(!turn){
            ULANGI1:
            printf("%s pasang ranjau\n",player1);
            printf("Jumlah ranjau yang ingin dipasang: ");
            scanf("%d",&input_ranjau);
            if((16<(input_ranjau+ranjau1))||(input_ranjau>4)){
                printf("Ranjau terlalu banyak");
                goto ULANGI1;
            }
            else {
                pasang_terakhir=input_ranjau;
                ranjau1+=input_ranjau;
                for(i=1;i<=input_ranjau;i++){
                	printf("Ranjau ke %d diisi pada lubang ke (nomer lubang dimulai dari 0): ",ranjau1-input_ranjau+i);
                	scanf("%d",&index_ranjau);
                    if(index_ranjau>15||index_ranjau<0){
                        printf("Nomer lubang hanya 0 hingga 15\n");
                        --i;
                    }
                    else if(lubang1[index_ranjau]!=0){
                        printf("Lubang tersebut telah diisi\n");
                        --i;
                    }
                    else lubang1[index_ranjau]=1;
                }
                printf("%s tebak ranjau\n",player2);
                for(i=1;i<=4;i++){
                	printf("Tebakan ke %d: ",i);
                	scanf("%d",&index_tebakan[i-1]);
                    if(index_tebakan[i-1]>15||index_tebakan[i-1]<0){
                        printf("Nomer lubang hanya 0 hingga 15\n");
                        --i;
                    }
                }
                err=pthread_create(&(tid),NULL,&hitung_nilai_tebak,NULL);
                if(err!=0){
                    printf("Game Error. Please restart the game\n");
                    return -1;
                }
                while(!hitung);
                turn=1;
            }
        }
        else{
            ULANGI2:
            printf("%s pasang ranjau\n",player2);
            printf("Jumlah ranjau yang ingin dipasang: ");
            scanf("%d",&input_ranjau);
            if((16<(input_ranjau+ranjau1))||(input_ranjau>4)){
                printf("Ranjau terlalu banyak");
                goto ULANGI2;
            }
            else {
                pasang_terakhir=input_ranjau;
                ranjau2+=input_ranjau;
                for(i=1;i<=input_ranjau;i++){
                	printf("Ranjau ke %d diisi pada lubang ke (nomer lubang dimulai dari 0): ",ranjau2-input_ranjau+i);
                	scanf("%d",&index_ranjau);
                    if(index_ranjau>15||index_ranjau<0){
                        printf("Nomer lubang hanya 0 hingga 15\n");
                        --i;
                    }
                    else if(lubang2[index_ranjau]!=0){
                        printf("Lubang tersebut telah diisi\n");
                        --i;
                    }
                    else lubang2[index_ranjau]=1;
                }
            	printf("%s tebak ranjau\n",player1);
                for(i=1;i<=4;i++){
                	printf("Tebakan ke %d: ",i);
                	scanf("%d",&index_tebakan[i-1]);
                    if(index_tebakan[i-1]>15||index_tebakan[i-1]<0){
                        printf("Nomer lubang hanya 0 hingga 15\n");
                        --i;
                    }
                }
                err=pthread_create(&(tid),NULL,&hitung_nilai_tebak,NULL);
                if(err!=0){
                    printf("Game Error. Please restart the game\n");
                    return -1;
                }
                while(!hitung);
                turn=0;
            }
        }
        printf("Skor saat ini:\n%s: %d\n%s: %d\n",player1,skor1,player2,skor2);
        if(skor1>9||skor2>9||(ranjau1>15||ranjau2>15))break;
    }
    printf("Skor akhir:\n%s: %d\n%s: %d\n",player1,skor1,player2,skor2);
    return 0;
}
