#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
	int e_num = 0;
	const int INF = 1e9;
	vector<vector<pair<int, int>>> graph; //храним граф списком смежности с учетом весов
	vector<int> visited;
	vector<int> dist;
	Graph(int v_num) {
		graph.resize(v_num);
		visited.resize(v_num);
		dist.resize(v_num);
		fill(dist.begin(), dist.end(), INF);
	}
	void fill_graph() {
		ifstream in;
		in.open("test.txt"); //тестовый файл представлен в формате списка рёбер, где нумерация рёбер начинается с 1
		int a, b, weight;
		while (in >> a && in >> b && in >> weight) {
			a--;
			b--;
			graph[a].push_back({ b, weight });
			graph[b].push_back({ a, weight });
			e_num++;
		}
		in.close();
	}
	void Dijkstra(int start) {
		dist[start - 1] = 0;
		for (int i = 0; i < graph.size(); i++) {
			int nearest = -1;
			for (int v = 0; v < graph.size(); v++) {
				if (!visited[v] && (nearest == -1 || dist[v] < dist[nearest])) {
					nearest = v;
				}
			}
			visited[nearest] = 1;
			for (pair<int, int> to : graph[nearest]) {
				if (dist[to.first] > dist[nearest] + to.second) {
					dist[to.first] = dist[nearest] + to.second;
				}
			}
		}
	}
};
int main() {
	int v_num, start;
	cin >> v_num;
	cout << "Enter the start vertex: ";
	cin >> start;
	Graph A(v_num);
	A.fill_graph();
	A.Dijkstra(start);
	for (int t : A.dist) {
		if (t != A.INF) {
			cout << t << " ";
		}
		else {
			cout << "X" << " ";
		}
	}
	return 0;
}