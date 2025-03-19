#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <random>
#include "Network.h"
#include "NetworkClassic.h"

using namespace std;
using namespace chrono;

// Configuration Constants
constexpr int NUM_TRIALS = 100;     // Number of pathfinding trials per network size
constexpr int WARM_UP_TRIALS = 10;  // Number of warm-up runs before benchmarking
constexpr int TIMEOUT_SECONDS = 300; // Timeout for large benchmarks (5 min)

// Network Sizes to Test
constexpr array<int, 3> NETWORK_SIZES = {10, 100, 1000};

// Struct for Benchmark Results
struct BenchmarkResult {
    vector<long long> times;
    double mean, median, stddev, variance;
    long long min, max, percentile_5, percentile_95;
    double cumulative, throughput; // Queries per second
};

// Compute Statistical Metrics
BenchmarkResult analyze_times(vector<long long>& times) {
    if (times.empty()) return {{}, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    sort(times.begin(), times.end());
    double sum = 0.0, var = 0.0;
    size_t size = times.size();

    for (const auto t : times) sum += t;
    const double mean = sum / size;
    const double median = (size % 2 == 0) ? (times[size / 2 - 1] + times[size / 2]) / 2.0 : times[size / 2];

    for (const auto t : times) var += pow(t - mean, 2);
    const double stddev = sqrt(var / size);

    return {
        times,
        mean, median, stddev, var / size,
        times.front(), times.back(),
        times[size * 5 / 100], times[size * 95 / 100],
        sum,
        1e9 / mean // Throughput (queries per second)
    };
}

// Generate Random Network Nodes
vector<string> generate_network(int size) {
    vector<string> IPs;
    for (int i = 0; i < size; i++) {
        IPs.emplace_back("192.168.0." + to_string(i + 1));
    }
    return IPs;
}

// Generate Random Connections
void generate_connections(Network* net1, NetworkClassic* net2, const vector<string>& IPs) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, IPs.size() - 1);

    for (size_t i = 0; i < IPs.size() * 2; i++) {
        int a = dist(gen);
        int b = dist(gen);
        if (a != b) {
            net1->AddConnection(IPs[a], IPs[b]);
            net2->AddConnection(IPs[a], IPs[b]);
        }
    }
}

// Benchmark a Single Network Size
void benchmark_network_size(int size) {
    vector<string> IPs = generate_network(size);
    auto* net1 = new Network(IPs);
    auto* net2 = new NetworkClassic(IPs);
    generate_connections(net1, net2, IPs);

    // Measure Floyd-Warshall Initialization
    auto init_start = high_resolution_clock::now();
    net1->ComputeAllPairsShortestPaths();
    auto init_end = high_resolution_clock::now();
    long long floyd_init_time = duration_cast<milliseconds>(init_end - init_start).count();

    const string& start_ip = IPs.front();
    const string& end_ip = IPs.back();

    vector<long long> floyd_times, bfs_times;

    // Warm-up Runs
    for (int i = 0; i < WARM_UP_TRIALS; i++) {
        net1->FindShortestPath(start_ip, end_ip);
        net2->FindShortestPathBFS(start_ip, end_ip);
    }

    // Benchmark Pathfinding Queries
    for (int i = 0; i < NUM_TRIALS; i++) {
        auto start = high_resolution_clock::now();
        net1->FindShortestPath(start_ip, end_ip);
        auto end = high_resolution_clock::now();
        floyd_times.push_back(duration_cast<nanoseconds>(end - start).count());

        start = high_resolution_clock::now();
        net2->FindShortestPathBFS(start_ip, end_ip);
        end = high_resolution_clock::now();
        bfs_times.push_back(duration_cast<nanoseconds>(end - start).count());
    }

    // Analyze Results
    const auto floyd_results = analyze_times(floyd_times);
    const auto bfs_results = analyze_times(bfs_times);

    cout << "\n==== Floyd-Warshall Benchmark n=" + to_string(size) + " ====\n";
    cout << "Mean (ns)  | Median (ns) | Stddev (ns) | P5 (ns)    | P95 (ns)   | Queries/sec | Init (ms) | Cumulative (ms) |\n";
    cout << "-----------------------------------------------------------------------------------------------------\n";

    // Print Floyd-Warshall Results
    cout << " | " << setw(9) << floyd_results.mean
         << " | " << setw(9) << floyd_results.median
         << " | " << setw(9) << floyd_results.stddev
         << " | " << setw(9) << floyd_results.percentile_5
         << " | " << setw(9) << floyd_results.percentile_95
         << " | " << setw(9) << floyd_results.throughput
         << " | " << setw(9) << floyd_init_time
         << " | " << setw(9) << floyd_results.cumulative / 1e6 << " |\n";

    cout << "\n==== BFS Benchmark n=" + to_string(size) + "  ====\n";
    cout << "| Mean (ns)  | Median (ns) | Stddev (ns) | P5 (ns)    | P95 (ns)   | Queries/sec | Cumulative (ms) |\n";
    cout << "----------------------------------------------------------------------------------------------\n";

    // Print BFS Results
    cout << " | " << setw(9) << bfs_results.mean
         << " | " << setw(9) << bfs_results.median
         << " | " << setw(9) << bfs_results.stddev
         << " | " << setw(9) << bfs_results.percentile_5
         << " | " << setw(9) << bfs_results.percentile_95
         << " | " << setw(9) << bfs_results.throughput
         << " | " << setw(9) << bfs_results.cumulative / 1e6 << " |\n";

    // Cleanup
    delete net1;
    delete net2;
}

// Main Entry Point
int main() {
    for (const int size : NETWORK_SIZES) {
        benchmark_network_size(size);
    }

    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "Benchmark completed successfully.\n";
    return 0;
}
