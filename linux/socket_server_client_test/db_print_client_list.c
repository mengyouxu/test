#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <db.h>

#include "client_info.h"

void db_print_err(int ret,int line)
{
        if(ret != 0){
                printf("L%d ERROR: %s\n",line,db_strerror(ret));
        }
}

int main(int argc, char *argv[])
{
	DB *dbp;
	DBC *db_cursor;
	DBT key,data;
	int ret_val = 0;
	
	ret_val = db_create(&dbp,NULL,0);
	db_print_err(ret_val,__LINE__);

	ret_val = dbp->open(dbp,NULL,"client_list.db",NULL,DB_HASH,DB_CREATE,0);
	db_print_err(ret_val,__LINE__);
	ret_val = dbp->cursor(dbp,NULL,&db_cursor,0);
	db_print_err(ret_val,__LINE__);
	memset(&key,0,sizeof(DBT));
	
	while(ret_val == 0){
		memset(&data,0,sizeof(DBT));
		ret_val = db_cursor->c_get(db_cursor,&key,&data,DB_NEXT);
		db_print_err(ret_val,__LINE__);
		if(ret_val == 0){
			printf("size[%d][%s] [%s:%u]\n",data.size,
				((struct client_info *)data.data)->name,
				((struct client_info *)data.data)->addr,
				((struct client_info *)data.data)->port);
		}
	}	
	if(dbp != NULL){
		dbp->close(dbp,0);
	}
	return 0;
}
