/**
 * @brief Le programme trie un talbeau de chaine de caracteres genere aleatoirement dans l'ordre alphabetique ou anti-alphabetique
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int compPerm = 0;
int compComp = 0;

/**
 * @brief defini le nombre de chaines
 */
#define MAX 150000

/**
 * @brief maximum de la fonction rand() 
 */
const int RAND_M=10;

/**
 * @brief nombre maximum de caracteres par chaines
 * sert pour avoir des chaines entre 5 et NBcaracteres
 */
const int NBCARACTERE=10;

/**
 * @brief type qui defini les tableau de chaine de caracteres
 */
typedef char t_char[MAX][NBCARACTERE+1];

/**
 * @brief trie un tableau dans l'ordre alphabetique avec la technique du tri a bulle
 * 
 * @param t tableau de MAX chaines
 */
void Tri_bulle_Croissant_nbCaract(t_char t);
void Tri_bulle_Croissant_alpha(t_char t);

/**
 * @brief trie un tableau dans l'ordre anti-alphabetique avec la technique du tri a bulle
 * 
 * @param t tableau de MAX chaines
 */
void Tri_bulle_Decroissant_nbCaract(t_char t);
void Tri_bulle_Decroissant_alpha(t_char t);

/**
 * @brief trie un tableau dans l'ordre alphabetique avec la technique du tri shaker
 * 
 * @param t tableau de MAX chaines
 */
void Tri_Shaker_Croissant_nbCarac(t_char t);
void Tri_Shaker_Croissant_alpha(t_char t);

/**
 * @brief trie un tableau dans l'ordre anti-alphabetique avec la technique du tri shaker
 * 
 * @param t tableau de MAX chaines
 */
void Tri_Shaker_Decroissant_nbCarac(t_char t);
void Tri_Shaker_Decroissant_alpha(t_char t);

/**
 * @brief fournie l'ecart entre les valeurs d'un tableau a comparer
 * 
 * @param inter ecart actuel
 * @return int ecart actuel divise par trois, soit le nouvel ecart
 */
int div3_TriPeigne(int inter);

/**
 * @brief echange deux valeurs dans la procedure TriPeigneCroissant et TriPeigneDecroissant
 * 
 * @param tab tableau de MAX chaines
 * @param inter ecart actuel
 * @param i indice de la valeur du tableau a comparer avec la valeur a l'indice i+inter
 */
void echangeur_TriPeigne(t_char tab, int inter, int i);

/**
 * @brief series de procedures qui trient un tableau dans l'ordre alphabetique avec la technique du tri a peigne
 * 
 * @param tab tableau de MAX chaines
 * @param inter ecart actuel
 */
void TriPeigneCroissant_nbcaract(t_char tab, int inter);
void TriPeigneCroissant_alpha(t_char tab, int inter, int deb, int fin);
void blocks_Croissant(t_char tab);

/**
 * @brief series de procedures qui trient un tableau dans l'ordre anti-alphabetique avec la technique du tri a peigne
 * 
 * @param tab tableau de MAX chaines
 * @param inter ecart actuel
 */
void TriPeigneDecroissant_nbcaract(t_char tab, int inter);
void TriPeigneDecroissant_alpha(t_char tab, int inter, int deb, int fin);
void blocks_Decroissant(t_char tab);

/**
 * @brief series de procedures qui trient un tableau dans l'ordre alphabetique avec la technique du tri rapide
 * 
 * @param tab tableau de MAX chaines
 * @param inter ecart actuel
 */
void Division_tableau_Croissant_nbcarac(t_char tab, int deb,int fin, int *pivot);
void TriRapideCroissant_nbcarac(t_char tab,int deb, int fin);
void TriRapideCroissant_alpha(t_char tab,int deb, int fin);
void Division_tableau_Croissant_alpha(char t[MAX][NBCARACTERE+1], int deb,int fin, int *pivot);
void separation_Rapide_croissant(t_char tab);

