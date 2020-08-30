class Solution {
public:
  int rob(vector<int>& nums) {
    if( nums.size() == 0 )
      return 0;
    else if( nums.size() == 1 )
      return nums[0];

    int previous2 = nums[0];
    int previous = max(nums[1], nums[0]);
    int maxSum = previous;
    for( int i = 2; i < nums.size(); i++ ) {
      if( previous2 + nums[i] > previous ) {
        maxSum = previous2 + nums[i];
        previous2 = previous;
        previous = maxSum;
      }
      else {
        previous2 = previous;
      }
    }
    return maxSum;
  }
};