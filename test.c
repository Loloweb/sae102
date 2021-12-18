#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define LIGNE 10
#define CARAC 5

void afficheTab(char tab[LIGNE][CARAC]);
void echange (char a[CARAC], char b[CARAC]);
void Tri_bulle_Croissant(char t[LIGNE][CARAC]);
void initTab(char t[LIGNE][CARAC]);

int main(){
    char tab[LIGNE][CARAC];
    srand(time(NULL));

    initTab(tab);
    afficheTab(tab);
    Tri_bulle_Croissant(tab);
    printf("\n");
    afficheTab(tab);
}

void afficheTab(char tab[LIGNE][CARAC]){
    int ligne, car;
    for (ligne=0; ligne< LIGNE; ligne++){
        printf("**********LIGNE %d**********\n", ligne);
        for (car=0; car<CARAC; car++){
            printf("%c", tab[ligne][car]);
        }
        printf("\n");
    }
}

void initTab(char t[LIGNE][CARAC]){
    int ligne, car, hasard;
    char temp;
    for (ligne=0; ligne< LIGNE; ligne++){
        for (car=0; car<CARAC-1; car++){
            t[ligne][car]=(rand()%(122-97+1)+97);
        }
        t[ligne][car]='\0';
    }
}

void Tri_bulle_Croissant(char t[LIGNE][CARAC])
{
    int D, d, c;
    bool ordre;
    ordre=false;
    c=0;

    for(D=0; D<LIGNE-1; D++){
        for(d=0; d<LIGNE-1-D; d++){
            while(ordre==false && c<CARAC){
                if(t[d][c]>t[d+1][c]){
                    echange(t[d], t[d+1]);
                    ordre=true;
                }else if(t[d][c]<t[d+1][c]){
                    ordre=true;
                }else{
                    c++;
                }
            }
        c=0;
        ordre=false;
        }
    }
}

void echange (char a[CARAC], char b[CARAC]){
    char temp[CARAC];
    strcpy(temp,a);
    strcpy(a,b);
    strcpy(b,temp);
}