/**
 * @brief series de procedures qui trient un tableau dans l'ordre anti-alphabetique avec la technique du tri rapide
 * 
 * @param tab tableau de MAX chaines
 * @param inter ecart actuel
 */
void Division_tableau_Decroissant_nbcarac(t_char tab, int deb,int fin, int *pivot);
void TriRapideDecroissant_nbcarac(t_char tab,int deb, int fin);
void TriRapideDecroissant_alpha(t_char tab,int deb, int fin);
void Division_tableau_Decroissant_alpha(char t[MAX][NBCARACTERE+1], int deb,int fin, int *pivot);
void separation_Rapide_Decroissant(t_char tab);


/**
 * @brief initialise un tableau de chaines avec des chaines aleatoires
 * 
 * @param t tableau de MAX chaines
 */
void initTab(t_char t);


/**
 * @brief affiche un tableau de chaines de caracteres
 * 
 * @param tab tableau de MAX chaines
 * @param trie indique si le tableau est trie, adpate l'affichage selon sa valeur (true= trie/ false= non trie)
 */
void afficheTab(t_char tab, bool trie);

/**
 * @brief echange deux chaines de deux tableaux
 * 
 * @param a premiere chaine
 * @param b deuxieme chaine
 */
void echange (char a[4], char b[4]);



int main()
{
    clock_t beginAll=clock();
    int choix;
    t_char t;
    int n=sizeof(t)/sizeof(t[0]); //pour tri a peigne

    srand(time(NULL));
    initTab(t);

    do{
        printf("De quelle maniere voulez-vous trier le tableau ?\n");
        printf("1. Tri a bulle Croissant\n");
        printf("2. Tri a bulle Decroissant\n");
        printf("3. Tri Shaker Croissant\n");
        printf("4. Tri Shaker Decroissant\n");
        printf("5. Tri a peigne Croissant\n");
        printf("6. Tri a peigne Decroissant\n");
        printf("7. Tri rapide Croissant\n");
        printf("8. Tri rapide Decroissant\n");
        scanf("%d", &choix);
        printf("\n");
    }while (choix<1 || choix>8);

    printf("Tableau non trie\n");
    afficheTab(t, false);

    printf("\n\t TRI EN COURS...\n\n");
    clock_t beginSort=clock();

    switch (choix)
    {
        case 1 : 
            Tri_bulle_Croissant_nbCaract(t);
            printf("\n\t PREPARATION DE L'AFFICHAGE...\n");
            printf("Tableau trie\n");
            afficheTab(t, true);
            printf("***************************************************************\n");
            printf("************************TRI A BULLE CROISSANT******************\n");
            printf("***************************************************************\n");
            break;

        case 2 :
            Tri_bulle_Decroissant_nbCaract(t);
            printf("\n\t PREPARATION DE L'AFFICHAGE...\n");
            printf("Tableau trie\n");
            afficheTab(t, true);
            printf("***************************************************************\n");
            printf("**********************TRI A BULLE DECROISSANT******************\n");
            printf("***************************************************************\n");
            break;

        case 3 : 
            Tri_Shaker_Croissant_nbCarac(t);
            printf("\n\t PREPARATION DE L'AFFICHAGE...\n");
            printf("Tableau trie\n");
            afficheTab(t, true);
            printf("***************************************************************\n");
            printf("***********************TRI SHAKER CROISSANT********************\n");
            printf("***************************************************************\n");
            break;

        case 4 : 
            Tri_Shaker_Decroissant_nbCarac(t);
            printf("\n\t PREPARATION DE L'AFFICHAGE...\n");
            printf("Tableau trie\n");
            afficheTab(t, true);
            printf("***************************************************************\n");
            printf("*********************TRI SHAKER DECROISSANT********************\n");
            printf("***************************************************************\n");
            break;

        case 5 :
            TriPeigneCroissant_nbcaract(t, n);
            printf("\n\t PREPARATION DE L'AFFICHAGE...\n");
            printf("Tableau trie\n");
            afficheTab(t, true);
            printf("***************************************************************\n");
            printf("***********************TRI PEIGNE CROISSANT********************\n");
            printf("***************************************************************\n");
            break;

        case 6 :
            TriPeigneDecroissant_nbcaract(t, n);
            printf("\n\t PREPARATION DE L'AFFICHAGE...\n");
            printf("Tableau trie\n");
            afficheTab(t, true);
            printf("***************************************************************\n");
            printf("*********************TRI PEIGNE DECROISSANT********************\n");
            printf("***************************************************************\n");
            break;

        case 7:
            
            printf("*****ETAPE 1*****\n");
            TriRapideCroissant_nbcarac(t, 0, MAX-1);
            printf("*****ETAPE 2*****\n");
            separation_Rapide_croissant(t);
            printf("\n\t PREPARATION DE L'AFFICHAGE...\n");
            printf("Tableau trie\n");
            afficheTab(t, true);
            printf("***************************************************************\n");
            printf("***********************TRI RAPIDE CROISSANT********************\n");
            printf("***************************************************************\n");
            break;

        case 8:
            
            printf("*****ETAPE 1*****\n");
            TriRapideDecroissant_nbcarac(t, 0, MAX-1);
            printf("*****ETAPE 2*****\n");
            separation_Rapide_Decroissant(t);
            printf("\n\t PREPARATION DE L'AFFICHAGE...\n");
            printf("Tableau trie\n");
            afficheTab(t, true);
            printf("***************************************************************\n");
            printf("*********************TRI RAPIDE DECROISSANT********************\n");
            printf("***************************************************************\n");
            break;
    }
    clock_t endSort=clock();
    clock_t endAll=clock();
    double timeSort=(endSort-beginSort)*1.0/CLOCKS_PER_SEC;
    double timeAll=(endAll-beginAll)*1.0/CLOCKS_PER_SEC;
    printf("Temps CPU du tri : %f secondes\n", timeAll);
    printf("Nombre de permutations : %d\n", compPerm);
    printf("Nombre de Comparaisons : %d", compComp);
    printf("\n");

    return 0;
}

