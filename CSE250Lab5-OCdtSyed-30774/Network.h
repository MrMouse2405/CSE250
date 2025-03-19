#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include <stack>

using namespace std;

class Network final {
public:
	enum color { WHITE, GRAY, BLACK };

	explicit Network(const vector<string>& IPList);
	~Network();

	void AddConnection(const string &server1, const string &server2, int weight = 1);
	[[nodiscard]] int GetNetworkSize() const;
	void ComputeAllPairsShortestPaths() const;
	string FindShortestPath(const string& homeServer, const string& targetServer);
	string FindShortestPathBFS(const string& homeServer, const string& targetServer);

	void PrintNetwork() const;  // Debugging function
	void RunTests();  // Testing function

private:
	struct EdgeListNode {
		int v1, v2, weight;
		EdgeListNode* next;
	};

	int m_NetworkSize;
	vector<string> m_Vertex2IP;
	unordered_map<string, int> m_IP2Vertex;
	EdgeListNode** m_EdgeLists;
	color* m_Colors;

	int** m_FloydWarshallDist;
	int** m_FloydWarshallNext;

	void whiten() const;
};
