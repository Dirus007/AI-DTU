#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

struct State {
    vector<vector<int>> board;
    int cost;
    vector<vector<vector<int>>> path;

    State(const vector<vector<int>>& b, int c, const vector<vector<vector<int>>>& p)
        : board(b), cost(c), path(p) {}

    bool operator>(const State &other) const {
        return cost > other.cost;
    }
};

struct VectorHash {
    size_t operator()(const vector<vector<int>>& v) const {
        size_t hash = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                hash = hash * 9 + v[i][j];
            }
        }
        return hash;
    }
};


const vector<vector<int>> goal_state = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
const vector<vector<int>> moves = {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4, 6}, {1, 3, 5, 7}, {2, 4, 8}, {3, 7}, {4, 6, 8}, {5, 7}};

pair<int, int> find_zero(const vector<vector<int>>& state) {
    for (int i = 0; i < state.size(); ++i)
        for (int j = 0; j < state[i].size(); ++j)
            if (state[i][j] == 0)
                return {i, j};
    return {-1, -1}; // Error case, should not happen
}

int misplaced_tiles(const vector<vector<int>>& state) {
    int count = 0;
    for (int i = 0; i < state.size(); ++i)
        for (int j = 0; j < state[i].size(); ++j)
            if (state[i][j] != 0 && state[i][j] != goal_state[i][j])
                count++;
    return count;
}

int manhattan_distance(const vector<vector<int>>& state) {
    int distance = 0;
    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < state[i].size(); ++j) {
            if (state[i][j] != 0) {
                int x = (state[i][j] - 1) / 3;
                int y = (state[i][j] - 1) % 3;
                distance += abs(i - x) + abs(j - y);
            }
        }
    }
    return distance;
}

vector<vector<vector<int>>> best_first_search(const vector<vector<int>>& initial_state) {
    // Uses Misplaced Tiles in priority queue
    priority_queue<State, vector<State>, greater<State>> frontier;
    unordered_set<vector<vector<int>>, VectorHash> visited;
    frontier.emplace(initial_state, misplaced_tiles(initial_state), vector<vector<vector<int>>>{initial_state});
    visited.insert(initial_state);

    while(!frontier.empty()) {
        State current = frontier.top();
        frontier.pop();

        if(current.board == goal_state) return current.path;

        pair<int, int> zero = find_zero(current.board);
        int z = zero.first * 3 + zero.second;

        for (int next : moves[z]) {
            vector<vector<int>> next_state = current.board;
            swap(next_state[zero.first][zero.second], next_state[next / 3][next % 3]);

            if (!visited.count(next_state)) {
                visited.insert(next_state);
                vector<vector<vector<int>>> next_path = current.path;
                next_path.push_back(next_state);
                frontier.emplace(next_state, misplaced_tiles(next_state), next_path);
            }
        }
    }
    return {};
}

vector<vector<vector<int>>> least_cost_search(const vector<vector<int>>& initial_state) {
    // Uses Manhattan Distance in priority queue
    priority_queue<State, vector<State>, greater<State>> frontier;
    unordered_set<vector<vector<int>>, VectorHash> visited;
    frontier.emplace(initial_state, 0, vector<vector<vector<int>>>{initial_state});
    visited.insert(initial_state);

    while (!frontier.empty()) {
        State current = frontier.top();
        frontier.pop();

        if(current.board == goal_state) return current.path;

        pair<int, int> zero = find_zero(current.board);
        int z = zero.first * 3 + zero.second;

        for (int next : moves[z]) {
            vector<vector<int>> next_state = current.board;
            swap(next_state[zero.first][zero.second], next_state[next / 3][next % 3]);

            if (!visited.count(next_state)) {
                visited.insert(next_state);
                vector<vector<vector<int>>> next_path = current.path;
                next_path.push_back(next_state);
                int cost = current.cost + 1; // Assuming step cost is always 1
                frontier.emplace(next_state, cost + manhattan_distance(next_state), next_path);
            }
        }
    }
    return {};
}

void print(vector<vector<int>>&board){
    for (auto& row : board) {
        for (int tile : row) {
            cout << tile << " ";
        }
        cout << endl;
    }
    cout << "---" << endl;
}

int main() {
    vector<vector<int>> initial_state = {{1, 2, 3}, {0, 4, 6}, {7, 5, 8}};

    auto solution_bfs = best_first_search(initial_state);
    cout << "Best First Search Solution:" << endl;
    for(auto& step : solution_bfs) {
        print(step);
    }

    auto solution_lcs = least_cost_search(initial_state);
    cout << "\nLeast Cost Search Solution:" << endl;
    for (auto& step : solution_lcs) {
        print(step);
    }

    return 0;
}
