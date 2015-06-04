#ifndef _VAL_H
#define _VAL_H

#include <stdint.h>
#include <stdlib.h>
#include <lua.h>  
#include <lauxlib.h>  
#include <lualib.h>

typedef int64_t Val_Integer;
typedef double  Val_Number;
typedef int8_t  Val_Boolean;

#define TVAL_NONE    0
#define TVAL_INTEGER 1
#define TVAL_NUMBER  2
#define TVAL_STRING  3
#define TVAL_BOOLEAN 4
#define TVAL_TABLE   5
#define TVAL_ARRAY   6

typedef union TVal{
	Val_Integer i;
	Val_Number  n;
	Val_Boolean b;
	void       *o;
}TVal;

typedef struct TValue TValue;

#define TValueHead 				\
		int     rcount;			\
		void   (*dctor)(void*); \
		TVal    value;			\
		int     tt

typedef struct TValue{
	TValueHead;
}TValue;

typedef struct iter{
	TValue *key;
	TValue *value;
	size_t  i;
}iter;


TValue     *TVal_New_integer(Val_Integer);
TValue     *TVal_New_number(Val_Number);
TValue     *TVal_New_boolean(int);
TValue     *TVal_New_string(const char *str);
TValue     *TVal_New_lstring(const char *str,size_t len);
TValue     *TVal_New_table();
TValue     *TVal_New_array();

Val_Integer TVal_tointeger(TValue*);
Val_Number  TVal_tonumber(TValue*);
int         TVal_toboolean(TValue*);
const char *TVal_tostring(TValue*);
const char *TVal_tolstring(TValue*,size_t *len);

int         TVal_isinteger(TValue*);
int         TVal_isnumber(TValue*);
int         TVal_isboolean(TValue*);
int         TVal_isstring(TValue*);
int         TVal_istable(TValue*);
int         TVal_isarray(TValue*);
int         TVal_type(TValue*);

TValue     *TVal_table_geti(TValue *t,Val_Integer);
TValue     *TVal_table_getb(TValue *t,Val_Boolean);
TValue     *TVal_table_getn(TValue *t,Val_Number);
TValue     *TVal_table_gets(TValue *t,const char*);

void 		TVal_table_seti(TValue *t,Val_Integer key,TValue *val);
void 		TVal_table_setb(TValue *t,Val_Boolean key,TValue *val);
void 		TVal_table_setn(TValue *t,Val_Number  key,TValue *val);
void 		TVal_table_sets(TValue *t,const char *key,TValue *val);
void        TVal_table_show_list(TValue *t);

static const iter nil_iter = {.i=-1,.key=NULL,.value=NULL};

static inline int TVal_is_vaild_iter(iter *it){
	return !(it->i == nil_iter.i && it->key == nil_iter.key && it->value == nil_iter.value);
}


//array index 1~n
TValue     *TVal_array_get(TValue  *a,size_t);
int 		TVal_array_set(TValue  *a,size_t,TValue *val);
int         TVal_array_push(TValue *a,TValue *v);
int         TVal_array_remove(TValue  *a,size_t);
size_t      TVal_array_len(TValue *a);

iter        TVal_next(TValue *t,iter*);

TValue     *toVal(lua_State *L,int idx);
int         pushVal(lua_State *L,TValue *v);


TValue     *TVal_retain(TValue*);
void        TVal_release(TValue*);

void        TVal_print(TValue*);

#endif