// Dijkstra's with a twist
class Solution {
public:
  template< class T >
  struct CustomGreater {
    bool operator() ( const T& a, const T& b ) {
      // Heap minimizes cost to go from src to current node.
      return a[1] > b[1];
    }
  };
    
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    vector<int> costs(n, INT_MAX);
    vector<int> numStops(n, INT_MAX);
    
    vector<vector<int>> adjMatrix(n, vector<int>(n, INT_MAX));
    for( auto flight : flights ) {
      int start = flight[0];
      int end = flight[1];
      int price = flight[2];
      adjMatrix[start][end] = price;
    }
    
    priority_queue< vector<int>, vector<vector<int>>, CustomGreater<vector<int>> > heap;
    costs[src] = 0;
    numStops[src] = 0;
    heap.push({src, costs[src], numStops[src]});
    while( heap.size() > 0 ) {
      auto top = heap.top(); heap.pop();
      int node = top[0]; // node id
      int cost = top[1]; // currently known cost to get from src to current node
      int stops = top[2]; // currently known stops (edges) to get from src to current node
      
      if( node == dst ) return cost;
      // Max stops is K + 1 (the final stop does not actually count as a stop).
      // There is no possibility of this node being valid in its current state
      // because it needs at least 1 more stop to get to the dst, which would be
      // too many.
      if( stops > K ) continue;
      
      // Iterate through all nodes, skipping over all that do not have an
      // immediate connection to the current.
      for( int neighbor = 0; neighbor < n; neighbor++ ) {
        // There is no connection between these nodes so just continue.
        if( adjMatrix[node][neighbor] == INT_MAX ) continue;

        int addedPrice = adjMatrix[node][neighbor];
        // Usually, dijkstra's only considers cost when determining if a node gets pushed 
        // to the queue. However, here, if a node shows up with a lower number of edges
        // than what was previously recorded, we must consider it, because the originally recorded
        // number of edges may exceed our constraint.
        if( cost + addedPrice < costs[neighbor] ) {
          heap.push({neighbor, cost + addedPrice, stops + 1});
          costs[neighbor] = cost + addedPrice;
        }
        else if( stops + 1 < numStops[neighbor] ) {
          heap.push({neighbor, costs[neighbor], stops + 1});
          numStops[neighbor] = stops + 1;
        }
      }
    }
    return costs[dst] == INT_MAX ? -1 : costs[dst];
  }
};