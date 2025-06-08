#pragma once
#ifndef FILM_H
#define FILM_H
using namespace std;
const int MAX_RECORDS = 1000;
const int MAX_TITLE_LENGTH = 100;
const int MAX_MEDIA_TYPE_LENGTH = 10;
extern const char* MEDIA_TYPES[];
const int MEDIA_TYPES_COUNT = 3;
const int MIN_YEAR = 1895;
const double MAX_PRICE = 1000.0;
const double MIN_PRICE = 50.0;

struct Film {
    int id;
    char title[MAX_TITLE_LENGTH];
    int year;
    char mediaType[MAX_MEDIA_TYPE_LENGTH];
    bool isAvailable;
    double price;
};

class FilmDatabase {
private:
    Film films[MAX_RECORDS];
    int count;
    int nextId;

    int findIndexById(int id);

public:
    FilmDatabase();
    bool addFilm(const Film& film);
    Film* getFilmById(int id);
    int getCount() const;
    Film* getFilmByIndex(int index);
    bool removeFilm(int id);
    void sortByTitle();
    void sortByYear();
    void sortByPrice();
    void sortByAvailability();
    bool loadFromFile(const char* filename);
    bool saveToFile(const char* filename);
};

#endif
