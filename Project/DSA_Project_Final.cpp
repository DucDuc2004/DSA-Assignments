#include <iostream>
using namespace std;
// #1 SỬ DỤNG MẢNG PHỤ
int trapRainWater(int height[], int n) {
    if (n <= 2) return 0;

    int left_max[n], right_max[n];
    left_max[0] = height[0];
    for (int i = 1; i < n; i++) {
        left_max[i] = max(left_max[i - 1], height[i]);
    }

    right_max[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        right_max[i] = max(right_max[i + 1], height[i]);
    }

    int water = 0;
    for (int i = 0; i < n; i++) {
        water += min(left_max[i], right_max[i]) - height[i];
    }

    return water;
}

// #2 SỬ DỤNG 2 CON TRỎ
int trapRainWater1(int height[], int n) {
    if (n <= 2) return 0;

    int left_max[n], right_max[n];
    left_max[0] = height[0];
    for (int i = 1; i < n; i++) {
        left_max[i] = max(left_max[i - 1], height[i]);
    }

    right_max[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        right_max[i] = max(right_max[i + 1], height[i]);
    }

    int water = 0;
    for (int i = 0; i < n; i++) {
        water += min(left_max[i], right_max[i]) - height[i];
    }

    return water;
}

int main() {
    int height[] = {7, 0, 4, 2, 5, 0, 6, 4, 0, 5};
    int n = sizeof(height) / sizeof(height[0]);
    cout << "Tong luong nuoc: " << trapRainWater(height, n) << endl;
    cout << "Tong luong nuoc: " << trapRainWater1(height, n) << endl;
    return 0;
}