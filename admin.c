#include "admin.h"

/**
    @brief Manage sessions for a specific event
    This function allows the user to manage sessions for a specific event by presenting
    them with a menu of options including adding a new session, deleting a session, or
    returning to the main menu. The function takes a MYSQL database connection and an
    integer eventId as parameters.
    @param db Pointer to a MYSQL database connection
    @param eventId Integer representing the id of the event to manage sessions for
*/
void manageSessions(MYSQL* db, int eventId) {
    int choice = 0;

    while (choice != 3) {
        printf("\n----- Gestion des sessions pour l'événement %d -----\n", eventId);
        printf("1. Ajouter une session\n");
        printf("2. Supprimer une session\n");
        printf("3. Retour au menu principal\n");

        printf("\nEntrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Session * session = inSession();
                insertSession(db, session, eventId);
                break;
            case 2:
                int id;
                getEventSessions(db, eventId);
                printf("Entrez l'id de la session que vous voulez supprimer : ");
                scanf("%d", id);
                delSession(db, id);
                break;
            case 3:
                // Retour au menu principal
                break;
            default:
                printf("\nChoix invalide. Veuillez réessayer.\n");
                break;
        }
    }
}


/**

    @brief Gère les événements en permettant l'ajout, la modification, la suppression et la consultation d'un événement ainsi que la gestion des sessions liées à un événement donné.
    @param db Pointeur vers la base de données MYSQL.
*/
void manageEvent(MYSQL* db) {
    int choix;

    do {
        printf("\n----- Gestion des événements -----");
        printf("\n1. Ajouter un événement");
        printf("\n2. Modifier un événement");
        printf("\n3. Supprimer un événement");
        printf("\n4. Consulter un événement");
        printf("\n0. Quitter");

        printf("\n\nVotre choix : ");
        scanf("%d", &choix);
        int id;
        Event * event;
        switch (choix) {
            case 1:
                printf("\nVous avez choisi d'ajouter un événement.\n");
                event = inEvent();
                insertEvent(db, event);
                break;

            case 2:
                printf("\nVous avez choisi de modifier un événement. Choisissez l'id\n");
                getEvents(db);
                scanf("%d", id);
                printf("\nEntrez les nouvelles informations\n");
                event = inEvent();
                updateEvent(db, event);
                break;

            case 3:
                printf("\nVous avez choisi de supprimer un événement. Choisissez l'id\n");
                getEvents(db);
                scanf("%d", id);
                delEvent(db, id);
                break;

            case 4 :
                printf("\nChoisissez l'id de l'evenement a consulter\n");
                scanf("%d", id);
                getEventSessions(db, id);
                manageSessions(db, id);
                break;

            case 0:
                printf("\nAu revoir !");
                break;

            default:
                printf("\nChoix invalide. Veuillez réessayer.");
                break;
        }
    } while (choix != 0);
}


/**

    @brief Fonction de gestion des utilisateurs
    Cette fonction permet de gérer les utilisateurs de l'application en leur offrant la possibilité de supprimer un utilisateur existant ou d'ajouter un nouvel utilisateur. L'utilisateur peut retourner au tableau de bord principal en entrant "0".
    @param db Un pointeur vers une structure MYSQL qui représente la base de données
    @return Aucune valeur de retour
*/
void manageUser(MYSQL* db) {
    int choix;

    do {
        printf("\n----- Gestion des utilisateurs -----");
        printf("\n1. Supprimer un utilisateur");
        printf("\n2. Ajouter un utilisateur");
        printf("\n0. Retour");

        printf("\n\nVotre choix : ");
        scanf("%d", &choix);

        int id;

        switch (choix) {
            case 1:
                printf("\nVeuillez entrez l'id de l'utilisateur que vous voulez supprimer");
                getUsers(db);
                scanf("%d", id);
                delUser(db, id);
                break;

            case 2:
                printf("\nVous avez choisi Ajouter un utilisateur.\n");
                User* user = inUser();
                insertUser(db, user);
                break;

            case 0:
                printf("\nRetour au tableau de bord.");
                break;

            default:
                printf("\nChoix invalide. Veuillez réessayer.");
                break;
        }

        if (choix != 0) {
            getUsers(db);
        }
    } while (choix != 0);
}


/**
    @brief Gère le tableau de bord principal pour l'application de gestion d'événements
    @param db un pointeur vers la base de données MYSQL à utiliser pour l'application
*/
void dashboard(MYSQL* db) {
    int choix;

    do {
        printf("\n----- Tableau de bord -----");
        printf("\n1. Gestion utilisateurs");
        printf("\n2. Gestion événements");
        printf("\n3. Statistiques");
        printf("\n0. Quitter");

        printf("\n\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                manageUser(db);
                break;

            case 2:
                manageEvent(db);
                break;

            case 3:
                // Ajoutez ici le code pour les statistiques
                break;

            case 0:
                printf("\nAu revoir !");
                break;
            default:
                printf("\nChoix invalide. Veuillez réessayer.");
                break;
        }
    } while (choix != 0);
}
