#include "stddefs.h"

//#include "webserver/router.h"

void webserverIndex(char **params);
void webserverAbout(char **params);
void webserverGet(char **params);

#define DEF_STR_CONCAT(a,b) a##b
#define DEF_STR_CONCAT_COUNT(a,b) DEF_STR_CONCAT(a,b)

#define routerIndexDef(method, url, callback) \
    { method, url, callback },

#define routerIndexCnt(method, url, callback) \
    DEF_STR_CONCAT_COUNT(ROUTE_, __COUNTER__),

#define routerTable(on) \
    on("GET","/", webserverIndex) \
    on("GET","/about", webserverAbout) \
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
void webserverAbout(char **params)
{
    //
}
void webserverGet(char **params)
{
    //
}

void WebserverHandle()
{
    //
}