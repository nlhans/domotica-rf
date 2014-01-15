#include "stddefs.h"

#include "ipstack/tcp.h"

#include "webserver/router.h"
#include "rtos/task.h"

const char* const http200 = "HTTP/1.1 200 OK\r\nContent-type: %s\r\n\r\n";
const char* const httpHelloWorld = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n<h1>Hello world</h1>This is a sample page to show this actually works.";

const char* const httpConnectionTable = "<h1>Connection list</h1><table style=\"border: 1px;\"><tr><td>#</td><td>IP</td><td>Port</td><td>State</td></tr>";
const char* const httpRtosTaskTable = "<h1>RTOS task table</h1><table style=\"border: 1px; \"><tr><td>#</td><td>Prio</td><td>Name</td><td>State</td><td>Stack</td><td>Time</td><td>Events</td></tr>";

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
//#define TCP_HELLO
void WebserverHandle(void* con, bool_t push, char* d, UI16_t s)
{
    char * bf = tcpGetDataPtr();
    UI08_t i = 0;
    UI16_t bfPos = 0;
    
    if (push)
    {
        TcpConnection_t *tcpConnection = (TcpConnection_t *) con;

        
#ifdef TCP_HELLO
        strcpy(bf, httpHelloWorld);
        
        // Tcp flags for HTTP header
        TcpFlags_t fl;
        fl.data = 0;
        fl.bits.ack = 1;
        fl.bits.psh = 1;
        fl.bits.fin = 1;

        tcpTxPacket(strlen(httpHelloWorld), fl, tcpConnection);
        return;
#else
        // Tcp flags for HTTP header
        TcpFlags_t fl;
        fl.data = 0;
        fl.bits.ack = 1;
        fl.bits.psh = 1;

        bfPos = sprintf(bf, http200, "text/html");
        tcpTxPacket(bfPos, fl, tcpConnection);
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
        bfPos = sprintf(bf, httpRtosTaskTable);
        while(ptr != NULL)
        {
            i++;
#ifdef RTOS_DEBUG
            if (ptr->state == TASK_STATE_DELAY)
                sprintf(state, RtosStateText[ptr->state], (ptr->nextRun-RtosGetTime()), (ptr->nextRun - ptr->lastRun));
            else
                strcpy(state, RtosStateText[ptr->state]);
#else
            strcpy(state, RtosStateText[ptr->state]);
#endif
            bfPos += sprintf(bf+bfPos, "<tr><td>%d</td>" // i
                    "<td>%d</td>" // priority
#ifdef RTOS_DEBUG
                    "<td>%s</td>" // name
#endif
                    "<td>%s</td>" // state
#ifdef RTOS_DEBUG
                    "<td>%d / %d / %d</td>" // stack
                    "<td>%lu ticks / last %lu / next %lu</td>" // time
#endif
#ifdef RTOS_EVENTS
                    "<td>%X / %X</td>"
#endif
                    "</tr>", // event
                i,
                ptr->priority,
#ifdef RTOS_DEBUG
                ptr->name,
#endif
                state
#ifdef RTOS_DEBUG
                ,ptr->stackUsage,  ptr->stackMaxUsage, ptr->stackSize,
                ptr->timeRan, ptr->lastRun, ptr->nextRun
#endif
#ifdef RTOS_EVENTS
               ,ptr->eventStore, ptr->eventMask
#endif
                    );

            ptr = (RtosTask_t*)ptr->list;
        }
#endif
        fl.bits.fin = 1;
        tcpTxPacket(strlen(bf), fl, tcpConnection);
        tcpCloseObj(tcpConnection);
#endif
        
    }

}