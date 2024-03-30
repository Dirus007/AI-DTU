#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class CryptarithmeticSolver {
public:
    unordered_map<char, int> mp;
    unordered_map<char, int> solvePuzzle(const string& s1, const string& s2, const string& s3) {
        string uniqueChars = getUniqueChars(s1 + s2 + s3);

        if(uniqueChars.size() > 10){
            cout << "Invalid strings: More than 10 unique characters." << endl;
            return {};
        }

        unordered_map<char, int> charToDigit;
        vector<bool> used(10, false);
        if(permutation(0, uniqueChars, charToDigit, used, s1, s2, s3)){
            mp = charToDigit;
            return charToDigit;
        }
        return {};
    }

    string getUniqueChars(const string& str) {
        string uniqueChars;
        unordered_set<char> seen;

        for (char ch : str) {
            if (seen.find(ch) == seen.end()) {
                seen.insert(ch);
                uniqueChars += ch;
            }
        }

        return uniqueChars;
    }

    bool permutation(int index, const string& uniqueChars, unordered_map<char, int>& charToDigit, vector<bool>& used, const string& s1, const string& s2, const string& s3) {
        if(index == uniqueChars.size()) return isValid(charToDigit, s1, s2, s3);

        for(int i = 0; i < 10; ++i) {
            if(!used[i]) {
                used[i] = true;
                charToDigit[uniqueChars[index]] = i;
                if (permutation(index + 1, uniqueChars, charToDigit, used, s1, s2, s3)) {
                    return true;
                }
                used[i] = false;
            }
        }
        return false;
    }

    bool isValid(const unordered_map<char, int>& charToDigit, const string& s1, const string& s2, const string& s3) {
        return getNumericValue(charToDigit, s1) + getNumericValue(charToDigit, s2) == getNumericValue(charToDigit, s3);
    }

    int getNumericValue(const unordered_map<char, int>& charToDigit, const string& str) {
        int value = 0;
        for (char ch : str) {
            value = value * 10 + charToDigit.at(ch);
        }
        return value;
    }
};

int main() {
    CryptarithmeticSolver solver;
    string s1 = "DONALD", s2 = "GERALD", s3 = "ROBERT";
    auto solution = solver.solvePuzzle(s1, s2, s3);

    if (!solution.empty()) {
        cout << "Solution found:" << endl;
        cout<<s1<<" = "<<solver.getNumericValue(solver.mp, s1)<<"\n";
        cout<<s2<<" = "<<solver.getNumericValue(solver.mp, s2)<<"\n";
        cout<<s3<<" = "<<solver.getNumericValue(solver.mp, s3)<<"\n";
        for (const auto& pair : solution) {
            cout << pair.first << " = " << pair.second << "\n";
        }
        cout << endl;
    } 
    else cout << "No solution found." << endl;

    return 0;
}
