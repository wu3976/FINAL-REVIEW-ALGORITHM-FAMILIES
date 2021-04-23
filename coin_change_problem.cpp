#include <vector>
#include <algorithm>
#include <limits>
#include <utility>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// Give a set S of different coins, each with infinite amount, and a target change
// c, find the smallest number of coins that can make the change.
// Return -1 if no change config is possible.

// Approximate with greedy algorithm
int coinChange_greedy_approx(vector<uint32_t> &coins, uint32_t change){
    // greedily choose largest coin.
    sort(coins.begin(), coins.end(), std::greater<uint32_t>());
    size_t i = 0;
    int count = 0;
    while (change != 0 && i < coins.size()){
        //cout << "xxx" << change << endl;
        if (change >= coins[i]){
            change -= coins[i];
            count++;
        } else {
            i++;
        }
    }
    return i == coins.size() ? -1 : count;
}

int DPhelper(vector<uint32_t> &coins, uint32_t change, vector<int> &memo){
    if (memo[change] != -1){
        return memo[change];
    }
    if (!change){
        return memo[0] = 0;
    }
    int currMinCount = numeric_limits<int>::max();
    for (size_t i = 0; i < coins.size(); i++){
        if (change >= coins[i]){
            currMinCount = min(currMinCount, DPhelper(coins, change - coins[i], memo));
        }
    }
    return memo[change] = currMinCount + 1;
}

// Compute with DP
int coinChange_DP(vector<uint32_t> &coins, uint32_t change){
    vector<int> memo(change + 1);
    std::fill(memo.begin(), memo.end(), -1);
    int result = DPhelper(coins, change, memo);
    // cout << "memo: ";
    /*for (size_t i = 0; i < memo.size(); i++){
        cout << memo[i] << " ";
    }*/
    //cout << endl;
    if (result == numeric_limits<int>::max()){
        return -1;
    }
    return result;
}

void branchBoundHelper(vector<uint32_t> &coins, uint32_t change, int current, int &currMin){
    if (!change){
        currMin = min(current, currMin);
        return;
    }
    int estimate = current + change / coins[0] + (change % coins[0] ? 1 : 0);
    if (estimate >= currMin){
        return;
    }
    for (size_t i = 0; i < coins.size(); i++){
        if (change >= coins[i]){
            branchBoundHelper(coins, change - coins[i], current + 1, currMin);
        }
    }
}

// Compute with Branch & Bound
int coinChange_branchBound(vector<uint32_t> &coins, uint32_t change){
    int currMin = coinChange_greedy_approx(coins, change); // now coins is sorted descending
    branchBoundHelper(coins, change, 0, currMin);
    return currMin;
}

void bruteForceHelper(vector<uint32_t> &coins, int curr, uint32_t change, int &currmin){
    //cout << "change: " << change << endl;
    if (!change){
        currmin = min(currmin, curr);
        return;
    }
    for (size_t i = 0; i < coins.size(); i++){
        if (change >= coins[i]){
            bruteForceHelper(coins, curr + 1, change - coins[i], currmin);
        }
    }
}

// Compute with Brute force
int coinChange_bruteForce(vector<uint32_t> &coins, uint32_t change){
    int currmin = numeric_limits<int>::max();
    bruteForceHelper(coins, 0, change, currmin);
    if (currmin == numeric_limits<int>::max()){
        return -1;
    }
    return currmin;
}

int main(int argc, char **argv){
    for (int i = 0; i < argc; i++){
        if (argv[i] == "-h" || argv[i] == "--help"){
            cout << "usage: ./coin [CHANGE_TARGET] <[COINS_SEQ]>\n";
            return 0;
        }
    }
    vector<uint32_t> coins(argc - 2);
    cout << "coins: ";
    for (size_t i = 0; i < coins.size(); i++){
        coins[i] = static_cast<uint32_t>(atoi(argv[i + 2]));
        cout << coins[i] << " ";
    }
    cout << endl;
    uint32_t change = static_cast<uint32_t>(atoi(argv[1]));
    cout << "change: " << change << endl;
    cout << "DP solution: " << coinChange_DP(coins, change) << endl;
    cout << "Greedy approximation: " << coinChange_greedy_approx(coins, change) << endl;
    cout << "Branch & Bound solution: " << coinChange_branchBound(coins, change) << endl;
    cout << "Brute Force: " << coinChange_bruteForce(coins, change) << endl;
}
