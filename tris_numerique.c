#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX 500000

const int RAND_M=10;

int compPerm = 0;
int compComp = 0;

//type qui défini les tableau 1D à MAX cases
typedef int t_int[MAX];
typedef int t_unic[(10*RAND_M)];

typedef struct{
    t_unic c_ValeurUnic;
    t_unic c_NbValeurUnic;
}unique;

/**
 * @brief trie un tableau dans l'ordre croissant avec la technique du tri à bulle
 * 
 * @param t tableau 1D à MAX cases
 */
void Tri_bulle_Croissant(t_int t);

/**
 * @brief trie un tableau dans l'ordre décroissant avec la technique du tri à bulle
 * 
 * @param t tableau 1D à MAX cases
 */
void Tri_bulle_Decroissant(t_int t);

/**
 * @brief trie un tableau dans l'ordre croissant avec la technique du tri shaker
 * 
 * @param t tableau 1D à MAX cases
 */
void Tri_Shaker_Croissant(t_int t);

/**
 * @brief trie un tableau dans l'ordre décroissant avec la technique du tri shaker
 * 
 * @param t tableau 1D à MAX cases
 */
void Tri_Shaker_Decroissant(t_int t);

/**
 * @brief fournie l'écart entre les valeurs d'un tableau a comparer
 * 
 * @param inter écart actuel
 * @return int écart actuel divisé par trois, soit le nouvel écart
 */
int div3_TriPeigne(int inter);

/**
 * @brief échange deux valeurs dans la procédure TriPeigneCroissant et TriPeigneDecroissant
 * 
 * @param tab tableau 1D à MAX cases
 * @param inter écart actuel
 * @param i indice de la valeur du tableau a comparer avec la valeur a l'indice i+inter
 */
void echangeur_TriPeigne(t_int tab, int inter, int i);

/**
 * @brief trie un tableau dans l'ordre croissant avec la technique du tri à peigne
 * 
 * @param tab tableau 1D à MAX cases
 * @param inter écart actuel
 */
void TriPeigneCroissant(t_int tab, int inter);

/**
 * @brief trie un tableau dans l'ordre décroissant avec la technique du tri à peigne
 * 
 * @param tab tableau 1D à MAX cases
 * @param inter écart actuel
 */
void TriPeigneDecroissant(t_int tab, int inter);

void echange (int *a, int *b);


/**
 * @brief premet de diviser et trier un tableau
 * 
 * @param tab tableau 1D à MAX cases
 * @param deb premier indice du tableau
 * @param fin dernier indice du tableau
 * @param pivot element de comparaison pour trier les valeurs du tableau
 */
void Division_tableau_Decroissant(t_int tab, int deb,int fin, int *pivot);
void Division_tableau_Croissant(t_int tab, int deb,int fin, int *pivot);

/**
 * @brief procédures récurrentes qui trient un tableau dans l'ordre croissant ou décroissant avec la technique du tri rapide
 * 
 * @param tab tableau 1D à MAX cases
 * @param deb premier indice du tableau
 * @param fin dernier indice du tableau
 */
void TriRapideCroissant(t_int tab,int deb, int fin);
void TriRapideDecroissant(t_int tab,int deb, int fin);

void initTab(t_int t);
void triUnique (t_int t, unique *tabUnic, int *indice);
void afficheTabTrieUnic (t_int t, unique tabUnic);
void afficheNonTrie (t_int t);

