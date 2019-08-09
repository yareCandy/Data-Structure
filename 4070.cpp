#include <iostream>
#include <cstring>
using namespace std;


void quick_sort(char a[][80], int left, int right)
{
    if (left >= right) return;
    int i = left;
    int j = right;
    char init[80];
    strcpy(init ,a[i]);
    //int tmp = left;
    while(i < j)
    {
        while(i < j && strcmp(a[j], init)<0) j--;
        if (i < j) {strcpy(a[i], a[j]); i++;}
        while(i < j && strcmp(a[i], init)>0) i++;
        if (i < j) {strcpy(a[j--], a[i]);j--;}
    }
    strcpy(a[i], init);
    quick_sort(a, left, i-1);
    quick_sort(a, i+1, right);
}

void read(char str[], char flag)
{
    char ch;
    cin >> ch;
    int i = 0;
    while (ch != '\n')
    {
        if (ch == flag)
        {
            ch = cin.get();
            continue;
        }
        str[i++] = ch;
        ch = cin.get();
    }
    str[i] = '\0';
}

int main()
{
    int i = 0;
    char ch, flag, str[80][80];
    cin >> ch; cin.get();//丢掉换行

    while(true)
    {
        cin >> flag;
        if (flag == '@')
            break;

        if (flag == ch)
            read(str[i], ch);
        else
        {
            str[i][0] = flag;
            read(1 + str[i], ch);
        }
        i++;
    }

    quick_sort(str, 0, i-1);
    for (int j = 0; j < i; j++)
    {
        cout << str[j];
        if (j != i - 1) cout << '\n';
    }

    return 0;
}