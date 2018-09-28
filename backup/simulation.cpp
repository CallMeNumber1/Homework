/*************************************************************************
	> File Name: simulation.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月19日 星期三 19时30分32秒
 ************************************************************************/

#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
int main(){
        int time_start;
        int fulltime = 100;//总时间
        int runtime = 50;//运行时间
    while(1){
                time_start = clock();
                while((clock()-time_start)<runtime){}
                usleep(fulltime-runtime);

    }
    return 0;
}
