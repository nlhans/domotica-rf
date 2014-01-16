#include "stddefs.h"

#include "ipstack/tcp.h"

#include "webserver/router.h"
#include "rtos/task.h"

#include "devices/SST26VF032.h"

char * webBf;
UI16_t webBfPos;

const char* const http200 = "HTTP/1.1 200 OK\r\nContent-type: %s\r\n\r\n";
const char* const http404 = "HTTP/1.1 404 Not Found\r\n\r\n<h1>404 Not Found</h1>The page you requested is not found, that means it doesn't exist. ";
const char* const httpHelloWorld = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n<h1>Hello world</h1>This is a sample page to show this actually works.";

const char* const httpConnectionTable = "<h1>Connection list</h1><table style=\"border: 1px;\"><tr><td>#</td><td>IP</td><td>Port</td><td>State</td></tr>";
const char* const httpRtosTaskTable = "<h1>RTOS task table</h1><table style=\"border: 1px; \"><tr><td>#</td><td>Prio</td><td>Name</td><td>State</td><td>Stack</td><td>Time</td><td>Events</td></tr>";

void webIndex(TcpConnection_t* connection, char **params);
void webTest(TcpConnection_t* connection, char **params);

/**** SYSTEM DIAGNOSTICS ****/
void webSysFlash(TcpConnection_t* connection, char **params);
void webSysTcpip(TcpConnection_t* connection, char **params);
void webSysRtos(TcpConnection_t* connection, char **params);

#define DEF_STR_CONCAT(a,b) a##b
#define DEF_STR_CONCAT_COUNT(a,b) DEF_STR_CONCAT(a,b)

#define routerIndexDef(method, url, options, callback) \
    { method, url, options, callback },

#define routerIndexCnt(method, url, options, callback) \
    DEF_STR_CONCAT_COUNT(ROUTE_, __COUNTER__),

#define ROUTE_IS_CONSTANT 0x0000
#define ROUTE_IS_ARGS 0x8000
#define ROUTE_IN_FLASH(addr) addr

#define routerTable(on) \
    on("GET", "/sys/tcpip",      ROUTE_IS_CONSTANT,      webSysTcpip) \
    on("GET", "/sys/flash",      ROUTE_IS_CONSTANT,      webSysFlash) \
    on("GET", "/sys/rtos",       ROUTE_IS_CONSTANT,      webSysRtos)  \
    on("GET", "/get/:0/:1",      ROUTE_IS_ARGS,          webTest)     \
    on("GET", "/favicon.ico",    ROUTE_IN_FLASH(0x0000), NULL)        \
    on("GET", "/404.html",       ROUTE_IN_FLASH(0x000B), NULL)        \
    on("GET", "/",               ROUTE_IS_CONSTANT,      webIndex)    \
    

enum
{
    routerTable(routerIndexCnt)
    NUM_OF_ROUTES
};

typedef struct Route_s
{
    const char *access;
    const char *url;
    union
    {
         UI16_t _opt;
         struct
         {
             UI16_t location:15;
             UI08_t arguments:1;
         } options;
    };
    void (*callback) (TcpConnection_t* connection, char **params);
} Route_t;

const Route_t webRoutes[NUM_OF_ROUTES] = {
    routerTable(routerIndexDef)
};

