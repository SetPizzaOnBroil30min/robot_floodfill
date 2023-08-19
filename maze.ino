#include <queue>
#include <iostream>

#define inf ((float)(_HUGE_ENUF * _HUGE_ENUF))
using namespace std;

class Maze {
    public:
        float maze[6][6][6][6] = {1};
        int currentposition[2] = {5,5}; // Set in bottom right corner
        int availablewalls[4] = {}; // Front, Right, Back, Left (needs to be referenced)
        queue<int> orientation; // 1 - East, 2 - South, 3 - West, 4 - North
        Maze() {orientation.push(1); orientation.push(2); orientation.push(3); orientation.push(4);}
        
/*
representation is always left facing right as forward, mapping is relative
{0, 0}  ------------------------------ 
        |                            |
        |                            |
        |                            |
        |                            |
        O->                          |
        |                            |
        |                            |
        |                            |
        |                            |
        ------------------------------ {26, 26}
*/
    void map_maze(int walls[4], int colour) {
        // Update current map with current cell information
        // Colour is 1 - White, 2 - Black, 3 - Green, 4 - Blue, 5 - Purple, 6 - Yellow, 7 - Red
        queue<int> wallDetected;

        for (int i = 0; i < 4; i++) {
            wallDetected.push(walls[i]);
            availablewalls[i] = walls[i];
        }

        // Reorder elements relative to orientation
        if (orientation.front() != 1) {
            for (int i = 0; i < 5 - orientation.front(); i++) {
                wallDetected.push(wallDetected.front());
                wallDetected.pop();
            }
        }

        if (maze[currentposition[0] + 1][currentposition[1]] == 0) {maze[currentposition[0] + 1][currentposition[1]] = wallDetected.front(); wallDetected.pop();}
        if (maze[currentposition[0]][currentposition[1] + 1] == 0) {maze[currentposition[0]][currentposition[1] + 1] = wallDetected.front(); wallDetected.pop();}
        if (maze[currentposition[0] - 1][currentposition[1]] == 0) {maze[currentposition[0] - 1][currentposition[1]] = wallDetected.front(); wallDetected.pop();}
        if (maze[currentposition[0]][currentposition[1] - 1] == 0) {maze[currentposition[0]][currentposition[1] - 1] = wallDetected.front(); wallDetected.pop();}            

        maze[currentposition[0]][currentposition[1]] = colour;
    }

    void move() {
        // Move in a direction by 1 cell
        switch (orientation.front()) {
            case 1:
                currentposition[0] += 2;
                break;

            case 2:
                currentposition[1] += 2;
                break;

            case 3:
                currentposition[0] -= 2;
                break;

            case 4:
                currentposition[1] -= 2;
                break;
        }
    }

    void turn_left() {
        for (int i = 0; i < 3; i++) {
            orientation.push(orientation.front());
            orientation.pop();
        }
    }

    void turn_right() {
        orientation.push(orientation.front());
        orientation.pop();
    }

    void print_maze() {
        for (auto &row : maze)
        {
            for (auto &column : row)
            {
                cout << column << " ";
            }
            cout << endl;
        }
    }
};