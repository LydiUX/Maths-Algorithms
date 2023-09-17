#include <iostream>
#include <cstdint>

using namespace std;

int64_t modExp(int64_t a, int64_t b, int64_t mod){
    if (a == 0){
        return 0;
    }
    int64_t res = 1;
    a %= mod;
    for (; b > 0; b >>= 1){ //repeated squaring method - main idea: decompose a^b = a^b1*a^b2*a^b3...*a^bn
        if (b & 1){
            res = (res % mod * a % mod) % mod; 
        }
        a = (a % mod * a % mod) % mod;
    }
    return res;
}

int main(){
    cout << modExp(382, 38122, 233) << endl;
    return 0;
}