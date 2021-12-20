#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

const int LIGNE=50;
const int CARAC=10;

void afficheTab(char tab[LIGNE][CARAC+1]);
void echange (char a[CARAC], char b[CARAC+1]);
void Tri_bulle_Croissant_nbCaract(char t[LIGNE][CARAC+1]);
void Tri_bulle_Croissant_alpha(char t[LIGNE][CARAC+1]);
void initTab(char t[LIGNE][CARAC+1]);

int main(){
    int boucle;
    char tab[LIGNE][(CARAC+1)];
    srand(time(NULL));


    initTab(tab);
    afficheTab(tab);
    putchar('\n');
    
    Tri_bulle_Croissant_nbCaract(tab);
    printf("\n");
    afficheTab(tab);
}

void afficheTab(char tab[LIGNE][CARAC+1]){
    int ligne, caract;
    for(ligne=0; ligne<LIGNE; ligne++){
        printf("%s", tab[ligne]);        
        printf("\n");
    }
}


void initTab(char t[LIGNE][CARAC+1]){

    int ligne, caract, nbCaractTemp;
    for (ligne=0; ligne<LIGNE; ligne++){
        nbCaractTemp=(rand()%(CARAC-5+1)+5);
        for(caract=0; caract<nbCaractTemp; caract++){
            t[ligne][caract]=(rand()%(122-97+1)+97);
        }
        if(nbCaractTemp<=CARAC){
            for(; caract<=CARAC; caract++){
                t[ligne][caract]='\0';
            }
        }
    }
}



void Tri_bulle_Croissant_nbCaract(char t[LIGNE][CARAC+1])
{
    int D, d, c;
    bool ordre;
    ordre=false;
    c=0;
    for(D=0; D<LIGNE-1; D++){
        for(d=0; d<LIGNE-1-D; d++){
        while(ordre==false && c<CARAC){
                if(strlen(t[d])>strlen(t[d+1])){
                    echange(t[d], t[d+1]);
                    ordre=true;
                }else if(strlen(t[d]) <= strlen(t[d+1])){
                    ordre=true;
                }
            }
        c=0;
        ordre=false;
        }
    }
    Tri_bulle_Croissant_alpha(t);
}

void Tri_bulle_Croissant_alpha(char t[LIGNE][CARAC+1])
{
    int D, d, c;
    bool ordre;
    ordre=false;
    c=0;
    for(D=0; D<LIGNE-1; D++){
        for(d=0; d<LIGNE-1-D; d++){
            if(strlen(t[d]) == strlen(t[d+1])){
                while(ordre==false && c<CARAC){
                    if(t[d][c]>t[d+1][c]){
                        echange(t[d],t[d+1]);
                        ordre=true;
                    }else if(t[d][c]<t[d+1][c]){
                        ordre=true;
                    }else{
                        c++;
                    }
                }
            }
            c=0;
            ordre=false;
        }
    }
}
void echange (char a[CARAC+1], char b[CARAC+1]){
    char temp[CARAC+1];
    strcpy(temp,a);
    strcpy(a,b);
    strcpy(b,temp);
}