# CinemaRent Control

## Русская версия

**Первый курс, курсовая работа**  
Язык: C++ (без использования STL)  
Веб-документация: HTML + CSS(внутренние стили) 

### Описание

CinemaRent Control — простая система управления коллекцией фильмов в видеопрокате.  
Реализована на языке C++ с использованием примитивных приёмов ООП (классы, массивы, указатели), без библиотек STL.  
Документация и пользовательский интерфейс — в виде статической HTML-страницы с CSS-стилями.

### Основные возможности

- **Добавление фильма** в базу  
- **Удаление фильма** по его уникальному `id`  
- **Поиск фильма** по `id`  
- **Сортировка** списка фильмов по:
  - названию
  - году выпуска
  - цене
  - наличию в прокате
- **Сохранение** всего каталога в текстовый файл (`films.dat`)  
- **Загрузка** каталога из текстового файла при старте  

### Технологии и особенности

- **C++** 
- Примитивная ООП-модель:
  - класс `Film` — структура записи о фильме  
  - класс `FilmDatabase` — статический массив, методы для работы с записями  
- **Нет STL**:
  - вместо `std::vector` — статический массив `Film films[MAX_RECORDS]`
  - вместо `std::string` — C-строки (`char title[MAX_TITLE_LENGTH]`)
  - ручная сортировка пузырьком вместо `<algorithm>`
- **HTML + CSS** — документация и интерфейс пользователя

### Структура проекта

```
CinemaRent-Control/
├── │
│   ├── main.cpp            
│   ├── film.h
│   ├── helpers.h
│   ├── interface.cpp
│   ├── interface.h        
│   ├── film.cpp            
│   └── films.dat           — база данных
│   ├── documentation.html  — HTML документация
│   
└── README.md               — этот файл
```

### Сборка и запуск

1. Компиляция (на примере g++):  
   ```bash
   cd CinemaRent-Control/src
   g++ -o CinemaRentControl main.cpp film.cpp
   ```
2. Запуск:  
   ```bash
   ./CinemaRentControl
   ```
3. Откройте `docs/documentation.html` в браузере или команда '9' в программе для подробной справки.
   

### Формат файла `films.dat`

Каждая строка — запись фильма, поля через `|`:
```
id|title|year|mediaType|isAvailable|price
```
- `id` — уникальный идентификатор
- `title` — название фильма
- `year` — год выпуска
- `mediaType` — тип носителя (`DVD`, `Blu-Ray`, `VHS`)
- `isAvailable` — доступность (1 = да, 0 = нет)
- `price` — цена проката

### Возможное развитие

- Авторизация пользователей (менеджер/клиент)
- Переход на динамическую память вместо статического массива
- Графический интерфейс (Qt, WinAPI)
- Поддержка форматов JSON/CSV
- Интеграция с СУБД (SQLite, MySQL)

### Автор и контакты

Email: m0khm@yandex.com

---

## English Version

**First-year coursework**  
Language: C++ (no STL)  
Web documentation: HTML + CSS  

### Description

CinemaRent Control is a simple film-rental catalog management system.  
Implemented in C++ using basic OOP constructs (classes, arrays, pointers) without STL.  
User documentation and interface are provided as a static HTML page with CSS.

### Features

- **Add Film** to the database  
- **Remove Film** by its unique `id`  
- **Search Film** by `id`  
- **Sort** film list by:
  - title
  - release year
  - price
  - availability
- **Save** catalog to a text file (`films.dat`)  
- **Load** catalog from the text file at startup

### Technology and Highlights

- **C++**, C++98/C++03 standards  
- Basic OOP:
  - `Film` class — film record structure  
  - `FilmDatabase` class — static array and methods
- **No STL**:
  - static array `Film films[MAX_RECORDS]` instead of `std::vector`
  - C-strings (`char title[MAX_TITLE_LENGTH]`) instead of `std::string`
  - bubble sort instead of `<algorithm>`
- **HTML + CSS** for documentation and UI

### Project Structure

```
CinemaRent-Control/
├── │
│   ├── main.cpp            
│   ├── film.h
│   ├── helpers.h
│   ├── interface.cpp
│   ├── interface.h        
│   ├── film.cpp            
│   └── films.dat           — saved film database file
│   ├── documentation.html  — HTML documentation
│   
└── README.md               — this file
```

### Build & Run

1. Compile (example using g++):  
   ```bash
   cd CinemaRent-Control/src
   g++ -o CinemaRentControl main.cpp film.cpp
   ```
2. Run:  
   ```bash
   ./CinemaRentControl
   ```
3. Open `docs/documentation.html` in your browser or '9' in programm for detailed guide

### `films.dat` Format

Each line is a record with fields separated by `|`:
```
id|title|year|mediaType|isAvailable|price
```
- `id` — unique identifier
- `title` — film title
- `year` — release year
- `mediaType` — media type (`DVD`, `Blu-Ray`, `VHS`)
- `isAvailable` — availability (1 = yes, 0 = no)
- `price` — rental price

### Future Enhancements

- User authentication (manager/client)
- Dynamic memory instead of static arrays
- GUI (Qt, WinAPI)
- Support for JSON/CSV formats
- Integration with databases (SQLite, MySQL)

### Author & Contact

Email: m0khm@yandex.com
