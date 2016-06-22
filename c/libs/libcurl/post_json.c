//g++ post_json.c -I/home/adam/Documents/libs/curl-7.42.0/include -L/home/adam/Documents/libs/curl-7.42.0/lib -lcurl -o post_json.linux

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <string>
#include <curl/curl.h>  
  
#define POSTURL    "http://csdk.3333.cn:8088/index.php/user/loginoauth"
#define POSTFIELDS "email=myemail@163.com&password=mypassword&autologin=1&submit=登 录&type="  
#define FILENAME   "curlposttest.log"  
  
size_t write_data(void* buffer, size_t size, size_t nmemb, void *stream) {  
    FILE *fptr = (FILE*)stream;  
    fwrite(buffer, size, nmemb, fptr);  
    return size*nmemb;  
}  


int main(int argc,char *argv[]) {  
    CURL *curl;  
    CURLcode res;  
    FILE* fptr;  
    struct curl_slist *http_header = NULL;


	char szJsonData[1024];  
    memset(szJsonData, 0, sizeof(szJsonData));  
	std::string strJson = "{";  
    strJson += "\"user_name\" : \"test\",";  
    strJson += "\"password\" : \"test123\"";  
    strJson += "}";  
    strcpy(szJsonData, strJson.c_str());  
  
    if ((fptr = fopen(FILENAME, "w")) == NULL) {  
		fprintf(stderr, "fopen file error:%s\n", FILENAME);  
		return -1;  
	}  
  
    curl = curl_easy_init();  
    if (!curl)  {  
		fprintf(stderr,"curl init failed\n");  
		return -1;  
	}  
  
    curl_easy_setopt(curl, CURLOPT_URL, POSTURL); //url地址

	curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/json;charset=UTF-8");  
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);
	
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, szJsonData); //post参数

	
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); //对返回的数据进行操作的函数地址  
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fptr); //这是write_data的第四个参数值  
    curl_easy_setopt(curl, CURLOPT_POST, 1); //设置问非0表示本次操作为post  
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1); //打印调试信息  
    curl_easy_setopt(curl, CURLOPT_HEADER, 1); //将响应头信息和相应体一起传给write_data  
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); //设置为非0,响应头信息location  
    /* curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/Users/zhu/CProjects/curlposttest.cookie");   */
  
    res = curl_easy_perform(curl);  
  
    if (res != CURLE_OK) {  
		switch(res) {  
		case CURLE_UNSUPPORTED_PROTOCOL:  
			fprintf(stderr, "不支持的协议,由URL的头部指定\n");  
		case CURLE_COULDNT_CONNECT:  
			fprintf(stderr, "不能连接到remote主机或者代理\n");  
		case CURLE_HTTP_RETURNED_ERROR:  
			fprintf(stderr, "http返回错误\n");  
		case CURLE_READ_ERROR:  
			fprintf(stderr, "读本地文件错误\n");  
		default:  
			fprintf(stderr, "返回值:%d\n",res);  
		}  
		return -1;  
	}  
  
    curl_easy_cleanup(curl);  
}  
