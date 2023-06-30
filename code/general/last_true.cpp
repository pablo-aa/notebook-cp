/*
  last_true(2, 10, [](int x) { return x * x <= 30; }); // outputs 5

  [l, r]

  if none of the values in the range work, return lo - 1
  
  f(1) = true
  f(2) = true
  f(3) = true
  f(4) = true
  f(5) = true
  f(6) = false
  f(7) = false
  f(8) = false

  last_true(1, 8, f) = 5
  last_true(7, 8, f) = 6
*/

int last_true(int lo, int hi, function<bool(int)> f) {
	lo--;
	while (lo < hi) {
		int mid = lo + (hi - lo + 1) / 2;

		if (f(mid)) {
			lo = mid;
		} else {
			hi = mid - 1;
		}
	}
	return lo;
}