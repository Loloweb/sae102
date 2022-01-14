#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX 20000

long int compteur_permutation = 0;
long int compteur_comparaison = 0;

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
    int c_poplo;
}t_preparationAffichage;

typedef t_covid t_tabCovid[MAX];

void LireFichier(t_tabCovid tab, int* nombreCas);
int population22_sequentiel(t_tabCovid tab, int nbCas);
int population22_trie (t_tabCovid tab, int nbCas);
void triDepartement(t_tabCovid tab, int nombreCas);
void triDate(t_tabCovid tab, int nombreCas);
int recherche1Janv_seq(t_tabCovid tab, int nombreCas, t_tabCovid tab1Janv);
int recherche1Janv_trie(t_tabCovid tab, int nombreCas, t_tabCovid tab1Janv);
void Debutannee35(t_tabCovid tab, int nombreCas);
void triClasse(t_tabCovid tab, int nombreCas);
void Division_tableau_Croissant_date(t_tabCovid tab, int deb,int fin, int *pivot);
void TriRapideCroissant_date(t_tabCovid tab,int deb, int fin);
void Division_tableau_Croissant_classe(t_tabCovid tab, int deb,int fin, int *pivot);
void TriRapideCroissant_classe(t_tabCovid tab,int deb, int fin);
void Division_tableau_Croissant_dep(t_tabCovid tab, int deb,int fin, int *pivot);
void TriRapideCroissant_dep(t_tabCovid tab,int deb, int fin);
void echange (t_covid *a, t_covid *b);


int main (){
    t_tabCovid tab;
    int nombreCas, cas;
    LireFichier(tab, &nombreCas);
    printf("\n");
    cas=population22_sequentiel(tab,nombreCas);
    printf("Nombre d'habitant dans les Cotes d'armor: %d\n", cas);

    printf("\n");
    cas=population22_trie (tab, nombreCas);
    printf("Nombre d'habitant dans les Cotes d'armor: %d\n", cas);

    printf("\n");
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
    clock_t debut=clock();

    bool trouv;
    trouv=false;
    boucle=0;
    habitant22=0;
    compteur_comparaison=0;
    compteur_permutation=0;

    while(boucle<MAX && !trouv){
        if(tab[boucle].c_classe==0 && tab[boucle].c_dep==22){
            habitant22=tab[boucle].c_pop;
            trouv=true;
        }
        boucle+=1;
        compteur_comparaison+=1;
    }

    clock_t fin=clock();
    double tempsCPU=(fin-debut)*1.0/CLOCKS_PER_SEC;
    printf("***POUR LA POPULATION DES COTES D'ARMOR**\n");
    printf("***SOLUTION 1: RECHERCHE SEQUENTIEL***\n");
    printf("Temps CPU: %.3f\n", tempsCPU);
    printf("nombre de permutations : %ld\n", compteur_permutation);
    printf("nombre de comparaisons : %ld\n", compteur_comparaison);

    return habitant22;
}

int population22_trie (t_tabCovid tab, int nbCas){
    int habitant22, boucle;
    clock_t debut_avec_tri=clock();

    bool trouv;
    trouv=false;
    boucle=0;
    habitant22=0;
    compteur_comparaison=0;
    compteur_permutation=0;

    triDepartement(tab,nbCas);

    clock_t debut_sans_tri=clock();

    while(boucle<MAX && !trouv){
        if(tab[boucle].c_classe==0 && tab[boucle].c_dep==22){
            habitant22=tab[boucle].c_pop;
            trouv=true;
        }
        boucle+=1;
        compteur_comparaison+=1;
    }

    clock_t fin_avec_tri=clock();
    clock_t fin_sans_tri=clock();

    double tempsCPU_avec_tri=(fin_avec_tri-debut_avec_tri)*1.0/CLOCKS_PER_SEC;
    double tempsCPU_sans_tri=(fin_sans_tri-debut_sans_tri)*1.0/CLOCKS_PER_SEC;
    printf("***POUR LA POPULATION DES COTES D'ARMOR**\n");
    printf("*******SOLUTION 2: TRI ET RECHERCHE**********\n");
    printf("Temps CPU avec tri: %.3f\n", tempsCPU_avec_tri);
    printf("Temps CPU sans tri: %.3f\n", tempsCPU_sans_tri);

    printf("nombre de permutations : %ld\n", compteur_permutation);
    printf("nombre de comparaisons : %ld\n", compteur_comparaison);
    return habitant22;
}


void triDepartement(t_tabCovid tab, int nombreCas) {
    TriRapideCroissant_dep(tab, 0, nombreCas); 
}

void triDate(t_tabCovid tab, int nombreCas) {
    TriRapideCroissant_date(tab, 0, nombreCas); 
}

int recherche1Janv_seq(t_tabCovid tab, int nombreCas, t_tabCovid tab1Janv){

    int boucle, nbElement1Janv;
    t_tabCovid temp;
    clock_t debut=clock();

    boucle=0;
    compteur_comparaison=0;
    compteur_permutation=0;
    nbElement1Janv=0;

    while(boucle<MAX){
        if(strcmp(tab[boucle].c_date, "2021-01-01")==0){
            temp[nbElement1Janv]=tab[boucle];
            nbElement1Janv+=1;
        }
        boucle+=1;
        compteur_comparaison+=1;
    }

    for (boucle=0; boucle<nbElement1Janv; boucle++){
        tab1Janv[boucle]=temp[boucle];
    }

    clock_t fin=clock();
    double tempsCPU=(fin-debut)*1.0/CLOCKS_PER_SEC;
    printf("***POUR LA DATE DU 2021-01-01**\n");

    printf("*****SOLUTION 1: RECHERCHE**********\n");
    printf("Temps CPU: %.3f\n", tempsCPU);
    printf("nombre de permutations : %ld\n", compteur_permutation);
    printf("nombre de comparaisons : %ld\n", compteur_comparaison);
    return nbElement1Janv;
}

