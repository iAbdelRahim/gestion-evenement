#include "user.h"

/**
    @brief Génère un numéro de ticket aléatoire entre 1000 et 9999 inclus.
    @return le numéro de ticket généré
*/
int genererNumeroTicket() {
    srand(time(NULL)); // Initialisation de la seed pour rand() avec le temps courant
    int min = 1000; // Valeur minimale du numéro de ticket
    int max = 9999; // Valeur maximale du numéro de ticket
    int numTicket = rand() % (max - min + 1) + min; // Génération aléatoire du numéro de ticket entre min et max inclus
    return numTicket;
}

/**
    @brief Affiche la liste des films disponibles dans la base de données et leurs détails.
    @param db un pointeur vers la base de données MySQL
*/
void getFilms(MYSQL* db) {
    MYSQL_RES* result;
    MYSQL_ROW row;
    Film film;

    printf("\n----- Liste des films disponibles -----\n");
    printf("\nID\tTitre\t\t\tRealisateur\tGenre\t\tAnnee\tDuree (min)\n");
    printf("---------------------------------------------------------------------------------\n");

    if (mysql_query(db, "SELECT * FROM film")) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    result = mysql_use_result(db);

    while ((row = mysql_fetch_row(result)) != NULL) {
        film.id = atoi(row[1]);
        strcpy(film.title, row[2]);
        strcpy(film.author, row[4]);
        strcpy(film.desc, row[3]);

        printf("%d\t%-25s %-15s %-15s\n", film.id, film.title, film.author, film.desc);
    }

    mysql_free_result(result);
}

/**
    @brief Vérifie si un film donné existe dans la base de données.
    @param db un pointeur vers la base de données MySQL
    @param id l'identifiant du film à rechercher
    @return 1 si le film existe, 0 sinon
*/
int existeFilm(MYSQL* db, int id) {
    MYSQL_RES* result;
    MYSQL_ROW row;
    int count = 0;

    char query[100];
    sprintf(query, "SELECT COUNT(*) FROM film WHERE id=%d", id);

    // Exécution de la requête SQL pour vérifier si le film existe
    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    result = mysql_use_result(db);
    row = mysql_fetch_row(result);
    count = atoi(row[0]);
    mysql_free_result(result);

    // Si le film existe, renvoie 1, sinon renvoie 0
    return count;
}

/**
    @brief Permet à un utilisateur de réserver un film en entrant son identifiant dans la base de données.
    @param db un pointeur vers la base de données MySQL
    @param userId l'identifiant de l'utilisateur qui souhaite réserver le film
*/
void reserverFilm(MYSQL* db, int userId) {
    printf("Films disponibles:\n");
    getFilms(db);

    int filmId;
    printf("Entrez l'ID du film que vous souhaitez réserver : ");
    scanf("%d", &filmId);

    if (!existeFilm(db, filmId)) {
        printf("Erreur : le film demandé n'existe pas.\n");
        return;
    }

    char query[1000];
    sprintf(query, "INSERT INTO reserver (cl_id, place_id) VALUES (%d, %d)", userId, filmId);
    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    int numeroTicket = genererNumeroTicket();

    sprintf(query, "INSERT INTO ticket (cl_id, eve_id, number) VALUES (%d, %d, %d)", userId, filmId, numeroTicket);
    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    sprintf(query, "INSERT INTO participer (id_user, id_event) VALUES (%d, %d)", userId, filmId);
    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }


    printf("Votre réservation a été enregistrée avec succès.\n");
    printf("Le numéro de votre ticket est : %d\n", numeroTicket);
}

/**
    @brief Affiche la liste des tickets de l'utilisateur donné en paramètre.
    @param db Un pointeur vers la structure de la base de données.
    @param user_id L'identifiant de l'utilisateur.
*/
void afficherTickets(MYSQL* db, int user_id) {
    MYSQL_RES* result_tickets;
    MYSQL_ROW row_tickets;
    MYSQL_RES* result_events;
    MYSQL_ROW row_events;
    int id_ticket, id_event, id_user;
    char numero_ticket[50], nom_event[50], type_event[50], date_event[50];

    // Exécution de la requête SQL pour obtenir la liste des tickets de l'utilisateur
    char query_tickets[500];
    sprintf(query_tickets, "SELECT * FROM ticket WHERE user_id=%d", user_id);
    if (mysql_query(db, query_tickets)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }
    result_tickets = mysql_use_result(db);

    // Parcours des résultats de la requête sur les tickets
    printf("\n----- Liste de mes tickets -----\n\n");
    printf("ID\tNuméro\tÉvénement\tType\tDate\n");
    while ((row_tickets = mysql_fetch_row(result_tickets)) != NULL) {
        id_ticket = atoi(row_tickets[0]);
        strcpy(numero_ticket, row_tickets[1]);
        id_event = atoi(row_tickets[2]);
        id_user = atoi(row_tickets[3]);

        // Exécution de la requête SQL pour obtenir les informations de l'événement correspondant
        char query_event[500];
        sprintf(query_event, "SELECT * FROM event WHERE id=%d", id_event);
        if (mysql_query(db, query_event)) {
            fprintf(stderr, "%s\n", mysql_error(db));
            exit(1);
        }
        result_events = mysql_use_result(db);

        // Affichage des résultats de la requête sur l'événement
        while ((row_events = mysql_fetch_row(result_events)) != NULL) {
            strcpy(nom_event, row_events[1]);
            strcpy(type_event, row_events[2]);
            strcpy(date_event, row_events[3]);
        }
        mysql_free_result(result_events);

        printf("%d\t%s\t%s\t%s\t%s\n", id_ticket, numero_ticket, nom_event, type_event, date_event);
    }

    mysql_free_result(result_tickets);
}