void initTab(t_char t){

    int ligne, caract, nbCaractTemp;

    for (ligne=0; ligne<MAX; ligne++){
        nbCaractTemp=(rand()%(NBCARACTERE-5+1)+5);
        for(caract=0; caract<nbCaractTemp; caract++){
            t[ligne][caract]=(rand()%(122-97+1)+97);
        }
        if(nbCaractTemp<=NBCARACTERE){
            for(; caract<=NBCARACTERE; caract++){
                t[ligne][caract]='\0';
            }
        }
    }
}

void echange (char a[NBCARACTERE+1], char b[NBCARACTERE+1]){
    char temp[NBCARACTERE+1];
    if(strcmp(a,b)!=0){
        strcpy(temp,a);
        strcpy(a,b);
        strcpy(b,temp);

        compPerm++;
    }
  
}

void afficheTab(t_char tab, bool trie){
    int ligne;
    ligne=0;
    if(!trie){
        for(ligne=0; ligne<MAX; ligne++){
            printf("%s\t", tab[ligne]);
        }
        printf("\n");
    }else{
        for(ligne=0; ligne<MAX; ligne++){
            if(strlen(tab[ligne])!=strlen(tab[ligne-1])){
                printf("\n");
                printf("chaines a %lu caracteres :\n", strlen(tab[ligne]));
                printf("\n");
            }
            printf("%s", tab[ligne]);
            printf("\n");
        }
    }
}

/**************************************************************
************************TRI A BULLE CROISSANT******************
***************************************************************/

