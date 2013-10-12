//gcc apue.c -o apue.linux

//gcc -std=c99 apue.c -o apue.linux

//c89 true false is not define 
//gcc -std=c89 apue.c -o apue.linux

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif


#ifndef bool
#define bool int
#endif


bool GbStop = false;

void sigaction_handle_fun(int signo, siginfo_t * siginfo, void * sigcontext)
{
/* perror("sigaction_handle_fun"); */
printf("sigaction_handle_fun signo:%d\n", signo);
GbStop = true;
}


int main(int argc, char* argv[])
{
printf("Program %s Begin\n", argv[0]);
struct sigaction act, oact;
sigemptyset(&act.sa_mask);
act.sa_flags = SA_SIGINFO;
act.sa_sigaction = sigaction_handle_fun;
sigaction(SIGTERM, &act, &oact);

char chcwdbuf[100];
if(getcwd (chcwdbuf, 100) == NULL)
{
perror("getcwd error");
}
else
{
printf("getcwd %s\n", chcwdbuf);
}

printf("input characters:\n");
int c;
while( (c = getc(stdin)) != EOF)
{
if(putc(c, stdout) == EOF)
{
perror("putc error");
}
}

while(!GbStop)
	/* while(1)  //C99 define true C89 didn't define */
{

}
  
return 0;
}
