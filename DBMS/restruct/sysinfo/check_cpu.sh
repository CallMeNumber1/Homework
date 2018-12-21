#!/bin/bash
time=`date +"%Y-%m-%d %H:%M:%S"`
# 首先计算CPU占用率
# 取第一行第二列及之后的数据 并且转化为数组 
nums=`cat /proc/stat | head -n 1 | cut -d " " -f 2-`
arr=($nums)
total_bef=0
used_bef=0
total_aft=0
used_aft=0
# echo ${arr[@]}
for i in ${arr[@]}; do
    (( total_bef+=$i ))
done
((used_bef=$total_bef-${arr[3]}-${arr[4]}))

sleep 0.5

nums=`cat /proc/stat | head -n 1 | cut -d " " -f 2-`
arr=($nums)
# echo ${arr[@]}
for i in ${arr[@]}; do
    (( total_aft+=$i ))
done
((used_aft=$total_aft-${arr[3]}-${arr[4]}))
occupy=`echo "scale=1;($used_aft-$used_bef)*100/($total_aft-$total_bef)" | bc`
# (( a=$used_aft-$used_bef ))
# (( b=$total_aft-$total_bef ))
# echo $a $b
# echo $occupy%

# 获取CPU温度
temper=`sensors | grep "temp"| head -3 | tail -1 | awk -F "+" '{print $2}'`
# echo $temper
num_temper=`echo $temper | tr -cd "[0-9.]"`
# echo $num_temper
warning="normal"
if [[ $(echo "$num_temper >= 70.0" | bc) -eq 1 ]]; then
    warning="note"
elif [[ $(echo "$num_temper >= 50.0" | bc) -eq 1 ]]; then
    warning="warning"
fi

# echo $warning

# 获取负载
load_str=`uptime | awk -F ":" '{print $4}'`
load=($load_str)

# echo ${load[@]}

echo $time ${load[@]} $occupy% $temper $warning
