//KMP.cpp
//KMP法寻找子链sub位置的算法
//利用失效函数等寻找最大子列

#include <iostream>
#include <cstring>
#include <string>
using namespace std;


template <class T>
int find(const T &string, const T &sub)
{
    int *p = new int[sub.size];
    int i, j;

    //生成失效函数
    p[0] = -1;
    for (int i = 1; i < sub.size; i++)
    {
        j = i - 1;
        while (j >= 0 && sub.data[p[j] + 1] != sub.data[i])
            j = p[j];
        if (j < 0) p[i] = -1;
        else p[i] = p[j] + 1;
    }

    //查找
    i = j = 0;
    while (i < string.size && j < sub.size)
    {
        if (sub.data[j] == string.data[i]) {i ++; j ++;}
        else if (j == 0) i ++;
        else j = p[j - 1] + 1;
    }
    delete []p;
    if (j == sub.size) return i - j + 1;
    else return -1;
}


int find (const char *n, const char *n2)//n2是需要查找的链， n是母链
{
    int i, j;
    int len1 = strlen(n);
    int len2 = strlen(n2);
    int *p = new int [len2];// 存放失效函数

    //寻找失效函数
    p[0] = -1;//第一个均是-1
    for (i = 1; i < len2; i++)
    {
        j = i - 1;
        while (j >= 0 && n2[p[j] + 1] != n2[i])
            j = p[j];
        if (j < 0) p[i] = -1;
        else p[i] = p[j] + 1;
    }

    //查找
    i = j = 0;
    while (i < len1 && j < len2)
    {
        if (n[i] == n2[j]) {i ++; j ++;}
        else if (j == 0) i++;
        else j = p[j - 1] + 1;
    }

    delete [] p;
    if (j == len2) return i - j;
    else return -1;
}


//寻找字符串中的最大回文子串
void longestPalindrom(const char *str)
{
    int i, j, start = 0, maxLength = 0;
    int size = strlen(str);
    bool **p = new bool *[strlen(str)];
    for (i = 0; i < size; i++)
    {
        p[i] = new bool [strlen(str)];
        for (j = 0; j < size; j++)
            p[i][j] = false;
    }


    for (i = 0; i < size; i++)
    {
        for (j = 0; j <= i; j++)
        {
            if (i - j < 2)
                p[i][j] = (str[i] == str[j]);
            else
                p[i][j] = (str[i] == str[j] && p[i-1][j+1]);
            if (p[i][j] && maxLength < i - j +1)
            {
                maxLength = i - j + 1;
                start = j;
            }
            cout << p[i][j] << " ";
        }
        cout << endl;
    }

    cout << maxLength << '\n';
    for (int k = start; k < maxLength + start; k++)
        cout << str[k];
    cout << endl;
}

void longest(const char *str);

int main()
{
    char  str[1000000];
    cin >> str;

    longest(str);
    return 0;
}


//Manacher法寻找最长回文串
void longest(const char *str)
 {
    char *s = new char[strlen(str) * 2 + 2];
    int size = strlen(s);

    for (int i=0;i<size;i++) //首先构造出新的字符串
    {
      if (i % 2 == 0)  s[i] = '#';
      else s[i] = str[i / 2];
    }

    int len = strlen(s);
    int *rd = new int [len];//用一个辅助数组来记录最大的回文串长度，注意这里记录的是新串的长度，原串的长度要减去1
    int tmp, pos = 0, mx = 0;
    int start = 0, maxLen = 0;

    for (int i = 1; i < len; i++)
    {
        tmp = rd[2 * pos - i] > (mx - i) ? (mx -i) : rd[pos * 2 - i];
        rd[i] = i < mx ? tmp : 1;
        while (i+rd[i] < len && i-rd[i]>0 && s[i + rd[i]] == s[i - rd[i]])//这里要注意数组越界的判断，源代码没有注意，release下没有报错
          rd[i]++;
      if (i + rd[i] > mx) //如果新计算的最右侧端点大于mx,则更新pos和mx
      {
        pos = i;
        mx = i + rd[i];
      }
      if (rd[i] - 1 > maxLen)
      {
        start = (i - rd[i]) / 2;
        maxLen = rd[i];
      }
    }
    cout <<  maxLen << endl;
    for (int k = start; k < start + maxLen; k++)
        cout << str[k];
    cout << endl;
  }
