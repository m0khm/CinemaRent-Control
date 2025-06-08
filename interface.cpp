#define _CRT_SECURE_NO_WARNINGS
#include "interface.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <limits>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX       // отключаем конфликтные макросы min/max
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
/* ------------------------------------------------------------- */

using namespace std;


UserInterface::UserInterface(FilmDatabase& database) : db(database) {
    enableColors();
}

void UserInterface::enableColors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

void UserInterface::clearScreen() {
    system("cls||clear");
}

void UserInterface::waitForInput() {
    cout << COLOR_MAGENTA << "\nНажмите Enter 2 раза для продолжения..." << COLOR_RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

/* -------------------------------------------------------------------------- */
/*                             Заголовок и меню                                */
/* -------------------------------------------------------------------------- */
void UserInterface::printHeader() {
    cout << COLOR_CYAN << "=============================================\n" << COLOR_RESET;
    cout << COLOR_YELLOW << "       CINEMARENT CONTROL - Учёт видеопроката\n" << COLOR_RESET;
    cout << COLOR_CYAN << "=============================================\n" << COLOR_RESET;
}

void UserInterface::printMainMenu() {
    cout << "\n" << COLOR_BOLD << "Главное меню:" << COLOR_RESET << "\n";
    cout << COLOR_GREEN << "1" << COLOR_RESET << ". Добавить фильм\n";
    cout << COLOR_GREEN << "2" << COLOR_RESET << ". Поиск фильма\n";
    cout << COLOR_GREEN << "3" << COLOR_RESET << ". Показать весь каталог\n";
    cout << COLOR_GREEN << "4" << COLOR_RESET << ". Редактировать фильм\n";
    cout << COLOR_GREEN << "5" << COLOR_RESET << ". Удалить фильм\n";
    cout << COLOR_GREEN << "6" << COLOR_RESET << ". Сохранить изменения\n";
    cout << COLOR_BLUE << "9" << COLOR_RESET << ". Открыть документацию\n";
    cout << COLOR_RED << "0" << COLOR_RESET << ". Выход\n";
    cout << COLOR_CYAN << "---------------------------------------------\n" << COLOR_RESET;
    cout << "Выберите действие: ";
}

/* -------------------------------------------------------------------------- */
/*                                  Ввод                                       */
/* -------------------------------------------------------------------------- */
void UserInterface::inputString(const char* prompt, char* buffer, int maxLength) {
    cout << prompt;
    cin.getline(buffer, maxLength);
}

int UserInterface::inputYear() {
    int year;
    cout << "Введите год выпуска (>= " << MIN_YEAR << "): ";
    while (!(cin >> year) || year < MIN_YEAR || year > getCurrentYear()) {
        cout << COLOR_RED << "Некорректный год. Повторите: " << COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return year;
}

void UserInterface::inputMediaType(char* buffer) {
    cout << "Тип носителя:\n";
    for (int i = 0; i < MEDIA_TYPES_COUNT; ++i) {
        cout << i + 1 << ". " << MEDIA_TYPES[i] << "\n";
    }
    int choice;
    cout << "Выберите (1-" << MEDIA_TYPES_COUNT << "): ";
    while (!(cin >> choice) || choice < 1 || choice > MEDIA_TYPES_COUNT) {
        cout << COLOR_RED << "Ошибка. Повторите выбор: " << COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    strncpy(buffer, MEDIA_TYPES[choice - 1], MAX_MEDIA_TYPE_LENGTH);
}

bool UserInterface::inputAvailability() {
    int choice;
    cout << "Фильм доступен? (1 - Да, 0 - Нет): ";
    while (!(cin >> choice) || (choice != 0 && choice != 1)) {
        cout << COLOR_RED << "Введите 1 (Да) или 0 (Нет): " << COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice == 1;
}

double UserInterface::inputPrice() {
    double price;
    cout << "Введите цену (" << MIN_PRICE << " - " << MAX_PRICE << "): ";
    while (!(cin >> price) || price < MIN_PRICE || price > MAX_PRICE) {
        cout << COLOR_RED << "Неверная цена. Повторите: " << COLOR_RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return price;
}

int UserInterface::getCurrentYear() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return now->tm_year + 1900;
}

/* -------------------------------------------------------------------------- */
/*                               Меню действий                                 */
/* -------------------------------------------------------------------------- */
void UserInterface::addFilmMenu() {
    Film film{};
    inputString("Название фильма: ", film.title, MAX_TITLE_LENGTH);
    film.year = inputYear();
    inputMediaType(film.mediaType);
    film.isAvailable = inputAvailability();
    film.price = inputPrice();

    if (db.addFilm(film))
        cout << COLOR_GREEN << "Фильм добавлен!\n" << COLOR_RESET;
    else
        cout << COLOR_RED << "Ошибка: база заполнена.\n" << COLOR_RESET;

    waitForInput();
}

void UserInterface::searchFilmMenu() {
    cout << "Введите ID фильма для поиска: ";
    int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Film* f = db.getFilmById(id);
    if (!f) {
        cout << COLOR_RED << "Фильм не найден.\n" << COLOR_RESET;
    }
    else {
        cout << "\nID: " << f->id << "\n"
            << "Название: " << f->title << "\n"
            << "Год: " << f->year << "\n"
            << "Носитель: " << f->mediaType << "\n"
            << "Доступен: " << (f->isAvailable ? "Да" : "Нет") << "\n"
            << "Цена: " << f->price << "\n";
    }
    waitForInput();
}

void UserInterface::editFilmMenu() {
    cout << "Введите ID фильма для редактирования: ";
    int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Film* f = db.getFilmById(id);
    if (!f) {
        cout << COLOR_RED << "Фильм не найден.\n" << COLOR_RESET;
        waitForInput(); return;
    }
    inputString("Новое название: ", f->title, MAX_TITLE_LENGTH);
    f->year = inputYear();
    inputMediaType(f->mediaType);
    f->isAvailable = inputAvailability();
    f->price = inputPrice();

    cout << COLOR_GREEN << "Фильм обновлён.\n" << COLOR_RESET;
    waitForInput();
}

void UserInterface::deleteFilmMenu() {
    cout << "Введите ID фильма для удаления: ";
    int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (db.removeFilm(id))
        cout << COLOR_GREEN << "Фильм удалён.\n" << COLOR_RESET;
    else
        cout << COLOR_RED << "Фильм не найден.\n" << COLOR_RESET;
    waitForInput();
}

void UserInterface::viewAllFilmsMenu() {
    int total = db.getCount();
    if (total == 0) {
        cout << COLOR_RED << "База фильмов пуста.\n" << COLOR_RESET;
        waitForInput(); return;
    }

    /* --- сортировка --- */
    cout << "\nВыберите сортировку:\n"
        << "1. По названию\n"
        << "2. По году\n"
        << "3. По стоимости\n"
        << "4. По наличию\n"
        << "0. Без сортировки\n"
        << "Выбор: ";
    int sc; cin >> sc; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (sc) {
    case 1: db.sortByTitle();        break;
    case 2: db.sortByYear();         break;
    case 3: db.sortByPrice();        break;
    case 4: db.sortByAvailability(); break;
    default:                         break;
    }

    /* --- вывод таблицы --- */
    cout << "\n" << COLOR_BOLD << "Каталог фильмов:" << COLOR_RESET << "\n";
    cout << COLOR_CYAN << left
        << setw(5) << "ID"
        << setw(30) << "Название"
        << setw(6) << "Год"
        << setw(10) << "Носитель"
        << setw(10) << "Доступен"
        << setw(10) << "Цена" << COLOR_RESET << "\n";

    for (int i = 0; i < total; ++i) {
        Film* f = db.getFilmByIndex(i);
        cout << setw(5) << f->id
            << setw(30) << f->title
            << setw(6) << f->year
            << setw(10) << f->mediaType
            << setw(10) << (f->isAvailable ? (string(COLOR_GREEN) + "Да" + COLOR_RESET)
                : (string(COLOR_RED) + "Нет" + COLOR_RESET))
            << "         "<< f->price << "\n";
    }
    waitForInput();
}

void UserInterface::openDocumentation() {
#if defined(_WIN32) || defined(_WIN64)
    system("start documentation.html");
#elif defined(__APPLE__)
    system("open documentation.html");
#else
    system("xdg-open documentation.html");
#endif
}

/* -------------------------------------------------------------------------- */
/*                                   run                                       */
/* -------------------------------------------------------------------------- */
void UserInterface::run() {
    printHeader();
    while (true) {
        printMainMenu();
        int choice; cin >> choice; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1: addFilmMenu(); break;
        case 2: searchFilmMenu(); break;
        case 3: viewAllFilmsMenu(); break;
        case 4: editFilmMenu(); break;
        case 5: deleteFilmMenu(); break;
        case 6:
            if (db.saveToFile("films.dat"))
                cout << COLOR_GREEN << "Изменения сохранены.\n" << COLOR_RESET;
            else
                cout << COLOR_RED << "Ошибка при сохранении.\n" << COLOR_RESET;
            waitForInput();
            break;
        case 9: openDocumentation(); waitForInput(); break;
        case 0: return;
        default:
            cout << COLOR_RED << "Неверный выбор. Попробуйте снова.\n" << COLOR_RESET;
            waitForInput();
        }
        clearScreen();
    }
}
