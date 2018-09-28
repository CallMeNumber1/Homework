#!/bin/bash
# 检测恶意进程,因为cpu占用率较低,将限制设在了占用5%以上即为恶意进程
# 难点:1.将字符串作为浮点数进行比较 2.eval的处理
# 题目中未理解部分:CPU占用单核50%即可
time=`date +"%Y-%m-%d %H:%M:%S"`
# 显示user,pid,cpu占用,mem占用,进程名
# 按照cpu占用率降序排序
# 疑问:sort后加-t ' '时不能得到正确结果
# awk中printf里每个语句后用分号;否则得不到正确结果
eval `ps -aux |  sort -gr -k 3| awk -F " " '{printf("user["NR"]=%s;pid["NR"]=%s;cpu["NR"]=%s;mem["NR"]=%s;pname["NR"]=%s\n",$1,$2,$3,$4,$NF)}' | head -10`
# 先找出潜在的恶意进程的pid
# 注意其中对浮点数做比较的语句
cnt=0
echo "potential bad process:"
for (( i=1; i<=${#cpu[*]}; i++ )); do
    if [ `echo "${cpu[$i]} > 5.0" | bc` -eq 1 ]; then
        echo ${pname[i]} ${pid[i]} ${user[i]} ${cpu[i]} ${mem[i]}
        (( potential_pid[$cnt]=${pid[i]} ))
        (( cnt=$cnt+1 ))
    fi
done
# 5s后继续再检查一遍
sleep 5
# 若潜在的恶意进程占用的cpu仍超过50%,则判断为恶意进程并输出对应信息
echo "bad process:"
for i in ${potential_pid[*]}; do
    temp=`ps -aux | grep $i | head -1 | awk '{print $3}'`
    if [ `echo "$temp > 5.0" | bc` -eq 1 ]; then
        eval `ps -aux | grep $i | head -1 | awk -F " " '{printf("bad_user=%s;bad_pid=%s;bad_cpu=%s;bad_mem=%s;bad_pname=%s",$1,$2,$3,$4,$NF)}'`
        echo $time ${bad_pname} ${bad_pid} ${bad_user} ${bad_cpu} ${bad_mem}
    fi
done

# 浮点数比较的另一种方法
# x=3.1
# y=3.2
# echo "$x $y" | awk '{if($1 > $2) print $1; else print $2}'
