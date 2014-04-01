//g++  testmysql.cpp -lmysqlclient -o testmysql.linux
#include <errno.h>
#include <unistd.h>
#include <mysql/mysql.h>

#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>


int main(int argc, char* argv[]) {

    MYSQL* g_pmysql = NULL;
    MYSQL_RES* sql_res;
    MYSQL_ROW sql_row;


    g_pmysql = mysql_init(NULL);
    if(NULL == g_pmysql) {
        perror("mysql_init");
        return EXIT_FAILURE;
    }


    // g_pmysql = mysql_real_connect(g_pmysql, const char *host,
    //    				   const char *user,
    //    				   const char *passwd,
    //    				   const char *db,
    //    				   unsigned int port,
    //    				   const char *unix_socket,
    //    				   unsigned long clientflag);

    g_pmysql = mysql_real_connect(g_pmysql, "127.0.0.1", NULL, NULL, "test", 0, NULL, 0);
    if(!g_pmysql) {
        perror("mysql_real_connect");
        return EXIT_FAILURE;
    }

    if(mysql_query(g_pmysql, "select * from user_tbl limit 10")) {
        perror("mysql_query");
        return EXIT_FAILURE;
    }

    if(!(sql_res = mysql_store_result(g_pmysql))) {
        perror("");
        return EXIT_FAILURE;        
    }

    std::cout << "mysql_num_rows:" << mysql_num_rows(sql_res) << std::endl;


    while(sql_row = mysql_fetch_row(sql_res)) {
        int field_count = -1;
        while(field_count < mysql_field_count(g_pmysql)) {
            std::cout << sql_row[++field_count] << "|";
            
        }
        std::cout << std::endl;
        
            
    }

    mysql_free_result(sql_res);

    
    mysql_close(g_pmysql);
    return EXIT_SUCCESS;
}
