// https://github.com/iqiyi/xHook/blob/master/docs/overview/android_plt_hook_overview.zh-CN.md
#include "test.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

void say_hello()
{
    const int buffer_size = 1024;
    char *buf = new char[buffer_size];
    if (NULL != buf)
    {
        snprintf(buf, buffer_size, "%s", "hello\n");
        printf("%s", buf);
    }
    delete []buf;
}