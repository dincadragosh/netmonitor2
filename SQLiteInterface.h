#ifndef SQLITEINTERFACE_H
#define SQLITEINTERFACE_H

#include <sqlite3.h>

class ProcessedPacket;
class ProcessedHTTPReq;

class SQLiteInterface
{
private:
    sqlite3 *db;
    char *db_file;
    char *insert_history;

public:
    SQLiteInterface();

    bool OpenDatabase();
    bool InsertHistory(ProcessedPacket *info);
    bool InsertHTTPReq(ProcessedHTTPReq *info);
    bool CloseDatabase();
};

#endif
