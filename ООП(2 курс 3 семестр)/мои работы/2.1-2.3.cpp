#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <queue>

using namespace std;
class SportsTeam {
private:
    string name;
    string city;
    int wins;
    int losses;
    int draws;
    int points;

public:
    SportsTeam() {}
    SportsTeam(const string& n, const string& c, int w, int l, int d) :
        name(n), city(c), wins(w), losses(l), draws(d), points(w * 3 + d) {}


    bool operator==(const SportsTeam& other) const {
        return (name == other.name) && (city == other.city);
    }

    bool operator<(const SportsTeam& other) const {
        return (wins != other.wins) ? (wins < other.wins) :
            (draws != other.draws) ? (draws < other.draws) :
            (losses != other.losses) ? (losses < other.losses) :
            (name < other.name);
    }

    string getName() const { return name; }

    string getCity() const { return city; }

    int getWins() const { return wins; }

    int getLosses() const { return losses; }

    int getDraws() const { return draws; }

    int getPoints() const { return points; }

    friend ostream& operator<<(ostream& os, const SportsTeam& team);
};
ostream& operator<<(ostream& os, const SportsTeam& team) {
    os << "Name: " << team.getName() << ", City: " << team.getCity()
        << ", Wins: " << team.getWins() << ", Losses: " << team.getLosses()
        << ", Draws: " << team.getDraws() << ", Points: " << team.getPoints();
    return os;
}
bool operator<(const SportsTeam team, int a) {
    return a < team.getWins();

}
bool findbyValue(const map<string, int>& tree, int value) {
    for (const auto& pair : tree) {
        if (pair.second == value) {
            return true;
        }
    }
    return false;
}

bool findbyKey(const map<string, int>& tree, const string& key) {
    return tree.find(key) != tree.end();
}

void printTree(const map<string, int>& tree) {
    for (const auto& pair : tree) {
        cout << "Name: " << pair.first << ", ID: " << pair.second << endl;
    }
}

bool findbyKey(const map<string, SportsTeam>& tree, const string& key) {
    return tree.find(key) != tree.end();
}

void printTree(const map<string, SportsTeam>& tree) {
    for (const auto& pair : tree) {
        cout << "Name: " << pair.first << ", ID: " << pair.second << endl;
    }
}

void printTreeWithParam(const map<string, SportsTeam>& tree, string key) {
    for (const auto& pair : tree) {
        if (pair.first == key) {
            cout << "Tree: " << pair.first << ", Param: " << pair.second << endl;
        }
    }
}

map<string, SportsTeam> filter(const map<string, SportsTeam>& tree, int data) {
    map<string, SportsTeam> filteredTree;
    for (const auto& pair : tree) {
        if (pair.second.getPoints() > data) {
            filteredTree.insert(pair);
        }
    }
    return filteredTree;
}

multimap<string, SportsTeam> filter(const multimap<string, SportsTeam>& tree, int data) {
    multimap<string, SportsTeam> filteredTree;
    for (const auto& pair : tree) {
        if (pair.second < data) {
            filteredTree.insert(pair);
        }
    }
    return filteredTree;
}

vector<int> uniqueValues(const map<string, int>& tree) {
    set<int> uniqueSet;
    for (const auto& pair : tree) {
        uniqueSet.insert(pair.second);
    }
    vector<int> uniqueVector(uniqueSet.begin(), uniqueSet.end());
    return uniqueVector;
}



template<typename T>
void print_queue(T& q) {
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    cout << '\n';
}






int main() {
    map<string, SportsTeam> sportsTeams;
    sportsTeams["Team1"] = SportsTeam("Team1", "City1", 10, 5, 3);
    sportsTeams["Team2"] = SportsTeam("Team2", "City2", 8, 7, 2);
    sportsTeams["Team3"] = SportsTeam("Team3", "City3", 12, 3, 1);
    sportsTeams["Team4"] = SportsTeam("Team4", "City4", 6, 9, 2);
    printTree(sportsTeams);

    cout << "Filtered Teams: " << endl;
    int filterValue = 20;
    map<string, SportsTeam> filteredTeams = filter(sportsTeams, filterValue);
    printTree(filteredTeams);



    multimap<string, SportsTeam> SortedTeams;
    SortedTeams.insert(make_pair("Team1", SportsTeam("Team1", "City1", 10, 5, 3)));
    SortedTeams.insert(make_pair("Team2", SportsTeam("Team2", "City2", 8, 7, 2)));
    SortedTeams.insert(make_pair("Team3", SportsTeam("Team3", "City3", 12, 3, 1)));

    return 0;
}
