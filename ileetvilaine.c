#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20000

typedef char t_chaine10[11];
typedef int t_int[MAX];

typedef struct{
    int c_dep; // numéro du département (22, 29, 35, 56)
    t_chaine10 c_date; // date en aaaa-mm-jj
    int c_pos; // nombre de cas enregistrés ce jour la, dans cette classe d'age et dans ce département
    int c_classe; // tranche d'age.
    // 9 représente de 0 à 9. 19 représente de 10 à 19... jusqu'a 90 qui représente 90 et +. La tranche d'age 0 représente toutes les tranches d'age
    int c_pop; // nombre d'habitants de cette tranche d'age dans ce département
}t_covid;

typedef t_covid t_tabCovid[MAX];


int main (){
    t_tabCovid tab;
    int nombreCas;
    LireFichier(tab, nombreCas);
}


void LireFichier(t_tabCovid tab, int* nombreCas){
    FILE* fichier;
    fichier =fopen("DonneesCovid.data.data", "rb");

    t_covid temp;
    int boucle, ok;

    boucle=0;

    if (fichier!=NULL){
        fread(&temp, 1, sizeof(t_covid), fichier);

        while(!feof(fichier) && (boucle<MAX)){
            tab[boucle]=temp;
            boucle+=1;
            fread(&temp, 1, sizeof(t_covid), fichier);
        } 
    }
    *nombreCas=boucle;
    ok=fclose(fichier);
}

int population22(t_tabCovid tab, int nbCas){
    int habitant22, boucle;

    habitant22=0;

    for(boucle=0; boucle<nbCas; boucle++){
        if(tab[boucle].c_dep==22){
            habitant22+=1;
        }
    }
    return habitant22;
    
}



void triDepartement(t_tabCovid tab, int nombreCas) {
    TriRapideCroissant(tab, 0, nombreCas); // peut etre juste enlever ça et renommer triRapideCroissant??????
}

/**************************************************************
******* TRI RAPIDE CROISSANT importé***************************
***************************************************************/

void Division_tableau_Croissant(t_tabCovid tab, int deb,int fin, int *pivot){
    int i,j;
    j=deb;
    for(i=deb;i<(fin);i++){
        if(tab[i].c_dep<tab[fin].c_dep){
            echange(&tab[i],&tab[j]);
            j+=1;
        }
    }
    echange(&tab[j],&tab[fin]);
    *pivot=j;
}

void TriRapideCroissant(t_tabCovid tab,int deb, int fin){
    int pivot;
    if(deb<fin){
        Division_tableau_Croissant(tab,deb,fin,&pivot);
        TriRapideCroissant(tab,deb,(pivot-1));
        TriRapideCroissant(tab,(pivot+1),fin);
    }
}