## 作业二

#### 题目说明

实现安全的rm命令。

1. 能够实现将删除的文件转移到一个作为垃圾桶的目录下，给用户一个反悔的机会。
2. 能够识别`-r -f *`等选项。
3. 能够定期清理垃圾桶中的文件。

#### 代码说明

```bash
#!/bin/bash
flag=0 #标记传递的命令参数
sum=0 #参数个数
if [ ! -d ~/.trash ]; then
    mkdir ~/.trash
fi
if [ "$1" = "-f" ] || [ "$2" = "-f" ]; then
    flag=1
    ((sum++))
fi
if [ "$1" = "-r" ] || [ "$2" = "-r" ]; then
    flag=2
    ((sum++))
fi
if [ $sum -eq 2 ]; then
    flag=3
fi
#echo $flag
if [ $# == 0 ]; then       #当未传入参数时
    echo "Usage: delete file1 [file2 file3...]"
else
    if [ $flag -eq 1 ]; then
        for file in "$@"; do
            if [ $file = "-f" ]; then   #-f时忽略警告信息
                continue
            fi
            if [ ! -e "$file" ] || [ -d "$file" ]; then
               # echo "$file"
                continue
            fi
            if [ -f "$file" ]; then
                mv -b "$file" ~/.trash/
            fi
        done
    elif [ $flag -eq 0 ]; then
        for file in "$@"; do
            if [ ! -e "$file" ]; then
                echo "$file not exits"
            elif [ -f "$file" ]; then
                mv -b "$file" ~/.trash/
            elif [ -d "$file" ]; then
                echo "can not remove a directory"
            fi
        done
    elif [ $flag -eq 2 ]; then
        for file in "$@"; do
            if [ $file = "-r" ]; then
                continue
            elif [ ! -e "$file" ]; then
                echo "$file not exits"
            elif [ -f "$file" ] || [ -d "$file" ]; then
                mv -b "$file" ~/.trash/
            fi
        done
    elif [ $flag -eq 3 ]; then
        for file in "$@"; do
            if [ $file = "-r" ] || [ $file = "-f" ]; then
                continue
            elif [ ! -e "$file" ]; then
                continue
            elif [ -f "$file" ] || [ -d "$file" ]; then
                mv -b "$file" ~/.trash/
            fi
        done
    fi
   # echo "You are about to delete these files:"
   # echo $@
fi
```

- 代码中指定目录`~/.trash`作为垃圾桶

- 运用flag变量来确定是否输入参数以及输入参数的各种情况，从而使命令做出不同的回应。flag默认为0，当flag为1时代表输入了-f参数，flag为2时代表输入了-r参数，flag为3时代表输入两个参数。

- 定期删除功能借助crontab实现，代码如下：

  ```shell
  #每天早晨8点定时清除7天前的文件
  0 8 * * * find ~/.trash -type f -o -type -d -mtime +7 -exec rm -rf {} \;
  ```

#### 难点记录

1. 实现自定义的rm识别参数时，使用flag和sum两个变量来完成。
2. 遍历命令传入的参数时，用选择条件对文件夹和文件进行分类判断实现不同处理方式。
3. 实现定期删除功能时，find的用法，要定期删除文件和文件夹时，可以用-o参数连接两个文件类型，-mtime参数用来判断文件的时间。

#### 执行结果

以shell文件夹为例，执行./delete.sh -r -f *

- 执行前：

![1534256913265](/tmp/1534256913265.png)

- 执行后：

![1534257021750](/tmp/1534257021750.png)

#### 改进方法

- 实现删除文件时，判断删除的总文件数目，如果超过一定数目（比如100个），则向用户给出警告是否继续执行，如此可以避免用户误操作的情况。