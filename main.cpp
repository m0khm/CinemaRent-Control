#include <iostream>
#include "film.h"
#include "interface.h"
#include <locale.h>
using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");

    FilmDatabase database;

    // грузим существующий файл (если есть)
    if (!database.loadFromFile("films.dat")) {
        cout << "Файл данных не найден. Будет создана новая база.\n";
    }

    UserInterface ui(database);
    ui.run();            // вся работа пользователя

   
    if (!database.saveToFile("films.dat")) {
        cerr << "Не удалось сохранить базу данных в файл films.dat\n";
    }
   

    return 0;
}
