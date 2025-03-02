#include <iostream>
#include <string>

using namespace std;

// Ball Class
class Ball {
private:
    int x, y;
public:
    Ball(int startX, int startY) : x(startX), y(startY) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    int getX() { return x; }
    int getY() { return y; }

    void getPosition() {
        cout << "Ball Position: (" << x << ", " << y << ")\n";
    }
};

// Goal Class
class Goal {
private:
    int goalX, goalY;
public:
    Goal(int x = 3, int y = 3) : goalX(x), goalY(y) {}

    bool isGoalReached(int ballX, int ballY) {
        return (ballX == goalX && ballY == goalY);
    }
};

// Robot Class
class Robot {
private:
    string name;
    int hits;
public:
    Robot(string robotName) : name(robotName), hits(0) {}

    void hitBall(Ball &ball, const string &direction) {
        if (direction == "up") ball.move(0, 1);
        else if (direction == "down") ball.move(0, -1);
        else if (direction == "left") ball.move(-1, 0);
        else if (direction == "right") ball.move(1, 0);
        hits++;
    }

    int getHits() { return hits; }
    string getName() { return name; }
};

// Team Class
class Team {
private:
    string teamName;
    Robot *robot;
public:
    Team(string name, string robotName) : teamName(name) {
        robot = new Robot(robotName);
    }

    ~Team() { delete robot; }

    Robot* getRobot() { return robot; }
    string getTeamName() { return teamName; }
};

// Game Class
class Game {
private:
    Team *teamOne, *teamTwo;
    Ball ball;
    Goal goal;
public:
    Game(string team1, string team2, string robot1, string robot2): teamOne(new Team(team1, robot1)), teamTwo(new Team(team2, robot2)), ball(0, 0), goal() {}

    ~Game() {
        delete teamOne;
        delete teamTwo;
    }

    void play(Team *team) {
        cout << "\n" << team->getTeamName() << " (" << team->getRobot()->getName() << ") is playing...\n";
        
        while (!goal.isGoalReached(ball.getX(), ball.getY())) {
            string direction;
            cout << "Enter move direction (up/down/left/right): ";
            cin >> direction;

            team->getRobot()->hitBall(ball, direction);
            ball.getPosition();

            if (goal.isGoalReached(ball.getX(), ball.getY())) {
                cout << "\nGoal reached by " << team->getTeamName() << " in " << team->getRobot()->getHits() << " hits!\n";
                break;
            }
        }
    }

    void declareWinner() {
        int hits1 = teamOne->getRobot()->getHits();
        int hits2 = teamTwo->getRobot()->getHits();

        cout << "\nGame Over!\n";
        if (hits1 < hits2)
            cout << teamOne->getTeamName() << " wins with " << hits1 << " hits!\n";
        else if (hits2 < hits1)
            cout << teamTwo->getTeamName() << " wins with " << hits2 << " hits!\n";
        else
            cout << "It's a tie!\n";
    }

    void startGame() {
        cout << "Football Game Begins!\n";
        play(teamOne);
        ball = Ball(0, 0);
        play(teamTwo);
        declareWinner();
    }
};

int main() {
    Game game("Team A", "Team B", "Robot1", "Robot2");
    game.startGame();
    return 0;
}
