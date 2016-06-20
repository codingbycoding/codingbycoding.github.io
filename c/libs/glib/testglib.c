//g++ testglib.c -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include  -lglib-2.0  -o testglib.linux

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include <unistd.h>
#include <stdlib.h>

/* GThreadPool *   g_thread_pool_new               (GFunc            func, */
/*                                                  gpointer         user_data, */
/*                                                  gint             max_threads, */
/*                                                  gboolean         exclusive, */
/*                                                  GError         **error); */

/* void            g_thread_pool_free              (GThreadPool     *pool, */
/*                                                  gboolean         immediate, */
/*                                                  gboolean         wait_); */

/* gboolean        g_thread_pool_push              (GThreadPool     *pool, */
/*                                                  gpointer         data, */
/*                                                  GError         **error); */


/* typedef gpointer (*GThreadFunc) (gpointer data); */


/* typedef void            (*GFunc)                (gpointer       data, */
/*                                                  gpointer       user_data); */



void WorkFunc() {
    
}


void PoolWorker(gpointer data, gpointer  user_data) {

    
    int imicrosends = rand()%1000000;
    fprintf(stdout, "%s|   data: %d going to sleep microsends:%d\n", (gchar*)user_data, *((gint*)data), imicrosends);
    usleep(imicrosends);
    
    fprintf(stdout, "end|   data: %d\n", *((gint*)data));    
}

int main(int argc, char** argv) {

    char pchdata[] = "userdata";
    srand(time(NULL));
    fprintf(stdout, "RAND_MAX:%u\n", RAND_MAX);
    
    GThreadPool* pThreadpool = g_thread_pool_new(PoolWorker, pchdata, 10, true, NULL);

    int intarry[10];
    for(int i=0; i<10; i++) {
        intarry[i] = i;
    }
    
    for(int i=0; i<10; i++) {
        g_thread_pool_push(pThreadpool, gpointer(intarry+i), NULL);
    }
    
    g_thread_pool_free(pThreadpool, false, true);
    
    fprintf(stdout, "%s\n", argv[0]);
    return EXIT_SUCCESS; 
}
