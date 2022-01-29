#include<stdio.h>
#include<stdlib.h>
#include "fonctions_tableau.h"            //On va se servir des fonctions de la partie précédente pour remplir les lignes de la matrice


/*Fonction permettant d'allouer un tableau à deux dimensions représentant une matrice de dimensions n×n en procédant par adresse
(la valeur de retour sert à tester la bonne exécution)*/

int alloue_matrice(int***M, int taille){
    int** mat_res = (int**) malloc( taille *sizeof(int*));
    for(int i = 0 ; i < taille ; i++){
        alloue_tableau(&mat_res[i],taille);
    }
    *M = mat_res;
    return (*M !=NULL);
}

/*Fonction permettant de désallouer la matrice*/

int desalloue_matrice(int**mat, int taille){
    for(int i = 0 ; i < taille ; i++){
        desalloue_tableau(mat[i]);
    }
    free(mat);
    return(mat==NULL);
}

/*Fonction de remplissage de la matrice avec des entiers aléatoires compris entre 0 et V*/
void remplir_matrice(int** mat, int taille, int V){
    for(int i = 0; i < taille ; i++){
        remplir_tableau(mat[i], taille ,V);
    }
}

/*Fonction d'affichage de la matrice*/
void affiche_matrice(int** mat, int taille){
    for(int i = 0; i < taille ; i++){
        afficher_tableau(mat[i],taille);
        printf("\n");
    }
}

/*Fonction permettant de vérifier que tous les éléments de la matrice mat sont différents*/
/*en O(n^4)*/
int mat_diff_v1(int** mat, int taille){
    int val_courante;
    int val_comparaison;
    int meme_element;
    for(int i1 = 0; i1 < taille ; i1++){
        for(int j1 = 0 ; j1 < taille ; j1++){
            val_courante = mat[i1][j1];
            for (int i2 = 0; i2 < taille; i2++){
                for (int j2 = 0; j2 < taille; j2++){
                    val_comparaison = mat[i2][j2];
                    meme_element = (i1==i2)&&(j1==j2);
                    if ( (val_courante == val_comparaison)&&(!meme_element) ){
                        return 0;
                    }
                }
            }
        }
    } 
    return 1;
}

/*meilleure complexité connaissant V : O(n^2)*/
int mat_diff_v2(int** mat, int taille,int V){
    /*On créé un tableau de taille V qu'on remplit de 0*/
    int* tab_comparaison;
    alloue_tableau(&tab_comparaison,V);
    remplir_tableau(tab_comparaison,V,1);
    
    int val_courante;
    for (int i = 0; i < taille; i++){
        for (int j = 0; j < taille; j++){
            val_courante = mat[i][j];
            if (tab_comparaison[val_courante] != 0){
                return 0;
            }
            tab_comparaison[val_courante] = 1;
        }
    }
    return 1;
}

/*Main permettant comparaison par gnuplot*/
int main(){
    //int V = 1000; //choix 1 : fixer V pour toutes les itérations
    FILE* fichier = fopen("sortie_vitesse.txt","w");
    for (int n=10; n < 10000; n = n+100){
        /*Création de la matrice*/
        int taille = n;
        int V = n*10; //choix 2 : faire varier V selon la taille de la matrice (amène au pire des cas)
        int** mat;
        alloue_matrice(&mat,taille);
        remplir_matrice(mat,taille,V);

        /*Test et comparaison de nos algorithmes*/
        clock_t temps_initial;
        clock_t temps_final;
        double temps_algo1;
        double temps_algo2;

        temps_initial = clock();
        mat_diff_v1(mat,taille);
        temps_final = clock();
        temps_algo1 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

        temps_initial = clock();
        mat_diff_v2(mat,taille,V);
        temps_final = clock();
        temps_algo2 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

        fprintf(fichier,"%d\t",n);
        fprintf(fichier,"%f\t",temps_algo1);
        fprintf(fichier,"%f\n",temps_algo2);
        
        /*Libération de la mémoire*/
        desalloue_matrice(mat,taille);
    }
}


