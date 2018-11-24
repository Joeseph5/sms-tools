#include <cmath>
#include <complex>
#include <iostream>
#include <iterator>

using namespace std;

// reverse bit
// such as input(001,3),output 100,
unsigned int bitReverse(unsigned int x, int log2n) {
  int n = 0;
  int mask = 0x1;
  for (int i = 0; i < log2n; i++) {
    n <<= 1;
    // 获取x的最低位，并赋给n
    n |= (x & 1);
    x >>= 1;
  }
  return n;
}

const double PI = 3.1415926536;

template <class Iter_T>
// log2n is the coefficience of power
void fft(Iter_T a, Iter_T b, int log2n) {
  typedef typename iterator_traits<Iter_T>::value_type complex;
  const complex J(0, 1);
  // left move log2n
  int n = 1 << log2n;

  for (unsigned int i = 0; i < n; ++i) {
    b[bitReverse(i, log2n)] = a[i];
  }

  for (int s = 1; s <= log2n; ++s) {
    int m = 1 << s;
    int m2 = m >> 1;
    complex w(1, 0);
    complex wm = exp(-J * (PI / m2));
    for (int j = 0; j < m2; ++j) {
      for (int k = j; k < n; k += m) {
        complex t = w * b[k + m2];
        complex u = b[k];
        b[k] = u + t;
        b[k + m2] = u - t;
      }
      w *= wm;
    }
  }
}

int main() {
  typedef complex<double> cx;
  cx a[] = {cx(0, 0), cx(1, 1), cx(3, 3), cx(4, 4),
            cx(4, 4), cx(3, 3), cx(1, 1), cx(0, 0)};
  cx b[8];
  fft(a, b, 3);
  for (int i = 0; i < 8; ++i) cout << b[i] << "\n";
}