void webSysFlash(TcpConnection_t* connection, char **params)
{
    UI08_t bf[8];
    UI08_t i = 0;
    TcpFlags_t fl;

    // Tcp flags for HTTP header
    fl.data = 0;
    fl.bits.ack = 1;
    fl.bits.psh = 1;
    fl.bits.fin = 1;

    webBfPos = sprintf(webBf, http200, "text/html");
    
    webBfPos += sprintf(webBf + webBfPos, "Flash ID: %X<br />", FlashReadId());

    UI16_t bfSize = 512;
    UI16_t contentIndex = 0;
    UI16_t contentLength = 0;
    UI32_t flashLocation = 0;
    UI16_t fileTypeLength = 0;
    char fileType[64];

    FlashRxBytes(0*32, &contentLength, 2);
    FlashRxBytes(0*32+2, &fileTypeLength, 2);
    FlashRxBytes(0*32+4, fileType, fileTypeLength);
    fileType[fileTypeLength] = 0;
    flashLocation = 0 * 32 + 4 + fileTypeLength;

    webBfPos += sprintf(webBf + webBfPos, "Content Length: %d<br />File Type Length: %d<br />File Type: %s<br />Flash Location: %lu",
    contentLength,
     fileTypeLength,
     fileType,
     flashLocation);


    tcpTxPacket(webBfPos, fl, connection);

}
void webSysRtos(TcpConnection_t* connection, char **params)
{
    TcpFlags_t fl;
    UI08_t i = 0;
    char state [32];
    RtosTask_t* ptr = &RtosTaskIdleObj;
    
    // Tcp flags for HTTP header
    fl.data = 0;
    fl.bits.ack = 1;
    fl.bits.psh = 1;

    webBfPos = sprintf(webBf, http200, "text/html");
    tcpTxPacket(webBfPos, fl, connection);

    fl.bits.fin = 1;

    webBfPos = sprintf(webBf, httpRtosTaskTable);
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
        webBfPos += sprintf(webBf+webBfPos, "<tr><td>%d</td>" // i
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

    tcpTxPacket(strlen(webBf), fl, connection);
    tcpCloseObj(connection);
}

void webSysTcpip(TcpConnection_t* connection, char **params)
{
    UI08_t i;
    TcpFlags_t fl;

    // Tcp flags for HTTP header
    fl.data = 0;
    fl.bits.ack = 1;
    fl.bits.psh = 1;
    fl.bits.fin = 1;
    
    webBfPos = sprintf(webBf, http200, "text/html");
    webBfPos += sprintf(webBf, httpConnectionTable);

    for (i = 0; i < TCP_MAX_CONNECTIONS; i++)
    {
        TcpConnection_t* c = &(tcpConnections[i]);
        
        webBfPos += sprintf(webBf + webBfPos, "<tr><td>%d</td><td>%d.%d.%d.%d</td><td>%u</td><td>%s</td></tr>",
                i,
                c->remoteIp[0],
                c->remoteIp[1],
                c->remoteIp[2],
                c->remoteIp[3],
                c->remotePort,
                TcpStateStrings[c->state]);

    }
    strcpy(webBf+webBfPos, "\r\n");
    
    tcpTxPacket(webBfPos, fl, connection);
}

void webIndex(TcpConnection_t* connection, char **params)
{
    strcpy(webBf, httpHelloWorld);

    // Tcp flags for HTTP header
    TcpFlags_t fl;
    fl.data = 0;
    fl.bits.ack = 1;
    fl.bits.psh = 1;
    fl.bits.fin = 1;

    tcpTxPacket(strlen(httpHelloWorld), fl, connection);
    
}

void webTest(TcpConnection_t* connection, char **params)
{
    webBfPos = sprintf(webBf, http200, "text/html");
    webBfPos += sprintf(webBf+webBfPos, "1: %s<br />2: %s<br />", params[0], params[1]);

    // Tcp flags for HTTP header
    TcpFlags_t fl;
    fl.data = 0;
    fl.bits.ack = 1;
    fl.bits.psh = 1;
    fl.bits.fin = 1;

    tcpTxPacket(webBfPos, fl, connection);
    
}

void web404(TcpConnection_t * connection)
{
    Route_t route404;
    route404.options.location = 11;
    webServeFlash(connection, &route404);
    return;
    strcpy(webBf, http404);

    // Tcp flags for HTTP header
    TcpFlags_t fl;
    fl.data = 0;
    fl.bits.ack = 1;
    fl.bits.psh = 1;
    fl.bits.fin = 1;

    tcpTxPacket(strlen(http404), fl, connection);
}

void webServeFlash(TcpConnection_t* connection, Route_t* route)
{
    TcpFlags_t fl;

    UI16_t bfSize = 512;
    UI16_t contentIndex = 0;
    UI16_t contentLength = 0;
    UI32_t flashLocation = 0;
    UI16_t fileTypeLength = 0;
    char fileType[64];

    FlashRxBytes(route->options.location*32, &contentLength, 2);
    FlashRxBytes(route->options.location*32+2, &fileTypeLength, 2);
    FlashRxBytes(route->options.location*32+4, fileType, fileTypeLength);
    fileType[fileTypeLength] = 0;

    printf("Content Length: %d, FileType: %s (%d)\n", contentLength, fileType, fileTypeLength);
    
    // Tcp flags for HTTP header
    fl.data = 0;
    fl.bits.ack = 1;
    fl.bits.psh = 1;

    webBfPos = sprintf(webBf, http200, fileType);
    tcpTxPacket(webBfPos, fl, connection);
    printf("Send HTTP header\n");
    flashLocation = route->options.location * 32 + 4 + fileTypeLength;

    do
    {
        if (contentIndex + bfSize > contentLength)
        {
            fl.bits.fin = 1;
            bfSize = contentLength - contentIndex;
        }

        printf("reading flash @ %lu for %d bytes\n", flashLocation, bfSize);
        FlashRxBytes(flashLocation, webBf, bfSize);
        tcpTxPacket(bfSize, fl, connection);

        // TODO: Figure out how big our available buffer is
        // TODO: Wait for acknowlegde?

        contentIndex += bfSize;
        flashLocation += bfSize;
        
    }while(contentLength > contentIndex);

}


void WebserverHandle(void* con, bool_t push, char* d, UI16_t s)
{
    UI08_t i;
    UI08_t argInd = 0;
    UI08_t argCnt = 0;
    
    char webRequestType[4];
    char webRequestUri[64];
    char * strPtr = d;
    char * routeUriPtr = NULL;

    TcpConnection_t *connection = (TcpConnection_t*) con;
    Route_t *route;
    bool_t routeMatched = FALSE;
    char* args[8];

    webBfPos = 0;
    webBf = tcpGetDataPtr();

    if (push)
    {
        i = 0;
        while (i < sizeof(webRequestType) && *strPtr != ' ' && *strPtr != '\0')
        {
            webRequestType[i] = *strPtr;
            i++;
            strPtr++;
        }
        webRequestType[i] = 0;

        strPtr = d+i+1;
        i = 0;
        while (i < sizeof(webRequestUri) && *strPtr != ' ' && *strPtr != '\0')
        {
            webRequestUri[i] = *strPtr;
            i++;
            strPtr++;
        }
        webRequestUri[i] = 0;

        // Match a route
        for(i = 0; i < NUM_OF_ROUTES; i++)
        {
            route = &(webRoutes[i]);
                
            // If the route table says there are no arguments, we can save
            // time by using strcmp() instead of parsing it letter-by-letter.
            if (route->options.arguments == FALSE)
            {
                if (strcmp(route->url, webRequestUri) == 0)
                {
                    // Reset args
                    routeMatched = TRUE;
                    memset(args, 0, sizeof(args));
                    break;
                }
            }
            else
            {
                strPtr = webRequestUri; // set strPtr to begin of URL
                routeUriPtr = route->url;

                argCnt = 0;
                argInd = 0;
                
                routeMatched = TRUE;

                // Parse the route to disapprove our "routeMatched = TRUE"
                while (*routeUriPtr != '\0')
                {
                    // If the route Uri contains a ':', then it's a "wildcard"
                    // Wildcard ends at the next slash
                    if (*routeUriPtr == ':')
                    {
                        routeUriPtr++;
                        
                        argInd = (*routeUriPtr) - '0';
                        
                        // Note the index
                        if (argInd < sizeof(args))
                        {
                            args[argInd] = strPtr;
                            if (argInd > argCnt)
                                argCnt = argInd;
                        }
                        else
                        {
                            // TODO: error!
                        }
                        
                        // Walk through end.
                        while (! (*strPtr == '\0' || *strPtr == '/') )
                        {
                            strPtr++;
                        }

                        while (! (*routeUriPtr == '\0' || *routeUriPtr == '/') )
                        {
                            routeUriPtr++;
                        }
                        continue;
                    }
                    else
                    {
                        // Match both strings
                        if (*strPtr != *routeUriPtr)
                        {
                            routeMatched = FALSE;
                            break;
                        }

                        routeUriPtr++;
                        strPtr++;
                    }
                }

                if (routeMatched == FALSE)
                {
                    memset(args, 0, sizeof(args));
                }
                else
                {
                    // Clean up the arguments list. We need to change string ends
                    for (argInd = 0; argInd < argCnt; argInd++)
                    {
                        strPtr = args[argInd];
                        while (! (*strPtr == '\0' || *strPtr == '/') )
                        {
                            strPtr++;
                        }
                        *strPtr = 0;
                    }

                    // Done , end the suffering
                    break;
                }
            }
        }

        if (routeMatched)
        {
            if (route->callback == NULL)
            {
                webServeFlash(connection, route);
            }
            else
            {
                route->callback(connection, args);
            }
        }
        else
        {
            web404(connection);
        }
        tcpCloseObj(connection);
    }

}