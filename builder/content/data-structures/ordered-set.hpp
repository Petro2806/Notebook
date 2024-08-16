#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


ordered_set s;
s.insert(47);
// Returns the number of elements less then k
s.order_of_key(k);
// Returns iterator to the k-th element or s.end()
s.find_by_order(k);
// Does not exist
s.count();
// Doesn't trigger RE. Returns 0 if compiled using F8
*s.end();
