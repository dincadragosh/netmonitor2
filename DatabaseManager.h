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

    //syncronization between collector and database
    pthread_mutex_t cond_lock;
    pthread_cond_t  cond_var;
    bool cond_bool;

public:
    DatabaseManager(Data& data, int no_collectors = 1);
    ~DatabaseManager();

    void Collect();
    void Database();
};

#endif