int recherche1Janv_trie(t_tabCovid tab, int nombreCas, t_tabCovid tab1Janv){

    int boucle, nbElement1Janv;
    t_tabCovid temp;
    clock_t debut=clock();
    bool trouv;

    trouv=false;
    boucle=0;
    compteur_comparaison=0;
    compteur_permutation=0;
    nbElement1Janv=0;

    clock_t debut_avec_tri=clock();

    TriRapideCroissant_date(tab, 0, nombreCas);

    clock_t debut_sans_tri=clock();

    while(boucle<MAX && trouv==false){
        while(strcmp(tab[boucle].c_date, "2021-01-01")==0){
            temp[nbElement1Janv]=tab[boucle];
            nbElement1Janv+=1;
            boucle+=1;
            trouv=true;
        }
        boucle+=1;
    }

    for (boucle=0; boucle<nbElement1Janv; boucle++){
        tab1Janv[boucle]=temp[boucle];
    }

    clock_t fin_avec_tri=clock();
    clock_t fin_sans_tri=clock();

    double tempsCPU_avec_tri=(fin_avec_tri-debut_avec_tri)*1.0/CLOCKS_PER_SEC;
    double tempsCPU_sans_tri=(fin_sans_tri-debut_sans_tri)*1.0/CLOCKS_PER_SEC;
    printf("***POUR LA POPULATION DES COTES D'ARMOR**\n");
    printf("*******SOLUTION 2: TRI ET RECHERCHE**********\n");
    printf("Temps CPU avec tri: %.3f\n", tempsCPU_avec_tri);
    printf("Temps CPU sans tri: %.3f\n", tempsCPU_sans_tri);

    printf("nombre de permutations : %ld\n", compteur_permutation);
    printf("nombre de comparaisons : %ld\n", compteur_comparaison);

    return nbElement1Janv;
}


void Debutannee35(t_tabCovid tab, int nombreCas){
    int elementsTabJanv, classe, compteur, affichage, total;
    t_tabCovid tab1Janv;

    classe=9;
    compteur=0;

    printf("\n");
    elementsTabJanv=recherche1Janv_seq(tab, nombreCas, tab1Janv);
    printf("Avec la recherche seule, il y a %d elements au 1 Janvier 2021\n", elementsTabJanv);
    
    printf("\n");
    elementsTabJanv=recherche1Janv_trie(tab, nombreCas, tab1Janv);
    printf("Avec un tri puis une recherche, il y a %d elements au 1 Janvier 2021\n", elementsTabJanv);

    triClasse(tab1Janv, elementsTabJanv);

    printf("Nombre de cas en Ille-et-Vilaine par classe d'age, le 1er janvier 2021\n");

    for (affichage=0; affichage< elementsTabJanv; affichage++){
        if (tab1Janv[affichage].c_dep==35 && tab1Janv[affichage].c_classe!=0){
            while (tab1Janv[affichage].c_classe!=89 && affichage<elementsTabJanv && tab1Janv[affichage].c_dep==35){
                compteur+=tab1Janv[affichage].c_pos;
                total+=tab1Janv[affichage].c_pos;
                affichage+=1;
            }
            printf("[ %2d - %2d] : %2d\n", classe-9, classe, compteur);
            classe+=10;
            compteur=0;

            if(tab1Janv[affichage].c_dep==35 && tab1Janv[affichage].c_classe==90){
                while (tab1Janv[affichage].c_classe==90 && affichage<elementsTabJanv && tab1Janv[affichage].c_dep==35){
                    compteur+=tab1Janv[affichage].c_pos;
                    total+=tab1Janv[affichage].c_pos;
                    affichage+=1;
                }
                printf("[ %2d - %2d] : %2d\n", classe, classe, compteur);
                classe+=10;
                compteur=0;
            
            }
        }
        
    }
    
}

void triClasse(t_tabCovid tab, int nombreCas) {
    TriRapideCroissant_classe(tab, 0, nombreCas);
}


/**************************************************************
******* TRI RAPIDE CROISSANT importé***************************
***************************************************************/

void Division_tableau_Croissant_date(t_tabCovid tab, int deb,int fin, int *pivot){
    int i,j;
    j=deb;
    for(i=deb;i<(fin);i++){
        if(strcmp(tab[i].c_date,tab[fin].c_date)<0){
            echange(&tab[i],&tab[j]);
            j+=1;
        }
        compteur_comparaison+=1;
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
    compteur_comparaison+=1;
}

void Division_tableau_Croissant_classe(t_tabCovid tab, int deb,int fin, int *pivot){
    int i,j;
    j=deb;
    for(i=deb;i<(fin);i++){
        if(tab[i].c_classe<tab[fin].c_classe){
            echange(&tab[i],&tab[j]);
            j+=1;
        }
        compteur_comparaison+=1;
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
    compteur_comparaison+=1;
}


void Division_tableau_Croissant_dep(t_tabCovid tab, int deb,int fin, int *pivot){
    int i,j;
    j=deb;
    for(i=deb;i<(fin);i++){
        if(tab[i].c_dep<tab[fin].c_dep){
            echange(&tab[i],&tab[j]);
            j+=1;
        }
        compteur_comparaison+=1;
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
    compteur_comparaison+=1;
}


void echange (t_covid *a, t_covid *b){
    t_covid temp;
    temp=*a;
    *a=*b;
    *b=temp;
    compteur_permutation+=1;
}