void Tri_bulle_Croissant_nbCaract(t_char t)
{
    int D, d, c;
    bool ordre;
    ordre=false;
    c=0;
    for(D=0; D<MAX-1; D++){
        for(d=0; d<MAX-1-D; d++){
            while(ordre==false && c<NBCARACTERE){
                    if(strlen(t[d])>strlen(t[d+1])){
                        echange(t[d], t[d+1]);
                        ordre=true;
                    }else if(strlen(t[d]) <= strlen(t[d+1])){
                        ordre=true;
                    }compComp++;
            }
        c=0;
        ordre=false;
        }
    }
    Tri_bulle_Croissant_alpha(t);
}

void Tri_bulle_Croissant_alpha(t_char t)
{
    int D, d, c;
    bool ordre;
    ordre=false;
    c=0;
    for(D=0; D<MAX-1; D++){
        for(d=0; d<MAX-1-D; d++){
            if(strlen(t[d]) == strlen(t[d+1])){
                while(ordre==false && c<NBCARACTERE){
                    if(t[d][c]>t[d+1][c]){
                        echange(t[d],t[d+1]);
                        ordre=true;
                    }else if(t[d][c]<t[d+1][c]){
                        ordre=true;
                    }else{
                        c++;
                    }compComp++;
                }
            }
            c=0;
            ordre=false;
        }
    }
}

/**************************************************************
**********************TRI A BULLE DECROISSANT******************
***************************************************************/
void Tri_bulle_Decroissant_nbCaract(t_char t)
{
    int D, d, c;
    bool ordre;
    ordre=false;
    c=0;
    for(D=0; D<MAX-1; D++){
        for(d=0; d<MAX-1-D; d++){
            while(ordre==false && c<NBCARACTERE){
                    if(strlen(t[d])<strlen(t[d+1])){
                        echange(t[d], t[d+1]);
                        ordre=true;
                    }else if(strlen(t[d]) >= strlen(t[d+1])){
                        ordre=true;
                    }compComp++;
            }
        c=0;
        ordre=false;
        }
    }
    Tri_bulle_Decroissant_alpha(t);
}

void Tri_bulle_Decroissant_alpha(t_char t)
{
    int D, d, c;
    bool ordre;
    ordre=false;
    c=0;
    for(D=0; D<MAX-1; D++){
        for(d=0; d<MAX-1-D; d++){
            if(strlen(t[d]) == strlen(t[d+1])){
                while(ordre==false && c<NBCARACTERE){
                    if(t[d][c]<t[d+1][c]){
                        echange(t[d],t[d+1]);
                        ordre=true;
                    }else if(t[d][c]>t[d+1][c]){
                        ordre=true;
                    }else{
                        c++;
                    }compComp++;
                }
            }
            c=0;
            ordre=false;
        }
    }
}

/**************************************************************
************************TRI SHAKER CROISSANT*******************
***************************************************************/
void Tri_Shaker_Croissant_nbCarac(t_char t)
{
    int aller, retour, deb, fin;

    deb=0;
    fin=MAX-1;

    while(fin-deb>0){
        for(aller=deb; aller<fin; aller++){
            if(strlen(t[aller])>strlen(t[aller+1])){
                echange(t[aller], t[aller+1]);
            }compComp++;
        }

        for(retour=fin; retour>deb; retour--){
            if(strlen(t[retour])<strlen(t[retour-1])){
                echange(t[retour], t[retour-1]);
            }compComp++;
        }
        fin-=1;
        deb+=1;
    }
    Tri_Shaker_Croissant_alpha(t);
}

void Tri_Shaker_Croissant_alpha(t_char t)
{
    int aller,retour , deb, fin, caract;
    bool ordre, permut;

    fin= MAX;
    deb=0;
    caract=0;
    ordre=false;

    while(ordre==false){
        ordre=true;

        for(aller=deb; aller<fin-1; aller++){
            permut=false;
            caract=0;
            if(strlen(t[aller])==strlen(t[aller+1])){
                while(permut==false){
                    if(t[aller][caract]> t[aller+1][caract]){
                        echange(t[aller], t[aller+1]);
                        permut=true;
                        ordre=false;
                    }else if(t[aller][caract]==t[aller+1][caract]){
                        caract++;
                    }else{
                        permut=true;
                    }compComp++;
                }
            }
        }

        for(retour=fin; retour<deb; retour--){
            permut=false;
            caract=0;
            if(strlen(t[retour])==strlen(t[retour-1])){
                while(permut==false){
                    if(t[retour][caract]< t[retour-1][caract]){
                        echange(t[retour], t[retour-1]);
                        permut=true;
                        ordre=false;
                    }else if(t[retour][caract]==t[retour-1][caract]){
                        caract++;
                    }else{
                        permut=true;
                    }compComp++;
                }
            }
        }
    }
}

