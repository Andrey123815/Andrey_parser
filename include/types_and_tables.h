#ifndef INCLUDE_TYPES_AND_TABLES_H_
#define INCLUDE_TYPES_AND_TABLES_H_

#define S_COUNT 5
#define L_COUNT 8

#include <stddef.h>

typedef enum {
    L_TO,
    L_FROM,
    L_DATE,
    L_CONTENT_TYPE,
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
    S_KEY,
    S_VALUE,
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
} event_t;

typedef void (*callback_t)(event_t event, void *data);
typedef int (*action_t)(callback_t callback, void *data);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

static int keys(callback_t callback, void *data) { callback(KEY, data); return 0;}
static int values(callback_t callback, void *data) { callback(VALUE, data); return 0;}
static int body(callback_t callback, void *data) { callback(TEXT_FOUND, data); return 0;}
static int end(callback_t callback, void *data) { callback(BOUND_FOUND, data); return 0;}


/*const unsigned int S_COUNT = 5;
const unsigned int L_COUNT = 8;*/

const rule_t table[S_COUNT][L_COUNT] = {
                /*L_CONTENT_TYPE              L_TO                      L_FROM                        L_DATE                  L_ENTER                 L_NO_ENTER                   L_EOF                     L_TEXT*/  // NOLINT
/*S_KEY*/  {{S_VALUE, values},    {S_VALUE, values},   {S_VALUE, values},   {S_VALUE, values},   {S_ERR,NULL},  {S_ERR,NULL}, {S_ERR,NULL}, {S_ERR,NULL}},  // NOLINT
/*S_VALUE*/{{S_ERR,NULL}, {S_ERR,NULL}, {S_ERR,NULL},{S_ERR,NULL},{S_ENTER,NULL},{S_KEY,NULL}, {S_ERR,NULL}, {S_ERR,NULL}},  // NOLINT
/*S_ENTER*/{{S_ERR,NULL}, {S_ERR,NULL}, {S_ERR,NULL},{S_ERR,NULL},{S_ERR,NULL},  {S_ERR,NULL}, {S_EOF,NULL}, {S_TEXT,NULL}},  // NOLINT
/*S_TEXT*/ {{S_ERR,NULL}, {S_ERR,NULL}, {S_ERR,NULL},{S_ERR,NULL},{S_ENTER,NULL},  {S_ERR,NULL}, {S_EOF,NULL}, {S_ERR,NULL}},  // NOLINT
/*S_EOF*/  {{S_ERR,NULL}, {S_ERR,NULL}, {S_ERR,NULL},{S_ERR,NULL},{S_ERR,NULL},  {S_ERR,NULL}, {S_ERR,NULL}, {S_ERR,NULL}},  // NOLINT
};

#endif  // INCLUDE_TYPES_AND_TABLES_H_
