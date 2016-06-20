//g++  testmysql.cpp -lmysqlclient -o testmysql.linux

//g++ -ggdb -std=c++0x testmysql.cpp -I/home/adam/test/strike2014/server/proto/client -I/home/adam/test/strike2014/server/online/src -L/home/adam/test/strike2014/server/proto/client -L/usr/local/lib/ -L/usr/local/lib/ -L/usr/lib64/mysql -lssl  -lclientproto -lmysqlclient -lprotobuf -o testmysql.linux 
	
#include <errno.h>
#include <unistd.h>
#include <mysql/mysql.h>

#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "pb0x01.pb.h"

int binary_exec_sql(MYSQL* g_pmysql, MYSQL_BIND* bind_data, const char* sql_cmd, google::protobuf::Message* message) {
	MYSQL_STMT* stmt = mysql_stmt_init(g_pmysql);
	if(NULL == stmt) {
		perror("mysql_stmt_init");
		return -1;
	}

	int ret = mysql_stmt_prepare(stmt, sql_cmd, strlen(sql_cmd));
	if(0 != ret) {
		perror("mysql_stmt_prepare");
		return -1;
	}
	
	std::string str;
	message->SerializeToString(&str);

	if(mysql_stmt_bind_param(stmt, bind_data)) {
		perror("mysql_stmt_bind_param");
		mysql_stmt_close(stmt);
		return -1;
	}

	if(mysql_stmt_send_long_data(stmt, 0, str.c_str(), str.size())) {
		perror("mysql_stmt_send_long_data");
		mysql_stmt_close(stmt);
		return -1;
	}

	if(0 != mysql_stmt_execute(stmt)) {
		perror("mysql_stmt_execute");
		mysql_stmt_close(stmt);
		return -1;
	}

	mysql_stmt_close(stmt);
	return 0;
}

