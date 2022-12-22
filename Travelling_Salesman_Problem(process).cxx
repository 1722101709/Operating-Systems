#include <iostream>
#include<vector>
using namespace std;
#define V 4

void tsp(int graph[][V], vector<bool>& v, int currPos, int n, int count, int cost, int& ans)
{
    if (count == n && graph[currPos][0]) {

        ans = min(ans, cost + graph[currPos][0]);

        return;

    }

    for (int i = 0; i < n; i++) {

        if (!v[i] && graph[currPos][i]) {

            v[i] = true;

            tsp(graph, v, i, n, count + 1,

                cost + graph[currPos][i], ans);

            v[i] = false;

        }

    }
};

int main()
{
clock_t t1,t2;
t1=clock();
    int n = 4;
 

    int graph[][V] = {

        { 0, 10, 15, 20 },

        { 10, 0, 35, 25 },

        { 15, 35, 0, 30 },

        { 20, 25, 30, 0 }

    };
 
    vector<bool> v(n);

    for (int i = 0; i < n; i++)

        v[i] = false;
 
    v[0] = true;

    int ans = INT_MAX;

    tsp(graph, v, 0, n, 1, 0, ans);
 
    cout << ans;
t2=clock();
cout<<"\n\ntime taken :"<<((t2-t1)*1000)/(double)CLOCKS_PER_SEC<<" milli seconds"<<endl;
    return 0;
}