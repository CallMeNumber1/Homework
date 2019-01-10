#include <iostream>

using namespace std;

int main(){
   // 申请一堆连续的空间
   int *p1 = new int[10];
   // 单个变量的初始化,值为100
   int *p = new int(100);
   for (int i = 0; i < 10; i++) {
       p1[i] = i + 1;
   }
   for (int i = 0; i < 10; i++) {
       cout<<i<<":"<<p1[i]<<endl;
   }
   // 注意释放方式不同
   delete[] p1;
   delete p;
   return 0;
}
