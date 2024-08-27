# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():
    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit(
            "Incorrect Usage - Two arguments required: python tournament.py FILENAME"
        )

    teams = []
    # TODO: Read teams into memory from file
    with open(sys.argv[1]) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            team_name = row["team"]
            team_rating = int(row["rating"])
            teams.append({"team": team_name, "rating": team_rating})

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):  # iterate through all simulations
        winning_team = simulate_tournament(teams)
        if winning_team in counts:
            counts[winning_team] += 1  # add one to the count
        else:
            counts[winning_team] = 1  # add the team to the list

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []
    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # Reduce the number of teams based on the winners
    # 16 - 8 - 4 - 2 - 1
    # Repeatedly simulate rouduns until there are no teams left
    while len(teams) > 1:  # no winner yet, still two or more
        teams = simulate_round(teams)  # function above returning list of winners
    return teams[0]["team"]  # return name of the winning team


if __name__ == "__main__":
    main()
