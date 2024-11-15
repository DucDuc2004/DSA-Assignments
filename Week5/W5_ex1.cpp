#include <iostream>
using namespace std;
void bubbleSort(int a[], int n){
    int i, j;
    for (int i = 0; i < n; ++i){
        for (int j = n - 1; j > i; --j){
            if (a[j] < a[j-1])
            {
                int temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
            }
        }
    }
}

int main(){
    int a[10] = {0,2,1,2,1,0,2,1,2,0};
    bubbleSort(a,10);
    for (int i = 0;i < 10; ++i){
        cout << a[i] << " ";
    }
    return 0;
}