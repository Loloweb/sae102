#include <stdlib.h>
#include <stdio.h>

void afficheTab(int tab[4][4]);

int main(){
    int tab[4][4]={
        {115, 100, 110, 0},
        {117, 101, 111, 0},
        {115, 102, 112, 0},
        {33, 103, 113, 0}
    };
    afficheTab(tab);
}

void afficheTab(int tab[4][4]){
    int ligne, colonne;
    for (colonne=0; colonne<4; colonne++) {
        for (ligne=0; ligne<4; ligne++){
            printf("%c", tab[colonne][ligne]);
        }
    }
}

/*void Tri_bulle_Croissant(int t)
{
    int i, j;

    for (i=0;i<MAX-1;i++)
    {
        for (j=0;j<MAX-i-1;j++)
        {
            if (t[j]>t[j+1])
            {
                echange(&t[j],&t[j+1]);
            }
        }
    }
}*/