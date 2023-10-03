/**
    @file functions.h
    @brief Définition des fonctions principales du programme de gestion d'événements.
    Ce fichier contient la définition des fonctions principales du programme de gestion d'événements.
    Ces fonctions sont responsables de la création et de la gestion des événements, des sessions,
    des billets, des plats et des places.
    Il contient également une fonction permettant de lier des films à une session.
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "struct.h"
#include <stdio.h>

/**
    @brief Ajoute un plat à un événement.
    @param plat Le plat à ajouter.
    @param event L'événement auquel ajouter le plat.
    @return L'événement modifié.
*/
Event * platEvent(Plat * plat, Event * event);

/**
    @brief Ajoute une place à un événement.
    @param place La place à ajouter.
    @param event L'événement auquel ajouter la place.
    @return L'événement modifié.
*/
Event * placeEvent(Place * place, Event * event);

/**
    @brief Ajoute un billet à un événement.
    @param ticket Le billet à ajouter.
    @param event L'événement auquel ajouter le billet.
    @return L'événement modifié.
*/
Event * ticketEvent(Ticket * ticket, Event * event);

/**
    @brief Ajoute un film à une session.
    @param film Le film à ajouter.
    @param session La session à laquelle ajouter le film.
    @return La session modifiée.
*/
Session * filmSession(Film * film, Session * session);

/**
    @brief Ajoute une session à un événement.
    @param session La session à ajouter.
    @param event L'événement auquel ajouter la session.
    @return L'événement modifié.
*/
Event * sessionEvent(Session * session, Event * event);

/**

    @brief Lie des films à une session.
    @param session La session à laquelle lier les films.
    @param nbFilms Le nombre de films disponibles.
    @param films Un tableau contenant les films disponibles.
*/

void linkFilmsToSession(Session * session, int nbFilms, Film* films[100]);

#endif