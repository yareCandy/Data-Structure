#include <iostream>
using namespace std;
const int N = 55;

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
    T getHead()const {return dt[(front + 1) % maxSize];}
    int size(){
        if (front <= rear) return rear - front;
        else return rear + maxSize - front;
    }
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

struct point
{
    int x, y;
    point(int X = 0, int Y = 0):x(X), y(Y){}
};

char s[N][N];
int n, m, **vis;
int num = 0, tot = 0;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
seqQueue<point> a(55);

void DFS(int x,int y)
{
	vis[x][y] = 1;//标为已经访问
	tot ++;//访问过的陆地数+1
	if(s[x][y] == '?')//如果是未知那未知的数也要+1
		num++;
	for(int i = 0;i < 4; i++)
	{
		int c = x + dx[i];
        int d = y + dy[i];
		if(c>=1 && c<=n && d>=1 && d<=m && (!vis[c][d]) && s[c][d] != '#')
			DFS(c,d);
	}
}

void find(int x,int y)
{
	vis[x][y] = 1;
	s[x][y] = '#';

	for(int i = 0; i < 4; i++)
	{
		int a = x + dx[i];
        int b = y + dy[i];
		if(a>=1 && a<=n && b>=1 && b<=m && (!vis[a][b]) && (s[a][b]=='?'))
			find(a,b);
	}
}

int check()
{
	int cnt = 0;
    for (int i = 0; i < n+2; i++){
        for (int j = 0; j < m+2; j++)
            vis[i][j] = 0;
    }

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(s[i][j] != '#' && !vis[i][j])
				DFS(i,j), cnt++;
	return cnt;
}

int main()
{
	point cur;
	seqQueue<point> b(55);//备用
    cin >> n >> m;
	vis = new int *[n+2];
	for (int i = 0; i < n+2; i++)
		vis[i] = new int [m+2];
	
	for(int i = 1;i <= n; i ++)
	{
        cin.get();
		for(int j = 1; j <= m; j++)
        {
            s[i][j] = cin.get();
			if(s[i][j] == '?')//把所有的'?'放在队列中3
				a.enQueue(point(i,j));
        }		
	}

	if(check() > 1)
	{
		if (num == tot) {cout << "Ambiguous\n"; return 0;}
		while(!a.isEmpty())
		{
			cur.x = a.getHead().x, cur.y = a.getHead().y;
			a.deQueue();
			if(s[cur.x][cur.y] == '#')
				continue;
			num = tot = 0;	
			
            for (int i = 0; i < n+2; i++)
                for (int j = 0; j < m+2; j++)
                    vis[i][j] = 0;
    
			DFS(cur.x, cur.y);
			if(num == tot)
			{
                for (int i = 0; i < n+2; i++){
                    for (int j = 0; j < m+2; j++)
                        vis[i][j] = 0;
                }
				find(cur.x, cur.y);
			}
			else
			{
				b.enQueue(cur);//不全是问号联通的区域
			}
			
		}

		if(check()>1)
		{
			cout << "Impossible\n";
			return 0;
		}
	}

	bool flag = true;
	while (!b.isEmpty())
	{
		int x = b.getHead().x, y = b.getHead().y;
		b.deQueue();

		if(s[x][y] == '#')	continue;
		s[x][y] = '#';
		int p = check();
		if(p == 1 || p == 0)
			flag = false;
		s[x][y] = '.';
	}

	while (!a.isEmpty())
	{
		int x = a.getHead().x, y = a.getHead().y;
		a.deQueue();

		if(s[x][y] == '#')	continue;
		s[x][y] = '#';
		int p = check();
		if(p == 1 || p == 0)
			flag = false;
		s[x][y] = '.';
	}

	if(!flag)
		cout << "Ambiguous\n";
	else
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++)
                cout << s[i][j];
        	cout << '\n';
        }
	return 0;
}