//gcc apue.c -o apue.linux

//gcc apue.c -lpthread -o apue.linux

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

#include <pthread.h>

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
char* strsig = strsignal(signo);
if(strsig != NULL)
{
printf("strsig:%s\n", strsig);
}


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

void cleanup_fun(void* arg)
{
printf("cleanup_fun %s\n", (char*)arg);
}

struct counter_t
{
pthread_mutex_t m_mutex;
int m_cout;

} gcounter;


void * pthread_fun0(void* arg)
{
char* charg = (char*)arg;
printf("pthread_fun0 arg:%s\n", arg);
pthread_t pthreadid = pthread_self();
printf("pthread_fun0 pthreadid:%u\n", pthreadid);

pthread_mutex_lock(&(gcounter.m_mutex));
int i=100;
for(; i<113; i++)
{
usleep(1000);
printf("%d\n", (gcounter.m_cout+i));
}

pthread_mutex_unlock(&(gcounter.m_mutex));

pthread_cleanup_push(cleanup_fun, "pthread_fun0 thread first cleanup");
pthread_cleanup_push(cleanup_fun, "pthread_fun0 thread second cleanup");
printf("pthread_fun0 cleanup_push compelete\n");

pthread_cleanup_pop(0);
pthread_cleanup_pop(0);
/* pthread_exit(NULL); */
pthread_exit((void*)0);
}


void * pthread_fun1(void* arg)
{
char* charg = (char*)arg;
printf("pthread_fun1 arg:%s\n", arg);
pthread_t pthreadid = pthread_self();
printf("pthread_fun1 pthreadid:%u\n", pthreadid);

pthread_mutex_lock(&(gcounter.m_mutex));

int i=222;
for(; i<230; i++)
{
usleep(1000);
printf("%d\n", (gcounter.m_cout+i));
}

pthread_mutex_unlock(&(gcounter.m_mutex));

pthread_cleanup_push(cleanup_fun, "pthread_fun1 thread first cleanup");
pthread_cleanup_push(cleanup_fun, "pthread_fun1 thread second cleanup");
printf("pthread_fun1 cleanup_push compelete\n");

pthread_cleanup_pop(0);
pthread_cleanup_pop(0);
return ((void*)1);
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


pthread_t pthreadid = pthread_self();
printf("pthreadid:%u\n", pthreadid);


pthread_mutex_init (&(gcounter.m_mutex), NULL);
gcounter.m_cout = 0;

pthread_attr_t pthreadattr;
pthread_attr_init(&pthreadattr);
size_t pthreadstacksize;

pthread_attr_getstacksize(&pthreadattr, &pthreadstacksize);
printf("pthreadstacksize:%u\n", pthreadstacksize);
printf("pthread_getconcurrency:%d\n", pthread_getconcurrency());

pthread_t newpthreadid;
char* charg = "000 pass to pthread";
int pcreateret = pthread_create(&newpthreadid, NULL, pthread_fun0, charg);
if(pcreateret != 0)
{
perror("pthread_create error");
}
else
{
printf("newpthreadid:%u\n", newpthreadid);
}

pthread_t newpthreadid1;
char* charg1 = "100 pass to pthread";
int pcreateret1 = pthread_create(&newpthreadid1, NULL, pthread_fun1, charg);
if(pcreateret1 != 0)
{
perror("pthread_create error");
}
else
{
printf("newpthreadid:%u\n", newpthreadid1);
}

void* pret;
pthread_join(newpthreadid, &pret);
pthread_join(newpthreadid1, &pret);

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

