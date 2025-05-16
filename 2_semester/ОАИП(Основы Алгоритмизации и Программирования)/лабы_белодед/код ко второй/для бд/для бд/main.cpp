#include <windows.h>              // Подключаем библиотеку для работы с Windows
#include <sqlext.h>               // Подключаем библиотеку для работы с базой данных через ODBC
#include <iostream>               // Подключаем для вывода текста в консоль
#include <vector>                 // Подключаем для хранения списков товаров и продаж
#include <set>                    // Подключаем для уникальных категорий товаров
#include <algorithm>              // Подключаем для сортировки
#include <string>                 // Подключаем для работы с текстом

// Проверяем, правильно ли введена дата (например, 2025-05-12)
bool validateDate(const std::wstring& date) {
    if (date.length() != 10 || date[4] != L'-' || date[7] != L'-') {
        return false;                   // Если длина не 10 или дефисы на неправильных местах, возвращаем false
    }
    try {
        int year = std::stoi(date.substr(0, 4));    // Берем год (первые 4 символа)
        int month = std::stoi(date.substr(5, 2));   // Берем месяц (5-6 символы)
        int day = std::stoi(date.substr(8, 2));     // Берем день (8-9 символы)
        if (month < 1 || month > 12 || day < 1 || day > 31 || year < 1900 || year > 9999) return false;
        if (month == 2 && day > 29) return false;   // Февраль не больше 29 дней
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
        return true;                                // Если всё ок, возвращаем true
    }
    catch (...) {
        return false;                               // Если ошибка при преобразовании, возвращаем false
    }
}

// Показываем ошибки, если база данных не работает
void showSQLError(SQLSMALLINT handleType, SQLHANDLE handle) {
    SQLWCHAR sqlState[1024];
    SQLWCHAR message[2048];
    SQLINTEGER nativeError;
    SQLSMALLINT textLength;
    SQLRETURN ret = SQLGetDiagRecW(handleType, handle, 1, sqlState, &nativeError, message, 2048, &textLength);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::wcout << L"ODBC Error: " << message << L" [State: " << sqlState << L"]\n";
    }
}

// Структура для хранения информации о товаре
struct Product {
    SQLINTEGER productID;                       // Уникальный номер товара
    std::wstring name;                          // Название товара
    std::wstring category;                      // Категория (например, "Electronics")
    SQLDOUBLE price;                            // Цена товара
    SQLINTEGER stock;                           // Количество на складе
};

// Структура для хранения информации о продаже
struct Sale {
    SQLINTEGER saleID;                          // Уникальный номер продажи
    SQLINTEGER productID;                       // Номер товара, который продали
    std::wstring saleDate;                      // Дата продажи
    SQLINTEGER quantity;                        // Количество проданных единиц
    SQLDOUBLE totalCost;                        // Общая стоимость продажи
};

// Подключаемся к базе данных (путь как в прошлой лабе, но для WarehouseDB)
bool connectToDB(SQLHENV& hEnv, SQLHDBC& hDbc) {
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);  // Создаем окружение для базы
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);  // Устанавливаем версию ODBC
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);            // Создаем соединение

    // Путь как в прошлой лабе, заменяем SoftwareDB на WarehouseDB
    SQLWCHAR connStr[] = L"Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=D:\\1_course\\2_semester\\ОАИП(Основы Алгоритмизации и Программирования)\\лабы_белодед\\код ко второй\\для бд\\SoftwareDB.accdb;";
    SQLWCHAR outConnStr[1024];
    SQLSMALLINT outConnStrLen;
    SQLRETURN ret = SQLDriverConnectW(hDbc, NULL, connStr, SQL_NTS, outConnStr, 1024, &outConnStrLen, SQL_DRIVER_COMPLETE);

    if (!SQL_SUCCEEDED(ret)) {                              // Если подключение не удалось
        showSQLError(SQL_HANDLE_DBC, hDbc);                 // Показываем ошибку
        return false;                                       // Возвращаем false
    }
    return true;                                            // Успешное подключение
}

// Читаем все товары из базы данных
std::vector<Product> readProducts(SQLHDBC hDbc) {
    std::vector<Product> products;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);          // Готовим запрос

    SQLRETURN ret = SQLExecDirectW(hStmt, (SQLWCHAR*)L"SELECT ProductID, Name, Category, Price, Stock FROM Products;", SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        SQLINTEGER productID, stock;
        SQLDOUBLE price;
        SQLWCHAR name[151], category[51];
        SQLLEN productIDLen, nameLen, categoryLen, priceLen, stockLen;

        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            Product product = { 0 };
            SQLGetData(hStmt, 1, SQL_C_LONG, &productID, 0, &productIDLen);
            SQLGetData(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), &nameLen);
            SQLGetData(hStmt, 3, SQL_C_WCHAR, category, sizeof(category), &categoryLen);
            SQLGetData(hStmt, 4, SQL_C_DOUBLE, &price, 0, &priceLen);
            SQLGetData(hStmt, 5, SQL_C_LONG, &stock, 0, &stockLen);

            product.productID = productID;
            product.name = name;
            product.category = category;
            product.price = price;
            product.stock = stock;
            products.push_back(product);
        }
    }
    else {
        showSQLError(SQL_HANDLE_STMT, hStmt);               // Показываем ошибку, если запрос не работает
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);                  // Освобождаем ресурсы
    return products;
}

