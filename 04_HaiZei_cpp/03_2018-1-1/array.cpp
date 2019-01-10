#include <iostream>

using namespace std;
class Array {
private:
    int *data;
    int length;
public:
    // 默认10个元素的数组
    Array(int length = 10) {
        data = new int[length];
        // 不加this会报错
        this->length = length;
        for (int i = 0; i < length; i++) {
            data[i] = i;
        }
    }
    // 拷贝构造函数
    Array(const Array &obj) {
        length = obj.length;
        data = new int[length];
        for (int i = 0; i < length; i++) {
            data[i] = i;
        }
    }
    // 获取长度
    int getLength() {
        return length;
    }
    // 获取元素
    int getElement(int index) {
        if (index < 0 || index >= length) return -1;
        return data[index];
    }
    // 修改元素
    int modify(int index, int val) {
        if (index < 0 || index >= length) return -1;
        data[index] = val;
        return 1;
    }
};


int main(){
   Array *array = new Array();
   cout << "Length: " << array->getLength() << endl;
   cout << "Elements: ";
   for (int i = 0; i < array->getLength(); i++) {
       cout << "index" << i << ":" << array->getElement(i) << " "; 
   }
   cout << endl;
   cout << "copy start" << endl;
   Array *newa = array;
   cout << "New Length: " << array->getLength() << endl;
   cout << "New Elements: ";
   for (int i = 0; i < array->getLength(); i++) {
       cout << "index" << i << ":" << array->getElement(i) << " "; 
   }
   return 0;
}