int binary_exec_sql_out(MYSQL* g_pmysql, /*MYSQL_BIND* bind_data,*/ const char* sql_cmd, google::protobuf::Message* message) {
	MYSQL_STMT* stmt = mysql_stmt_init(g_pmysql);
	if(NULL == stmt) {
		perror("mysql_stmt_init");
		return -1;
	}

	int ret = mysql_stmt_prepare(stmt, sql_cmd, strlen(sql_cmd));
	if(0 != ret) {
		perror("mysql_stmt_prepare");
		return -1;
	}
	
	MYSQL_BIND bind_out[1];
	char ch_out[2048] = {0};
	unsigned long llength = 0;
	memset(bind_out, 0, sizeof(bind_out));
	bind_out[0].buffer_type = MYSQL_TYPE_BLOB;
	bind_out[0].buffer = ch_out;
	bind_out[0].buffer_length = sizeof(ch_out);
	bind_out[0].length = &llength;
	bind_out[0].is_null = false;
		
	
	if(0 !=  mysql_stmt_bind_result(stmt, bind_out)) {
		perror("mysql_stmt_bind_result");
		mysql_stmt_close(stmt);
		return -1;
	}

	if(0 != mysql_stmt_execute(stmt)) {
		perror("mysql_stmt_execute");
		mysql_stmt_close(stmt);
		return -1;
	}

	// MYSQL_RES* prepare_meta_result = mysql_stmt_result_metadata(stmt); 
	// unsigned int column_count= mysql_num_fields(prepare_meta_result);
	
		
	if(0 != mysql_stmt_store_result(stmt)) {
		perror("mysql_stmt_store_result");
		mysql_stmt_close(stmt);
		return -1;
	}		

	if(0 != mysql_stmt_fetch(stmt)) {
		perror("mysql_stmt_fetch");
		mysql_stmt_close(stmt);
		return -1;
	}

	// mysql_stmt_fetch_column(stmt, bind_out, 0, 0);

	message->ParseFromArray(bind_out[0].buffer, *bind_out[0].length);

	mysql_stmt_free_result(stmt);
	mysql_stmt_close(stmt);
	return 0;
}


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

    g_pmysql = mysql_real_connect(g_pmysql, "127.0.0.1", "strike2014", "strike@2014", NULL, 0, NULL, 0);
    if(!g_pmysql) {
        perror("mysql_real_connect");
        return EXIT_FAILURE;
    }

    // if(mysql_query(g_pmysql, "select * from user_tbl limit 10")) {
    //     perror("mysql_query");
    //     return EXIT_FAILURE;
    // }

    // if(!(sql_res = mysql_store_result(g_pmysql))) {
    //     perror("");
    //     return EXIT_FAILURE;        
    // }

    // std::cout << "mysql_num_rows:" << mysql_num_rows(sql_res) << std::endl;

    // while(sql_row = mysql_fetch_row(sql_res)) {
    //     int field_count = -1;
    //     while(field_count < mysql_field_count(g_pmysql)) {
    //         std::cout << sql_row[++field_count] << "|";
            
    //     }
    //     std::cout << std::endl;        
            
    // }

    // mysql_free_result(sql_res);

	// std::string str_real = "INSERT user_tbl VALUES()";
	
	// if(mysql_real_query(g_pmysql, str_real.c_str(), str_real.size())) {
    //     perror("mysql_real_query");
    //     return EXIT_FAILURE;
    // }

	// MYSQL_STMT* stmt = mysql_stmt_init(g_pmysql);
	// if(NULL == stmt) {
	// 	perror("mysql_stmt_init");
	// 	return EXIT_FAILURE;
	// }

	// char query[2048] = {0};
	// snprintf(query, sizeof(query), "INSERT VALUES(%d, %d, ?)", userid, maild_id);
	
	// int ret = mysql_stmt_prepare(stmt, query, strlen(query));
	// if(0 != ret) {
	// 	perror("mysql_stmt_prepare");
	// 	return EXIT_FAILURE;
	// }

	// commonproto::pb_mail_t pb_mail;
	
	// std::string str;
	// pb_mail.SerializeToString(&str);
	
	// MYSQL_BIND bind_input[1];
	// memset(bind_input, 0, sizeof(bind_input));
	// bind_input[0].buffer_type = MYSQL_TYPE_BLOB;
	// bind_input[0].buffer = str.c_str();
	// bind_input[0].buffer_length = str.size();
	// bind_input[0].length = 0;
	// bind_input[0].is_null = false;	
		
	// if(!mysql_stmt_bind_param(stmt, &bind_input)) {
	// 	perror("mysql_stmt_bind_param");
	// 	mysql_stmt_close(stmt);
	// 	return EXIT_FAILURE;
	// }

	// if(!mysql_stmt_send_long_data(stmt, 0, str.c_str(), str.size())) {
	// 	perror("mysql_stmt_send_long_data");
	// 	mysql_stmt_close(stmt);
	// 	return EXIT_FAILURE;
	// }

	// if(0 != mysql_stmt_execute(stmt)) {
	// 	perror("mysql_stmt_execute");
	// 	mysql_stmt_close(stmt);
	// 	return EXIT_FAILURE;
	// }

	// mysql_stmt_close(stmt);

	commonproto::pb_mail_t pb_mail;
	pb_mail.set_mail_id(10049899);
	pb_mail.set_title("测试");
	pb_mail.set_sender("");
	pb_mail.set_content("");
	pb_mail.set_timestamp(10049899);
	pb_mail.set_read_mark(0);

	commonproto::pb_money_t* money = pb_mail.mutable_attachment()->add_moneys();
	money->set_type(commonproto::DIAMOND_MONEY);
	money->set_count(89);
	
	MYSQL_BIND bind_data[1];
	std::string str;
	pb_mail.SerializeToString(&str);
	memset(bind_data, 0, sizeof(bind_data));
	bind_data[0].buffer_type = MYSQL_TYPE_BLOB;
	// bind_data[0].buffer = str.c_str();
	// bind_data[0].buffer_length = str.size();
	// bind_data[0].length = 0;
	bind_data[0].is_null = false;

	// const char* sql_cmd = "INSERT strike2014_db_1_5.mail_table_4 VALUES(10045, 10049899, '测试', '', '', ?, 0, 10049899)";
	
 // 	if(0 != binary_exec_sql(g_pmysql, bind_data, sql_cmd, &pb_mail)) {
		
 // }

	// MYSQL_BIND bind_out[1];
	// std::string str_out;
	// char ch_out[2048] = {0};
	// unsigned long llength = 0;
	// memset(bind_out, 0, sizeof(bind_out));
	// bind_out[0].buffer_type = MYSQL_TYPE_BLOB;
	// bind_out[0].buffer = ch_out;
	// bind_out[0].buffer_length = sizeof(ch_out);
	// bind_out[0].length = &llength;
	// bind_out[0].is_null = false;
	pb_mail.Clear();

	const char* sql_cmd_out = "SELECT attachment from strike2014_db_1_5.mail_table_4 where mail_id = 10049899";
	
	if(0 != binary_exec_sql_out(g_pmysql, /*bind_out,*/ sql_cmd_out, &pb_mail)) {
		
 }
	std::cout << pb_mail.Utf8DebugString() << std::endl;

    mysql_close(g_pmysql);
    return EXIT_SUCCESS;
}
