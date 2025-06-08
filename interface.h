#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include "film.h"
#include <string>

class UserInterface {
private:
    FilmDatabase& db;

    /* --- служебные методы --- */
    void enableColors();
    void clearScreen();
    void waitForInput();
    void printHeader();
    void printMainMenu();

    /* --- ввод --- */
    void inputString(const char* prompt, char* buffer, int maxLength);
    int  inputYear();
    void inputMediaType(char* buffer);
    bool inputAvailability();
    double inputPrice();
    int  getCurrentYear();

    /* --- меню и таблицы --- */
    void addFilmMenu();
    void searchFilmMenu();
    void editFilmMenu();
    void deleteFilmMenu();
    void viewAllFilmsMenu();
    void openDocumentation();

public:
    /* --- ANSI‑цвета --- */
    static constexpr const char* COLOR_RESET = "\033[0m";
    static constexpr const char* COLOR_RED = "\033[31m";
    static constexpr const char* COLOR_GREEN = "\033[32m";
    static constexpr const char* COLOR_YELLOW = "\033[33m";
    static constexpr const char* COLOR_BLUE = "\033[34m";
    static constexpr const char* COLOR_MAGENTA = "\033[35m";
    static constexpr const char* COLOR_CYAN = "\033[36m";
    static constexpr const char* COLOR_WHITE = "\033[37m";
    static constexpr const char* COLOR_BOLD = "\033[1m";

    explicit UserInterface(FilmDatabase& database);
    void run();
};

#endif // INTERFACE_H
