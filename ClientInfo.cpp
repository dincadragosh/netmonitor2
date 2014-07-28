#include <string.h>
#include <ClientInfo.h>


ClientInfo::ClientInfo(string& mac)
{
    this->mac_name = mac;
}

bool ClientInfo::operator == (string& mac)
{
    return this->mac_name == mac;
}

bool ClientInfo::operator != (string& mac)
{
    return this->mac_name != mac;
}

/*bool ClientInfo::operator == (byte *mac)
{
    return !(memcmp(&this->mac, mac, sizeof(this->mac)));
}

bool ClientInfo::operator != (byte *mac)
{
    return !(*this == mac);
}
*/