/**************************************************************
**********************TRI SHAKER DECROISSANT*******************
***************************************************************/

void Tri_Shaker_Decroissant_nbCarac(t_char t)
{
    int aller, retour, deb, fin;

    deb=0;
    fin=MAX-1;

    while(fin-deb>0){
        for(aller=deb; aller<fin; aller++){
            if(strlen(t[aller])<strlen(t[aller+1])){
                echange(t[aller], t[aller+1]);
            }else if(strlen(t[aller]) >= strlen(t[aller+1])){
            }compComp++;
        }

        for(retour=fin; retour>deb; retour--){
            if(strlen(t[retour])>strlen(t[retour-1])){
                echange(t[retour], t[retour-1]);
            }else if(strlen(t[retour]) <= strlen(t[retour-1])){
            }compComp++;
        }
        fin-=1;
        deb+=1;
    }
    Tri_Shaker_Decroissant_alpha(t);
}

void Tri_Shaker_Decroissant_alpha(t_char t)
{
    int aller,retour , deb, fin, caract;
    bool ordre, permut;

    fin= MAX;
    deb=0;
    caract=0;
    ordre=false;

    while(ordre==false){
        ordre=true;

        for(aller=deb; aller<fin-1; aller++){
            permut=false;
            caract=0;
            if(strlen(t[aller])==strlen(t[aller+1])){
                while(permut==false){
                    if(t[aller][caract]< t[aller+1][caract]){
                        echange(t[aller], t[aller+1]);
                        permut=true;
                        ordre=false;
                    }else if(t[aller][caract]==t[aller+1][caract]){
                        caract++;
                    }else{
                        permut=true;
                    }compComp++;
                }
            }
        }

        for(retour=fin; retour<deb; retour--){
            permut=false;
            caract=0;
            if(strlen(t[retour])==strlen(t[retour-1])){
                while(permut==false){
                    if(t[retour][caract]> t[retour-1][caract]){
                        echange(t[retour], t[retour-1]);
                        permut=true;
                        ordre=false;
                    }else if(t[retour][caract]==t[retour-1][caract]){
                        caract++;
                    }else{
                        permut=true;
                    }compComp++;
                }
            }
        }
    }
}

/**************************************************************
********************TRI RAPIDE CROISSANT***********************
***************************************************************/

void Division_tableau_Croissant_nbcarac(t_char tab, int deb,int fin, int *pivot){
    int i,j;
    j=deb;
    for(i=deb;i<fin;i++){
        if(strlen(tab[i])<strlen(tab[fin])){
            echange(tab[i],tab[j]);
            j+=1;
        }compComp++;
    }
    echange(tab[j],tab[fin]);
    *pivot=j;
}

void TriRapideCroissant_nbcarac(t_char tab,int deb, int fin){
    int pivot;
    if(deb<fin){
        Division_tableau_Croissant_nbcarac(tab,deb,fin,&pivot);
        TriRapideCroissant_nbcarac(tab,deb,(pivot-1));
        TriRapideCroissant_nbcarac(tab,(pivot+1),fin);
    }
}

void TriRapideCroissant_alpha(t_char tab,int deb, int fin){
    int pivot;
    if(deb<fin){
        Division_tableau_Croissant_alpha(tab,deb,fin,&pivot);
        TriRapideCroissant_alpha(tab,deb,(pivot-1));
        TriRapideCroissant_alpha(tab,(pivot+1),fin);
    }
}

