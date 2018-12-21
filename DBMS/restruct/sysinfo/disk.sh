#!/bin/bash
# 因为从第一行开始存，即数组应该从１开始遍历
eval `df -T -m -x tmpfs -x devtmpfs| tail -n +2 | awk '{printf("used["NR"]=%d;available["NR"]=%d;percent["NR"]=%s;point["NR"]=%s\n", $4,$5,$6,$7)}'`
# echo ${#used[@]}
time=`date +"%Y-%m-%d %H:%M:%S"`
((used_all=0))
((available_all=0))
for (( i=1; i <= ${#used[@]}; i++ )); do
    ((used_all+=${used[i]}))
    ((available_all+=${available[i]}))
done
percent_all=`echo "scale=1;$used_all/($used_all+$available_all)*100" | bc`
# echo $used_all $available_all $percent_all
echo $time 0 disk $used_all $available_all $percent_all%
for (( i=1; i <= ${#used[@]}; i++ )); do
    echo $time 1 ${point[i]} ${used[i]} ${available[i]} ${percent[i]}
done

