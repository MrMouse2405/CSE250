#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;

class NetworkClassic final {
public:
    explicit NetworkClassic(const vector<string>& IPList);
    ~NetworkClassic();

    void AddConnection(const string &server1, const string &server2);
    [[nodiscard]] int GetNetworkSize() const;
    string FindShortestPath(const string& homeServer, const string& targetServer);
    string FindShortestPathBFS(const string& homeServer, const string& targetServer);

    void PrintNetwork() const;  // Debugging function

private:
    struct Edge {
        int v1, v2;
    };

    int m_NetworkSize;
    vector<string> m_Vertex2IP;
    unordered_map<string, int> m_IP2Vertex;
    vector<Edge> m_EdgeList;
};
