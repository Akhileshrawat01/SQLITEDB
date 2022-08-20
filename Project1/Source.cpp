#include<iostream>
#include<stdio.h>
#include<sqlite3.h>
using namespace std;
static int createDB(const char* s);
static int createTable(const char* s);
static int deleteData(const char* s);
static int insertData(const char* s);
static int updateData(const char* s);
static int selectData(const char* s);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);

int main()
{
	const char* dir = R"(D:\htmlprac\STUDENTS.db)";

	createDB(dir);
	createTable(dir);
	deleteData(dir); // use prior to insert
	insertData(dir); // uncomment the deleteData above to avoid duplicates
	updateData(dir);
	selectData(dir);

	return 0;
}

static int createDB(const char* s)
{
	sqlite3* DB;

	int exit = 0;
	exit = sqlite3_open(s, &DB);

	sqlite3_close(DB);

	return 0;
}

static int createTable(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "CREATE TABLE IF NOT EXISTS GRADES("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME      TEXT NOT NULL, "
		"ROLLNO     TEXT NOT NULL, "
		"PHYSICS       INT  NOT NULL, "
		"HINDI       INT  NOT NULL, "
		"ENGLISH       INT  NOT NULL, "
		"CHEMISTRY    INT  NOT NULL, "
		"MATH     INT  NOT NULL );";

	try
	{
		int exit = 0;
		exit = sqlite3_open(s, &DB);
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error in createTable function." << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Table created Successfully" << endl;
		sqlite3_close(DB);
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}

	return 0;
}

static int insertData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql("INSERT INTO GRADES (NAME, ROLLNO, PHYSICS,HINDI,ENGLISH,CHEMISTRY,MATH) VALUES('Alice', 23,89,90,66,44,55);"
		"INSERT INTO GRADES (NAME, ROLLNO, PHYSICS,HINDI,ENGLISH,CHEMISTRY,MATH) VALUES('Bob', 43,66,78,99,78,76);"
		"INSERT INTO GRADES (NAME, ROLLNO, PHYSICS,HINDI,ENGLISH,CHEMISTRY,MATH) VALUES('Fred', 66,89,55,56,67,78);");

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in insertData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records inserted Successfully!" << endl;

	return 0;
}

static int updateData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql("UPDATE GRADES SET ROLLNO = 1 WHERE NAME = 'ALICE'");

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in updateData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records updated Successfully!" << endl;

	return 0;
}

static int deleteData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "DELETE FROM GRADES;";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in deleteData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records deleted Successfully!" << endl;

	return 0;
}

static int selectData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "SELECT * FROM GRADES;";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		cerr << "Error in selectData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records selected Successfully!" << endl;

	return 0;
}

// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		// column name and value
		cout << azColName[i] << ": " << argv[i] << endl;
	}

	cout << endl;

	return 0;
}