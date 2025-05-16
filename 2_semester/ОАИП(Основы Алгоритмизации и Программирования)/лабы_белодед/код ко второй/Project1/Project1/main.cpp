#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>

// Функция для вывода ошибок ODBC
void showError(unsigned int handleType, const SQLHANDLE& handle) {
	SQLWCHAR sqlState[1024];
	SQLWCHAR message[1024];
	SQLSMALLINT i = 1;
	while (SQLGetDiagRecW(handleType, handle, i, sqlState, NULL, message, sizeof(message) / sizeof(SQLWCHAR), NULL) == SQL_SUCCESS) {
		std::wcerr << L"SQL Error [" << i << L"]: " << message
			<< L"\nSQL State: " << sqlState << std::endl;
		i++;
	}
}

// Функция для подключения к базе данных
SQLHANDLE connectToDatabase() {
	SQLHANDLE sqlEnvHandle = nullptr;
	SQLHANDLE sqlConnHandle = nullptr;

	// Инициализация окружения
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle)) {
		std::cerr << "Error allocating environment handle" << std::endl;
		return nullptr;
	}

	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) {
		showError(SQL_HANDLE_ENV, sqlEnvHandle);
		SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
		return nullptr;
	}

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle)) {
		showError(SQL_HANDLE_ENV, sqlEnvHandle);
		SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
		return nullptr;
	}

	// Подключение к серверу (измените параметры подключения при необходимости)
	SQLWCHAR* connStr = (SQLWCHAR*)L"DRIVER={ODBC Driver 17 for SQL Server};SERVER=localhost\\SQLEXPRESS;DATABASE=OurFirstBD;Trusted_Connection=yes;";

	SQLWCHAR outConnStr[1024];
	SQLSMALLINT outConnStrLen;

	SQLRETURN retCode = SQLDriverConnectW(sqlConnHandle, NULL, connStr, SQL_NTS,
		outConnStr, sizeof(outConnStr) / sizeof(SQLWCHAR), &outConnStrLen,
		SQL_DRIVER_COMPLETE);

	if (!SQL_SUCCEEDED(retCode)) {
		std::wcerr << L"Failed to connect to SQL Server. Connection string: " << connStr << std::endl;
		showError(SQL_HANDLE_DBC, sqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
		return nullptr;
	}

	return sqlConnHandle;
}

// Функция для вывода таблицы
void printTable(SQLHANDLE sqlConnHandle) {
	SQLHANDLE sqlStmtHandle;
	SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle);

	// Выполнение запроса
	SQLWCHAR* sqlQuery = (SQLWCHAR*)L"SELECT Id, username, email, age, register_date FROM dbo.FirstTable";
	SQLExecDirectW(sqlStmtHandle, sqlQuery, SQL_NTS);

	// Вывод заголовков таблицы
	std::wcout << std::left
		<< std::setw(5) << L"ID"
		<< std::setw(20) << L"Username"
		<< std::setw(25) << L"Email"
		<< std::setw(10) << L"Age"
		<< std::setw(20) << L"Register Date"
		<< std::endl;
	std::wcout << std::setfill(L'-') << std::setw(80) << L"" << std::setfill(L' ') << std::endl;

	// Вывод данных
	while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
		SQLINTEGER id, age;
		SQLWCHAR username[101], email[101];
		SQL_TIMESTAMP_STRUCT registerDate;
		SQLLEN usernameLen, emailLen, ageLen, registerDateLen;

		SQLGetData(sqlStmtHandle, 1, SQL_C_LONG, &id, 0, NULL);
		SQLGetData(sqlStmtHandle, 2, SQL_C_WCHAR, username, sizeof(username), &usernameLen);
		SQLGetData(sqlStmtHandle, 3, SQL_C_WCHAR, email, sizeof(email), &emailLen);
		SQLGetData(sqlStmtHandle, 4, SQL_C_LONG, &age, 0, &ageLen);
		SQLGetData(sqlStmtHandle, 5, SQL_C_TYPE_TIMESTAMP, &registerDate, sizeof(registerDate), &registerDateLen);

		// Форматирование даты
		wchar_t dateBuffer[20];
		swprintf(dateBuffer, 20, L"%04d-%02d-%02d %02d:%02d:%02d",
			registerDate.year, registerDate.month, registerDate.day,
			registerDate.hour, registerDate.minute, registerDate.second);

		std::wcout << std::left
			<< std::setw(5) << id
			<< std::setw(20) << (usernameLen == SQL_NULL_DATA ? L"NULL" : username)
			<< std::setw(25) << (emailLen == SQL_NULL_DATA ? L"NULL" : email)
			<< std::setw(10) << (ageLen == SQL_NULL_DATA ? L"NULL" : std::to_wstring(age))
			<< std::setw(20) << (registerDateLen == SQL_NULL_DATA ? L"NULL" : dateBuffer)
			<< std::endl;
	}

	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
}