// Читаем все продажи из базы данных
std::vector<Sale> readSales(SQLHDBC hDbc) {
    std::vector<Sale> sales;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    SQLRETURN ret = SQLExecDirectW(hStmt, (SQLWCHAR*)L"SELECT SaleID, ProductID, SaleDate, Quantity, TotalCost FROM Sales;", SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        SQLINTEGER saleID, productID, quantity;
        SQLDOUBLE totalCost;
        SQLWCHAR saleDate[50];
        SQLLEN saleIDLen, productIDLen, saleDateLen, quantityLen, totalCostLen;

        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            Sale sale = { 0 };
            SQLGetData(hStmt, 1, SQL_C_LONG, &saleID, 0, &saleIDLen);
            SQLGetData(hStmt, 2, SQL_C_LONG, &productID, 0, &productIDLen);
            SQLGetData(hStmt, 3, SQL_C_WCHAR, saleDate, sizeof(saleDate), &saleDateLen);
            SQLGetData(hStmt, 4, SQL_C_LONG, &quantity, 0, &quantityLen);
            SQLGetData(hStmt, 5, SQL_C_DOUBLE, &totalCost, 0, &totalCostLen);

            sale.saleID = saleID;
            sale.productID = productID;
            sale.saleDate = saleDate;
            sale.quantity = quantity;
            sale.totalCost = totalCost;
            sales.push_back(sale);
        }
    }
    else {
        showSQLError(SQL_HANDLE_STMT, hStmt);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return sales;
}

// Показываем все товары на экране
void displayProducts(const std::vector<Product>& products) {
    for (const auto& product : products) {
        std::wcout << L"ProductID: " << product.productID << L", Name: " << product.name
            << L", Category: " << product.category << L", Price: " << product.price
            << L", Stock: " << product.stock << L"\n";
    }
}

// Сортируем товары по цене и обновляем базу
void sortProductsByPrice(SQLHDBC hDbc, std::vector<Product>& products) {
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.price < b.price;                       // Сортируем по возрастанию цены
        });

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    SQLRETURN ret = SQLExecDirectW(hStmt, (SQLWCHAR*)L"DELETE FROM Products;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        std::wcout << L"Error clearing Products table\n";
        showSQLError(SQL_HANDLE_STMT, hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    for (const auto& product : products) {
        SQLHSTMT insertStmt;
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &insertStmt);
        SQLWCHAR query[512];
        swprintf_s(query, 512, L"INSERT INTO Products (ProductID, Name, Category, Price, Stock) VALUES (%d, '%s', '%s', %f, %d);",
            product.productID, product.name.c_str(), product.category.c_str(), product.price, product.stock);
        ret = SQLExecDirectW(insertStmt, query, SQL_NTS);
        if (!SQL_SUCCEEDED(ret)) {
            std::wcout << L"Error inserting product\n";
            showSQLError(SQL_HANDLE_STMT, insertStmt);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, insertStmt);
    }
    std::wcout << L"Products sorted by price and saved successfully.\n";
}

// Считаем продажи по категориям
void salesStatsByCategory(const std::vector<Sale>& sales, const std::vector<Product>& products) {
    std::set<std::wstring> categories;                          // Храним уникальные категории
    for (const auto& product : products) {
        categories.insert(product.category);                    // Добавляем каждую категорию
    }

    std::wcout << L"Sales statistics by category:\n";
    for (const auto& category : categories) {                    // Проходим по всем категориям
        int totalSold = 0;
        double totalRevenue = 0.0;
        for (const auto& sale : sales) {
            auto it = std::find_if(products.begin(), products.end(), [&sale, &category](const Product& product) {
                return product.productID == sale.productID && product.category == category;  // Сравниваем по ID и категории
                });
            if (it != products.end()) {
                totalSold += sale.quantity;                     // Суммируем количество
                totalRevenue += sale.totalCost;                 // Суммируем выручку
            }
        }
        std::wcout << category << L": " << totalSold << L" items sold, Total Revenue: " << totalRevenue << L"\n";
    }
}

