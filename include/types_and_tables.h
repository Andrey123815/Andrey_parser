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
    L_BOUND,
} lexem_t;


typedef struct {
    lexem_t lexem;
    int flag;
    char* end;
} flag_lexem;


typedef enum {
    S_BEGIN,
    S_GET_KEY,
    S_GET_KEY_VALUE,
    S_ENTER,
    S_TEXT,
    S_BOUND,
    S_EOF,
    S_END,
    S_ERR
} state_t;


typedef enum {
    KEY,
    VALUE,
    ENTER,
    TEXT_FOUND,
    BOUND_FOUND,
} cjson_event_t;


typedef void (*cjson_callback_t)(cjson_event_t event, const char *s, const char *end, void *data);


typedef void *(action_t)(char*, char**end, cjson_callback_t callback, void *data);


typedef struct {
    state_t state;
    action_t action;
} rule_t;


static int keys(const char *s, const char **end, cjson_callback_t callback, void *data { 
	callback(KEY, s, *end, data); 
	return 0; 
}

static int values(const char *s, const char **end, cjson_callback_t callback, void *data) { 
	callback(VALUE, s, *end, data); 
	return 0;
}

static int text_bound(const char *s, const char **end, cjson_callback_t callback, void *data) { 
	callback(TEXT_FOUND, s, *end, data); 
	return 0;
}

static int end(const char *s, const char **end, cjson_callback_t callback, void *data){ 
	callback(BOUND_FOUND, s, *end, data);
	return 0;
}


const unsigned int S_COUNT = 9;
const unsigned int L_COUNT = 7;

const rule_t table[S_COUNT][L_COUNT] = {
                     /*L_CONTENT_TYPE                  L_OTHER_KEYS         L_ENTER        L_NO_ENTER       L_EOF         L_TEXT      */
/*S_GET_KEY*/        {S_GET_KEY_VALUE,KEY},  {S_GET_KEY_VALUE,values}, {S_ERR,NULL},  {S_ERR,NULL},  {S_ERR,NULL}, {S_ERR,NULL},
/*S_GET_KEY_VALUE*/  {S_ERR,NULL},              {S_ERR,NULL},             {S_ERR,NULL},  {S_ERR,keys},  {S_ERR,NULL}, {S_ERR,NULL},
/*S_ENTER*/          {S_ERR,NULL},              {S_ERR,NULL},             {S_ERR,NULL},  {S_ERR,NULL},  {S_EOF,NULL}, {S_TEXT,NULL},
/*S_TEXT*/           {S_ERR,NULL},              {S_ERR,NULL},             {S_ERR,NULL},  {S_ERR,NULL},  {S_EOF,NULL}, {S_TEXT,text_bound},
/*S_EOF*/            {S_ERR,NULL},              {S_ERR,NULL},             {S_ERR,NULL},  {S_ERR,NULL},  {S_END,NULL}, {S_ERR,NULL},
/*S_END*/            {S_ERR,NULL},              {S_ERR,NULL},             {S_ERR,NULL},  {S_ERR,NULL},  {S_ERR,end},  {S_ERR,NULL}
};


#endif //DZ_4_PARSER_H

