#define _CRT_SECURE_NO_WARNINGS
#include "film.h"
#include <fstream>
#include <cstring>
using namespace std;

FilmDatabase::FilmDatabase() : count(0), nextId(1) {}

const char* MEDIA_TYPES[] = { "DVD", "Blu-Ray", "VHS" };

int FilmDatabase::findIndexById(int id) {
    for (int i = 0; i < count; i++) {
        if (films[i].id == id) {
            return i;
        }
    }
    return -1;
}

bool FilmDatabase::addFilm(const Film& film) {
    if (count >= MAX_RECORDS) return false;
    films[count] = film;
    films[count].id = nextId++;
    count++;
    return true;
}

Film* FilmDatabase::getFilmById(int id) {
    int index = findIndexById(id);
    return (index != -1) ? &films[index] : nullptr;
}

int FilmDatabase::getCount() const { return count; }

Film* FilmDatabase::getFilmByIndex(int index) {
    return (index >= 0 && index < count) ? &films[index] : nullptr;
}

bool FilmDatabase::removeFilm(int id) {
    int index = findIndexById(id);
    if (index == -1) return false;

    for (int i = index; i < count - 1; i++) {
        films[i] = films[i + 1];
    }
    count--;
    return true;
}

void FilmDatabase::sortByTitle() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(films[j].title, films[j + 1].title) > 0) {
                ::swap(films[j], films[j + 1]);
            }
        }
    }
}

void FilmDatabase::sortByYear() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (films[j].year > films[j + 1].year) {
                ::swap(films[j], films[j + 1]);
            }
        }
    }
}

void FilmDatabase::sortByPrice() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (films[j].price > films[j + 1].price) {
                ::swap(films[j], films[j + 1]);
            }
        }
    }
}

void FilmDatabase::sortByAvailability() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (!films[j].isAvailable && films[j + 1].isAvailable) {
                ::swap(films[j], films[j + 1]);
            }
        }
    }
}

bool FilmDatabase::loadFromFile(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    count = 0;
    nextId = 1;
    char line[256];
    int maxId = 0;

    while (file.getline(line, sizeof(line))) {
        Film film;
        char* token = strtok(line, "|");

        if (token) film.id = atoi(token);
        token = strtok(nullptr, "|");
        if (token) strncpy(film.title, token, MAX_TITLE_LENGTH);
        token = strtok(nullptr, "|");
        if (token) film.year = atoi(token);
        token = strtok(nullptr, "|");
        if (token) strncpy(film.mediaType, token, MAX_MEDIA_TYPE_LENGTH);
        token = strtok(nullptr, "|");
        if (token) film.isAvailable = atoi(token) == 1;
        token = strtok(nullptr, "|");
        if (token) film.price = atof(token);

        if (count < MAX_RECORDS) {
            films[count] = film;
            count++;
            if (film.id >= maxId) {
                maxId = film.id + 1;
            }
        }
    }

    nextId = maxId;
    file.close();
    return true;
}

bool FilmDatabase::saveToFile(const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    for (int i = 0; i < count; i++) {
        file << films[i].id << "|" << films[i].title << "|" << films[i].year << "|"
            << films[i].mediaType << "|" << (films[i].isAvailable ? 1 : 0) << "|"
            << films[i].price << "\n";
    }

    file.close();
    return true;
}
