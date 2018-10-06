## 简介

- 本仓库用于存放船上的作业

#### socket

- 此文件夹包含了socket编程初期阶段的代码
  - client.c与server.c配对,用于实现客户端与服务器端的简单通信.
  - client_send_file.c与server-1.c配对,用于实现客户端向服务器端发送文件内容的业务.

#### socket_sysinfo

- 包含了如下程序:
  - send.c:客户端,实现shell脚本的调用,并将输出信息传给服务器端.
  - recv.c:服务器端,实现根据不同客户端,接受数据并存放到相应的以客户端IP地址命名的目录中.

#### my_print.c

- 实现printf函数,但仅能打印%d类型,后续可以添加更多功能.

#### myls.c

- Linux C实现ls命令