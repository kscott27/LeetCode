// Bellman-Ford
class Solution {
public:
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    vector<int> cost(n, INT_MAX);
    // Initialize the starting node my relaxing it
    cost[src] = 0;

    // Number of edges = number of stops + 1
    for( int i = 0; i <= K; i++ ) {
      vector<int> temp(cost);
      for( auto flight : flights ) {
        int start = flight[0];
        int end = flight[1];
        int price = flight[2];
        // Continue if start node has not been relaxed. Initially,
        // only the starting node is capable of relaxing neighbors.
        if( cost[start] == INT_MAX ) continue;
        
        // Further relax the end node
        temp[end] = min(temp[end], cost[start] + price);
      }
      cost = temp;
    }
    return cost[dst] != INT_MAX ? cost[dst] : -1;
  }
};