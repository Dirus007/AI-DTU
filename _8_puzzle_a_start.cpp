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
    int g; // Cost to reach the current state (g(n))
    int h; // Heuristic estimate (h(n))
    vector<vector<vector<int>>> path;

    State(const vector<vector<int>>& b, int g, int h, const vector<vector<vector<int>>>& p)
        : board(b), g(g), h(h), path(p) {}

    int f() const { return g + h; } // f(n) = g(n) + h(n)

    bool operator>(const State &other) const {
        return this->f() > other.f();
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
    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < state[i].size(); ++j) {
            if (state[i][j] == 0) return {i, j};
        }
    }
    return {-1, -1};
}

int h(const vector<vector<int>>& state) {
    int distance = 0;
    for(int i = 0; i < state.size(); ++i){
        for(int j = 0; j < state[i].size(); ++j){
            int val = state[i][j];
            if(val != 0) {
                int targetX = (val - 1) / 3;
                int targetY = (val - 1) % 3;
                distance += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return distance;
}

vector<vector<vector<int>>> astar_search(const vector<vector<int>>& initial_state) {
    priority_queue<State, vector<State>, greater<State>> frontier;
    unordered_set<vector<vector<int>>, VectorHash> explored;

    frontier.push(State(initial_state, 0, h(initial_state), vector<vector<vector<int>>>{initial_state}));

    while(!frontier.empty()){
        State current = frontier.top();
        frontier.pop();

        if(current.board == goal_state) return current.path;

        if(!explored.insert(current.board).second) continue;

        pair<int, int> zero = find_zero(current.board);
        int z = zero.first * 3 + zero.second;

        for(int m : moves[z]){
            int nextX = m / 3;
            int nextY = m % 3;
            vector<vector<int>> next_state = current.board;
            swap(next_state[zero.first][zero.second], next_state[nextX][nextY]);

            if(explored.find(next_state) == explored.end()){
                vector<vector<vector<int>>> next_path = current.path;
                next_path.push_back(next_state);
                int next_g = current.g + 1;
                int next_h = h(next_state);
                frontier.push(State(next_state, next_g, next_h, next_path));
            }
        }
    }

    return {};
}

void print_path(const vector<vector<vector<int>>>& path) {
    for (const auto& step : path) {
        for (const auto& row : step) {
            for (int tile : row) {
                cout << tile << " ";
            }
            cout << endl;
        }
        cout << "-----\n";
    }
}

int main() {
    vector<vector<int>> initial_state = {{1, 2, 3}, {0, 4, 6}, {7, 5, 8}};
    auto solution_path = astar_search(initial_state);
    cout << "A* Search Solution Path:" << endl;
    print_path(solution_path);

    return 0;
}
