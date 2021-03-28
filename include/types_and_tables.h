#ifndef DZ_4_PARSER_H
#define DZ_4_PARSER_H

/*typedef enum {
    L_CONTENT_TYPE,
    L_OTHER_KEYS,
    L_ENTER,
    L_EOF,
    L_TEXT,
    L_BOUND,
} lexem_t;*/

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
    S_END
} state_t;

typedef enum {
    get_key,
    EVENT_GET_KEY_VALUE,
    EVENT_MISS_ENTER,
    EVENT_TEXT_FOUND,
    EVENT_BOUND_FOUND,
} cjson_event_t;

typedef void (*cjson_callback_t)(cjson_event_t event, const char *s, const char *end, void *data);
typedef void* (action_t)(char*, char**end, cjson_callback_t callback, void *data);
typedef int (*action_t)(const char *s, const char **end, cjson_callback_t callback, void *data);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

static int keys(const char *s, const char **end, cjson_callback_t callback, void *data) { callback(get_key, s, *end, data); return 0; }
static int values(const char *s, const char **end, cjson_callback_t callback, void *data) { callback(get_key_value, s, *end, data); return 0; }
static int enter(const char *s, const char **end, cjson_callback_t callback, void *data) { callback(miss_enter, s, *end, data); return 0; }
static int text_bound(const char *s, const char **end, cjson_callback_t callback, void *data) { callback(text_found, s, *end, data); return 0; }
static int end(const char *s, const char **end, cjson_callback_t callback, void *data) { callback(bound_found s, *end, data); return 0; }


const unsigned int S_COUNT = 8;
const unsigned int L_COUNT = 6;

const rule_t table[S_COUNT][L_COUNT] = {
                  /*L_CONTENT_TYPE      L_OTHER_KEYS       L_ENTER        L_NO_ENTER          L_EOF            L_TEXT         */
/*S_GET_KEY*/        {S_GET_KEY_VALUE,get_key_value},      {S_GET_KEY_VALUE,get_key_value},    {S_ERR,NULL},   {S_ERR,NULL},     {S_ERR,NULL}, 	 {S_ERR,NULL},
/*S_GET_KEY_VALUE*/  {S_ERR,NULL},      {S_ERR,NULL},    {S_ERR,miss_enter},   {S_ERR,get_key},     {S_ERR,NULL}, 	 {S_ERR,NULL},
/*S_ENTER*/          {S_ERR,NULL},      {S_ERR,NULL},    {S_ERR,NULL},   {S_ERR,NULL},     {S_EOF,NULL}, 	 {S_TEXT,NULL},
/*S_TEXT*/           {S_ERR,NULL},      {S_ERR,NULL},    {S_ERR,NULL},   {S_ERR,NULL},     {S_EOF,NULL}, 	 {S_TEXT,text_bound},
/*S_EOF*/            {S_ERR,NULL},      {S_ERR,NULL},    {S_ERR,NULL},   {S_ERR,NULL},     {S_END,NULL}, 	 {S_ERR,NULL},
/*S_END*/            {S_ERR,NULL},      {S_ERR,NULL},    {S_ERR,NULL},   {S_ERR,NULL},     {S_ERR,end},     {S_ERR,NULL},
};

#endif //DZ_4_PARSER_H
