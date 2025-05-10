#include <windows.h>
#include <sqlext.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

// Функция для проверки формата даты YYYY-MM-DD
// Проверяет, что введённая дата корректна (например, 2023-05-15)
// Возвращает true, если дата правильная, и false, если есть ошибки
bool validateDate(const std::wstring& date) {
    // Проверяем длину строки и наличие символов '-' на нужных позициях
    if (date.length() != 10 || date[4] != L'-' || date[7] != L'-') {
        return false;
    }

    try {
        // Извлекаем год, месяц и день из строки и преобразуем их в числа
        int year = std::stoi(date.substr(0, 4)); // Первые 4 символа — год
        int month = std::stoi(date.substr(5, 2)); // Символы 5-6 — месяц
        int day = std::stoi(date.substr(8, 2));   // Символы 8-9 — день
        // Проверяем, что месяц от 1 до 12
        if (month < 1 || month > 12) return false;
        // Проверяем, что день от 1 до 31
        if (day < 1 || day > 31) return false;
        // Проверяем, что год в разумных пределах (1900–9999)
        if (year < 1900 || year > 9999) return false;
        // Проверяем количество дней в месяце (простая проверка, без учёта високосных годов)
        if (month == 2 && day > 29) return false; // Февраль не может иметь больше 29 дней
        // Апрель, июнь, сентябрь и ноябрь имеют 30 дней
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
        return true; // Дата корректна
    }
    catch (...) {
        return false; 
    }
}

// Функция для отображения ошибок ODBC
// Если что-то идёт не так при работе с базой данных, эта функция покажет, что именно пошло не так
void showSQLError(SQLSMALLINT handleType, SQLHANDLE handle) {
    SQLWCHAR sqlState[1024]; // Буфер для кода состояния ошибки
    SQLWCHAR message[2048];  // Буфер для текста ошибки
    SQLINTEGER nativeError;  // Код ошибки
    SQLSMALLINT textLength;  // Длина текста ошибки
    // Получаем информацию об ошибке
    SQLRETURN ret = SQLGetDiagRecW(handleType, handle, 1, sqlState, &nativeError, message, 2048, &textLength);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        // Выводим текст ошибки и код состояния
        std::wcout << L"ODBC Error: " << message << L" [State: " << sqlState << L"]\n";
    }
}

// Структура для хранения данных одной записи из таблицы Applications
struct Application {
    SQLINTEGER id;          // ID записи (автоинкрементное поле в базе)
    std::wstring appName;   // Название приложения (например, Notepad++)
    double version;         // Версия приложения (например, 8.5)
    std::wstring developer; // Разработчик (например, Notepad++ Team)
    std::wstring releaseDate; // Дата выпуска (например, 2023-05-15)
};

// Функция для подключения к базе данных Access
// Устанавливает соединение с файлом SoftwareDB.accdb
bool connectToDB(SQLHENV& hEnv, SQLHDBC& hDbc) {
    // Создаём окружение (environment) для работы с ODBC
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    // Устанавливаем версию ODBC (используем версию 3)
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    // Создаём дескриптор соединения (connection handle)
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Строка подключения: указываем драйвер и путь к файлу базы данных
    SQLWCHAR connStr[] = L"Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=D:\\1_course\\2_semester\\ОАИП(Основы Алгоритмизации и Программирования)\\лабы_белодед\\код ко второй\\для бд\\SoftwareDB.accdb;";
    SQLWCHAR outConnStr[1024]; // Буфер для строки подключения после выполнения
    SQLSMALLINT outConnStrLen; // Длина строки подключения
    // Выполняем подключение к базе данных
    SQLRETURN ret = SQLDriverConnectW(hDbc, NULL, connStr, SQL_NTS, outConnStr, 1024, &outConnStrLen, SQL_DRIVER_COMPLETE);

    if (!SQL_SUCCEEDED(ret)) {
        // Если подключение не удалось, показываем ошибку
        showSQLError(SQL_HANDLE_DBC, hDbc);
        return false;
    }
    return true; // Подключение успешно
}

