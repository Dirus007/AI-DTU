#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>

using namespace std;

vector<int> random_solution(int n) {
    vector<int> solution;
    for(int i = 0; i < n; ++i)solution.push_back(i);
    random_device rd;
    mt19937 g(rd());
    shuffle(solution.begin(), solution.end(), g);
    return solution;
}

int route_length(const vector<vector<int>>& tsp, const vector<int>& solution) {
    int length = 0;
    for(size_t i = 0; i < solution.size(); ++i) length += tsp[solution[i]][solution[(i + 1) % solution.size()]];
    return length;
}

vector<vector<int>> get_neighbours(const vector<int>& solution) {
    vector<vector<int>> neighbours;
    for(size_t i = 0; i < solution.size(); ++i){
        for(size_t j = i + 1; j < solution.size(); ++j){
            vector<int> neighbour = solution;
            swap(neighbour[i], neighbour[j]);
            neighbours.push_back(neighbour);
        }
    }
    return neighbours;
}

pair<vector<int>, int> get_best_neighbour(const vector<vector<int>>& tsp, const vector<vector<int>>& neighbours) {
    int best_length = INT_MAX;
    vector<int> best_neighbour;
    for(const auto& neighbour : neighbours){
        int current_length = route_length(tsp, neighbour);
        if(current_length < best_length){
            best_length = current_length;
            best_neighbour = neighbour;
        }
    }
    return {best_neighbour, best_length};
}

pair<vector<int>, int> hill_climbing(const vector<vector<int>>& tsp) {
    vector<int> current_solution = random_solution(tsp.size());
    int current_length = route_length(tsp, current_solution);

    while(true){
        auto neighbours = get_neighbours(current_solution);
        auto [best_neighbour, best_neighbour_length] = get_best_neighbour(tsp, neighbours);

        if(best_neighbour_length >= current_length) break;

        current_solution = best_neighbour;
        current_length = best_neighbour_length;
    }

    return {current_solution, current_length};
}

int main() {
    int MAX = 1e9;
    vector<vector<int>> tsp = {
        {MAX, 600, 600, 900},
        {400, MAX, 300, 800},
        {100, 300, MAX, 200},
        {300, 500, 200, MAX}
    };

    auto [best_solution, best_length] = hill_climbing(tsp);
    cout << "Best solution:";
    for (int city : best_solution) {
        cout << " " << city;
    }
    cout << "\nLength of the best solution: " << best_length << endl;
    return 0;
}
