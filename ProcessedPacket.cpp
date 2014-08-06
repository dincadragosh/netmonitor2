#include <ProcessedPacket.h>

ProcessedPacket::ProcessedPacket(ClientInfo& client, string& host, monitor_time& time, long int no_pkt)
    : client(client), host(host), time(time), no_pkt(no_pkt)
{
}
