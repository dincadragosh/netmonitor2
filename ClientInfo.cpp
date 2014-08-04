#include <string.h>
#include <ClientInfo.h>


ClientInfo::ClientInfo(string mac)
    : mac_name(mac)
{
}

bool ClientInfo::operator== (string& mac)
{
    return this->mac_name == mac;
}

bool ClientInfo::operator!= (string& mac)
{
    return this->mac_name != mac;
}

bool ClientInfo::operator< (const ClientInfo& mac) const
{
    return this->mac_name < mac.mac_name;
}

bool ClientInfo::operator> (const ClientInfo& mac) const
{
    return this->mac_name > mac.mac_name;
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

ClientInfo::operator std::string () const
{
    return this->mac_name;
}