int main()
{
    clock_t beginAll=clock();
    int choix;
    t_int t;
    int n=sizeof(t)/sizeof(t[0]); //pour tri a peigne
    unique tabUnic;


    srand(time(NULL));
    initTab(t);

    do{
        printf("De quelle manière voulez-vous trier le tableau ?\n");
        printf("1. Tri à bulle Croissant\n");
        printf("2. Tri à bulle Décroissant\n");
        printf("3. Tri Shaker Croissant\n");
        printf("4. Tri Shaker Décroissant\n");
        printf("5. Tri à peigne Croissant\n");
        printf("6. Tri à peigne Décroissant\n");
        printf("7. Tri rapide Croissant\n");
        printf("8. Tri rapide Décroissant\n");
        scanf("%d", &choix);
        printf("\n");
    }while (choix<1 || choix>8);

    printf("Tableau non trié\n");
    afficheNonTrie (t);
    printf("\n\t TRI EN COURS...\n");
    clock_t beginSort=clock();

    switch (choix)
    {
        case 1 : 
            Tri_bulle_Croissant(t);
            break;

        case 2 :
            Tri_bulle_Decroissant(t);
            break;

        case 3 : 
            Tri_Shaker_Croissant(t);
            break;

        case 4 : 
            Tri_Shaker_Decroissant(t);
            break;

        case 5 :
            TriPeigneCroissant(t, n);
            break;

        case 6 :
            TriPeigneDecroissant(t, n);
            break;

        case 7:
            TriRapideCroissant(t,0,(MAX-1));
            break;

        case 8:
            TriRapideDecroissant(t,0,(MAX-1));
            break;
    }
    printf("\n\t PREPARATION DE L'AFFICHAGE...\n");
    printf("Tableau trié\n");
    afficheTabTrieUnic (t, tabUnic);
    printf("\n");

    clock_t endSort=clock();
    clock_t endAll=clock();
    double timeSort=(endSort-beginSort)*1.0/CLOCKS_PER_SEC;
    double timeAll=(endAll-beginAll)*1.0/CLOCKS_PER_SEC;
    printf("Temps CPU du tri : %f secondes\n", timeAll);
    printf("Nombre de permutations : %d\n", compPerm);
    printf("Nombre de Comparaisons : %d", compComp);

    return 0;
}

void initTab(t_int t){
    int boucle;
    for (boucle=0;boucle<MAX;boucle++){
        t[boucle]=((rand()%((10*RAND_M)-1+1))+1);
    }
}

void echange (int *a, int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;

    compPerm++;
}

void afficheNonTrie (t_int t){
    int i;

    for (i=0;i<MAX;i++){
        printf("%d ", t[i]);
    }
    printf("\n");
}

