#!/bin/bash 
max_str=("" "" "")
path=("" "" "")
length=("" "" "")

filter() {
    a=(rmvb png img jpg jpeg gif md avi zip tar gz 7z)
    suffix=`echo $1 | awk -F. '{print $NF}'`
    echo ${a[*]} | grep "$suffix" >/dev/null
    if [[ $? -eq 0 ]]; then
        return 1
    fi
    return 0
}

find() {
    echo $1
    for i in `cat $1`; do
    len=${#i}
    if [[ $len -gt ${length[1]} ]]; then
        length[1]=$len
        max_str[1]=$i
        path[1]=$1

    elif [[ $len -gt ${length[2]} ]]; then
        length[2]=$len
        max_str[2]=$i
        path[2]=$1
    elif [[ $len -gt ${length[3]} ]]; then
        length[3]=$len
        max_str[3]=$i
        path[3]=$1
    fi
    done
}


traverse() {
    for i in `ls $1`; do
        file=$1"/"$i
        if [[ -d $file ]]; then
            traverse $file
        else
           # echo $file
            file $file | grep "exec" >/dev/null
            if [[ $? -eq 1 ]]; then
                filter $file
                if [[ $? -eq 0 ]]; then
                    find $file
                fi
            fi
        fi
    done
}

traverse $1

for(( i = 1; i <= 3; i++ )); do
    echo ${length[$i]} ${max_str[$i]} ${path[$i]}
done

