#include "queries.h"

User* inUser () {
    User* user = malloc(sizeof(User));
    printf("Entrez le nom : ");
    scanf("%s", user->fName);
    while(getchar() != '\n');
    
    printf("Entrez le prénom : ");
    scanf("%s", user->lName);
    while(getchar() != '\n');
    
    printf("Entrez le rôle : ");
    scanf("%s", user->role);
    while(getchar() != '\n');
    
    printf("Entrez l'email : ");
    scanf("%s", user->email);
    while(getchar() != '\n');
    
    printf("Entrez le mot de passe : ");
    scanf("%s", user->password);
    while(getchar() != '\n');

    user->id = -1;

    return user;
}
User* insertUser(MYSQL * db, User* user) {
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    int i = 0;
    char query[1500];
    sprintf(query, "insert into users (fist_name, last_name, role, email, password) values(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\")", user->fName, user->lName, user->role, user->email, user->password);
    mysql_query(db, query);
    char query2[]="select last_insert_id()";
    mysql_query(db, query2);
    result = mysql_store_result(db);
    row = mysql_fetch_row(result);

    user->id = atoi(row[0]);

    return user;
}
void getUsers(MYSQL* db) {
    MYSQL_RES* result;
    MYSQL_ROW row;
    int id;
    char nom[50], prenom[50], email[50], password[50];

    printf("\n----- Liste des utilisateurs -----");

    // Exécution de la requête SQL pour obtenir la liste des utilisateurs
    if (mysql_query(db, "SELECT * FROM users")) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    result = mysql_use_result(db);

    // Affichage des résultats de la requête
    printf("\n\nID\tNom\tPrénom\tEmail\t");
    while ((row = mysql_fetch_row(result)) != NULL) {
        id = atoi(row[0]);
        strcpy(nom, row[1]);
        strcpy(prenom, row[2]);
        strcpy(email, row[3]);

        printf("\n%d\t%s\t%s\t%s\t", id, nom, prenom, email);
    }

    mysql_free_result(result);
    printf("\n");
}


Event* inEvent () {
    Event* event = malloc(sizeof(Event));
    printf("Entrez le label : ");
    scanf("%s", event->label);
    while(getchar() != '\n');

    printf("Entrez le lieu : ");
    scanf("%s", event->lieu);
    while(getchar() != '\n');
    
    printf("Entrez le type : ");
    scanf("%s", event->type);
    while(getchar() != '\n');
    
    printf("Entrez la date (AAAA-MM-JJ): ");
    scanf("%s", event->date);
    while(getchar() != '\n');

    event->id = -1;

    return event;
}
Event* insertEvent(MYSQL * db, Event* event) {
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    int i = 0;
    char query[1500];
    sprintf(query, "insert into event (type, place, date_event, label) values(\"%s\", \"%s\", \"%s\", \"%s\")", event->type, event->lieu, event->date, event->label);
    mysql_query(db, query);
    char query2[]="select last_insert_id()";
    mysql_query(db, query2);
    result = mysql_store_result(db);
    row = mysql_fetch_row(result);

    event->id = atoi(row[0]);
    event->nPlat = 0;
    event->nPlace = 0;
    event->nTicket = 0;


    return event;
}
void getEvents(MYSQL* db) {
    MYSQL_RES* result;
    MYSQL_ROW row;
    int id;
    char type[50], place[50], date_event[50], label[100];

    printf("\n----- Liste des événements -----");

    if (mysql_query(db, "SELECT * FROM event")) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    result = mysql_use_result(db);

    printf("\n\nID\tType\tPlace\tDate\tLabel");
    while ((row = mysql_fetch_row(result)) != NULL) {
        id = atoi(row[0]);
        strcpy(type, row[1]);
        strcpy(place, row[2]);
        strcpy(date_event, row[3]);
        strcpy(label, row[4]);

        printf("\n%d\t%s\t%s\t%s\t%s", id, type, place, date_event, label);
    }

    mysql_free_result(result);
    printf("\n");
}
void getEventSessions(MYSQL* db, int event_id) {
    MYSQL_RES* result;
    MYSQL_ROW row;
    int id;
    char name[50], date[50];

    printf("\n----- Liste des sessions pour l'événement %d -----", event_id);

    char query[100];
    sprintf(query, "SELECT * FROM sessions WHERE eve_id=%d", event_id);
    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    result = mysql_use_result(db);

    printf("\n\nID\tNom\tDate\t");
    while ((row = mysql_fetch_row(result)) != NULL) {
        id = atoi(row[0]);
        strcpy(name, row[2]);
        strcpy(date, row[3]);

        printf("\n%d\t%s\t%s\t", id, name, date);
    }

    mysql_free_result(result);
    printf("\n");
}


