#!/usr/bin/env python
#coding:utf-8

import os
import sys
import threading,time
from time import sleep, ctime

class Work_Job(threading.Thread):

    def __init__(self, *args, **kwargs):
        super(Work_Job, self).__init__(*args, **kwargs)
        self.__flag = threading.Event()     # 用于暂停线程的标识
        self.__flag.set()       # 设置为True
        self.__running = threading.Event()      # 用于停止线程的标识
        self.__running.set()      # 将running设置为True

    def run(self):
        while self.__running.isSet():
            self.__flag.wait()      # 为True时立即返回, 为False时阻塞直到内部的标识位为True后返回
            print time.time()
            time.sleep(1)

    def pause(self):
        self.__flag.clear()     # 设置为False, 让线程阻塞

    def resume(self):
        self.__flag.set()    # 设置为True, 让线程停止阻塞

    def stop(self):
        self.__flag.set()       # 将线程从暂停状态恢复, 如何已经暂停的话
        self.__running.clear()        # 设置为False

        _time = [2, 4, 6, 8]
        # Thread hang time 线程挂起的时间
        _maxlink = len(_time)
        # A pool of thread max-link 线程池的最大的数量
        _thread_pool = []

        # A pool of thread that save instantiation threads   存放线程实例的线程池


#
# def loop(index, time):
#     """ A function to class Thread for sleep some times """
#     print "start loop %s at: " % index, ctime()
#     sleep(time[index])
#     print "end loop %s at: " % index, ctime()
#
# def Thread_Pool(*arg):
#     """ A function that create and save instantiation
#      of threading to thread pool """
#     func, LN, Time = arg
#     for i in range(LN):
#         t = threading.Thread(target=func, args=(i, Time))
#         _thread_pool.append(t)
#         # 将线程实例放到线程池
#
# def Thread_Start(arg):
#     """ A function that represents a thread of control. """
#     for i in range(arg):
#         _thread_pool[i].start()



## new function

class my_thread(threading.Thread):
    _time = [2, 4, 6, 8]
    # Thread hang time 线程挂起的时间
    _maxlink = len(_time)
    # A pool of thread max-link 线程池的最大的数量
    _thread_pool = []

    def __init__(self,*arg):
        pass

    # A pool of thread that save instantiation threads   存放线程实例的线程池

    def loop(index, time):
        """ A function to class Thread for sleep some times """
        print "start loop %s at: " % index, ctime()
        sleep(time[index])
        print "end loop %s at: " % index, ctime()


def Thread_Pool(*arg):
    """ A function that create and save instantiation
     of threading to thread pool """
    func, LN, Time = arg
    for i in range(LN):
        t = threading.Thread(target=func, args=(i, Time))
        t.setDaemon(True)
        _thread_pool.append(t)

def Thread_Start(arg):
    """A function that represents a thread of control."""

    for i in range(arg):
        _thread_pool[i].start()
    for i in range(arg):
        _thread_pool[i].join()


def main():
    """A function of main"""
    print "process start at: ".upper(), ctime()
    Thread_Pool(loop, _maxlink, _time)
    Thread_Start(_maxlink)
    print "process end at: ".upper(), ctime()


# if __name__ == '__main__':
#     main()