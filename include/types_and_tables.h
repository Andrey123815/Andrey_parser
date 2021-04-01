#ifndef INCLUDE_TYPES_AND_TABLES_H_
#define INCLUDE_TYPES_AND_TABLES_H_

#define S_COUNT 5
#define L_COUNT 7

#include "callback.h"
#include <stddef.h>

typedef enum {
    L_TO,
    L_FROM,
    L_DATE,
    L_CONTENT_TYPE,
    L_ENTER,
    L_EOF,
    L_TEXT,
    L_ERR
} lexem_t;

typedef enum {
    S_BEGIN,
    S_HEAD,
    S_HEAD_END,
    S_BODY,
    S_END,
    S_ERR,
} state_t;

typedef struct {
    state_t state;
    action_t action;
} rule_t;

const rule_t table[S_COUNT][L_COUNT] = {
                     /*L_TO                          L_FROM                        L_DATE                L_CONTENT_TYPE                  L_ENTER                          L_EOF                    L_TEXT*/  // NOLINT
/*S_BEGIN*/   {{S_HEAD, NULL},{S_HEAD, NULL},{S_HEAD, NULL},{S_HEAD, NULL},{S_ERR, NULL},     {S_ERR, NULL}, {S_ERR, NULL}},  // NOLINT
/*S_HEAD*/    {{S_HEAD, NULL},{S_HEAD, NULL},{S_HEAD, NULL},{S_HEAD, NULL},{S_HEAD_END, NULL},{S_ERR, NULL}, {S_ERR, NULL}},  // NOLINT
/*S_HEAD_END*/{{S_ERR, NULL}, {S_ERR, NULL}, {S_ERR, NULL}, {S_ERR, NULL}, {S_ERR, NULL},     {S_END, NULL}, {S_BODY, NULL}},  // NOLINT
/*S_BODY*/    {{S_ERR, NULL}, {S_ERR, NULL}, {S_ERR, NULL}, {S_ERR, NULL}, {S_ERR, NULL},     {S_END, NULL}, {S_BODY, NULL}},  // NOLINT
/*S_END*/     {{S_ERR, NULL}, {S_ERR, NULL}, {S_ERR, NULL}, {S_ERR, NULL}, {S_ERR, NULL},     {S_ERR, NULL}, {S_ERR, NULL}},  // NOLINT
};

#endif  // INCLUDE_TYPES_AND_TABLES_H_
