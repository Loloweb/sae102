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
    int i, j;
    bool permut;
    permut=false;
    j=0;

    for (i=0;i<LIGNE-1;i++)
    {
        j=0;
        permut=false;
        while(j<CARAC && permut==false)
        {
            if (t[i][j]>t[i+1][j])
            {
                echange(&t[i][j],&t[i+1][j]);
                permut=true;
            }
            j++;
        }
    }
}

void echange (char a[CARAC], char b[CARAC]){
    char temp[CARAC];
    strcpy(temp,a);
    strcpy(a,b);
    strcpy(b,temp);
}