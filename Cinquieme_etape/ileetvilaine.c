#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

typedef struct{
    int c_classe;
    int c_pop;
}t_preparationAffichage;

typedef t_covid t_tabCovid[MAX];

void LireFichier(t_tabCovid tab, int* nombreCas);
int population22(t_tabCovid tab, int nbCas);
void triDepartement(t_tabCovid tab, int nombreCas);
void Division_tableau_Croissant_date(t_tabCovid tab, int deb,int fin, int *pivot);
void TriRapideCroissant_date(t_tabCovid tab,int deb, int fin);
void Division_tableau_Croissant_classe(t_tabCovid tab, int deb,int fin, int *pivot);
void TriRapideCroissant_classe(t_tabCovid tab,int deb, int fin);
void Division_tableau_Croissant_dep(t_tabCovid tab, int deb,int fin, int *pivot);
void TriRapideCroissant_dep(t_tabCovid tab,int deb, int fin);

void triClasse(t_tabCovid tab, int nombreCas);

void echange (t_covid *a, t_covid *b);
void triDate(t_tabCovid tab, int nombreCas);
void Debutannee35(t_tabCovid tab, int nombreCas);


int main (){
    t_tabCovid tab;
    int nombreCas, cas;
    LireFichier(tab, &nombreCas);
    cas=population22(tab,nombreCas);
    printf("%d", cas);
    triDepartement(tab, nombreCas);
    triDate(tab,nombreCas);
    Debutannee35(tab,nombreCas);

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

int population22_sequentiel(t_tabCovid tab, int nbCas){
    int habitant22, boucle;
    bool trouv;
    trouv=false;
    boucle=0;
    habitant22=0;
    while(boucle<MAX && !trouv){
        if(tab[boucle].c_classe==0 && tab[boucle].c_dep==22){
            habitant22=tab[boucle].c_pop;
            trouv=true;
        }
        boucle+=1;
    }
    return habitant22;
}

void triDepartement(t_tabCovid tab, int nombreCas) {
    TriRapideCroissant_dep(tab, 0, nombreCas); 
}

void triDate(t_tabCovid tab, int nombreCas) {
    TriRapideCroissant_date(tab, 0, nombreCas); 
}

void Debutannee35(t_tabCovid tab, int nombreCas){
    int total, compteur, affichage, classe;
    triClasse(tab, nombreCas);
    classe=0;

    printf("Nombre de cas en Ille-et-Vilaine par classe d'age, le 1er janvier 2021\n");
    for(affichage=0; affichage< nombreCas; affichage++){
        if (strcmp(tab[affichage].c_date, "01/01/2020") && tab[affichage].c_dep==35){
            if(tab[affichage].c_classe!=tab[affichage+1].c_classe){
                printf("[%2d - %3d] : %d\n", tab[affichage].c_classe, tab[affichage+1].c_classe, tab[affichage].c_pos);
                total+=tab[affichage].c_pos;
            }
        }
        
    }
    printf("TOTAL= %d\n", total);
}


void triClasse(t_tabCovid tab, int nombreCas) {
    t_preparationAffichage Affichage;
    TriRapideCroissant_classe(tab, 0, nombreCas);
}


/**************************************************************
******* TRI RAPIDE CROISSANT importé***************************
***************************************************************/

void Division_tableau_Croissant_date(t_tabCovid tab, int deb,int fin, int *pivot){
    int i,j;
    j=deb;
    for(i=deb;i<(fin);i++){
        if(tab[i].c_date<tab[fin].c_date){
            echange(&tab[i],&tab[j]);
            j+=1;
        }
    }
    echange(&tab[j],&tab[fin]);
    *pivot=j;
}

void TriRapideCroissant_date(t_tabCovid tab,int deb, int fin){
    int pivot;
    if(deb<fin){
        Division_tableau_Croissant_date(tab,deb,fin,&pivot);
        TriRapideCroissant_date(tab,deb,(pivot-1));
        TriRapideCroissant_date(tab,(pivot+1),fin);
    }
}

void Division_tableau_Croissant_classe(t_tabCovid tab, int deb,int fin, int *pivot){
    int i,j;
    j=deb;
    for(i=deb;i<(fin);i++){
        if(tab[i].c_classe<tab[fin].c_classe){
            echange(&tab[i],&tab[j]);
            j+=1;
        }
    }
    echange(&tab[j],&tab[fin]);
    *pivot=j;
}

void TriRapideCroissant_classe(t_tabCovid tab,int deb, int fin){
    int pivot;
    if(deb<fin){
        Division_tableau_Croissant_classe(tab,deb,fin,&pivot);
        TriRapideCroissant_classe(tab,deb,(pivot-1));
        TriRapideCroissant_classe(tab,(pivot+1),fin);
    }
}


void Division_tableau_Croissant_dep(t_tabCovid tab, int deb,int fin, int *pivot){
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

void TriRapideCroissant_dep(t_tabCovid tab,int deb, int fin){
    int pivot;
    if(deb<fin){
        Division_tableau_Croissant_dep(tab,deb,fin,&pivot);
        TriRapideCroissant_dep(tab,deb,(pivot-1));
        TriRapideCroissant_dep(tab,(pivot+1),fin);
    }
}


void echange (t_covid *a, t_covid *b){
    t_covid temp;
    temp=*a;
    *a=*b;
    *b=temp;
}