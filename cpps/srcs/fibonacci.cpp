int Fibonacci(unsigned int n) {
  if (n == 0 || n == 1) {
    return n;
  }
  int dp_i_pre_pre = 0;
  int dp_i_pre = 1;
  int ret = 0;
  for (int i = 2; i <= n; ++i) {
    ret = dp_i_pre + dp_i_pre_pre;
    dp_i_pre_pre = dp_i_pre;
    dp_i_pre = ret;
  }
  return ret;
}