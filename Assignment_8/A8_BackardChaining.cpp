#include <bits/stdc++.h>
using namespace std;

// Backward Chaining Algorithm
bool backward_chaining(vector<pair<vector<string>, string>>& rules,
                       set<string>& facts,
                       string goal,
                       int depth = 0) {
    string indent(depth * 2, ' ');
    cout << indent << "Trying to prove: " << goal << "\n";

    // If goal is already known fact
    if (facts.find(goal) != facts.end()) {
        cout << indent << "✅ " << goal << " is a known fact.\n";
        return true;
    }

    // Get rules that conclude this goal
    vector<pair<vector<string>, string>> applicable_rules;
    for (auto& rule : rules) {
        if (rule.second == goal)
            applicable_rules.push_back(rule);
    }

    if (applicable_rules.empty()) {
        cout << indent << "❌ No rules to prove " << goal << ". Fails.\n";
        return false;
    }

    // Try each applicable rule
    for (auto& rule : applicable_rules) {
        auto conditions = rule.first;
        auto conclusion = rule.second;

        cout << indent << "Checking rule: [";
        for (int i = 0; i < conditions.size(); i++) {
            cout << conditions[i];
            if (i < conditions.size() - 1) cout << ", ";
        }
        cout << "] -> " << conclusion << "\n";

        bool success = true;
        for (auto& condition : conditions) {
            if (!backward_chaining(rules, facts, condition, depth + 1)) {
                success = false;
                break;
            }
        }

        if (success) {
            cout << indent << "✅ Rule succeeded: [";
            for (int i = 0; i < conditions.size(); i++) {
                cout << conditions[i];
                if (i < conditions.size() - 1) cout << ", ";
            }
            cout << "] -> " << goal << "\n";
            return true;
        }
    }

    cout << indent << "❌ Could not prove " << goal << ".\n";
    return false;
}

int main() {
    // Example Knowledge Base
    vector<pair<vector<string>, string>> rules = {
        {{"A", "B"}, "C"},  // Rule1: If A and B then C
        {{"C"}, "D"},       // Rule2: If C then D
        {{"D"}, "E"}        // Rule3: If D then E
    };

    set<string> facts = {"A", "B"};  // Initial facts
    string goal = "E";               // Goal to prove

    // Run Backward Chaining
    bool result = backward_chaining(rules, facts, goal);
    cout << "\nFinal Result: " << (result ? "True" : "False") << "\n";

    return 0;
}