void afficheTabTrieUnic (t_int t, unique tabUnic){
    int i, indice;
    triUnique (t, &tabUnic, &indice);
    printf("┏━━━━━━━━━━━┳━━━━━━━━━━━━━┓\n");
    printf("┃   Valeur  ┃ Occurrences ┃\n");
    printf("┣━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    for (i=0;i<indice;i++){
        
        printf("┃     %4d  ┃     %6d  ┃\n",tabUnic.c_ValeurUnic[i], tabUnic.c_NbValeurUnic[i]);
        if (i==(indice-1)){
            printf("┗━━━━━━━━━━━┻━━━━━━━━━━━━━┛\n");
        }else{
            printf("┣━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
        }
    }
    printf("\n");
}

void triUnique (t_int t, unique *tabUnic, int *indice){
    int boucle, occurence;
    *indice=0;
    occurence=0;
    for (boucle=0;boucle<=MAX;boucle++){
        
        if (boucle==0){
            tabUnic->c_ValeurUnic[*indice]=t[boucle];
            occurence+=1;
        } else {
            if (t[boucle]==(tabUnic->c_ValeurUnic[*indice])){
                occurence+=1; 
            } else if(t[boucle]!=tabUnic->c_ValeurUnic[*indice] || boucle==(MAX)){
                (tabUnic->c_NbValeurUnic[*indice])=occurence;
                *indice+=1;
                if(boucle!=MAX){
                    tabUnic->c_ValeurUnic[*indice]=t[boucle];
                    occurence=1;
                }
            }
        }
    }
}

/**************************************************************
******* TRI A BULLE CROISSANT ET DECROISSANT ******************
***************************************************************/


void Tri_bulle_Croissant(t_int t)
{
    int i, j;

    for (i=0;i<MAX-1;i++)
    {
        for (j=0;j<MAX-i-1;j++)
        {
            if (t[j]>t[j+1])
            {
                echange(&t[j],&t[j+1]);
            }compComp++;
        }
    }
}

void Tri_bulle_Decroissant(t_int t)
{
    int i, j;

    for (i=0;i<MAX-1;i++)
    {
        for (j=0;j<MAX-i-1;j++)
        {
            if (t[j]<t[j+1])
            {
                echange(&t[j],&t[j+1]);
            }compComp++;
        }
    }
}


/**************************************************************
******* TRI SHAKER CROISSANT ET DECROISSANT *******************
***************************************************************/

void Tri_Shaker_Croissant(t_int t)
{
    int i, j;
    bool tri;

    tri = true;

    while (tri == true)
    {
        tri = false;

        for (i=0;i<MAX-2;i++)
        {
            if (t[i]>t[i+1])
            {
                echange(&t[i],&t[i+1]);
                tri=true;
            }compComp++;
        }

        for (i=MAX-2;i>0;i--)
        { 
            if (t[i]>t[i+1])
            {
                echange(&t[i],&t[i+1]);
                tri=true;
            }compComp++;

        }
    }

}

void Tri_Shaker_Decroissant(t_int t)
{
    int i, j;
    bool tri;

    tri = true;

    while (tri == true)
    {
        tri = false;

        for (i=0;i<MAX-2;i++)
        {
            if (t[i]<t[i+1])
            {
                echange(&t[i],&t[i+1]);
                tri = true;
            }compComp++;
        }

        for (i=MAX-2;i>0;i--)
        {
            if (t[i]<t[i+1])
            {
                echange(&t[i],&t[i+1]);
                tri = true;
            }compComp++;

        }
    }

}

/**************************************************************
******* TRI RAPIDE CROISSANT DECROISSANT***********************
***************************************************************/

void Division_tableau_Croissant(t_int tab, int deb,int fin, int *pivot){
    int i,j;
    j=deb;
    for(i=deb;i<(fin);i++){
        if(tab[i]<tab[fin]){
            echange(&tab[i],&tab[j]);
            j+=1;
        }compComp++;
    }
    echange(&tab[j],&tab[fin]);
    *pivot=j;
}

void TriRapideCroissant(t_int tab,int deb, int fin){
    int pivot;
    if(deb<fin){
        Division_tableau_Croissant(tab,deb,fin,&pivot);
        TriRapideCroissant(tab,deb,(pivot-1));
        TriRapideCroissant(tab,(pivot+1),fin);
    }
}

void Division_tableau_Decroissant(t_int tab, int deb,int fin, int *pivot){
    int i,j;
    j=deb;
    for(i=deb;i<(fin);i++){
        if(tab[i]>tab[fin]){
            echange(&tab[i],&tab[j]);
            j+=1;
        }compComp++;
    }
    echange(&tab[j],&tab[fin]);
    *pivot=j;
}

void TriRapideDecroissant(t_int tab,int deb, int fin){
    int pivot;
    if(deb<fin){
        Division_tableau_Decroissant(tab,deb,fin,&pivot);
        TriRapideDecroissant(tab,deb,(pivot-1));
        TriRapideDecroissant(tab,(pivot+1),fin);
    }
}

/**************************************************************
******* TRI PEIGNE CROISSANT DECROISSANT***********************
***************************************************************/

int div3_TriPeigne(int inter) {
    inter/=3;
    if (inter<1) {
        inter=1;
    }
    return inter;
}

void echangeur_TriPeigne(t_int tab, int inter, int i) {
    int temp=tab[i];
    tab[i]=tab[i+inter];
    tab[i+inter]=temp;

    compPerm++;
}

void TriPeigneCroissant(t_int tab, int inter) {
    bool swap=true;
    while (inter!=1 || swap==true) {
        inter = div3_TriPeigne(inter);
        swap=false;
        for (int i=0;i<MAX-inter;i++) {
            if (tab[i]>tab[i+inter]) {
                echangeur_TriPeigne(tab, inter, i);
                swap=true;
            }compComp++;
        }
    }
}

void TriPeigneDecroissant(t_int tab, int inter) {
    bool swap=true;
    while (inter!=1 || swap==true) {
        inter = div3_TriPeigne(inter);
        swap=false;
        for (int i=0;i<MAX-inter;i++) {
            if (tab[i]<tab[i+inter]) {
                echangeur_TriPeigne(tab, inter, i);
                swap=true;
            }compComp++;
        }
    }
}

