#include <windows.h>
#include <sqlext.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

// ������� ��� �������� ������� ���� YYYY-MM-DD
// ���������, ��� �������� ���� ��������� (��������, 2023-05-15)
// ���������� true, ���� ���� ����������, � false, ���� ���� ������
bool validateDate(const std::wstring& date) {
    // ��������� ����� ������ � ������� �������� '-' �� ������ ��������
    if (date.length() != 10 || date[4] != L'-' || date[7] != L'-') {
        return false;
    }

    try {
        // ��������� ���, ����� � ���� �� ������ � ����������� �� � �����
        int year = std::stoi(date.substr(0, 4)); // ������ 4 ������� � ���
        int month = std::stoi(date.substr(5, 2)); // ������� 5-6 � �����
        int day = std::stoi(date.substr(8, 2));   // ������� 8-9 � ����
        // ���������, ��� ����� �� 1 �� 12
        if (month < 1 || month > 12) return false;
        // ���������, ��� ���� �� 1 �� 31
        if (day < 1 || day > 31) return false;
        // ���������, ��� ��� � �������� �������� (1900�9999)
        if (year < 1900 || year > 9999) return false;
        // ��������� ���������� ���� � ������ (������� ��������, ��� ����� ���������� �����)
        if (month == 2 && day > 29) return false; // ������� �� ����� ����� ������ 29 ����
        // ������, ����, �������� � ������ ����� 30 ����
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
        return true; // ���� ���������
    }
    catch (...) {
        return false; 
    }
}

// ������� ��� ����������� ������ ODBC
// ���� ���-�� ��� �� ��� ��� ������ � ����� ������, ��� ������� �������, ��� ������ ����� �� ���
void showSQLError(SQLSMALLINT handleType, SQLHANDLE handle) {
    SQLWCHAR sqlState[1024]; // ����� ��� ���� ��������� ������
    SQLWCHAR message[2048];  // ����� ��� ������ ������
    SQLINTEGER nativeError;  // ��� ������
    SQLSMALLINT textLength;  // ����� ������ ������
    // �������� ���������� �� ������
    SQLRETURN ret = SQLGetDiagRecW(handleType, handle, 1, sqlState, &nativeError, message, 2048, &textLength);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        // ������� ����� ������ � ��� ���������
        std::wcout << L"ODBC Error: " << message << L" [State: " << sqlState << L"]\n";
    }
}

// ��������� ��� �������� ������ ����� ������ �� ������� Applications
struct Application {
    SQLINTEGER id;          // ID ������ (���������������� ���� � ����)
    std::wstring appName;   // �������� ���������� (��������, Notepad++)
    double version;         // ������ ���������� (��������, 8.5)
    std::wstring developer; // ����������� (��������, Notepad++ Team)
    std::wstring releaseDate; // ���� ������� (��������, 2023-05-15)
};

// ������� ��� ����������� � ���� ������ Access
// ������������� ���������� � ������ SoftwareDB.accdb
bool connectToDB(SQLHENV& hEnv, SQLHDBC& hDbc) {
    // ������ ��������� (environment) ��� ������ � ODBC
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    // ������������� ������ ODBC (���������� ������ 3)
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    // ������ ���������� ���������� (connection handle)
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // ������ �����������: ��������� ������� � ���� � ����� ���� ������
    SQLWCHAR connStr[] = L"Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=D:\\1_course\\2_semester\\����(������ �������������� � ����������������)\\����_�������\\��� �� ������\\��� ��\\SoftwareDB.accdb;";
    SQLWCHAR outConnStr[1024]; // ����� ��� ������ ����������� ����� ����������
    SQLSMALLINT outConnStrLen; // ����� ������ �����������
    // ��������� ����������� � ���� ������
    SQLRETURN ret = SQLDriverConnectW(hDbc, NULL, connStr, SQL_NTS, outConnStr, 1024, &outConnStrLen, SQL_DRIVER_COMPLETE);

    if (!SQL_SUCCEEDED(ret)) {
        // ���� ����������� �� �������, ���������� ������
        showSQLError(SQL_HANDLE_DBC, hDbc);
        return false;
    }
    return true; // ����������� �������
}

