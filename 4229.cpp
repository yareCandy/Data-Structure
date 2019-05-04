//4229.cpp
//OJ4229
//第一行一个整数N，表示总共的论文数目，从0～n-1编号。
//接下来若干行，每行执行一个操作。
//每行的第一个字段指示操作的类型，分别有add, query, finish三种不同的操作，格式如下。
//如果第一个字段是add，则接下来输入两个整数i，j 表示论文i引用的论文j，也就是说论文j的被引用数增加1。
//如果第一个字段是query，则输出当前论文被引用数最高的论文编号和被引用数，用空格隔开，如果有两篇以上的论文符合条件，输出论文编号最小的那一个。
//如果第一个字段是finish，则结束输入。

#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, i, j, minLabel = 0, maxValue = 0;
    char command[10];
    cin >> N;
    int array[50002] = {0};
    minLabel = maxValue = 0;

    cin.get();
    cin >> command;
    while (true)
    {
        if (!strcmp(command, "add"))
        {
            cin >> i;
            cin >> j;
            cin.get();
            array[j]++;
            if (array[j] > maxValue)
            {
                maxValue = array[j];
                minLabel = j;
            }
            else if (array[j] == maxValue)
            {
                if (j < minLabel)
                    minLabel = j;
            }
        }

        else if(!strcmp(command, "query"))
            cout << minLabel << ' ' << maxValue <<'\n';

        else if (!strcmp(command, "finish"))
            break;
            
        cin >> command;
    }

    return 0;
}