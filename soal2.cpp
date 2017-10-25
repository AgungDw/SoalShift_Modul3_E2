#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>

using namespace std;

int index_tebakan[4],pasang_terakhir,skor1=0,skor2=0;
bool turn=0,lubang1[16],lubang2[16],hitung=0;
pthread_t tid[2];

int main()
{
	string player1,player2;
    int ranjau1=0,ranjau2=0,input_ranjau,err,index_ranjau;
    cout<<"Input nama player 1: ";
    cin>>player1;
    cout<<"Input nama player 2: ";
    cin>>player2;
    cout<<"Game Dimulai!\n";
    while(1){
        hitung=0;
        if(!turn){
            ULANGI1:
            cout<<player1<<" pasang ranjau\n";
            cout<<"Jumlah ranjau yang ingin dipasang: ";
            cin>>input_ranjau;
            if((16<(input_ranjau+ranjau1))||(input_ranjau>4)){
                cout<<"Ranjau terlalu banyak";
                goto ULANGI1;
            }
            else {
                pasang_terakhir=input_ranjau;
                ranjau1+=input_ranjau;
                for(int i=1;i<=input_ranjau;i++){
                    cout<<"Ranjau ke "<<ranjau1-input_ranjau+i<<" diisi pada lubang ke (nomer lubang dimulai dari 0): ";
                    cin>>index_ranjau;
                    if(index_ranjau>15||index_ranjau<0){
                        cout<<"Nomer lubang hanya 0 hingga 15\n";
                        --i;
                    }
                    else if(lubang1[index_ranjau]!=0){
                        cout<<"Lubang tersebut telah diisi\n";
                        --i;
                    }
                    else lubang1[i-1]=1;
                }
                cout<<player2<<" tebak ranjau\n";
                for(int i=1;i<=4;i++){
                    cout<<"Tebakan ke "<<i<<": ";
                    cin>>index_tebakan[i-1];
                    if(index_tebakan[i-1]>15||index_tebakan[i-1]<0){
                        cout<<"Nomer lubang hanya 0 hingga 15\n";
                        --i;
                    }
                }
                err=pthread_create(&(tid[0]),NULL,&hitung_nilai_pasang,NULL);
                if(err!=0){
                    cout<<"Game Error. Please restart the game\n";
                    return -1;
                }
                while(!hitung);
                err=pthread_create(&(tid[1]),NULL,&hitung_nilai_tebak,NULL);
                if(err!=0){
                    cout<<"Game Error. Please restart the game\n";
                    return -1;
                }
                while(hitung);
                turn=1;
            }
        }
}