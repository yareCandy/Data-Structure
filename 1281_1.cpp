#include <iostream>
using namespace std;

template<class T>
class seqQueue
{
private:
    T *dt;
    int maxSize;
    int front, rear;
    void doubleSpace();
public:
    seqQueue(int initSize = 10);
    ~seqQueue(){delete [] dt;}
    bool isEmpty()const {return front == rear;}
    void enQueue(const T &d);
    T deQueue();
};

template<class T>
void seqQueue<T>::doubleSpace()
{
    T *tmp = dt;
    dt = new T [maxSize * 2];

    for (int i = 1; i <= maxSize; i++)
        dt[i] = tmp[(front + i) % maxSize];
    front = 0;
    rear = maxSize;
    maxSize *= 2;
    delete [] tmp;
}

template<class T>
seqQueue<T>::seqQueue(int initSize)
{
    dt = new T [initSize];
    maxSize = initSize;
    front = rear = 0;
}

template<class T>
void seqQueue<T>::enQueue(const T &d)
{
    if ((rear+1)%maxSize == front)
        doubleSpace();
    rear = (rear+1) % maxSize;
    dt[rear] = d;
}

template<class T>
T seqQueue<T>::deQueue()
{
    front = (front + 1) % maxSize;
    return dt[front];
}

int M, N, m, n;
int a[40][40] = {0};
int startx, starty, endx, endy;
struct point
{
    int x, y, step;
    point(int X = 0, int Y = 0, int s = 0):x(X), y(Y), step(s){}
};

void receive(bool visited[][40])
{
    for (int i = 0; i < M; i ++)
        for (int j = 0; j < N; j++)
        {
            cin >> a[i][j];
            if (a[i][j] == 3)
            {startx = i; starty = j; visited[i][j] = 0;}
            else if (a[i][j] == 4)
            {endx = i, endy = j; visited[i][j] = 0;}
            else if (a[i][j] == 0 || a[i][j] == 2)
                visited[i][j] = 1;
        }
}

inline bool inmap(int x, int y)
{
    if (x >= 0 && y >= 0 && x < M && y < N)
        return true;
    return false;
}

int bfs(int x, int y, bool visited[][40])
{
    int dir[8][2] = {{m, n}, {-m, n}, {m, -n}, {-m, -n}, {n, m}, {n, -m}, {-n, m}, {-n, -m}};//向下、向上、向右、向左
    seqQueue<point> que(40);
    point cur, tmp;
    if (inmap(x, y))
        que.enQueue(point(x, y));

    while (!que.isEmpty())
    {
        cur = que.deQueue();
        visited[cur.x][cur.y] = true;

        if (cur.x == endx && cur.y == endy)//到达终点
            return cur.step;

        for (int i = 0; i < 8; i++)
        {
            tmp.x = cur.x + dir[i][0];
            tmp.y = cur.y + dir[i][1];
            
            if (inmap(tmp.x, tmp.y) && !visited[tmp.x][tmp.y])
            {
                tmp.step = cur.step + 1;
                que.enQueue(tmp);
            }
        }
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int result;
    cin >> M >> N >> m >> n;
    bool visited[40][40] = {0};
 
    receive(visited);
    result = bfs(startx, starty, visited);
    cout << result << '\n';
 
    return 0;
}