void Division_tableau_Croissant_alpha(t_char t, int deb,int fin, int *pivot){
    int i,j, caract;
    bool permut;
    j=deb+1;
    for(i=deb;i<fin-1;i++){
        permut= false;
        caract=0;
        if(i!=j){
            while(permut==false){
                if(t[i][caract]> t[j][caract]){
                    echange(t[i], t[j]);
                    permut=true;
                }else if(t[i][caract]==t[j][caract]){
                    caract++;
                }else{
                    permut=true;
                }
            }
        j+=1;
        }
        
    }
    echange(t[j],t[fin]);
    *pivot=j;
}

void separation_Rapide_croissant(t_char tab){
    int deb, fin, indice;
    indice= 0;
    deb=0;
    while (indice<MAX){
        if (strlen(tab[deb])==strlen(tab[indice])){
            indice++;
        }else{
            TriRapideCroissant_alpha(tab,deb, indice);
            deb=indice;
        }
    }
    if(indice==MAX){
        TriRapideCroissant_alpha(tab,deb, indice);
    }
}

/**************************************************************
******************TRI RAPIDE DECROISSANT***********************
***************************************************************/

void Division_tableau_Decroissant_nbcarac(t_char tab, int deb,int fin, int *pivot){
    int i,j;
    j=deb;
    for(i=deb;i<fin;i++){
        if(strlen(tab[i])>strlen(tab[fin])){
            echange(tab[i],tab[j]);
            j+=1;
        }compComp++;
    }
    echange(tab[j],tab[fin]);
    *pivot=j;
}

void TriRapideDecroissant_nbcarac(t_char tab,int deb, int fin){
    int pivot;
    if(deb<fin){
        Division_tableau_Decroissant_nbcarac(tab,deb,fin,&pivot);
        TriRapideDecroissant_nbcarac(tab,deb,(pivot-1));
        TriRapideDecroissant_nbcarac(tab,(pivot+1),fin);
    }
}

void TriRapideDecroissant_alpha(t_char tab,int deb, int fin){
    int pivot;
    if(deb<fin){
        Division_tableau_Decroissant_alpha(tab,deb,fin,&pivot);
        TriRapideDecroissant_alpha(tab,deb,(pivot-1));
        TriRapideDecroissant_alpha(tab,(pivot+1),fin);
    }
}

void Division_tableau_Decroissant_alpha(t_char t, int deb,int fin, int *pivot){
    int i,j, caract;
    bool permut;
    j=deb+1;
    for(i=deb;i<fin-1;i++){
        permut= false;
        caract=0;
        if(i!=j){
            while(permut==false){
                if(t[i][caract]< t[j][caract]){
                    echange(t[i], t[j]);
                    permut=true;
                }else if(t[i][caract]==t[j][caract]){
                    caract++;
                }else{
                    permut=true;
                }
            }
        j+=1;
        }
        
    }
    echange(t[j],t[fin]);
    *pivot=j;
}

void separation_Rapide_Decroissant(t_char tab){
    int deb, fin, indice;
    indice= 0;
    deb=0;
    while (indice<MAX){
        if (strlen(tab[deb])==strlen(tab[indice])){
            indice++;
        }else{
            TriRapideDecroissant_alpha(tab,deb, indice);
            deb=indice;
        }
    }
    if(indice==MAX){
        TriRapideDecroissant_alpha(tab,deb, indice);
    }
}

/**************************************************************
********************TRI PEIGNE GENERAL*************************
***************************************************************/

int div3_TriPeigne(int inter){
    inter/=3;
    if (inter<1) {
        inter=1;
    }
    return inter;
}

void echangeur_TriPeigne(t_char tab, int inter, int i){
    char temp[NBCARACTERE+1];
    strcpy(temp,tab[i]);
    strcpy(tab[i],tab[i+inter]);
    strcpy(tab[i+inter],temp);

    compPerm++;
}
/**************************************************************
********************TRI PEIGNE CROISSANT***********************
***************************************************************/

