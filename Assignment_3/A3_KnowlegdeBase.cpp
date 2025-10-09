#include <bits/stdc++.h>
using namespace std;

class KnowledgeBase {
private:
    unordered_map<string, vector<string>> parent; // parent -> list of children
    unordered_map<string, string> gender;         // person -> "male"/"female"

public:
    // --- Adding Facts ---
    void add_parent(const string& p, const string& c) {
        parent[p].push_back(c);
    }

    void add_father(const string& f, const string& c) {
        gender[f] = "male";
        add_parent(f, c);
    }

    void add_mother(const string& m, const string& c) {
        gender[m] = "female";
        add_parent(m, c);
    }

    // --- Queries ---
    bool is_parent(const string& p, const string& c) {
        auto it = parent.find(p);
        if (it == parent.end()) return false;
        return find(it->second.begin(), it->second.end(), c) != it->second.end();
    }

    bool is_sibling(const string& a, const string& b) {
        for (auto& entry : parent) {
            auto& kids = entry.second;
            if (find(kids.begin(), kids.end(), a) != kids.end() &&
                find(kids.begin(), kids.end(), b) != kids.end() &&
                a != b) {
                return true;
            }
        }
        return false;
    }

    bool is_ancestor(const string& a, const string& b) {
        if (is_parent(a, b)) return true;
        auto it = parent.find(a);
        if (it != parent.end()) {
            for (auto& child : it->second) {
                if (is_ancestor(child, b)) return true;
            }
        }
        return false;
    }
};

// --- Helper to trim spaces ---
string trim(const string& s) {
    string result;
    for (char c : s) {
        if (c != ' ') result.push_back(c);
    }
    return result;
}

int main() {
    KnowledgeBase kb;
    cout << "Enter facts and queries (e.g. father(Jay,Minal), sibling(Rahul,Raj)?). Enter stop to quit.\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        line = trim(line);

        if (line == "stop") break;
        if (line.empty()) continue;

        bool query = false;
        if (!line.empty() && line.back() == '?') {
            query = true;
            line.pop_back(); // remove '?'
        }

        // Extract relation
        size_t l = line.find("(");
        size_t r = line.find(")");
        if (l == string::npos || r == string::npos) continue;

        string rel = line.substr(0, l);
        string args = line.substr(l + 1, r - l - 1);

        vector<string> parts;
        stringstream ss(args);
        string token;
        while (getline(ss, token, ',')) {
            parts.push_back(token);
        }

        string A = parts.size() > 0 ? parts[0] : "";
        string B = parts.size() > 1 ? parts[1] : "";

        // --- Fact Adding ---
        if (!query) {
            if (rel == "parent") kb.add_parent(A, B);
            else if (rel == "father") kb.add_father(A, B);
            else if (rel == "mother") kb.add_mother(A, B);
            else if (rel == "male" || rel == "female") {
                // gender fact
                // In this simple model, gender is stored directly
            }
            cout << "Fact added.\n";
        } 
        // --- Query ---
        else {
            bool ans = false;
            if (rel == "parent") ans = kb.is_parent(A, B);
            else if (rel == "sibling") ans = kb.is_sibling(A, B);
            else if (rel == "ancestor") ans = kb.is_ancestor(A, B);

            cout << (ans ? "Yes" : "No") << "\n";
        }
    }

    return 0;
}
