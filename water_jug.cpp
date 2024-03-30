#include <iostream>
#include <queue>
#include <stack>
#include <set>
using namespace std;

struct Node {
    int x, y;
    vector<pair<int, int>> path;
};

// Function to check if a state is already visited
bool isVisited(set<pair<int, int>> &visited, Node&node) {
    return visited.find({node.x, node.y}) != visited.end();
}

// BFS implementation
void BFS(int a, int b, int target) {
    set<pair<int, int>> visited;
    bool isSolvable = false;
    vector<pair<int, int>> final_path;
    
    queue<Node> q;
    q.push({0,0, {}});  // Initial state

    while(!q.empty()){
        Node u = q.front();
        q.pop();

        if(isVisited(visited, u)) continue;

        visited.insert({u.x, u.y});
        u.path.push_back({u.x, u.y});

        if((u.x == target && u.y == 0) || (u.y == target && u.x == 0)){
            isSolvable = true;
            final_path = u.path;
            break;
        }

        // Fill Jug A
        q.push({a, u.y, u.path});
        // Fill Jug B
        q.push({u.x, b, u.path});
        // Empty Jug A
        q.push({0, u.y, u.path});
        // Empty Jug B
        q.push({u.x, 0, u.path});
        // Pour A -> B
        q.push({u.x - min(u.x, b - u.y), u.y + min(u.x, b - u.y), u.path});
        // Pour B -> A
        q.push({u.x + min(a - u.x, u.y), u.y - min(a - u.x, u.y), u.path});
    }

    if(isSolvable) {
        cout << "Path to target using BFS"<< endl;
        for(auto &step : final_path)
            cout << "Jug A: " << step.first <<"/"<< a<<", Jug B: " << step.second <<"/"<<b<< endl;
    } 
    else cout << "No solution possible using BFS"<< endl;
}

// DFS implementation (similar structure to BFS but using stack)
void DFS(int a, int b, int target) {
    set<pair<int, int>> visited;
    bool isSolvable = false;
    vector<pair<int, int>> final_path;
    
    stack<Node> q;
    q.push({0,0, {}});  // Initial state

    while(!q.empty()){
        Node u = q.top();
        q.pop();

        if(isVisited(visited, u)) continue;

        visited.insert({u.x, u.y});
        u.path.push_back({u.x, u.y});

        if((u.x == target && u.y == 0) || (u.y == target && u.x == 0)){
            isSolvable = true;
            final_path = u.path;
            break;
        }

        // Fill Jug A
        q.push({a, u.y, u.path});
        // Fill Jug B
        q.push({u.x, b, u.path});
        // Empty Jug A
        q.push({0, u.y, u.path});
        // Empty Jug B
        q.push({u.x, 0, u.path});
        // Pour A -> B
        q.push({u.x - min(u.x, b - u.y), u.y + min(u.x, b - u.y), u.path});
        // Pour B -> A
        q.push({u.x + min(a - u.x, u.y), u.y - min(a - u.x, u.y), u.path});
    }

    if(isSolvable) {
        cout << "Path to target using BFS"<< endl;
        for(auto &step : final_path)
            cout << "Jug A: " << step.first <<"/"<< a<<", Jug B: " << step.second <<"/"<<b<< endl;
    } 
    else cout << "No solution possible using BFS"<< endl;
}

int main() {
    int Jug1 = 4, Jug2 = 3, target = 2;
    cout << "Using BFS:" << endl;
    BFS(Jug1, Jug2, target);
    cout << "\nUsing DFS:" << endl;
    DFS(Jug1, Jug2, target);
    return 0;
}
