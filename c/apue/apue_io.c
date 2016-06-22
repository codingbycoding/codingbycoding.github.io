//gcc apue_io.c -o apue_io.linux

//gcc apue_io.c -lpthread -o apue_io.linux


#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
  printf("%s \n", argv[0]);

  int n;
  int fds[2];
  pid_t pid;

  enum {MAXLINE = 1024}; 
  char chbuf[MAXLINE];
  if( pipe(fds) < 0)
    {
      perror("pipe < 0 \n");
    }
  
  if( (pid = fork()) < 0)
    {
      printf("fork < 0\n");
    }
  else if(pid == 0)
    {
      sleep(2);
      printf("fork child\n");
      close(fds[1]);
      n = read(fds[0], chbuf, MAXLINE);
      write(STDOUT_FILENO, chbuf, n);
      
    }
  else 
    {
      printf("fork parent\n");
      close(fds[0]);
      write(fds[1], "HelloWorld!\n", 12);
    }

  sleep(3);
  return 0;
}
