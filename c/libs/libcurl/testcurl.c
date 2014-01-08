//gcc -I/home/abc/Document/curl-7.34.0/include  -lcurl testcurl.c -o testcurl.linux

#include <curl/curl.h>
#include <stdio.h>

int main()
{
  CURL* urlhandle = curl_easy_init();

  if(NULL == urlhandle)
    {
      //fprintf(STDOUT, "curl_easy_init error");
      printf("curl_easy_init error\n");
      return -1;
    }
  
  curl_easy_setopt(urlhandle, CURLOPT_URL, "http://www.baidu.com");
  CURLcode retcode = curl_easy_perform(urlhandle);

  if(0 !=  retcode)
    {
      printf("curl_easy_perform error: %s\n", curl_easy_strerror(retcode));
    }
  
  curl_easy_cleanup(urlhandle);
  
  return 0;
}