// Функция для добавления элемента
void addItem(SQLHANDLE sqlConnHandle) {
	std::wstring username, email;
	int age;

	std::wcout << L"Enter username: ";
	std::getline(std::wcin, username);

	std::wcout << L"Enter email: ";
	std::getline(std::wcin, email);

	std::wcout << L"Enter age (or 0 for NULL): ";
	std::wcin >> age;
	std::wcin.ignore();

	SQLHANDLE sqlStmtHandle;
	SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle);

	std::wstring query = L"INSERT INTO dbo.FirstTable (username, email, age) VALUES (?, ?, ";
	query += (age == 0 ? L"NULL" : std::to_wstring(age)) + L")";

	SQLPrepareW(sqlStmtHandle, (SQLWCHAR*)query.c_str(), SQL_NTS);

	// Привязка параметров
	SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, 100, 0, (SQLPOINTER)username.c_str(), 0, NULL);
	SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, 100, 0, (SQLPOINTER)email.c_str(), 0, NULL);

	SQLExecute(sqlStmtHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);

	std::wcout << L"Item added successfully!" << std::endl;
}

// Функция для удаления элемента
void deleteItem(SQLHANDLE sqlConnHandle) {
	printTable(sqlConnHandle);

	int id;
	std::wcout << L"Enter ID to delete: ";
	std::wcin >> id;
	std::wcin.ignore();

	SQLHANDLE sqlStmtHandle;
	SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle);

	std::wstring query = L"DELETE FROM dbo.FirstTable WHERE Id = " + std::to_wstring(id);
	SQLExecDirectW(sqlStmtHandle, (SQLWCHAR*)query.c_str(), SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);

	std::wcout << L"Item deleted successfully!" << std::endl;
}

// Функция для сортировки по возрасту
void sortByAge(SQLHANDLE sqlConnHandle) {
	SQLHANDLE sqlStmtHandle;
	SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle);

	// Выполнение запроса с сортировкой
	SQLWCHAR* sqlQuery = (SQLWCHAR*)L"SELECT Id, username, email, age, register_date FROM dbo.FirstTable ORDER BY age";
	SQLExecDirectW(sqlStmtHandle, sqlQuery, SQL_NTS);

	// Вывод отсортированной таблицы
	std::wcout << L"\nTable sorted by age:\n";
	std::wcout << std::left
		<< std::setw(5) << L"ID"
		<< std::setw(20) << L"Username"
		<< std::setw(25) << L"Email"
		<< std::setw(10) << L"Age"
		<< std::setw(20) << L"Register Date"
		<< std::endl;
	std::wcout << std::setfill(L'-') << std::setw(80) << L"" << std::setfill(L' ') << std::endl;

	while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
		SQLINTEGER id, age;
		SQLWCHAR username[101], email[101];
		SQL_TIMESTAMP_STRUCT registerDate;
		SQLLEN usernameLen, emailLen, ageLen, registerDateLen;

		SQLGetData(sqlStmtHandle, 1, SQL_C_LONG, &id, 0, NULL);
		SQLGetData(sqlStmtHandle, 2, SQL_C_WCHAR, username, sizeof(username), &usernameLen);
		SQLGetData(sqlStmtHandle, 3, SQL_C_WCHAR, email, sizeof(email), &emailLen);
		SQLGetData(sqlStmtHandle, 4, SQL_C_LONG, &age, 0, &ageLen);
		SQLGetData(sqlStmtHandle, 5, SQL_C_TYPE_TIMESTAMP, &registerDate, sizeof(registerDate), &registerDateLen);

		wchar_t dateBuffer[20];
		swprintf(dateBuffer, 20, L"%04d-%02d-%02d %02d:%02d:%02d",
			registerDate.year, registerDate.month, registerDate.day,
			registerDate.hour, registerDate.minute, registerDate.second);

		std::wcout << std::left
			<< std::setw(5) << id
			<< std::setw(20) << (usernameLen == SQL_NULL_DATA ? L"NULL" : username)
			<< std::setw(25) << (emailLen == SQL_NULL_DATA ? L"NULL" : email)
			<< std::setw(10) << (ageLen == SQL_NULL_DATA ? L"NULL" : std::to_wstring(age))
			<< std::setw(20) << (registerDateLen == SQL_NULL_DATA ? L"NULL" : dateBuffer)
			<< std::endl;
	}

	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
}

// Главное меню
void showMenu(SQLHANDLE sqlConnHandle) {
	int choice;
	do {
		std::wcout << L"\nMenu:\n";
		std::wcout << L"1. Print table\n";
		std::wcout << L"2. Add item\n";
		std::wcout << L"3. Delete item\n";
		std::wcout << L"4. Sort by age\n";
		std::wcout << L"5. Exit\n";
		std::wcout << L"Enter your choice: ";
		std::wcin >> choice;
		std::wcin.ignore();

		switch (choice) {
		case 1:
			printTable(sqlConnHandle);
			break;
		case 2:
			addItem(sqlConnHandle);
			break;
		case 3:
			deleteItem(sqlConnHandle);
			break;
		case 4:
			sortByAge(sqlConnHandle);
			break;
		case 5:
			std::wcout << L"Exiting...\n";
			break;
		default:
			std::wcout << L"Invalid choice!\n";
		}

		if (choice != 5) {
			std::wcout << L"\nPress any key to continue...";
			_getch();
		}
	} while (choice != 5);
}

int main() {
	// Подключение к базе данных
	SQLHANDLE sqlConnHandle = connectToDatabase();
	if (!sqlConnHandle) {
		std::wcerr << L"Failed to connect to database. Exiting...\n";
		return 1;
	}

	// Отображение меню
	showMenu(sqlConnHandle);

	// Закрытие соединения
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);

	return 0;
}
