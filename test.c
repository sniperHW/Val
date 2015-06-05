#include <stdio.h>
#include "Val.h"

int main(){

	printf("test lua\n");
	{
		lua_State *L = luaL_newstate();
		luaL_openlibs(L);
		if (luaL_dofile(L,"test.lua")) {
			const char * error = lua_tostring(L, -1);
			lua_pop(L,1);
			printf("%s\n",error);
			return 0;
		}

		lua_getglobal(L,"luaval");
		TValue *v = toVal(L,-1);
		iter it = TVal_next(v,NULL);
		while(TVal_is_vaild_iter(&it)){
			printf("key:");TVal_print(it.key);
			printf(",value:");TVal_print(it.value);printf("\n");
			it = TVal_next(v,&it);
		}
		TVal_release(v);

		v = TVal_New_table();
		TValue *v1 = TVal_New_array();
		int i;
		for(i = 1;i <= 32; ++i)
		{
			TValue *vi = TVal_New_integer(i);
			TVal_array_push(v1,vi);
			TVal_release(vi);
		}
		TVal_table_sets(v,"a",v1);
		TVal_release(v1);

		TValue *v2 = TVal_New_string("hello");
		TVal_table_sets(v,"b",v2);
		TVal_release(v2);		 

		lua_getglobal(L,"func");
		pushVal(L,v);
		if(0 != lua_pcall(L,1,0,0)){
			printf("%s\n",lua_tostring(L,-1));
			return 0;
		}

		TVal_release(v);
	}

	printf("test remove\n");
	{
		TValue *t = TVal_New_table();
		int i = 0;
		for(; i < 16;++i){
			TValue *ti = TVal_New_integer(i);
			TVal_table_seti(t,i*16,ti);
			TVal_release(ti);
		}

		TVal_table_seti(t,7*16,NULL);
		TValue *ti = TVal_New_integer(7);
		TVal_table_seti(t,7*16,ti);
		TVal_release(ti);		

		TVal_table_show_list(t);
		
		for(i = 16; i < 32;++i){
			TValue *ti = TVal_New_integer(i);
			TVal_table_seti(t,i*16,ti);
			TVal_release(ti);
		}

		for(i = 0; i < 32;++i){
			TValue *ti = TVal_table_geti(t,i*16);
			if(ti){
				TVal_print(ti);printf("\n");
				TVal_release(ti);
			}
		}

		printf("test shrink\n");
		for(i = 0; i < 17;++i){
			TValue *ti = TVal_New_integer(i);
			TVal_table_seti(t,i*16,NULL);
			TVal_release(ti);
		}	

		for(i = 0; i < 32;++i){
			TValue *ti = TVal_table_geti(t,i*16);
			if(ti){
				TVal_print(ti);printf("\n");
				TVal_release(ti);
			}
		}

		printf("test table iterator\n");
		iter it = TVal_next(t,NULL);
		while(TVal_is_vaild_iter(&it)){
			printf("key:");TVal_print(it.key);
			printf(",value:");TVal_print(it.value);printf("\n");
			it = TVal_next(t,&it);
		}
		TVal_release(t);		

	}
	{
		printf("----------array-----------\n");
		TValue *array = TVal_New_array();
		int i;
		for(i = 1;i <= 32; ++i)
		{
			TValue *vi = TVal_New_integer(i);
			TVal_array_push(array,vi);
			TVal_release(vi);
		}

		TVal_array_remove(array,1);
		TVal_array_remove(array,1);


		iter it = TVal_next(array,NULL);
		while(TVal_is_vaild_iter(&it)){
			printf("key:");TVal_print(it.key);
			printf(",value:");TVal_print(it.value);printf("\n");
			it = TVal_next(array,&it);
		}
		TVal_release(array);	
	}

	printf("total TValue count:%d\n",TVal_objc());
		
	return 0;
}