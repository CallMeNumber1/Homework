#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#define MAX 1000
using namespace std;
int g[MAX + 5][MAX + 5] = {0};
int f[MAX + 5][MAX + 5] = {0};
int main(){
    int n, m, ans;  
    cin>>n>>m;
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < m; j++) {
           cin>>g[i][j];
       }
   }
   
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < m; j++) {
            for (int k = i; k < n; k++) {
                for (int l = j; l < m; l++) {
                    int cnt ;

                    if (cnt == (k - i + 1) * (l - j + 1)) ans += 1;
                }
            }        
       }
   }
   
   return 0;
}
