//gcc apue.c -o apue.linux

//gcc -std=c99 apue.c -o apue.linux

//c89 true false is not define 
//gcc -std=c89 apue.c -o apue.linux


//stdio, erno, cwd  path, sigaction, time, atexit
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <sys/times.h>

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

void atexit_fun1()
{
printf("atexit_fun1\n");
}

void atexit_fun2()
{
printf("atexit_fun2\n");
}

int main(int argc, char* argv[])
{
printf("Program %s Begin\n", argv[0]);
struct tms begintime;
clock_t begreal = times(&begintime);

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


time_t t = time(NULL);
struct tm* localtm = localtime(&t);
printf("Time:%s\n", asctime(localtm));

printf("getlogin:%s\n", getlogin());


atexit(atexit_fun1);
atexit(atexit_fun2);

printf("getpid():%d\n", getpid());

pid_t pid;

if( (pid = fork()) < 0)
{
perror("fork error\n");
}
else if(pid == 0)
{
printf("great this is child process created by fork \n");
printf("getpid():%d\n", getpid());
printf("getppid():%d\n", getppid());
printf("getpgrp():%d\n", getpgrp());
}
else
{
printf("parent process is here.\n");

}

/* extern char** environ; */

/* char** env = environ; */
/* while(*env) */
/* { */
/* ++env; */
/* printf("%s\n", *env); */
/* } */



/* while(environ[]) */
/* { */
/* printf(""); */
/* } */

/* while(!GbStop) */
/* 	/\* while(1)  //C99 define true C89 didn't define *\/ */
/* { */

/* } */
struct tms endtime;
clock_t endreal = times(&endtime);

printf("real:%f\n"
"user:%f\n"
"sys:%f\n",
	       (float)(endreal-begreal)/CLOCKS_PER_SEC, (float)(endtime.tms_utime-begintime.tms_utime)/CLOCKS_PER_SEC, (float)(endtime.tms_stime-begintime.tms_stime)/CLOCKS_PER_SEC );

return 0;
}
