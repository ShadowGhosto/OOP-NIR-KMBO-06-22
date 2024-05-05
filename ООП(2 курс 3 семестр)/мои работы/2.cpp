#include <iostream>
#include <list>
#include <string>

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

SportsTeam pop(list<SportsTeam>& teams) {
    auto it = teams.begin();
    auto maxPriorityTeam = *it;
    for (; it != teams.end(); ++it) {
        if (*it < maxPriorityTeam) {
            maxPriorityTeam = *it;
        }
    }
    teams.remove(maxPriorityTeam);
    return maxPriorityTeam;
}

ostream& operator<<(ostream& os, const SportsTeam& team) {
    os << "�������: " << team.name << ", �����: " << team.city << ", �����: " << team.wins
        << ", ���������: " << team.losses << ", ������: " << team.draws << ", �����: " << team.points;
    return os;
}
int main() {
    setlocale(LC_ALL, "rus");
    list<SportsTeam> teams;
    teams.emplace_back("�������1", "�����1", 5, 3, 2);
    teams.emplace_back("�������2", "�����2", 4, 2, 1);
    teams.emplace_back("�������3", "�����3", 6, 1, 3);
    teams.emplace_back("�������4", "�����4", 4, 3, 2);

    cout << "������ ������ �� ��������: " << endl;
    for (const SportsTeam& team : teams) { cout << team << endl; }

    SportsTeam removedTeam = pop(teams);
    cout << "������� �������: " << endl << removedTeam << endl;

    cout << "������ ������ ����� ��������: " << endl;
    for (const SportsTeam& team : teams) { cout << team << endl; }

    return 0;
}
