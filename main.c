//
//  main.c
//  DesktopBackground
//
//  Created by apple on 2019/10/30.
//  Copyright © 2019 apple. All rights reserved.
//

#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    sqlite3 *db;
    char *zErrMsg=0;
    int rc;
    char *sql;
    
    rc=sqlite3_open("/Users/apple/Library/Application Support/Dock/desktoppicture.db", &db);
    
    if(rc){
        fprintf(stderr, "Can't open database: %s\n",sqlite3_errmsg(db));
    }else{
        fprintf(stdout, "Opened database successfully\n");
    }
    
    /*create SQL statement*/
    sql="UPDATE data SET value='~/Pictures/壁纸/67055273_p0.jpg';";
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    }else{
       fprintf(stdout, "Operation done successfully\n");
    }
    
    sqlite3_close(db);
    system("killall Dock");
    return 0;
}


