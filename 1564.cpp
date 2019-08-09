#include <iostream>

using namespace std;


int x0, y0, x1, y1, chessboard[10][10] = {-10}, minCost = 2147483647;
bool visited[10][10] = {0};
int dir[4][2] = {{1,0}, {-1, 0}, {0,1}, {0,-1}};//方向

void visit(int, int, int, int);

bool inmap(int x, int y)
{
    if (x >= 0 && y >= 0 && x < 6 && y < 6)
        return true;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int m = 0; m < n; m++) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cin >> chessboard[i][j];
            }
        }
        cin >> x0 >> y0 >> x1 >> y1;
        visit(x0, y0, 0, 1);
        cout << minCost << '\n';
    }
}

void visit(int x0, int y0, int cost, int status) {
    if (minCost > cost) {
        if (x0 == x1 && y0 == y1) {
            minCost = cost;
            return;
        } else {
            int x = x0, y = y0;
           
            for (int i = 0; i < 4; i++)
            {
                x0 = x + dir[i][0];
                y0 = y + dir[i][1];
                if (inmap(x0, y0) && !visited[x0][y0])
                {
                    int costTmp = status * chessboard[x0][y0];
                    visited[x0][y0] = true;
                    visit(x0, y0, cost + costTmp, costTmp % 4 + 1);
                    visited[x0][y0] = false;
                }
            }

            
            int x2 = x0 - 1, y2 = y0;
            if (x2 >= 0 && x2 < 6 && !visited[x2][y2]) {
                int costTmp = status * chessboard[x2][y2];
                visited[x2][y2] = 1;
                visit(x2, y2, cost + costTmp, costTmp % 4 + 1);
                visited[x2][y2] = 0;
            }
            x2 = x0 + 1, y2 = y0;
            if (x2 >= 0 && x2 < 6 && !visited[x2][y2]) {
                int costTmp = status * chessboard[x2][y2];
                visited[x2][y2] = 1;
                visit(x2, y2, cost + costTmp, costTmp % 4 + 1);
                visited[x2][y2] = 0;
            }
            x2 = x0, y2 = y0 - 1;
            if (y2 >= 0 && y2 < 6 && !visited[x2][y2]) {
                int costTmp = status * chessboard[x2][y2];
                visited[x2][y2] = 1;
                visit(x2, y2, cost + costTmp, costTmp % 4 + 1);
                visited[x2][y2] = 0;
            }
            x2 = x0, y2 = y0 + 1;
            if (y2 >= 0 && y2 < 6 && !visited[x2][y2]) {
                int costTmp = status * chessboard[x2][y2];
                visited[x2][y2] = 1;
                visit(x2, y2, cost + costTmp, costTmp % 4 + 1);
                visited[x2][y2] = 0;
            }
        }
    }
}