// ������� ��� ������ ���� ������ �� ������� Applications
// ���������� ������ ������� (Application), ������� �������� � ����
std::vector<Application> readData(SQLHDBC hDbc) {
    std::vector<Application> apps; // ������ ��� �������� ���� �������
    SQLHSTMT hStmt; // ���������� ������� (statement handle)
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt); // ������ ���������� �������

    // ��������� SQL-������: �������� ��� ������� �� ������� Applications
    SQLRETURN ret = SQLExecDirectW(hStmt, (SQLWCHAR*)L"SELECT ID, AppName, Version, Developer, ReleaseDate FROM Applications;", SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        // ���������� ��� �������� ������ �� ��������
        SQLINTEGER id;
        SQLWCHAR appName[101], developer[101], releaseDate[50];
        SQLDOUBLE version;
        SQLLEN idLen, appNameLen, versionLen, developerLen, releaseDateLen;

        // ������ ������ �� ������� �� �����
        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            Application app = { 0 }; // ������ ������ ��������� ��� ������� ������

            // ������ ID (������������� ��������)
            ret = SQLGetData(hStmt, 1, SQL_C_LONG, &id, 0, &idLen);
            if (!SQL_SUCCEEDED(ret)) {
                std::wcout << L"Error fetching ID\n";
                showSQLError(SQL_HANDLE_STMT, hStmt);
                break;
            }
            app.id = id;

            // ������ AppName (������)
            ret = SQLGetData(hStmt, 2, SQL_C_WCHAR, appName, sizeof(appName), &appNameLen);
            if (!SQL_SUCCEEDED(ret)) {
                std::wcout << L"Error fetching AppName\n";
                showSQLError(SQL_HANDLE_STMT, hStmt);
                break;
            }
            app.appName = appName;

            // ������ Version (����� � ��������� ������)
            ret = SQLGetData(hStmt, 3, SQL_C_DOUBLE, &version, 0, &versionLen);
            if (!SQL_SUCCEEDED(ret)) {
                std::wcout << L"Error fetching Version\n";
                showSQLError(SQL_HANDLE_STMT, hStmt);
                break;
            }
            app.version = version;

            // ������ Developer (������)
            ret = SQLGetData(hStmt, 4, SQL_C_WCHAR, developer, sizeof(developer), &developerLen);
            if (!SQL_SUCCEEDED(ret)) {
                std::wcout << L"Error fetching Developer\n";
                showSQLError(SQL_HANDLE_STMT, hStmt);
                break;
            }
            app.developer = developer;

            // ������ ReleaseDate (������)
            ret = SQLGetData(hStmt, 5, SQL_C_WCHAR, releaseDate, sizeof(releaseDate), &releaseDateLen);
            if (!SQL_SUCCEEDED(ret)) {
                std::wcout << L"Error fetching ReleaseDate\n";
                showSQLError(SQL_HANDLE_STMT, hStmt);
                app.releaseDate = L"Invalid Date";
            }
            else {
                // ���� ���� �������� ����� (��������, 2023-05-15 00:00:00), �������� ���
                std::wstring dateStr(releaseDate);
                size_t spacePos = dateStr.find(L" ");
                if (spacePos != std::wstring::npos) {
                    app.releaseDate = dateStr.substr(0, spacePos);
                }
                else {
                    app.releaseDate = dateStr;
                }
            }

            apps.push_back(app); // ��������� ������ � ������
        }
    }
    else {
        showSQLError(SQL_HANDLE_STMT, hStmt); // ���������� ������, ���� ������ �� ������
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt); // ����������� ���������� �������
    return apps; // ���������� ������ �������
}

// ������� ��� ������ ������ �� �����
// ��������� ������ ������� � �������� �� � �������
void displayData(const std::vector<Application>& apps) {
    for (const auto& app : apps) {
        std::wcout << L"ID: " << app.id << L", AppName: " << app.appName
            << L", Version: " << app.version
            << L", Developer: " << app.developer
            << L", ReleaseDate: " << app.releaseDate << L"\n";
    }
}

// ������� ��� ������� ����� ������ � ������� Applications
void insertData(SQLHDBC hDbc, const std::wstring& appName, double version, const std::wstring& developer, const std::wstring& releaseDate) {
    // ���������, ��� ���� ���������
    if (!validateDate(releaseDate)) {
        std::wcout << L"Invalid date format. Please use YYYY-MM-DD with valid values (e.g., 2023-05-15).\n";
        return;
    }

    SQLHSTMT hStmt; // ������ ���������� ��� SQL-�������
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    // ��������� SQL-������ ��� ������� ����� ������
    // ��� ���� � Access ����� ������������ ������ #YYYY-MM-DD#
    SQLWCHAR query[512];
    swprintf_s(query, 512, L"INSERT INTO Applications (AppName, Version, Developer, ReleaseDate) VALUES ('%s', %f, '%s', #%s#);",
        appName.c_str(), version, developer.c_str(), releaseDate.c_str());

    // ��������� ������
    SQLRETURN ret = SQLExecDirectW(hStmt, query, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::wcout << L"Record inserted successfully.\n"; // �������� �� �������� �������
        std::wcout << L"\nUpdated database:\n";
        displayData(readData(hDbc)); // ���������� ���������� �������
    }
    else {
        showSQLError(SQL_HANDLE_STMT, hStmt); // ���������� ������, ���� ������ �� ������
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt); // ����������� ����������
}

