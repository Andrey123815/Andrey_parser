#ifndef DZ_4_TYPES_AND_TABLES_H
#define DZ_4_PARSER_H

#include <stddef.h>

typedef enum {
    L_CONTENT_TYPE,
    L_OTHER_KEYS,
    L_ENTER,
    L_NO_ENTER,
    L_EOF,
    L_TEXT,
    L_ERR
} lexem_t;

typedef struct {
    lexem_t lexem;
    int flag;
    char* end;
} flag_lexem;

typedef enum {
    S_GET_KEY,
    S_GET_KEY_VALUE,
    S_ENTER,
    S_TEXT,
    S_EOF,
    S_ERR
} state_t;

typedef enum {
    KEY,
    VALUE,
    ENTER,
    TEXT_FOUND,
    BOUND_FOUND,
} cjson_event_t;

typedef void (*callback_t)(cjson_event_t event, void *data);
//typedef void *(action_t)(char*, char**end, cjson_callback_t callback, void *data);
typedef int (*action_t)(callback_t callback, void *data);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

static int keys(callback_t callback, void *data) { callback(KEY, data); return 0;}
static int values(callback_t callback, void *data) { callback(VALUE, data); return 0;}
static int text_bound(callback_t callback, void *data) { callback(TEXT_FOUND, data); return 0;}
static int end(callback_t callback, void *data) { callback(BOUND_FOUND, data); return 0;}


const unsigned int S_COUNT = 5;
const unsigned int L_COUNT = 6;

const rule_t table[S_COUNT][L_COUNT] = {
                     /*L_CONTENT_TYPE              L_OTHER_KEYS             L_ENTER        L_NO_ENTER          L_EOF        L_TEXT      */
/*S_GET_KEY*/        {S_GET_KEY_VALUE,values},  {S_GET_KEY_VALUE,values}, {S_ERR,NULL},   {S_ERR,NULL},     {S_ERR,NULL}, {S_ERR,NULL},
/*S_GET_KEY_VALUE*/  {S_ERR,NULL},              {S_ERR,NULL},             {S_ENTER,NULL}, {S_GET_KEY,keys}, {S_ERR,NULL}, {S_ERR,NULL},
/*S_ENTER*/          {S_ERR,NULL},              {S_ERR,NULL},             {S_ERR,NULL},   {S_ERR,NULL},     {S_EOF,end},  {S_TEXT,text_bound},
/*S_TEXT*/           {S_ERR,NULL},              {S_ERR,NULL},             {S_ENTER,NULL}, {S_ERR,NULL},     {S_EOF,end},  {S_ERR,NULL},
/*S_EOF*/            {S_ERR,NULL},              {S_ERR,NULL},             {S_ERR,NULL},   {S_ERR,NULL},     {S_ERR,NULL}, {S_ERR,NULL}
};

#endif //DZ_4_PARSER_H
