#include <bit>
#include <iostream>

using i64 = signed long long;
using u64 = unsigned long long;
using f64 = double;

static_assert(sizeof(i64) == 8);
static_assert(sizeof(u64) == 8);
static_assert(sizeof(f64) == 8);

namespace {

constexpr auto mantissa_size = 52ull;
constexpr auto mantissa_mask = (1ull << mantissa_size) - 1;
constexpr auto exponent_mask = ~mantissa_mask;

u64 mantissa(u64 x) {
  return x & mantissa_mask;
}

u64 exponent(u64 x) {
  return x & exponent_mask;
}

constexpr u64 f2b(f64 f) {
  u64 repr = std::bit_cast<u64>(f);
  u64 f_sign = repr >> 63;
  u64 f_exp = (repr >> 52) & 0b11111111111;
  u64 f_mantissa = repr & ((1ull << 52) - 1);
  // std::memcpy(&repr, &f, sizeof(f));
  // std::cerr << f_sign << ' ' << f_exp << ' ' << f_mantissa << '\n';

  u64 b_exp, b_mantissa;

  if (!f_sign) {
    // general case:
    b_exp = f_exp;
    b_mantissa = f_mantissa;
  } else {
    // negative numbers
    b_exp = -f_exp - !!f_mantissa;
    b_mantissa = -f_mantissa & mantissa_mask;
  }

  // std::cerr << int(b_exp) << ' ' << b_mantissa << '\n';

  return b_exp << mantissa_size | b_mantissa;
}

constexpr f64 b2f(u64 b) {
  auto b_exponent = static_cast<i64>(b) >> mantissa_size;
  auto b_mantissa = b & mantissa_mask;
  // std::cerr << b_exponent << ' ' << b_mantissa << '\n';

  u64 f_sign = b_exponent < 0;
  u64 f_mantissa = b_exponent < 0 ? -b_mantissa & mantissa_mask : b_mantissa;

  u64 f_exponent;
  if (b_exponent < 0) {
    f_exponent = -b_exponent;
    if (f_exponent && b_mantissa)
      f_exponent -= 1;
  } else {
    f_exponent = b_exponent;
  }


  // std::cerr << f_sign << ' ' << f_exponent << ' ' << f_mantissa << '\n';
  u64 f = f_sign << 63 | f_exponent << 52 | f_mantissa;
  return std::bit_cast<f64>(f);
}

void test_around(u64 i) {
  std::cerr << b2f(i-2) << '\n';
  std::cerr << b2f(i-1) << '\n';
  std::cerr << b2f(i) << '\n';
  std::cerr << b2f(i+1) << '\n';
  std::cerr << b2f(i+2) << '\n';
  std::cerr << "\n";
}

}


int main() {
  std::cerr.precision(17);

  test_around(f2b(-2.));
  test_around(f2b(-1.));
  test_around(f2b(0.));
  test_around(f2b(0.99999999999999989));
  test_around(f2b(1.));
  test_around(f2b(1.0000000000000002));
  test_around(f2b(2.));
  test_around(f2b(4.));
  test_around(9218868437227405311ull);
  test_around(9223372036854775807ull);
  test_around(-9218868437227405311ull);

  return 0;
}