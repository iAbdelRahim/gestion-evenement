/**
    @file user.h
    @brief Fichier d'en-tête pour les fonctions et structures liées à l'utilisateur.
    Ce fichier contient les déclarations de fonctions qui gèrent les opérations liées à l'utilisateur, telles que la récupération de films, la réservation de billets, l'affichage de billets et la création de mariages. Il inclut également les en-têtes et les structures nécessaires.
*/

#ifndef USER_H
#define USER_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "queries.h"

int genererNumeroTicket();
void getFilms(MYSQL* db);
int existeFilm(MYSQL* db, int id);
void reserverFilm(MYSQL* db, int userId);
void afficherTickets(MYSQL* db, int user_id);
void getUserEvents(MYSQL* db, int userId);
void creerMariage(MYSQL* db);
void userInterface(MYSQL * db, User* user);

#endif