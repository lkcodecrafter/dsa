class Solution {
public:

    int n;
    int m[301][5001];
    int solve(int i, int amount, vector<int>& coins ){

        if(amount ==0){
            return 1;
        }
        if(i == n || amount < 0){
            return 0;
        }

        if(m[i][amount]!=-1){
            return m[i][amount];
        }

        if(coins[i]> amount){
            return m[i][amount] = solve(i+1, amount, coins);
        }

        int take = solve(i,  amount - coins[i], coins);
        int not_take = solve(i+1, amount, coins);

        return m[i][amount]= take+not_take;
    }
    int change(int amount, vector<int>& coins) {
        n = coins.size();
        memset(m, -1, sizeof(m));
        return solve(0, amount, coins);
    }
};