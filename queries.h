/**
    @file queries.h
    @brief This file contains function declarations for performing various database queries related to users, events, sessions, tickets, places, plats, and films.
    It includes the MySQL C API library and several header files that define data structures used in the function signatures.
    The function declarations include inUser, insertUser, getUsers, delUser, inEvent, insertEvent, getEvents, updateEvent, delEvent, getEventSessions, insertPlace, insertPlat, inSession,
    insertSession, delSession, insertTicket, insertFilm, and getFilmsBySessionId.
    These functions allow users to interact with the database by registering, creating, modifying, and deleting events, sessions, and tickets.
*/
#ifndef QUERIES_H
#define QUERIES_H

#include <mysql/mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "string.h"
#include "functions.h"

User* inUser();
User* insertUser(MYSQL * db, User* user);
void getUsers(MYSQL* db);
void delUser(MYSQL* db, int id);


Event* inEvent ();
Event* insertEvent(MYSQL * db, Event* event);
void getEvents(MYSQL* db);
void updateEvent(MYSQL* db, Event* event);
void delEvent(MYSQL* db, int id);
void getEventSessions(MYSQL* db, int event_id);


Place* insertPlace(MYSQL* db, Event* event, Place* place);
Plat* insertPlat(MYSQL * db, Event* event, Plat* plat);

Session* inSession();
Session* insertSession(MYSQL* db, Session* session, int eve_id);
void delSession(MYSQL* db, int id);

Ticket* insertTicket(MYSQL* db, Ticket* ticket);
Film* insertFilm(MYSQL* db, Film* film);

Film ** getFilmsBySessionId(MYSQL* db, int id);


#endif