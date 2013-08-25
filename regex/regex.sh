#!/bin/sh
# M-x set-buffer-file-coding-system RET unix


#set -v

#hungry pattern
#{} *
echo "HungerPattern Begin..."
HungerPattern="[hH][1].*[hH][1]"
grep -P  --color=auto ${HungerPattern} test.html



#lazy pattern
#{}? *?
echo "LazyPattern Begin..."
LazyPattern="[hH][1].*?[hH][1]"
grep -P  --color=auto  ${LazyPattern} test.html


#cross lines pattern
echo "UnixCrossLines Begin..."
UnixCrossLines="\n"


echo "WinCrossLines Begin..."
WinCrossLines="\r\n"


#Backtrace \1
echo "BacktracePattern Begin..."
BacktracePattern="([Hh][1-9]).*?\1"
grep -P --color=auto  ${BacktracePattern} test.html
# grep -P "([Hh][1-9]).*?\1" test.html
