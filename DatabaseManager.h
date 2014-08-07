#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <pthread.h>

class Data;

class DatabaseManager
{
private:
    Data *data;
    int no_collectors;

    pthread_t pthread_collector;
    pthread_t pthread_database;

    void CollectHTTPReq();
    void Collect(void *user);
    void Database(void *user);
public:
    DatabaseManager(Data& data, int no_collectors = 1);
    ~DatabaseManager();
};

#endif
