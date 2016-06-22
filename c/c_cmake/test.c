#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

#include "test.h"

#define MAX_LEN 1024
typedef struct Student
{
	long id;
	int count;
	pthread_mutex_t m_mutex;	
	char name[MAX_LEN];
} Student_t;

void* thread_fun_1(void* argstr)
{
	printf("thread_fun_1::%s\n", (char*)argstr);
	pthread_exit("thread_fun exit");
}

Student_t g_stu;
/*g_stu.id = 100100;
  g_stu.name = "Test_name";
  g_stu.count = 10;
 */
int main()
{
	printf("Changed...\n");
	printf("HelloWorld.\n");
	printf("File:%s Line:%d\n", __FILE__, __LINE__);
	Student_t st0 = {1000000, "jack"};
	Student_t *st_ptr = malloc( sizeof(Student_t) );
	st_ptr->id = 2000000;
	strcpy(st_ptr->name, "tom");
	if(NULL == (st_ptr = realloc(st_ptr, sizeof(Student_t) - MAX_LEN)))
	{

	}

	Student_t **st_ptr_ptr;
	st_ptr_ptr = malloc( 4 * sizeof(Student_t) );
	//st_ptr_ptr[0]->id = 8000000;


	static int number = 0;
	pid_t pid_tem = fork();
	if(pid_tem == 0) {
		printf("Parent Process!\n");
	}
	else{
		printf("Child Process!\n");
		printf("Child Process EXIT!\n");
		return 0;
	}

	printf("All number is:%d\n", ++number);
	//exit(0);



	pthread_t pid;
	void* pexit_ret;
	int pret = pthread_create(&pid, NULL, thread_fun_1, "yes pthread");
	if(pret != 0)
	{
		printf("pthread_create failed!\n");
	}
	else
	{
		pthread_join(pid, &pexit_ret);
		printf("pexit_ret:%s\n", (char*)pexit_ret);
	}


	free(st_ptr);
	st_ptr = NULL;
	return 0;
}
//Test Emacs.
