#include <ProcessedHTTPReq.h>

ProcessedHTTPReq::ProcessedHTTPReq(ClientInfo& client,string& host, time_t& time, long int no_pkt)
    : ProcessedPacket(client,host, time, no_pkt), requested()
{
}
