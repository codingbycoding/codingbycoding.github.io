


#include "NativeTester.h"

#include "stdio.h"

JNIEXPORT void JNICALL Java_NativeTester_greeting
  (JNIEnv * env, jclass cl , jint i, jstring str)
{
  printf("jint:%d  str:%s\n", i, str);
}
