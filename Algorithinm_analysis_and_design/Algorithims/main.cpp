#include<iostream>  
#include<queue>
using namespace std;

int main(){
	unsigned long long n, m, s, t,i;
	cin >> n >> m >> s >> t;
	bool **cost = new bool*[n];
	bool *used = new bool[n];
	int *distance = new int[n];
	for (i = 0; i < n; ++i)
		cost[i] = new bool[n];
	fill(used, used + n,INFINITY);//
	fill(distance, distance + n, false);
	for (i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		cost[x - 1][y - 1] = true;
	}
	distance[s] = 0;
	while (true) {
		long long v = -1;
		for (unsigned long long u = 0; u < n; ++u) {
			if (!used[u] && (v == -1 || distance[u] < distance[v]))
				v = u;
		}
		if (v == -1)
			break;
		used[v] = true;
		for (unsigned long long u = 0; u < n; ++u) {
			distance[u] = min(distance[u], distance[u] + cost[v][u]);
			if (u == t-1) {
				cout << distance[u] << endl;
				system("pause");
				return 0;
			}
		}
	}

	system("pause");
	return 0;
}
