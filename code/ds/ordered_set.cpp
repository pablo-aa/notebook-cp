// Ordered Set
//
// set roubado com mais operacoes
// 
// para alterar para multiset
// trocar less para less_equal
// 
// ordered_set<int> s
//
// order_of_key(k) // number of items strictly smaller than k -> int
// find_by_order(k) // k-th element in a set (counting from zero) -> iterator
// 
// https://cses.fi/problemset/task/2169
// 
// O(log N) para insert, erase (com iterator), order_of_key, find_by_order

using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
