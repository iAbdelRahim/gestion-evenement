/**

    @file admin.h
    @brief Fichier d'en-tête contenant les déclarations de fonctions pour la gestion des événements, sessions et utilisateurs
    Ce fichier contient les déclarations de fonctions pour la gestion des événements, sessions et utilisateurs en tant qu'administrateur.
    Ces fonctions sont implémentées dans admin.c et dépendent des fichiers d'en-tête suivants: struct.h, input.h et queries.h.
*/
#ifndef ADMIN_H
#define ADMIN_H

#include "struct.h"
#include "queries.h"

/**
    @brief Gère les sessions d'un événement donné
    Cette fonction permet à l'administrateur de gérer les sessions d'un événement donné, notamment en ajoutant et en supprimant des sessions.
    @param db L'objet de connexion MySQL
    @param eventId L'identifiant de l'événement à gérer
*/
void manageSessions(MYSQL * db, int eventId);

/**

    @brief Gère les événements
    Cette fonction permet à l'administrateur de gérer les événements, y compris leur ajout, modification, suppression et consultation.
    @param db L'objet de connexion MySQL
*/
void manageEvent(MYSQL * db);

/**
    @brief Gère les utilisateurs
    Cette fonction permet à l'administrateur de gérer les utilisateurs, notamment en les ajoutant et en les supprimant.
    @param db L'objet de connexion MySQL
*/
void manageUser(MYSQL * db);

/**
    @brief Affiche le tableau de bord
    Cette fonction affiche le tableau de bord avec les options pour gérer les utilisateurs, les événements et afficher les statistiques.
    @param db L'objet de connexion MySQL
*/
void dashboard(MYSQL * db);

#endif