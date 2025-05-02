#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <Windows.h>
#include <iomanip>
#include <algorithm>

using namespace std;

class Clubs {
public:
    string name;
    short matches = 0;
    short points = 0;
    short wins = 0;
    short draws = 0;
    short losses = 0;
    short goals_for = 0;
    short goals_against = 0;

    Clubs(string name) : name(name) {}

    void updateStats(short goalsFor, short goalsAgainst) {
        matches++;
        goals_for += goalsFor;
        goals_against += goalsAgainst;
        if (goalsFor > goalsAgainst) {
            wins++;
            points += 3;
        }
        else if (goalsFor == goalsAgainst) {
            draws++;
            points++;
        }
        else {
            losses++;
        }
    }
};

class League {
public:
    vector<Clubs> clubs;
    vector<string> match_logs;

    void addClub(const string& clubName) {
        clubs.emplace_back(clubName);
    }

    void leagueSimulate() {
        cout << "League is simulating... please wait" << endl;
        Sleep(3000);

        for (size_t i = 0; i < clubs.size(); i++) {
            for (size_t j = i + 1; j < clubs.size(); j++) {
                Clubs& home = clubs[i];
                Clubs& away = clubs[j];
                short homeGoals = rand() % 6;
                short awayGoals = rand() % 6;

                home.updateStats(homeGoals, awayGoals);
                away.updateStats(awayGoals, homeGoals);

                string match_result = home.name + " " + to_string(homeGoals) +
                    " - " + to_string(awayGoals) + " " + away.name;
                match_logs.push_back(match_result);
            }
        }

        for (size_t i = 0; i < clubs.size(); i++) {
            for (size_t j = i + 1; j < clubs.size(); j++) {
                Clubs& home = clubs[i];
                Clubs& away = clubs[j];
                short homeGoals = rand() % 6;
                short awayGoals = rand() % 6;

                home.updateStats(homeGoals, awayGoals);
                away.updateStats(awayGoals, homeGoals);

                string match_result = home.name + " " + to_string(homeGoals) +
                    " - " + to_string(awayGoals) + " " + away.name;
                match_logs.push_back(match_result);
            }
        }
    }

    void displayTable() {
        sort(clubs.begin(), clubs.end(), [](const Clubs& a, const Clubs& b) {
            return a.points > b.points; 
            });

        cout << "\nDisplay Table of Season: " << endl;
        cout << left << setw(15) << "Club" << setw(8) << "Matches" << setw(5) << "W" << setw(5) << "D" << setw(5)
            << "L" << setw(8) << "G" << setw(8) << "GA" << setw(5) << "Points" << endl;

        for (const auto& club : clubs) {
            cout << left << setw(15) << club.name
                << setw(8) << club.matches
                << setw(5) << club.wins
                << setw(5) << club.draws
                << setw(5) << club.losses
                << setw(8) << club.goals_for
                << setw(8) << club.goals_against
                << setw(5) << club.points
                << endl;
        }
    }

    void displayLog() {
        for (const auto& log : match_logs)
            cout << log << endl;
    }

    void listClubs() {
        for (const auto& club : clubs)
            cout << " - " << club.name << endl;
    }

    bool isClubInLeague(const string& clubName) {
        auto it = find_if(clubs.begin(), clubs.end(), [&](const Clubs& club) {
            return club.name == clubName;
            });
        return it != clubs.end();
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    League league;
    league.addClub("Real Madrid");
    league.addClub("Barcelona");
    league.addClub("Girona");
    league.addClub("Atletic Bilibao");
    league.addClub("Sevilia");
    league.addClub("Atletico Madrid");
    league.addClub("Valencia");
    league.addClub("Getafe");
    league.addClub("Cadiz");
    league.addClub("Espanyol");
    league.addClub("Real Betis");
    league.addClub("Real Sociedad");
    league.addClub("Mallocra");
    league.addClub("Cordoba");
    league.addClub("Malaga");

    league.listClubs();
    string user_club;
    string show_log;

    cout << "Choose club: ";
    getline(cin, user_club); 

    if (league.isClubInLeague(user_club)) {
        league.leagueSimulate();
        league.displayTable();
    }
    else {
        cout << "Club \"" << user_club << "\" is not in the league!" << endl;
        return 0; 
    }

    cout << "Do you want to see log matches? (Y/N): ";
    cin >> show_log;

    if (show_log == "Y" || show_log == "y")
        league.displayLog();

    return 0;
}
