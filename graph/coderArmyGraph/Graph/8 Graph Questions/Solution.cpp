#include <iostream>
#include <vector>
#include <queue>
using namespace std;

    int helpaterp(vector<vector<int>> hospital) {
        int n = hospital.size();
        int m = hospital[0].size();
        vector<vector<int>>visited (n , vector<int>(m,0));
        queue<pair<int,int>>q;
        int time = -1;
            // Push initially infected cells
        for(int i =0;i<n;i++){
            for(int j=0;j<m;i++){
                if(hospital[i][j]==2){
                    q.push({i,j});
                    visited[i][j]=1;
                }
            }
        }

        int dx[] = {1,1,0,0};
        int dy[] = {-1,1,0,0};
        while(!q.empty()){
            pair node = q.front();
            q.pop();
            int x = node.first;
            int y = node.second;


            
        }
     return 0;   
    }

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
