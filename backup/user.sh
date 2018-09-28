#!/bin/bash

user_num=`cat /etc/passwd | awk -F ":" '{if($3>=1000) print $1}' | wc -l`
echo $user_num

