/**
    @file struct.h
    @brief Définit les structures utilisées dans le programme de gestion d'événements.
    Les structures comprennent User, Session, Film, Event, Plat, Place et Ticket.
*/
#ifndef STRUCT_H
#define STRUCT_H

typedef struct user User;
typedef struct session Session;
typedef struct film Film;
typedef struct event Event;
typedef struct plat Plat;
typedef struct place Place;
typedef struct ticket Ticket;

typedef struct place {
    int id;
    User* user;
    Event* event;
} Place;

typedef struct session {
    int id;
    char name[255];
    char date[255];
    int nFilm;
    int * nbSessions;
    Event* event;
    Film ** films;
} Session;

typedef struct film {
    int id;
    char title[255];
    char desc[255];
    char author[255];
    int * nbFilms;
    Session* session;
} Film;

typedef struct event {
    int id;
    char type[255];
    char lieu[255];
    char date[255];
    char label[255];
    int nPlat;
    int nTicket;
    int nPlace;
    int nSession;
    Session** sessions;
    Ticket** tickets;
    Place** places;
    Plat** plats;
} Event;

typedef struct plat {
    int id;
    char label[255];
    Event* event;
    User* user;
} Plat;

typedef struct user {
    int id;
    char fName[255];
    char lName[255];
    char role[255];
    char email[255];
    char password[255];
    Place** places;
    Ticket** tickets;
    Plat** plats;
} User;

typedef struct ticket {
    int id;
    int number;
    char date[255];
    Event* event;
    User* user;
} Ticket;

#endif