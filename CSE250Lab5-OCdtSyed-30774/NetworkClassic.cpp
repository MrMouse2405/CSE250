#include "NetworkClassic.h"

#include <algorithm>

NetworkClassic::NetworkClassic(const vector<string>& IPList) {
    
    m_NetworkSize = IPList.size();
    m_Vertex2IP = IPList;
    
    for (int i = 0; i < m_NetworkSize; i++) {
        m_IP2Vertex[IPList[i]] = i;
    }
}

NetworkClassic::~NetworkClassic() = default;

void NetworkClassic::AddConnection(const string& server1, const string& server2) {
    const int v1 = m_IP2Vertex[server1];
    const int v2 = m_IP2Vertex[server2];

    m_EdgeList.push_back({v1, v2});
    m_EdgeList.push_back({v2, v1});
}

int NetworkClassic::GetNetworkSize() const {
    return m_NetworkSize;
}

string NetworkClassic::FindShortestPathBFS(const string& homeServer, const string& targetServer) {
    const int home = m_IP2Vertex[homeServer];
    const int destination = m_IP2Vertex[targetServer];

    vector parent(m_NetworkSize, -1);
    queue<int> bfsQueue;
    vector visited(m_NetworkSize, false);

    bfsQueue.push(home);
    visited[home] = true;

    while (!bfsQueue.empty()) {
        const int current = bfsQueue.front();
        bfsQueue.pop();

        if (current == destination) break;

        for (const auto& edge : m_EdgeList) {
            if (edge.v1 == current && !visited[edge.v2]) {
                visited[edge.v2] = true;
                parent[edge.v2] = current;
                bfsQueue.push(edge.v2);
            }
        }
    }

    if (!visited[destination]) return "No path found!";

    vector<int> path;
    for (int at = destination; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    string result = m_Vertex2IP[path[0]];
    for (size_t i = 1; i < path.size(); i++) {
        result += "," + m_Vertex2IP[path[i]];
    }

    return result;
}

string NetworkClassic::FindShortestPath(const string& homeServer, const string& targetServer) {
    return FindShortestPathBFS(homeServer, targetServer);
}

void NetworkClassic::PrintNetwork() const {
    cout << "\nNetworkClassic Connections (Edge List):\n";
    for (const auto& edge : m_EdgeList) {
        cout << m_Vertex2IP[edge.v1] << " <-> " << m_Vertex2IP[edge.v2] << "\n";
    }
}
