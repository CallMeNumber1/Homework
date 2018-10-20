#!/bin/bash
for i in `seq 1 10`; do
    scp ./find_three.sh ChongH@pi$i:.
    ssh ChongH@pi$i "bash find_three.sh > ./out.log"
    scp ChongH@pi$i:./out.log ./dir/pi$i.log
done
