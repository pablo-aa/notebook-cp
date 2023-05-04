random_device dev;
mt19937 rng(dev());

uniform_int_distribution<mt19937::result_type> dist(1, 6); // distribution in range [1, 6]

int val = dist(rng);