void blocks_Croissant(t_char tab){
    int deb, fin, indice;
    indice= 0;
    deb=0;
    while (indice<MAX){
        if (strlen(tab[deb])==strlen(tab[indice])){
            indice++;
        }else{
            TriPeigneCroissant_alpha(tab, (indice-deb), deb, indice);
            deb=indice;
        }
    }
    if(indice==MAX){
        TriPeigneCroissant_alpha(tab, (indice-deb), deb, indice);
    }
}

void TriPeigneCroissant_nbcaract(t_char tab, int inter){
    int i;
    bool swap=true;
    while (inter!=1 || swap==true) {
        inter = div3_TriPeigne(inter);
        swap=false;
        for (i=0;i<MAX-inter;i++) {
            if (strlen(tab[i])>strlen(tab[i+inter])) {
                echangeur_TriPeigne(tab, inter, i);
                swap=true;
            }
        }
    }
    blocks_Croissant(tab);
}

void TriPeigneCroissant_alpha(t_char tab, int inter, int deb, int fin){
    int c, i, passe;
    bool swap, ordre;
    i=deb;
    swap=true;
    passe=0;
    while (passe<(fin-deb)) {
        inter = div3_TriPeigne(inter);
        swap=false;
        for (i=deb;i<fin-inter;i++) {

            c=0;
            ordre=false;
            if (strlen(tab[i])==strlen(tab[i+inter])){
                while(ordre==false && c<NBCARACTERE){
                    if(tab[i][c]>tab[i+inter][c]){
                        echangeur_TriPeigne(tab, inter, i);
                        ordre=true;
                    }else if(tab[i][c]<tab[i+inter][c]){
                        ordre=true;
                    }else if(tab[i][c]==tab[i+inter][c]){
                        c++;
                    }compComp++;
                }
            }
        }
        passe++;
    }
}

/**************************************************************
******************TRI PEIGNE DECROISSANT***********************
***************************************************************/

void blocks_Decroissant(t_char tab){
    int deb, fin, indice;
    indice= 0;
    deb=0;
    while (indice<MAX){
        if (strlen(tab[deb])==strlen(tab[indice])){
            indice++;
        }else{
            TriPeigneDecroissant_alpha(tab, (indice-deb), deb, indice);
            deb=indice;
        }
    }
    if(indice==MAX){
        TriPeigneDecroissant_alpha(tab, (indice-deb), deb, indice);
    }
}

void TriPeigneDecroissant_nbcaract(t_char tab, int inter){
    int i;
    bool swap=true;
    while (inter!=1 || swap==true) {
        inter = div3_TriPeigne(inter);
        swap=false;
        for (i=0;i<MAX-inter;i++) {
            if (strlen(tab[i])<strlen(tab[i+inter])) {
                echangeur_TriPeigne(tab, inter, i);
                swap=true;
            }
        }
    }
    blocks_Decroissant(tab);
}

void TriPeigneDecroissant_alpha(t_char tab, int inter, int deb, int fin){
    int c, i, passe;
    bool swap, ordre;
    i=deb;
    swap=true;
    passe=0;
    while (passe<(fin-deb)) {
        inter = div3_TriPeigne(inter);
        swap=false;
        for (i=deb;i<fin-inter;i++) {
            c=0;
            ordre=false;
            if (strlen(tab[i])==strlen(tab[i+inter])){
                while(ordre==false && c<NBCARACTERE){
                    if(tab[i][c]<tab[i+inter][c]){
                        echangeur_TriPeigne(tab, inter, i);
                        ordre=true;
                    }else if(tab[i][c]>tab[i+inter][c]){
                        ordre=true;
                    }else if(tab[i][c]==tab[i+inter][c]){
                        c++;
                    }compComp++;
                }
            }
        }
        passe++;
    }
}