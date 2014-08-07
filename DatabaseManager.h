#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <pthread.h>

class Data;

class DatabaseManager
{
private:
    Data *data;
    int no_collectors;

    void CollectHTTPReq();
    void Collect();
    void Database();
public:
    DatabaseManager(Data& data, int no_collectors = 1);
    ~DatabaseManager();
};

#endif
