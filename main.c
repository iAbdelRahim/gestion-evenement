/**
    @file main.c
    @brief Ceci est le fichier principal pour le programme de gestion d'événements.
    Ce programme permet aux utilisateurs de se connecter au système, de s'inscrire et d'effectuer diverses actions telles que
    la création, la modification ou la suppression d'événements. Les administrateurs peuvent se connecter pour accéder au tableau de bord et effectuer
    des tâches administratives supplémentaires. Le programme se connecte à une base de données MySQL pour stocker et récupérer des données.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "struct.h"
#include "queries.h"
#include "admin.h"
#include "user.h"

/**
    @brief Permet à un administrateur de se connecter au système
    Invite l'administrateur à entrer son adresse e-mail et son mot de passe. Si les identifiants correspondent aux valeurs codées en dur,
    la fonction appelle la fonction tableau de bord pour afficher le menu administrateur et renvoie 1. Sinon, elle
    affiche un message d'erreur et renvoie 0.
    @param db Un pointeur vers la connexion à la base de données MySQL
    @return 1 si l'administrateur se connecte avec succès, 0 sinone
*/
int connexionAdmin(MYSQL * db) {
    char email[50], password[50];

    printf("Veuillez saisir votre email : ");
    scanf("%s", email);

    printf("Veuillez saisir votre mot de passe : ");
    scanf("%s", password);

    if (strcmp(email, "admin@yond.admin") == 0 && strcmp(password, "admin-adm1n") == 0) {
        dashboard(db);
        return 1;
    } else {
        printf("Erreur des identifiants | Reessayez \n");
        return 0;
    }
}

/**
    @brief Permet à un utilisateur de se connecter au système
    Demande à l'utilisateur de saisir son adresse e-mail et son mot de passe. La fonction construit une requête pour sélectionner l'utilisateur avec l'adresse e-mail et le mot de passe donnés dans la base de données. Si une ligne est retournée, la fonction crée une nouvelle structure User et remplit ses champs avec les données de la ligne, puis affiche un message de succès et renvoie un pointeur vers User. Si aucune ligne n'est retournée, la fonction affiche un message d'erreur et renvoie NULL.
    @param db Un pointeur vers la connexion à la base de données MySQL
    @return Un pointeur vers une structure User si l'utilisateur se connecte avec succès, NULL sinon
*/
User * connexion(MYSQL* db) {
    char email[50], password[50];
    char query[100];
    MYSQL_RES *res;
    MYSQL_ROW row;

    printf("Veuillez saisir votre email : ");
    scanf("%s", email);

    printf("Veuillez saisir votre mot de passe : ");
    scanf("%s", password);

    sprintf(query, "SELECT * FROM users WHERE email='%s' AND password='%s'", email, password);

    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        return 0;
    }

    res = mysql_use_result(db);


    if (res) {
        row = mysql_fetch_row(res);

        if (row) {
            User * user;
            user->id = atoi(row[0]);
            strcpy(user->lName, row[1]);
            strcpy(user->fName, row[2]);
            strcpy(user->email, row[3]);

            printf("Connexion réussie pour l'utilisateur %s\n", email);
            mysql_free_result(res);
            return user;
        }
    }

    printf("Email ou mot de passe incorrect. Veuillez réessayer.\n");

    mysql_free_result(res);

    return NULL;
}

/**
    @brief Fonction principale
    Initialise une connexion à une base de données MySQL, affiche un menu à l'utilisateur et exécute les actions appropriées
    en fonction de l'entrée de l'utilisateur. Le programme continue d'afficher le menu jusqu'à ce que l'utilisateur choisisse de quitter.
    @return 0 en cas d'exécution réussie du programme.
*/
int main() {
 
    MYSQL *db = mysql_init(NULL);

    if(db==NULL){
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    if(mysql_real_connect(db, "localhost", "root", "Azerty123$", "eventDB", 0, NULL, 0)==NULL){
        printf("connexion etablie");
        fprintf(stderr, "%s\n", mysql_error(db));
        mysql_close(db);
        exit(1);
    }

    int choix;
    User * user;

    do {
        printf("\n----- Menu -----");
        printf("\n1. Connexion admin");
        printf("\n2. Connexion");
        printf("\n3. S'inscrire");
        printf("\n0. Quitter");

        printf("\n\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\nVous avez choisi Connexion admin.");
                connexionAdmin(db);
                break;

            case 2:
                printf("\nVous avez choisi Connexion utilisateur.");
                user = connexion(db);
                if (user != NULL) {
                    userInterface(db, user);
                }
                break;

            case 3: 
                user = inUser();
                insertUser(db, user);
                userInterface(db, user);
                break;

            case 0:
                printf("\nAu revoir ! \n");
                break;

            default:
                printf("\nChoix invalide. Veuillez réessayer.");
                break;
        }
    } while (choix != 0);

    return 0;
}
