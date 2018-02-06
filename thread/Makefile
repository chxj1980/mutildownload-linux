#①安装的第三方软件
#/usr/bin                             可执行文件
#/usr/lib                              可执行文件的库文件
#/usr/include                     可执行文件的头文件
#②安装的第三方库
#/usr/local/bin                   安装的库的一些测试程序
#/usr/local/lib                    安装的库的库文件
#/usr/local/include            安装的库的头文件

cc = g++
CFLAGS = -g -Wall -O2 -pthread -I./ -I/usr/local/include -I/usr/include/curl
LDFLAGS = -L/usr/local/lib -L/usr/lib
SRC = threadpool.cpp taskthread.cpp curldownload.cpp testdownload.cpp
LLFLAGS = -lcurl

all:
	$(cc) $(CFLAGS) $(SRC) $(LDFLAGS) -o threadpool $(LLFLAGS)
clean:
	rm -rf *.o threadpool
