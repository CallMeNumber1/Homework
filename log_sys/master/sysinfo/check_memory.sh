#bin/bash
time=`date +"%Y-%m-%d %H:%M:%S"`
# 上一次动态平均默认值
(( last_dynamic=84 ))
if [[ $1 != "" ]]; then
    ((last_dynamic=$1))
fi
total=`free -m | grep "Mem" | awk '{print $2}'`
used=`free -m | grep "Mem" | awk '{print $3}'`
free=`free -m | grep "Mem" | awk '{print $4}'`
occupy=`echo "scale=3;(($used*1.0/$total*100))" | bc | awk '{printf "%.1f", $0}'`
dynamic=`echo "scale=3;(($last_dynamic*0.3+0.7*$occupy))" | bc | awk '{printf "%.1f", $0}'`
echo "时间                总量    剩余量    当前占用  动态平均值"
echo $time $total "   "$free    "     "$occupy%  "    "$dynamic%


