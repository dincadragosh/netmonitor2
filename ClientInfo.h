#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <string>

using namespace std;

class ClientInfo
{
private:
public:
    string mac_name;

    ClientInfo(string& mac_name);

    bool operator == (string& mac);
    bool operator != (string& mac);
};

#endif
