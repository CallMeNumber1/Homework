## 简介

本仓库用于存放HaiZei的相关作业，包括了：

- C语言课程示例代码
- C++语言课程示例代码
- 数据结构课程示例代码
- LinuxC网络编程项目：[分布式服务器监控系统]()

#### socket

- 此文件夹包含了socket编程初期阶段的代码
  - client.c与server.c配对,用于实现客户端与服务器端的简单通信.
  - client_send_file.c与server-1.c配对,用于实现客户端向服务器端发送文件内容的业务.

#### socket_sysinfo

- 包含了如下程序:
  - send.c:客户端,实现shell脚本的调用,并将输出信息传给服务器端.
  - recv.c:服务器端,实现根据不同客户端,接受数据并存放到相应的以客户端IP地址命名的目录中.

#### log_sys

- 存放了两个函数
- write_Pi_log.c
  - 将指定格式的字符串写入日志文件中
- get_conf_value.c
  - 从一个配置文件读取某个配置项

#### Linux项目-分布式服务器监控系统

###### 更新时间:2018.12.09

- 目前思路
  - 主线程先读取`conf.ini`配置文件进行初始化链表,之后创建5个线程.
  - 每个链表即为某一个子线程的工作队列
    - 子线程死循环判断自己对应的链表,如果上面某个节点连接不上了,就执行`delete_node()`将其删除,并打印提示信息
  - 主线程内建立listen状态的套接字,每有一个client连接,accept创建新的连接套接字,则插入当前连接数最少的链表,即交给子线程处理
    - client连接前,先判断是否已存在这个主机,如果存在则提示已存在,否则才插入链表
  - 主线程join等待子线程执行完毕
    - 子线程的回调函数func()是死循环,主线程的listen()  也是死循环,因此下面下的join和return不可能运行

- 目前已完成:

  - `master`端

    - `/log_sys/master/master.c`

  - client端

    - `/socket/c.c`

  - 使用方式

    - master监听8080端口

    - client监听8000端口
    - 可以绑定同一个端口,只要不是同一台机器
    - 另外client去连接的端口要与master监听的端口一致
    - master,client都既能监听也能主动连接

- 目前疑问
  - 主要任务是什么?
    - client监控系统各项指标,出现异常时发送报警信息给master?
    - master如何处理?写日志?
  - master和client已建立的连接是长连接还是短连接?
  - 发送报警信息是用长连接还是短连接?
  - 如何实现两类连接?

#### /project

- 该目录为`2018.12.09`号创建
- 整理了截止此日期的项目完成情况
  - 待完成:output函数写日志文件以及后续项目功能
- 将master端的各个函数分别放在独立的文件,形成多文件,并写了makefile
  - 其中common.h中存放了socket编程的公共头文件,以及公共数据结构,公共变量的声明
    - 若将公共变量的定义放在.h中则链接时会出现重定义问题
  - common.c存放了公共变量的定义