#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
  
#define ordered_set tree<pair<int64_t, int64_t>, null_type,less<pair<int64_t, int64_t>>, rb_tree_tag,tree_order_statistics_node_update>