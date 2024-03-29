#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

/*
example: ordered_set s; s.insert(47);
s.order_of_key(k); - returns number of elements less then k
s.find_by_order(k); - returns iterator to k-th element or s.end()
s.count() does not exist.
*s.end() doesn't trigger runtime error. returns 0 if compiled using f8
 */
