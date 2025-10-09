#include <bits/stdc++.h>
using namespace std;

// Forward Chaining Algorithm
bool forward_chaining(vector<pair<vector<string>, string>>& rules,
                      set<string> facts,
                      string goal) {
    set<int> applied_rules;  // rules already used

    while (true) {
        bool new_fact_added = false;

        for (int i = 0; i < rules.size(); i++) {
            auto conditions = rules[i].first;
            string conclusion = rules[i].second;

            // If this rule has not been applied and all conditions are satisfied
            bool applicable = true;
            for (auto& cond : conditions) {
                if (facts.find(cond) == facts.end()) {
                    applicable = false;
                    break;
                }
            }

            if (applied_rules.find(i) == applied_rules.end() && applicable) {
                // Apply the rule
                facts.insert(conclusion);
                applied_rules.insert(i);
                new_fact_added = true;

                cout << "Applied Rule " << (i + 1) << ": ";
                for (int j = 0; j < conditions.size(); j++) {
                    cout << conditions[j];
                    if (j < conditions.size() - 1) cout << " & ";
                }
                cout << " -> " << conclusion << "\n";

                cout << "Current Facts: { ";
                for (auto& f : facts) cout << f << " ";
                cout << "}\n";

                if (conclusion == goal) {
                    cout << "✅ Goal reached!\n";
                    return true;
                }
            }
        }

        if (!new_fact_added) break;
    }

    cout << "❌ Goal not reached.\n";
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

    // Run Forward Chaining
    bool result = forward_chaining(rules, facts, goal);
    cout << "Result: " << (result ? "True" : "False") << endl;

    return 0;
}