// Добавляем новую продажу
void addSale(SQLHDBC hDbc, std::vector<Sale>& sales, std::vector<Product>& products) {
    int productID, quantity;
    std::wstring saleDate;

    std::wcout << L"Enter ProductID to sell: ";
    std::cin >> productID;
    std::cin.ignore();
    std::wcout << L"Enter Quantity: ";
    std::cin >> quantity;
    std::cin.ignore();
    std::wcout << L"Enter SaleDate (YYYY-MM-DD): ";
    std::getline(std::wcin, saleDate);

    if (!validateDate(saleDate)) {
        std::wcout << L"Invalid date format. Please use YYYY-MM-DD (e.g., 2025-05-01).\n";
        return;
    }

    auto productIt = std::find_if(products.begin(), products.end(), [productID](const Product& product) {
        return product.productID == productID;                  // Ищем товар по ID
        });
    if (productIt == products.end() || productIt->stock < quantity) {
        std::wcout << L"Product not found or insufficient stock.\n";
        return;
    }

    double totalCost = productIt->price * quantity;             // Рассчитываем стоимость
    productIt->stock -= quantity;                               // Уменьшаем запас

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    SQLWCHAR query[256];
    swprintf_s(query, 256, L"UPDATE Products SET Stock = %d WHERE ProductID = %d;", productIt->stock, productID);
    SQLRETURN ret = SQLExecDirectW(hStmt, query, SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        showSQLError(SQL_HANDLE_STMT, hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    SQLHSTMT insertStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &insertStmt);
    swprintf_s(query, 256, L"INSERT INTO Sales (ProductID, SaleDate, Quantity, TotalCost) VALUES (%d, #%s#, %d, %f);",
        productID, saleDate.c_str(), quantity, totalCost);
    ret = SQLExecDirectW(insertStmt, query, SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        showSQLError(SQL_HANDLE_STMT, insertStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, insertStmt);
        return;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, insertStmt);

    std::wcout << L"Sale recorded successfully. Stock updated.\n";
    std::wcout << L"Updated Products:\n";
    displayProducts(readProducts(hDbc));
}

// Автоматически заказываем товары, если их меньше 5
void autoOrderLowStock(SQLHDBC hDbc, std::vector<Product>& products) {
    std::wcout << L"Checking for low stock (less than 5 units):\n";
    for (auto& product : products) {
        if (product.stock < 5) {
            int orderQuantity = 20 - product.stock;             // Заказываем до 20 единиц
            product.stock += orderQuantity;

            SQLHSTMT hStmt;
            SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
            SQLWCHAR query[256];
            swprintf_s(query, 256, L"UPDATE Products SET Stock = %d WHERE ProductID = %d;", product.stock, product.productID);
            SQLRETURN ret = SQLExecDirectW(hStmt, query, SQL_NTS);
            if (!SQL_SUCCEEDED(ret)) {
                showSQLError(SQL_HANDLE_STMT, hStmt);
            }
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

            std::wcout << L"Ordered " << orderQuantity << L" units for ProductID: " << product.productID
                << L", Name: " << product.name << L". New stock: " << product.stock << L"\n";
        }
    }
}

// Главная функция с меню
int main() {
    SetConsoleOutputCP(CP_UTF8);                             // Настраиваем консоль для русских букв

    SQLHENV hEnv = nullptr;
    SQLHDBC hDbc = nullptr;

    if (!connectToDB(hEnv, hDbc)) {                         // Пробуем подключиться к базе
        return 1;                                           // Если не получилось, выходим
    }

    int choice;
    while (true) {
        std::wcout << L"\nMenu:\n";                         // Показываем меню
        std::wcout << L"1. Display all products\n";         // 1: Показать товары
        std::wcout << L"2. Sort products by price\n";       // 2: Сортировать по цене
        std::wcout << L"3. Show sales statistics by category\n";  // 3: Статистика продаж
        std::wcout << L"4. Add new sale\n";                 // 4: Добавить продажу
        std::wcout << L"5. Auto-order low stock products\n";  // 5: Автозаказ товаров
        std::wcout << L"6. Exit\n";                         // 6: Выход
        std::wcout << L"Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 6) break;                             // Выходим, если выбрали 6

        std::vector<Product> products = readProducts(hDbc); // Читаем список товаров
        std::vector<Sale> sales = readSales(hDbc);          // Читаем список продаж

        switch (choice) {
        case 1:
            displayProducts(products);                      // Показываем товары
            break;
        case 2:
            sortProductsByPrice(hDbc, products);            // Сортируем товары
            std::wcout << L"Updated database:\n";
            displayProducts(readProducts(hDbc));
            break;
        case 3:
            salesStatsByCategory(sales, products);          // Показываем статистику
            break;
        case 4:
            addSale(hDbc, sales, products);                 // Добавляем продажу
            break;
        case 5:
            autoOrderLowStock(hDbc, products);              // Проверяем и заказываем товары
            break;
        default:
            std::wcout << L"Invalid choice.\n";             // Если выбор неверный
        }
    }

    if (hDbc) {                                             // Закрываем соединение с базой
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    }
    if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;                                               // Завершаем программу
}