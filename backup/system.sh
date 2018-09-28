#!/bin/bash
time=`date +"%Y-%m-%d %H:%M:%S"`
# 主机名
host=`hostname`
# 操作系统版本
os=`cat /etc/issue | cut -d " " -f -3`
# 内核版本
core=`cat /proc/version | cut -d " " -f -3`
# 运行时间
last_time=`uptime | cut -d " " -f 3- | cut -d "," -f 1 | tr " :" "_"`
# 获取负载
load_str=`uptime | cut -d "," -f 3- | cut -d ":" -f 2-`
load=($load_str)

# 获取CPU温度
temper=`sensors | grep "temp"| head -3 | tail -1 | awk -F "+" '{print $2}'`
# echo $temper
num_temper=`echo $temper | tr -cd "[0-9.]"`
# echo $num_temper
cpu_warning="normal"
if [[ $(echo "$num_temper >= 70.0" | bc) -eq 1  ]]; then
        cpu_warning="note"
elif [[ $(echo "$num_temper >= 50.0" | bc) -eq 1  ]]; then
        cpu_warning="warning"
fi

# 获取磁盘信息
eval `df -T -m -x tmpfs -x devtmpfs| tail -n +2 | awk '{printf("used["NR"]=%d;available["NR"]=%d;percent["NR"]=%s;point["NR"]=%s\n", $4,$5,$6,$7)}'`
((used_all=0))
((available_all=0))
for (( i=1; i <= ${#used[@]}; i++  )); do
        ((used_all+=${used[i]}))
            ((available_all+=${available[i]}))
done
percent_all=`echo "scale=1;$used_all*100/($used_all+$available_all)" | bc`
disk_warning="normal"

if [[ $(echo "percent_all > 70.0 " | bc) -eq 1 ]]; then
    disk_warning="note"
elif [[ $(echo "percent_all > 50.0" | bc) -eq 1 ]]; then
    disk_warning="warning"
fi

# 内存信息
eval `free -m | grep "Mem" | awk '{printf("total=%d;used=%d;free=%d",$2,$3,$4)}'`
occupy=`echo "scale=3;(($used*1.0/$total*100))" | bc | awk '{printf "%.1f", $0}'`
mem_warning="normal"
if [[ $(echo "occupy > 70.0 " | bc) -eq 1 ]]; then
    mem_warning="note"
elif [[ $(echo "occupy_all > 50.0" | bc) -eq 1 ]]; then
    mem_warning="warning"
fi

echo $time $host $os/$core $last_time ${load[@]} $available_all $percent_all% $total $occupy% $temper $disk_warning $mem_warning $cpu_warning



