#include "CricketTeam.hpp"

CricketTeam::CricketTeam(const string& name) : name(name) {}

void CricketTeam::addPlayer(const string& playerName) {
    players.emplace_back(playerName);
}

const string& CricketTeam::getName() const {
    return name;
}

vector<CricketPlayer>& CricketTeam::getPlayers() {
    return players;
}

void CricketTeam::showDetails() const {
    cout << "Team: " << name << "\nPlayers:\n";
    for (const auto& player : players) {
        cout << "  " << player.getName() << "\n";
    }
}

void CricketTeam::setPlayerNames() {
    cout << "Enter the names of the players of team " << name << "\n";
    for (int i = 0; i < 11; i++) {
        cout << "Player " << i + 1 << ", Name - ";
        string playerName;
        cin >> playerName;
        addPlayer(playerName);
    }
    cout << "\n";
}

int CricketTeam::getChoice() const {
    return choice;
}
