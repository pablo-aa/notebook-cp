/*
  first_true(2, 10, [](int x) { return x * x >= 30; }); // outputs 6

  [l, r]

  if none of the values in the range work, return hi + 1
  
  f(1) = false
  f(2) = false
  f(3) = false
  f(4) = false
  f(5) = false
  f(6) = true
  f(7) = true
  f(8) = true
*/

int first_true(int lo, int hi, function<bool(int)> f) {
	hi++;
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;

		if (f(mid)) {
			hi = mid;
		} else {
			lo = mid + 1;
		}
	}
	return lo;
}
