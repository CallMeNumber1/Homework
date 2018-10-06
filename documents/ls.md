# Linux下用C语言实现ls -al

## 基础知识

#### ls

显示不隐藏的文件与文件夹

- -l 显示不隐藏的文件和文件夹的详细信息.
- -al 显示所有文件与文件夹的详细信息

#### 文件的链接

- 硬链接
  - 硬链接是采用对inode代表文件引用计数的方式对文件进行链接，对任一链接文件进行修改都会直接影响到全部链接文件，而删除某一链接文件，不会影响其它链接文件的内容，但是文件的引用计数会-1，除非引用计数为0，否则inode所代表的文件不会被删除。
  - 限制:不能跨文件系统,不能链接到目录
- 软链接
  - 和windows里的快捷方式几乎等价.
  - 软链接文件中存的是原文件的文件名(不在同一个目录下时会加上绝对路径)
  - 对软链接文件的修改会影响到被链接文件.

#### C语言改变字体颜色

```
\033[显示方式;前景色;背景色 m
  显示方式:0（默认值）、1（高亮）、22（非粗体）、4（下划线）、24（非下划线）、5（闪烁）、25（非闪烁）、7（反显）、27（非反显）
  前景色:30（黑色）、31（红色）、32（绿色）、 33（黄色）、34（蓝色）、35（洋红）、36（青色）、37（白色）
  背景色:40（黑色）、41（红色）、42（绿色）、 43（黄色）、44（蓝色）、45（洋红）、46（青色）、47（白色）
注意:打印完之后记得恢复默认\033[0m
\33[30m -- \33[37m 设置前景色
30:黑
31:红
32:绿
33:黄
34:蓝色
35:紫色
36:深绿
37:白色
\33[0m恢复默认
```

- lstat()函数(const char * file_name, struct stat * bufs )
  - 取得参数file_name所指的文件状态
  - 执行成功则返回0,失败返回1
- 结构体stuct stat 存储了文件的各类信息

```c
struct stat* info_p
info_p->st_mode // 文件权限
..st_nlink //文件链接数
..
```

## 代码实现

```c
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

void show_file_info(char* filename, struct stat* info_p)
{
        char* uid_to_name(), *ctime(), *gid_to_name(), *filemode();
        void mode_to_letters();
        char modestr[11];

        mode_to_letters(info_p->st_mode, modestr);

        printf("%s", modestr);
        printf(" %4d", (int) info_p->st_nlink);
        printf(" %-8s", uid_to_name(info_p->st_uid));
        printf(" %-8s", gid_to_name(info_p->st_gid));
        printf(" %8ld", (long) info_p->st_size);
        printf(" %.12s", 4 + ctime(&info_p->st_mtime));
        printf(" %s\n", filename);

}

void mode_to_letters(int mode, char str[])
{
        strcpy(str, "----------");

        if (S_ISDIR(mode))
    {
                str[0] = 'd';
            
    }

        if (S_ISCHR(mode))
    {
                str[0] = 'c';
            
    }

        if (S_ISBLK(mode))
    {
                str[0] = 'b';
            
    }

        if ((mode & S_IRUSR))
    {
                str[1] = 'r';
            
    }

        if ((mode & S_IWUSR))
    {
                str[2] = 'w';
            
    }

        if ((mode & S_IXUSR))
    {
                str[3] = 'x';
            
    }

        if ((mode & S_IRGRP))
    {
                str[4] = 'r';
            
    }

        if ((mode & S_IWGRP))
    {
                str[5] = 'w';
            
    }

        if ((mode & S_IXGRP))
        {
                    str[6] = 'x';
                
        }

            if ((mode & S_IROTH))
            {
                        str[7] = 'r';
                    
            }

                if ((mode & S_IWOTH))
                {
                            str[8] = 'w';
                        
                }

                    if ((mode & S_IXOTH))
                    {
                                str[9] = 'x';
                            
                    }

}

char* uid_to_name(uid_t uid)
{
        struct passwd* getpwuid(),* pw_ptr;
        static char numstr[10];

        if((pw_ptr = getpwuid(uid)) == NULL)
    {
                sprintf(numstr,"%d",uid);

                return numstr;
            
    }
        else
    {
                return pw_ptr->pw_name;
            
    }

}

char* gid_to_name(gid_t gid)
{
        struct group* getgrgid(),* grp_ptr;
        static char numstr[10];

        if(( grp_ptr = getgrgid(gid) ) == NULL)
    {
                sprintf(numstr,"%d",gid);
                return numstr;
            
    }
        else
    {
                return grp_ptr->gr_name;
            
    }

}
void do_ls(char dirname[])
{
        DIR* dir_ptr;
        struct dirent* direntp;

        if ((dir_ptr = opendir(dirname)) == NULL)
    {
                fprintf(stderr, "ls2: cannot open %s \n", dirname);
            
    }
        else
    {
                while ((direntp = readdir(dir_ptr)) != NULL)
        {
                        dostat(direntp->d_name);
                    
        }

                close(dir_ptr);
            
    }

}

void dostat(char* filename)
{
        struct stat info;

        if (stat(filename, &info) == -1)
    {
                perror(filename);
            
    }
        else
    {
                show_file_info(filename, &info);
            
    }

}

int main(int ac,char* av[])
{
        if(ac == 1)
    {
                do_ls(".");
            
    }
        else
    {
                while(--ac)
        {
                        printf("%s: \n",++*av);
                        do_ls(*av);
                    
        }
            
    }

}
```

