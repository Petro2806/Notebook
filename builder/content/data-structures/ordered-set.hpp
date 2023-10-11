#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
// example: ordered_set s; s.insert(47);
// s.order_of_key(k); -- returns number of elements less then k
// s.find_by_order(k); - returns iterator to k-th element or s.end()
// s.count() does not exist. Use find in set and upper_bound in multiset.
// *s.end() = 0
// ordered_multiset:
// 		1) lower_bound and upper_bound swapped
//      2) find does not work
// 		3) you cannot erase by value. Use s.erase(s.upper_bound(x)) instead
//      4) to count x use s.order_of_key(x + 1) - s.order_of_key(x).
