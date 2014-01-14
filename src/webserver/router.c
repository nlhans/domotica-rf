#include "stddefs.h"

#include "ipstack/tcp.h"

#include "webserver/router.h"
#include "rtos/task.h"

const char* const http200 = "HTTP/1.1 200 OK\r\nContent-type: %s\r\n\r\n";
const char* const httpConnectionTable = "<h1>Connection list</h1><table style=\"border: 1px;\"><tr><td>#</td><td>IP</td><td>Port</td><td>State</td></tr>";
const char* const httpRtosTaskTable = "<h1>RTOS task table</h1><table style=\"border: 1px; \"><tr><td>#</td><td>Prio</td><td>Name</td><td>State</td><td>Stack</td><td>Time</td></tr>";

void webserverIndex(char **params);
void webserverConnections(char **params);
void webserverGet(char **params);

#define DEF_STR_CONCAT(a,b) a##b
#define DEF_STR_CONCAT_COUNT(a,b) DEF_STR_CONCAT(a,b)

#define routerIndexDef(method, url, callback) \
    { method, url, callback },

#define routerIndexCnt(method, url, callback) \
    DEF_STR_CONCAT_COUNT(ROUTE_, __COUNTER__),

#define routerTable(on) \
    on("GET","/", webserverIndex) \
    on("GET","/connections", webserverConnections) \
    on("GET","/get/:url/:id", webserverGet)

enum
{
    routerTable(routerIndexCnt)
    NUM_OF_ROUTES
};

typedef struct Route_s
{
    const char *access;
    const char *url;

    void (*callback) (char **uriParameters);
} Route_t;

const Route_t routerIndex[NUM_OF_ROUTES] = {
    routerTable(routerIndexDef)
};

void webserverIndex(char **params)
{
    //
}
void webserverConnections(char **params)
{
    //
}
void webserverGet(char **params)
{
    //
}

void WebserverHandle(void* con, bool_t push, char* d, UI16_t s)
{
    UI08_t i = 0;
    char bf[1024];
    UI16_t bfPos = 0;
    
    if (push)
    {
        TcpConnection_t *tcpConnection = (TcpConnection_t *) con;

        // Tcp flags for HTTP header
        TcpFlags_t fl;
        fl.data = 0;
        fl.bits.ack = 1;
        fl.bits.psh = 1;

        sprintf(bf, http200, "text/html");
        
        tcpTxPacket((UI08_t*) bf, strlen(bf), fl, tcpConnection);

#ifdef TCP_CONNECTION_TABLE
        bfPos += sprintf(bf, httpConnectionTable);

        for (i = 0; i < TCP_MAX_CONNECTIONS; i++)
        {
            TcpConnection_t* c = tcpConnections + i;
            //
            bfPos += sprintf(bf + bfPos, "<tr><td>%d</td><td>%d.%d.%d.%d</td><td>%u</td><td>%s</td></tr>",
                    i,
                    c->remoteIp[0],
                    c->remoteIp[1],
                    c->remoteIp[2],
                    c->remoteIp[3],
                    c->remotePort,
                    TcpStateStrings[c->state]);

        }
        strcpy(bf+bfPos, "\r\n");
#else
        char state [32];
        RtosTask_t* ptr = &RtosTaskIdleObj;
        i = 0;
        bfPos += sprintf(bf, httpRtosTaskTable);
        while(ptr != NULL)
        {
            i++;
            if (ptr->state == TASK_STATE_DELAY)
                sprintf(state, RtosStateText[ptr->state], (ptr->nextRun-RtosGetTime()), (ptr->nextRun - ptr->lastRun));
            else
                strcpy(state, RtosStateText[ptr->state]);

            bfPos += sprintf(bf+bfPos, "<tr><td>%d</td><td>%d</td><td>%s</td><td>%s</td><td>%d / %d / %d</td><td>%u ticks / last %u / next %u</td></tr>",
                i,
                ptr->priority,
                ptr->name,
                state,
                ptr->stackUsage,  ptr->stackMaxUsage, ptr->stackSize,
                ptr->timeRan, ptr->lastRun, ptr->nextRun);

            ptr = ptr->list;
        }
#endif
        fl.bits.fin = 1;
        tcpTxPacket((UI08_t*) bf, strlen(bf), fl, tcpConnection);
        
    }

}