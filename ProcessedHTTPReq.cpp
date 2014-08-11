#include <ProcessedHTTPReq.h>

ProcessedHTTPReq::ProcessedHTTPReq(ClientInfo& client,string& host, monitor_time& time, int no_pkt)
    : ProcessedPacket(client,host, time, no_pkt), requested()
{
}