// Функция для чтения всех данных из таблицы Applications
// Возвращает вектор записей (Application), которые хранятся в базе
std::vector<Application> readData(SQLHDBC hDbc) {
    std::vector<Application> apps; // Вектор для хранения всех записей
    SQLHSTMT hStmt; // Дескриптор запроса (statement handle)
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt); // Создаём дескриптор запроса

    // Выполняем SQL-запрос: выбираем все столбцы из таблицы Applications
    SQLRETURN ret = SQLExecDirectW(hStmt, (SQLWCHAR*)L"SELECT ID, AppName, Version, Developer, ReleaseDate FROM Applications;", SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        // Переменные для хранения данных из столбцов
        SQLINTEGER id;
        SQLWCHAR appName[101], developer[101], releaseDate[50];
        SQLDOUBLE version;
        SQLLEN idLen, appNameLen, versionLen, developerLen, releaseDateLen;

        // Читаем строки из таблицы по одной
        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            Application app = { 0 }; // Создаём пустую структуру для текущей записи

            // Читаем ID (целочисленное значение)
            ret = SQLGetData(hStmt, 1, SQL_C_LONG, &id, 0, &idLen);
            if (!SQL_SUCCEEDED(ret)) {
                std::wcout << L"Error fetching ID\n";
                showSQLError(SQL_HANDLE_STMT, hStmt);
                break;
            }
            app.id = id;

            // Читаем AppName (строку)
            ret = SQLGetData(hStmt, 2, SQL_C_WCHAR, appName, sizeof(appName), &appNameLen);
            if (!SQL_SUCCEEDED(ret)) {
                std::wcout << L"Error fetching AppName\n";
                showSQLError(SQL_HANDLE_STMT, hStmt);
                break;
            }
            app.appName = appName;

            // Читаем Version (число с плавающей точкой)
            ret = SQLGetData(hStmt, 3, SQL_C_DOUBLE, &version, 0, &versionLen);
            if (!SQL_SUCCEEDED(ret)) {
                std::wcout << L"Error fetching Version\n";
                showSQLError(SQL_HANDLE_STMT, hStmt);
                break;
            }
            app.version = version;

            // Читаем Developer (строку)
            ret = SQLGetData(hStmt, 4, SQL_C_WCHAR, developer, sizeof(developer), &developerLen);
            if (!SQL_SUCCEEDED(ret)) {
                std::wcout << L"Error fetching Developer\n";
                showSQLError(SQL_HANDLE_STMT, hStmt);
                break;
            }
            app.developer = developer;

            // Читаем ReleaseDate (строку)
            ret = SQLGetData(hStmt, 5, SQL_C_WCHAR, releaseDate, sizeof(releaseDate), &releaseDateLen);
            if (!SQL_SUCCEEDED(ret)) {
                std::wcout << L"Error fetching ReleaseDate\n";
                showSQLError(SQL_HANDLE_STMT, hStmt);
                app.releaseDate = L"Invalid Date";
            }
            else {
                // Если дата содержит время (например, 2023-05-15 00:00:00), обрезаем его
                std::wstring dateStr(releaseDate);
                size_t spacePos = dateStr.find(L" ");
                if (spacePos != std::wstring::npos) {
                    app.releaseDate = dateStr.substr(0, spacePos);
                }
                else {
                    app.releaseDate = dateStr;
                }
            }

            apps.push_back(app); // Добавляем запись в вектор
        }
    }
    else {
        showSQLError(SQL_HANDLE_STMT, hStmt); // Показываем ошибку, если запрос не удался
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt); // Освобождаем дескриптор запроса
    return apps; // Возвращаем вектор записей
}

// Функция для вывода данных на экран
// Принимает вектор записей и печатает их в консоль
void displayData(const std::vector<Application>& apps) {
    for (const auto& app : apps) {
        std::wcout << L"ID: " << app.id << L", AppName: " << app.appName
            << L", Version: " << app.version
            << L", Developer: " << app.developer
            << L", ReleaseDate: " << app.releaseDate << L"\n";
    }
}

// Функция для вставки новой записи в таблицу Applications
void insertData(SQLHDBC hDbc, const std::wstring& appName, double version, const std::wstring& developer, const std::wstring& releaseDate) {
    // Проверяем, что дата корректна
    if (!validateDate(releaseDate)) {
        std::wcout << L"Invalid date format. Please use YYYY-MM-DD with valid values (e.g., 2023-05-15).\n";
        return;
    }

    SQLHSTMT hStmt; // Создаём дескриптор для SQL-запроса
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    // Формируем SQL-запрос для вставки новой записи
    // Для даты в Access нужно использовать формат #YYYY-MM-DD#
    SQLWCHAR query[512];
    swprintf_s(query, 512, L"INSERT INTO Applications (AppName, Version, Developer, ReleaseDate) VALUES ('%s', %f, '%s', #%s#);",
        appName.c_str(), version, developer.c_str(), releaseDate.c_str());

    // Выполняем запрос
    SQLRETURN ret = SQLExecDirectW(hStmt, query, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::wcout << L"Record inserted successfully.\n"; // Сообщаем об успешной вставке
        std::wcout << L"\nUpdated database:\n";
        displayData(readData(hDbc)); // Показываем обновлённую таблицу
    }
    else {
        showSQLError(SQL_HANDLE_STMT, hStmt); // Показываем ошибку, если запрос не удался
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt); // Освобождаем дескриптор
}

// Функция для удаления записи из таблицы по ID
void deleteData(SQLHDBC hDbc, int id) {
    SQLHSTMT hStmt; // Создаём дескриптор для SQL-запроса
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    // Формируем SQL-запрос для удаления записи с заданным ID
    SQLWCHAR query[256];
    swprintf_s(query, 256, L"DELETE FROM Applications WHERE ID=%d;", id);

    // Выполняем запрос
    SQLRETURN ret = SQLExecDirectW(hStmt, query, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::wcout << L"Record deleted successfully.\n"; // Сообщаем об успешном удалении
        std::wcout << L"\nUpdated database:\n";
        displayData(readData(hDbc)); // Показываем обновлённую таблицу
    }
    else {
        showSQLError(SQL_HANDLE_STMT, hStmt); // Показываем ошибку, если запрос не удался
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt); // Освобождаем дескриптор
}

