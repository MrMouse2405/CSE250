#include "Network.h"

void Network::whiten() const {
    for (int i = 0; i < m_NetworkSize; i++) {
        m_Colors[i] = WHITE;
    }
}

Network::Network(const vector<string>& IPList) {
    m_NetworkSize = IPList.size();
    m_Vertex2IP = IPList;

    m_EdgeLists = new EdgeListNode*[m_NetworkSize]();
    m_Colors = new color[m_NetworkSize];

    for (int i = 0; i < m_NetworkSize; i++) {
        m_IP2Vertex[IPList[i]] = i;
    }

    m_FloydWarshallDist = new int*[m_NetworkSize];
    m_FloydWarshallNext = new int*[m_NetworkSize];

    for (int i = 0; i < m_NetworkSize; i++) {
        m_FloydWarshallDist[i] = new int[m_NetworkSize];
        m_FloydWarshallNext[i] = new int[m_NetworkSize];

        for (int j = 0; j < m_NetworkSize; j++) {
            m_FloydWarshallDist[i][j] = (i == j) ? 0 : INT_MAX;
            m_FloydWarshallNext[i][j] = (i == j) ? j : -1;
        }
    }

    whiten();
}

Network::~Network() {
    for (int i = 0; i < m_NetworkSize; i++) {
        EdgeListNode* current = m_EdgeLists[i];
        while (current) {
            const EdgeListNode* temp = current;
            current = current->next;
            delete temp;
        }
        delete[] m_FloydWarshallDist[i];
        delete[] m_FloydWarshallNext[i];
    }

    delete[] m_EdgeLists;
    delete[] m_Colors;
    delete[] m_FloydWarshallDist;
    delete[] m_FloydWarshallNext;
}

void Network::AddConnection(const string& server1, const string& server2, const int weight) {
    const int v1 = m_IP2Vertex[server1];
    const int v2 = m_IP2Vertex[server2];

    auto* edge1 = new EdgeListNode{ v1, v2, weight, m_EdgeLists[v1] };
    m_EdgeLists[v1] = edge1;

    auto* edge2 = new EdgeListNode{ v2, v1, weight, m_EdgeLists[v2] };
    m_EdgeLists[v2] = edge2;

    m_FloydWarshallDist[v1][v2] = weight;
    m_FloydWarshallDist[v2][v1] = weight;
    m_FloydWarshallNext[v1][v2] = v2;
    m_FloydWarshallNext[v2][v1] = v1;
}

void Network::ComputeAllPairsShortestPaths() const {
    for (int k = 0; k < m_NetworkSize; k++) {
        for (int i = 0; i < m_NetworkSize; i++) {
            for (int j = 0; j < m_NetworkSize; j++) {
                if (m_FloydWarshallDist[i][k] != INT_MAX &&
                    m_FloydWarshallDist[k][j] != INT_MAX &&
                    m_FloydWarshallDist[i][k] + m_FloydWarshallDist[k][j] < m_FloydWarshallDist[i][j]) {

                    m_FloydWarshallDist[i][j] = m_FloydWarshallDist[i][k] + m_FloydWarshallDist[k][j];
                    m_FloydWarshallNext[i][j] = m_FloydWarshallNext[i][k];
                }
            }
        }
    }
}

string Network::FindShortestPath(const string& homeServer, const string& targetServer) {
    int home = m_IP2Vertex[homeServer];
    int destination = m_IP2Vertex[targetServer];

    if (m_FloydWarshallDist[home][destination] == INT_MAX) {
        return "No path found!";
    }

    vector<int> path;
    for (int at = home; at != destination; at = m_FloydWarshallNext[at][destination]) {
        if (at == -1) return "No path found!";
        path.push_back(at);
    }
    path.push_back(destination);

    string result = m_Vertex2IP[path[0]];
    for (size_t i = 1; i < path.size(); i++) {
        result += "," + m_Vertex2IP[path[i]];
    }

    return result;
}

void Network::PrintNetwork() const {
    cout << "\nNetwork Connections:\n";
    for (int i = 0; i < m_NetworkSize; i++) {
        cout << m_Vertex2IP[i] << ": ";
        for (EdgeListNode* node = m_EdgeLists[i]; node; node = node->next) {
            cout << m_Vertex2IP[node->v2] << " ";
        }
        cout << "\n";
    }
}

void Network::RunTests() {
    cout << "\nRunning Tests...\n";
    cout << FindShortestPath("156.54.164.27", "239.101.227.2") << endl;
    cout << FindShortestPath("190.17.60.22", "98.136.34.166") << endl;
    cout << FindShortestPath("190.17.60.22", "223.122.154.117") << endl;
    cout << FindShortestPath("190.17.60.22", "11.64.80.23") << endl;
    cout << FindShortestPath("187.92.39.116", "112.70.131.241") << endl;
}
