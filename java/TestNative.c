/* gcc -I "D:\Program Files (x86)\Java\jdk1.6.0_35\include"  -I "D:\Program Files (x86)\Java\jdk1.6.0_35\include\win32" -shared -o libTestNative.so TestNative.c */

/* gcc -fPIC -I "D:\Program Files (x86)\Java\jdk1.6.0_35\include"  -I "D:\Program Files (x86)\Java\jdk1.6.0_35\include\win32" -shared -o libTestNative.so TestNative.c */


/* cl -I "D:\Program Files (x86)\Java\jdk1.6.0_35\include"  -I "D:\Program Files (x86)\Java\jdk1.6.0_35\include\win32" -LD TestNative.c NativeTester.c -FeTestNative.dll */



#include "TestNative.h"

#include <stdio.h>

JNIEXPORT void JNICALL Java_TestNative_greeting  (JNIEnv * env, jclass cl )
{
  printf("Welcome TestNative.c\n");
}
