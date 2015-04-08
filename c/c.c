/* gcc -ggdb c.c -o c.linux */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <ucontext.h>

myPrint(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	printf("%s\n", fmt);
	/* printf("22 %d\n", *ap); */
    
	int nVar1 = va_arg(ap, int);
	printf("nVar1 %d\n", nVar1);
	/* printf("32 %d\n", *ap); */
	/* printf("32 %d\n", ap); */

  
	/* char* s = NULL; */
	/* s = va_arg(ap, char*); */
	/* s = va_arg(ap, int); */
	/* printf( */
	/* printf("string %s\n", ap); */
	va_end(ap);
}

/* myPrint(const char* fmt, ...) */
/* { */
/*   va_list ap; */
/*   va_start(ap, fmt); */
  
/*   va_end(ap); */
/* } */


void test_ucontext(void* arg) {
	printf("test_ucontext\n");
}


int main() {
	//char stack[1024*1024];
	void* stack = calloc(1, sizeof(char)*1024*1024*100);

	
	printf("HelloWorld!\n");
	myPrint("vararg %d%d%d", 22, 32, "jack");

	printf("%s\n", "abc");

	int context_run_count_limit = 8;
	ucontext_t context, ocontext;;
	getcontext(&context);

	printf("ucontext ?\n");
	if(0 != context_run_count_limit--) {
		setcontext(&context);
	}

  	getcontext(&context);
	context.uc_stack.ss_sp = stack;
	context.uc_stack.ss_size = 1024*1024*100;
	context.uc_stack.ss_flags = 0;
	context.uc_link = &ocontext;
	//context.uc_link = NULL;
	makecontext(&context, (void (*)(void))&test_ucontext, 0);		
	swapcontext (&ocontext, &context);



	printf("The end of main.\n");
	return 0;
}
