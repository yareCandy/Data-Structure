//word.cpp
//单词以单链表的形式存储，寻找两个单词共同后缀的地址
//思路：将两个单词的末端对其,即用两个指针，分别指向头节点，让长的指针先走
//遍历两次，第一次寻找长度，第二次寻找共同后缀的地址

#include <iostream>
#include <cstring>
using namespace std;

struct node
{
    char s;//保存当前的字母
    node *next;
};

const node *find(const node *s1, const node *s2)
{
    int len1, len2;//分别保存s1，s2的长度
    const node *p =  s1, *q = s2;

    //寻找长度
    for (len1 = 0; p != NULL; len1 ++)
        p = p -> next;
    for (len2 = 0; q != NULL; len2 ++)
        q = q -> next;

    //查找共同位置
    p = s1, q = s2;
    while (p != q)
    {
        if (len1 > len2) {p = p -> next; len1 --;}
        else if (len1 == len2) {p = p -> next; q = q -> next;}
        else {q = q -> next; len2 --;}
    }

    if (q == NULL) return NULL;
    else return p;
}
