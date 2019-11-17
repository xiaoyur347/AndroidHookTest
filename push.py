#!/usr/bin/env python

from __future__ import print_function
import os
import subprocess


def run_command(cmd):
    p = subprocess.Popen(cmd, shell=True, universal_newlines=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    curline = p.stdout.readline()

    while curline != "":
        curline = curline.strip()
        if len(curline) != 0:
            print (curline)
        curline = p.stdout.readline()
    p.wait()
    print ("ret={}".format(p.returncode))


def push(src, dst):
    cmd = "adb push {} {}".format(src, dst)
    print(cmd)
    run_command(cmd)

def shell(cmd_str):
    cmd = "adb shell {}".format(cmd_str)
    print(cmd)
    run_command(cmd)

if __name__ == "__main__":
    abi="x86"
    push("app/build/intermediates/cmake/debug/obj/{}/test_executable".format(abi), "/data/local/tmp/test_executable")
    push("app/build/intermediates/cmake/debug/obj/{}/libtest_library.so".format(abi), "/data/local/tmp/libtest_library.so")
    shell("chmod 0777 /data/local/tmp/test_executable")
    shell("'export LD_LIBRARY_PATH=/data/local/tmp/;/data/local/tmp/test_executable'")