// ������� ��� �������� ������ �� ������� �� ID
void deleteData(SQLHDBC hDbc, int id) {
    SQLHSTMT hStmt; // ������ ���������� ��� SQL-�������
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    // ��������� SQL-������ ��� �������� ������ � �������� ID
    SQLWCHAR query[256];
    swprintf_s(query, 256, L"DELETE FROM Applications WHERE ID=%d;", id);

    // ��������� ������
    SQLRETURN ret = SQLExecDirectW(hStmt, query, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::wcout << L"Record deleted successfully.\n"; // �������� �� �������� ��������
        std::wcout << L"\nUpdated database:\n";
        displayData(readData(hDbc)); // ���������� ���������� �������
    }
    else {
        showSQLError(SQL_HANDLE_STMT, hStmt); // ���������� ������, ���� ������ �� ������
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt); // ����������� ����������
}

// ������� ��� ���������� ������� �� ������ � ���������� �� � ����
void sortByVersionAndSave(SQLHDBC hDbc) {
    // 1. ������ ��� ������ �� ����
    std::vector<Application> apps = readData(hDbc);

    // 2. ��������� ������ � ������ �� ����������� ������
    std::sort(apps.begin(), apps.end(), [](const Application& a, const Application& b) {
        return a.version < b.version;
        });

    // 3. ������� ������� Applications ����� �������� ��������������� ������
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

    // 4. ��������� ��������������� ������ ������� � �������
    for (const auto& app : apps) {
        SQLHSTMT insertStmt;
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &insertStmt);

        // ��������� ������ ��� ������� ������ ������
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

    // 5. ���������� ��������� ����������
    std::wcout << L"Applications sorted and saved successfully.\n";
    std::wcout << L"\nUpdated database:\n";
    displayData(readData(hDbc));
}

// ������� ������� ���������
int main() {
    SetConsoleOutputCP(CP_UTF8); // ������������� ��������� ������� ��� ��������� Unicode

    SQLHENV hEnv = nullptr; // ���������� ��� ��������� ODBC
    SQLHDBC hDbc = nullptr; // ���������� ��� ���������� � ����� ������

    // ������������ � ���� ������
    if (!connectToDB(hEnv, hDbc)) {
        return 1; // ���� ����������� �� �������, ��������� ���������
    }

    int choice; // ���������� ��� ������ ����� ����
    std::wstring appName, developer, releaseDate; // ���������� ��� ����� ������
    double version;
    int id;

    // �������� ���� ���������
    while (true) {
        // ������� ���� � ���������� �������
        std::wcout << L"\nMenu:\n";
        std::wcout << L"1. Display all applications\n"; // �������� ��� ������
        std::wcout << L"2. Insert new application\n";  // �������� ����� ������
        std::wcout << L"3. Delete application\n";      // ������� ������
        std::wcout << L"4. Sort applications by version (ascending) and save\n"; // ����������� � ���������
        std::wcout << L"5. Exit\n";                    // ����� �� ���������
        std::wcout << L"Enter choice: ";
        std::cin >> choice; // ��������� ����� ������������
        std::cin.ignore();  // ������� ����� �����

        if (choice == 5) break; // ���� ������� ����� 5, ������� �� �����

        // ������������ ����� ������������
        switch (choice) {
        case 1: // �������� ��� ������
            displayData(readData(hDbc));
            break;

        case 2: // �������� ����� ������
            std::wcout << L"Enter AppName: ";
            std::getline(std::wcin, appName); // ��������� �������� ����������
            std::wcout << L"Enter Version: ";
            std::cin >> version; // ��������� ������
            std::cin.ignore();   // ������� �����
            std::wcout << L"Enter Developer: ";
            std::getline(std::wcin, developer); // ��������� ������������
            std::wcout << L"Enter ReleaseDate (YYYY-MM-DD): ";
            std::getline(std::wcin, releaseDate); // ��������� ���� �������
            insertData(hDbc, appName, version, developer, releaseDate); // ��������� ������
            break;

        case 3: // ������� ������
            std::wcout << L"Enter ID to delete: ";
            std::cin >> id; // ��������� ID ������ ��� ��������
            deleteData(hDbc, id); // ������� ������
            break;

        case 4: // ����������� � ���������
            sortByVersionAndSave(hDbc);
            break;

        default:
            std::wcout << L"Invalid choice.\n"; // �������� � ������������ ������
        }
    }

    // ��������� ���������� � ����� ������ ����� �����������
    if (hDbc) {
        SQLDisconnect(hDbc); // ����������� �� ����
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc); // ����������� ���������� ����������
    }
    if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv); // ����������� ���������

    return 0; // ��������� ���������
}