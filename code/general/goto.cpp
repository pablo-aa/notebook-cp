while (t--) {
  for (int d = 0; d < 11; d++) {
    if (n % 11 == 0) {
      cout << "YES" << endl;
      goto done;
    }
            
    n -= 111;
    if (n < 0) break;
  }
  cout << "NO" << endl;
        
  done:;
}