/**
    @brief Obtient tous les événements d'un utilisateur à partir de son identifiant.
    @param db Pointeur vers la connexion MySQL.
    @param userId Identifiant de l'utilisateur.
*/
void getUserEvents(MYSQL* db, int userId) {
    MYSQL_RES* result;
    MYSQL_ROW row;
    int eventId;
    char type[50], place[50], date[50], label[50];

    char query[100];
    sprintf(query, "SELECT event.id, type, place, date_event, label FROM event JOIN participer ON event.id = participer.event_id WHERE participer.user_id = %d", userId);
    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    result = mysql_use_result(db);

    // Affichage des résultats de la requête
    printf("\n----- Liste des événements de l'utilisateur -----");
    printf("\n\nID\tType\tLieu\tDate\tLabel");
    while ((row = mysql_fetch_row(result)) != NULL) {
        eventId = atoi(row[0]);
        strcpy(type, row[1]);
        strcpy(place, row[2]);
        strcpy(date, row[3]);
        strcpy(label, row[4]);

        printf("\n%d\t%s\t%s\t%s\t%s", eventId, type, place, date, label);
    }

    mysql_free_result(result);
    printf("\n");
}

/**
    @brief Permet à l'utilisateur de créer un mariage.
    @param db Pointeur vers la connexion MySQL.
*/
void creerMariage(MYSQL* db) {
    char label[50], type[50], place[50], choix[2];
    int jour, mois, annee;
    MYSQL_RES* result;
    MYSQL_ROW row;
    int eve_id, plat_id;
    char nom_plat[50];

    int nb_invit, i, j;

    printf("\n----- Créer un mariage -----");

    printf("\nLabel : ");
    scanf("%s", label);
    printf("Type : mariage");
    strcpy(type, "mariage");
    printf("\nPlace : ");
    scanf("%s", place);
    printf("Date (jj/mm/aaaa) : ");
    scanf("%d/%d/%d", &jour, &mois, &annee);

    char query[300];
    sprintf(query, "INSERT INTO event (type, place, date_event, label) VALUES ('%s', '%s', '%d-%02d-%02d', '%s')", type, place, annee, mois, jour, label);
    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }
    printf("Le mariage a été créé avec succès.");

    sprintf(query, "SELECT LAST_INSERT_ID()");
    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    result = mysql_use_result(db);
    if ((row = mysql_fetch_row(result)) != NULL) {
        eve_id = atoi(row[0]);
    }
    mysql_free_result(result);

    // Ajout de plats au menu
    do {
        printf("\nSouhaitez-vous ajouter un plat au menu (O/N) ? ");
        scanf("%s", choix);

        if (toupper(choix[0]) == 'O') {
            printf("\nNom du plat : ");
            scanf("%s", nom_plat);

            sprintf(query, "INSERT INTO plat (eve_id, label) VALUES (%d, '%s')", eve_id, nom_plat);
            if (mysql_query(db, query)) {
                fprintf(stderr, "%s\n", mysql_error(db));
                exit(1);
            }
            printf("Le plat a été ajouté au menu.");
        }
    } while (toupper(choix[0]) == 'O');

    do {
        printf("\nSouhaitez-vous inviter un utilisateur (O/N) ? ");
        scanf("%s", choix);

        if (toupper(choix[0]) == 'O') {
            getUsers(db);
        
            // Insertion des invités dans la table participer
            int user_id;
            printf("Entrez l'id de l'utilisateur : ");
            scanf("%d", &user_id);

            sprintf(query, "INSERT INTO participer (user_id, event_id) VALUES (%d, %d)", user_id, eve_id);
            if (mysql_query(db, query)) {
                fprintf(stderr, "%s\n", mysql_error(db));
                exit(1);
            }

            printf("L'utilisateur a été invité");
        }
    } while (toupper(choix[0]) == 'O');

}

/**
    @brief Interface utilisateur pour les fonctionnalités.
    @param db Pointeur vers la connexion MySQL.
    @param user Pointeur vers l'utilisateur connecté.
*/
void userInterface(MYSQL * db, User* user) {
    int choice = 0;

    while (choice != 5) {
        printf("\n----- Menu utilisateur -----\n");
        printf("1. Mes tickets\n");
        printf("2. Reserver Film\n");
        printf("3. Organiser un mariage\n");
        printf("4. Programmes de mes événements\n");
        printf("5. Se déconnecter\n");

        printf("\nEntrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                afficherTickets(db, user->id);
                break;
            
            case 2:
                reserverFilm(db, user->id);
                break;
            
            case 3:
                creerMariage(db);
                break;
            
            case 4:
                getUserEvents(db, user->id);
                break;

            case 5:
                printf("\nAu revoir !\n");
                user = NULL;
                break;
            
            default:
                printf("\nChoix invalide. Veuillez réessayer.\n");
                break;
        }
    }
}