// Функция для сортировки записей по версии и сохранения их в базу
void sortByVersionAndSave(SQLHDBC hDbc) {
    // 1. Читаем все записи из базы
    std::vector<Application> apps = readData(hDbc);

    // 2. Сортируем записи в памяти по возрастанию версии
    std::sort(apps.begin(), apps.end(), [](const Application& a, const Application& b) {
        return a.version < b.version;
        });

    // 3. Очищаем таблицу Applications перед вставкой отсортированных данных
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    SQLRETURN ret = SQLExecDirectW(hStmt, (SQLWCHAR*)L"DELETE FROM Applications;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        std::wcout << L"Error clearing table before sorting\n";
        showSQLError(SQL_HANDLE_STMT, hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // 4. Вставляем отсортированные записи обратно в таблицу
    for (const auto& app : apps) {
        SQLHSTMT insertStmt;
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &insertStmt);

        // Формируем запрос для вставки каждой записи
        SQLWCHAR query[512];
        swprintf_s(query, 512, L"INSERT INTO Applications (AppName, Version, Developer, ReleaseDate) VALUES ('%s', %f, '%s', #%s#);",
            app.appName.c_str(), app.version, app.developer.c_str(), app.releaseDate.c_str());

        ret = SQLExecDirectW(insertStmt, query, SQL_NTS);
        if (!SQL_SUCCEEDED(ret)) {
            std::wcout << L"Error inserting sorted record\n";
            showSQLError(SQL_HANDLE_STMT, insertStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, insertStmt);
            return;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, insertStmt);
    }

    // 5. Показываем результат сортировки
    std::wcout << L"Applications sorted and saved successfully.\n";
    std::wcout << L"\nUpdated database:\n";
    displayData(readData(hDbc));
}

// Главная функция программы
int main() {
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку консоли для поддержки Unicode

    SQLHENV hEnv = nullptr; // Переменная для окружения ODBC
    SQLHDBC hDbc = nullptr; // Переменная для соединения с базой данных

    // Подключаемся к базе данных
    if (!connectToDB(hEnv, hDbc)) {
        return 1; // Если подключение не удалось, завершаем программу
    }

    int choice; // Переменная для выбора опции меню
    std::wstring appName, developer, releaseDate; // Переменные для ввода данных
    double version;
    int id;

    // Основной цикл программы
    while (true) {
        // Выводим меню с доступными опциями
        std::wcout << L"\nMenu:\n";
        std::wcout << L"1. Display all applications\n"; // Показать все записи
        std::wcout << L"2. Insert new application\n";  // Добавить новую запись
        std::wcout << L"3. Delete application\n";      // Удалить запись
        std::wcout << L"4. Sort applications by version (ascending) and save\n"; // Сортировать и сохранить
        std::wcout << L"5. Exit\n";                    // Выход из программы
        std::wcout << L"Enter choice: ";
        std::cin >> choice; // Считываем выбор пользователя
        std::cin.ignore();  // Очищаем буфер ввода

        if (choice == 5) break; // Если выбрана опция 5, выходим из цикла

        // Обрабатываем выбор пользователя
        switch (choice) {
        case 1: // Показать все записи
            displayData(readData(hDbc));
            break;

        case 2: // Добавить новую запись
            std::wcout << L"Enter AppName: ";
            std::getline(std::wcin, appName); // Считываем название приложения
            std::wcout << L"Enter Version: ";
            std::cin >> version; // Считываем версию
            std::cin.ignore();   // Очищаем буфер
            std::wcout << L"Enter Developer: ";
            std::getline(std::wcin, developer); // Считываем разработчика
            std::wcout << L"Enter ReleaseDate (YYYY-MM-DD): ";
            std::getline(std::wcin, releaseDate); // Считываем дату выпуска
            insertData(hDbc, appName, version, developer, releaseDate); // Добавляем запись
            break;

        case 3: // Удалить запись
            std::wcout << L"Enter ID to delete: ";
            std::cin >> id; // Считываем ID записи для удаления
            deleteData(hDbc, id); // Удаляем запись
            break;

        case 4: // Сортировать и сохранить
            sortByVersionAndSave(hDbc);
            break;

        default:
            std::wcout << L"Invalid choice.\n"; // Сообщаем о некорректном выборе
        }
    }

    // Закрываем соединение с базой данных перед завершением
    if (hDbc) {
        SQLDisconnect(hDbc); // Отключаемся от базы
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc); // Освобождаем дескриптор соединения
    }
    if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv); // Освобождаем окружение

    return 0; // Завершаем программу
}