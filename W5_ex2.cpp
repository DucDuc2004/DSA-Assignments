#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

vector<int> generateBlumNumbers(int N) {
    vector<int> primes;
    
    for (int i = 2; i <= sqrt(N); i++) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }
    
    vector<int> blumNumbers;
    
    for (size_t i = 0; i < primes.size(); i++) {
        for (size_t j = i; j < primes.size(); j++) {
            int blumNumber = primes[i] * primes[j];
            if (blumNumber < N) {
                if (find(blumNumbers.begin(), blumNumbers.end(), blumNumber) == blumNumbers.end()) {
                    blumNumbers.push_back(blumNumber);
                }
            }
        }
    }
    
    sort(blumNumbers.begin(), blumNumbers.end()); 
    return blumNumbers;
}

vector<pair<int, int>> findBlumPairsWithBlumSum(const vector<int>& blumNumbers, int N) {
    vector<pair<int, int>> result;
    
    for (size_t i = 0; i < blumNumbers.size(); i++) {
        for (size_t j = i + 1; j < blumNumbers.size(); j++) {
            int sum = blumNumbers[i] + blumNumbers[j];
            if (sum < N && find(blumNumbers.begin(), blumNumbers.end(), sum) != blumNumbers.end()) {
                result.emplace_back(blumNumbers[i], blumNumbers[j]);
            }
        }
    }
    
    return result;
}

bool isBlumNumberExist(const vector<int>& blumNumbers, int M) {
    return binary_search(blumNumbers.begin(), blumNumbers.end(), M);
}

int main() {
    int N, M;
    cout << "Nhap N: ";
    cin >> N;

    vector<int> blumNumbers = generateBlumNumbers(N);
    
    cout << "Day so Blum nho hon " << N << " la:\n";
    for (int num : blumNumbers) {
        cout << num << " ";
    }
    cout << endl;
    
    vector<pair<int, int>> blumPairs = findBlumPairsWithBlumSum(blumNumbers, N);
    cout << "Cac cap so Blum co tong la Blum:\n";
    for (auto& pair : blumPairs) {
        cout << pair.first << " + " << pair.second << endl;
    }
    
    cout << "Nhap so Blum check: ";
    cin >> M;
    
    if (isBlumNumberExist(blumNumbers, M)) {
        cout << M << " Blum co trong day\n";
    } else {
        cout << M << " Khong co trong day Blum.\n";
    }
    return 0;
}