Plat* insertPlat(MYSQL * db, Event* event, Plat* plat) {
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    int i = 0;
    char query[1500];
    sprintf(query, "insert into plat (eve_id, label) values(%d, \"%s\")", event->id, plat->label);
    mysql_query(db, query);
    char query2[]="select last_insert_id()";
    mysql_query(db, query2);
    result = mysql_store_result(db);
    row = mysql_fetch_row(result);

    plat->id = atoi(row[0]);

    platEvent(plat, event);

    return plat;
}

Place* insertPlace(MYSQL* db, Event* event, Place* place) {
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    char query[1500];
    sprintf(query, "INSERT INTO place (eve_id, client_id) VALUES (%d, %d)", place->user->id, place->event->id);
    mysql_query(db, query);
    char query2[]="SELECT last_insert_id()";
    mysql_query(db, query2);
    result = mysql_store_result(db);
    row = mysql_fetch_row(result);
    place->id = atoi(row[0]);

    placeEvent(place, event);

    return place;
}


Session* inSession() {
    Session* session = malloc(sizeof(Session));
    printf("Entrez le nom de la session : ");
    scanf("%s", session->name);
    while(getchar() != '\n');


    printf("Entrez la date de la session (AAAA-MM-JJ) : ");
    scanf("%s", session->date);
    while(getchar() != '\n');

    session->nFilm = 0;
    session->event = NULL;

    session->id = -1;

    return session;
}
Session* insertSession(MYSQL* db, Session* session, int eve_id) {
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    char query[1000];
    sprintf(query, "INSERT INTO session (eve_id, name, date_session) VALUES ( %d, \"%s\", \"%s\")", eve_id, session->name, session->date);
    mysql_query(db, query);
    char query2[]="SELECT last_insert_id()";
    mysql_query(db, query2);
    result = mysql_store_result(db);
    row = mysql_fetch_row(result);
    session->id = atoi(row[0]);
    return session;
}


Film* insertFilm(MYSQL* db, Film* film) {
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    char query[2000];
    sprintf(query, "INSERT INTO film (ses_id, titre, description, auteur) VALUES (%d, \"%s\", \"%s\", \"%s\")", film->session->id, film->title, film->desc, film->author);
    mysql_query(db, query);
    char query2[]="SELECT last_insert_id()";
    mysql_query(db, query2);
    result = mysql_store_result(db);
    row = mysql_fetch_row(result);
    film->id = atoi(row[0]);
    return film;
}

Ticket* insertTicket(MYSQL* db, Ticket* ticket) {
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    char query[2000];
    sprintf(query, "INSERT INTO ticket (cl_id, eve_id, date) VALUES (%d, %d,\"%s\")", ticket->user->id, ticket->event->id, ticket->date);
    mysql_query(db, query);
    char query2[]="SELECT last_insert_id()";
    mysql_query(db, query2);
    result = mysql_store_result(db);
    row = mysql_fetch_row(result);
    ticket->id = atoi(row[0]);
    return ticket;
}


// Update
void updateEvent(MYSQL* db, Event* event) {
    char requete[255];

    sprintf(requete, "UPDATE event SET type = '%s', place = '%s', date_event = '%s', label = '%s' WHERE id = %d",
            event->type, event->lieu, event->date, event->label, event->id);

    if (mysql_query(db, requete)) {
        printf("\nErreur lors de la mise à jour de l'événement : %s\n", mysql_error(db));
        return;
    }

    printf("\nL'événement a été mis à jour avec succès.\n");
}


// Supprimer
void delUser(MYSQL* db, int id) {
    char requete[255];
    MYSQL_RES* result;
    MYSQL_ROW row;

    sprintf(requete, "DELETE FROM users WHERE id = %d", id);

    if (mysql_query(db, requete)) {
        printf("\nErreur lors de la suppression de l'utilisateur : %s\n", mysql_error(db));
        return;
    }

    printf("\nL'utilisateur a été supprimé avec succès.\n");
}

void delEvent(MYSQL* db, int id) {
    char requete[255];
    MYSQL_RES* result;
    MYSQL_ROW row;

    sprintf(requete, "DELETE FROM event WHERE id = %d", id);

    if (mysql_query(db, requete)) {
        printf("\nErreur lors de la suppression de l'utilisateur : %s\n", mysql_error(db));
        return;
    }

    printf("\nL'event a été supprimé avec succès.\n");
}

void delSession(MYSQL* db, int id) {
    char requete[255];
    MYSQL_RES* result;
    MYSQL_ROW row;

    sprintf(requete, "DELETE FROM session WHERE id = %d", id);

    if (mysql_query(db, requete)) {
        printf("\nErreur lors de la suppression de l'utilisateur : %s\n", mysql_error(db));
        return;
    }

    printf("\nL'event a été supprimé avec succès.\n");
}

