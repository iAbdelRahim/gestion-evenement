#include "functions.h"

/**
    @brief Ajoute un plat à un événement
    Cette fonction permet d'ajouter un plat à un événement enregistré.
    @param plat Le plat à ajouter à l'événement
    @param event L'événement concerné
    @return Un pointeur vers l'événement mis à jour avec le nouveau plat ajouté
*/
Event * platEvent(Plat * plat, Event * event) {
    event->plats[event->nPlat] = plat;
    event->nPlat ++;

    plat->event = event;

    return event;
}

/**
    @brief Ajoute une place à un événement
    Cette fonction permet d'ajouter une place à un événement enregistré.
    @param place La place à ajouter à l'événement
    @param event L'événement concerné
    @return Un pointeur vers l'événement mis à jour avec la nouvelle place ajoutée
*/
Event * placeEvent(Place * place, Event * event){
    event->places[event->nPlace] = place;
    event->nPlace++;

    place->event = event;

    return event;
}

/**
    @brief Ajoute un ticket à un événement
    Cette fonction permet d'ajouter un ticket à un événement enregistré.
    @param ticket Le ticket à ajouter à l'événement
    @param event L'événement concerné
    @return Un pointeur vers l'événement mis à jour avec le nouveau ticket ajouté
*/
Event * ticketEvent(Ticket * ticket, Event * event){
    event->tickets[event->nTicket] = ticket;
    event->nTicket++;

    ticket->event = event;

    return event;
}

/**
    @brief Ajoute un film à une session
    Cette fonction permet d'ajouter un film à une session enregistrée.
    @param film Le film à ajouter à la session
    @param session La session concernée
    @return Un pointeur vers la session mise à jour avec le nouveau film ajouté
*/
Session * filmSession(Film * film, Session * session){
    session->films[session->nFilm] = film;
    session->nFilm++;

    film->session = session;
    
    return session;
}

/**
    @brief Ajoute une session à un événement
    Cette fonction permet d'ajouter une session à un événement enregistré.
    @param session La session à ajouter à l'événement
    @param event L'événement concerné
    @return Un pointeur vers l'événement mis à jour avec la nouvelle session ajoutée
*/
Event * sessionEvent(Session * session, Event * event){
    event->sessions[event->nSession] = session;
    event->nSession++;

    session->event = event;
    
    return event;
}

/**
    @brief Ajoute un ticket à un utilisateur
    Cette fonction permet d'ajouter un ticket à un utilisateur enregistré.
    @param ticket Le ticket à ajouter à l'utilisateur
    @param user L'utilisateur concerné
    @return Un pointeur vers l'utilisateur mis à jour avec le nouveau ticket ajouté
*/
User * ticketUser(Ticket * ticket, User * user) {
    user->tickets[user->tickets[0]->event->nTicket] = ticket;
    user->tickets[0]->event->nTicket++;

    ticket->user = user;

    return user;
}

/**
    @brief Ajoute une place à un utilisateur
    Cette fonction permet d'ajouter une place à un utilisateur enregistré.
    @param place La place à ajouter à l'utilisateur
    @param user L'utilisateur concerné
    @return Un pointeur vers l'utilisateur mis à jour avec la nouvelle place ajoutée
*/
User * placeUser(Place * place, User * user) {
    user->places[user->tickets[0]->event->nPlace] = place;
    user->tickets[0]->event->nPlace++;

    place->user = user;

    return user;
}

/**
    @brief Ajoute un plat à un utilisateur
    Cette fonction permet d'ajouter un plat à un utilisateur enregistré.
    @param plat Le plat à ajouter à l'utilisateur
    @param user L'utilisateur concerné
    @return Un pointeur vers l'utilisateur mis à jour avec le nouveau plat ajouté
*/
User * platUser(Plat * plat, User * user) {
    user->plats[user->tickets[0]->event->nPlat] = plat;
    user->tickets[0]->event->nPlat++;

    plat->user = user;

    return user;
}

/**
    @brief Lie des films à une session donnée
    Cette fonction permet de lier des films à une session donnée en demandant à l'utilisateur de sélectionner un film à la fois.
    Une fois un film sélectionné, la fonction vérifie si le film est déjà lié à la session et l'ajoute à la session si ce n'est pas le cas.
    Cette opération est répétée jusqu'à ce que l'utilisateur saisisse 0 pour arrêter.
    @param session La session à laquelle lier les films
    @param nbFilms Le nombre total de films disponibles
    @param films Le tableau de pointeurs de films disponibles

*/
void linkFilmsToSession(Session* session, int nbFilms, Film* films[100]) {
    printf("Liste des films disponibles :\n");
    for(int i = 0; i < nbFilms; i++) {
        printf("%d - %s (%s)\n", films[i]->id, films[i]->title, films[i]->author);
    }

    int choix;
    int nbFilmsAjoutes = 0;
    do {
        printf("Sélectionnez un film à ajouter à la session (0 pour arrêter) : ");
        scanf("%d", &choix);
        while(getchar() != '\n');

        if(choix > 0 && choix <= nbFilms) {
            // Vérifie si le film est déjà lié à la session
            int estLie = 0;
            for(int i = 0; i < session->nFilm; i++) {
                if(session->films[i]->id == choix) {
                    estLie = 1;
                    break;
                }
            }

            // Ajoute le film à la session s'il n'est pas déjà lié
            if(!estLie) {
                Film* film = films[choix-1];
                session->films[nbFilmsAjoutes] = film;
                session->nFilm++;
                film->session = session;
                nbFilmsAjoutes++;
            } else {
                printf("Ce film est déjà lié à la session.\n");
            }
        }
    } while(choix != 0);

    printf("Les films suivants ont été ajoutés à la session :\n");
    for(int i = 0; i < nbFilmsAjoutes; i++) {
        printf("%s\n", session->films[i]->title);
    }
}
