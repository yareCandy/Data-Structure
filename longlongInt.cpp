//longlongInt.cpp
#include <iostream>
#include <cstring>
using namespace std;

class longLongInt
{
    friend longLongInt operator+(const longLongInt &, const longLongInt &);
    friend ostream &operator<<(ostream &, const longLongInt &);
    friend longLongInt operator-(const longLongInt &, const longLongInt &);

    private:
        char sign;
        char *num;
    public:
        longLongInt(const char *n = "");
        longLongInt(const longLongInt &);
        longLongInt &operator=(const longLongInt &);
        ~longLongInt(){ delete num;}
};

char *add(const char *n1, const char *n2);
char *sub(const char *n1, const char *n2);
bool great(const char *n1, const char *n2);

//构造函数
longLongInt::longLongInt(const char *n)
{
    const char *tmp; //保存参数绝对值
    //处理第一位
    switch(n[0])
    {
        case '-': sign = '-'; tmp = n + 1; break;
        case '+': sign = '+';  tmp = n + 1; break;//跳过符号位
        default:  sign = '+'; tmp = n;
    }

    if (strcmp (tmp, "0") == 0) tmp = ""; //n == 0时
    int len = strlen (tmp);

    num = new char[len + 1];
    for (int i = 0; i < len; i++) //反向存储数据
        num[len - i - 1] = tmp [i];

    num [len] = '\0';
}

longLongInt::longLongInt(const longLongInt &other)
{
    sign = other.sign;
    num = new char[strlen(other.num) + 1];
    strcpy (num, other.num);
}

longLongInt &longLongInt::operator=(const longLongInt &n1)
{
    if (this == &n1) return *this;

    if (num != NULL) delete num;
    num = new char[strlen(n1.num) + 1];
    strcpy (num, n1.num);

    return *this;
}

longLongInt operator+(const longLongInt &n1, const longLongInt &n2)
{
    longLongInt result;
    if (n1.sign == n2.sign)
    {
        result.sign = n1.sign;
        result.num = add(n1.num, n2.num);
    }
    else
    {
        if (great(n1.num, n2.num))
        {
            result.num = sub(n1.num, n2.num);
            result.sign = n1.sign;
        }
        else
        {
            result.num = sub(n2.num, n1.num);
            result.sign = n2.sign;
        }
    }

    return result;
}


longLongInt operator-(const longLongInt &n1, const longLongInt &n2)
{
    longLongInt tmp = n2;
    if (tmp.sign == '+') tmp.sign = '-';
    else tmp.sign = '+';

    return n1 + tmp;
}

ostream &operator<<(ostream &os, const longLongInt &n)
{
    if (strlen(n.num) == 0) os << 0;
    else
    {
        if (n.sign == '+')
            for (int i = strlen(n.num)- 1; i >= 0; i--)
                os << n.num[i];
        else
        {
            os << n.sign;
            for (int i = strlen(n.num)- 1; i >= 0; i--)
             os << n.num[i];
        }
    }

    return os;
}

char *add(const char *n1, const char *n2)
{
    int i, result, carry = 0;//carry进位
    int len1 = strlen(n1), len2 = strlen(n2);
    int maxSize = (len1 > len2) ? len1 : len2;
    int minSize = (len1 > len2) ? len2 : len1;
    char *sum = new char [maxSize + 2];

    for (i  = 0; i < minSize; i++)
    {
        result = n1[i] - '0' + n2[i] - '0' + carry;
        sum[i] = result % 10 + '0';
        carry = result / 10;
    }

    while(i < len2)
    {
        result = n2[i] + carry;
        sum[i++] = result % 10 + '0';
        carry = result / 10;
    }

    while(i < len1)
    {
        result = n1[i] + carry;
        sum[i++] = result % 10 + '0';
        carry = result / 10;
    }

    //处理最后的进位
    //如果最后有进位，sum的大小刚好，不进位则多出来一位
    if (carry != 0) sum[i++] = carry;
    sum[i] = '\0';

    return sum;
}

char *sub(const char *n1, const char *n2)
{
    //两减数相等，结果位0
    if (strcmp(n1, n2) == 0) return "";

    int i, minus = 0, len1 = strlen(n1);//借位
    char *sum = new char[strlen(n1) + 1];

    for (i = 0; n1[i] != '\0'; i++)
    {
        if (n1[i] - minus < n2[i])
        {
            sum[i] = 10 + n1[i] - minus - n2[i] + '0';
            minus = 1;
        }
        else
        {
            sum[i] = n1[i] - minus - n2[i] + '0';
            minus = 0;
        }
    }

    while(i < len1)
    {
        if (n1[i] < minus)
        {
            sum[i] = 10 + n1[i] - minus;
            minus = 1;
        }
        else
        {
            sum[i] = n1[i] - minus;
            minus = 0;
            i++;
        }
    }
    sum[i] = '\0';
    //处理末尾的‘0’
    //如：32423 - 32421在内存中32423 - 12423 = 20000
    for (i = strlen(sum); i > 0; i--)
        if (sum[i - 1] != '0')
            sum[i] = '\0';

    return sum;
}

bool great(const char *n1, const char *n2)
{
    int len1 = strlen(n1), len2 = strlen(n2);

    if (len1 > len2) return true;
    else if (len1 < len2) return false;
    else
    {
        for (int i = len1 - 1; i >= 0; i--)
        {
            if (n1[i] > n2[i]) return true;
            if (n1[i] < n2[i]) return false;
        }
    }

    return false;

}

int main()
{
    longLongInt n1("923");
    longLongInt n2("-921");
    //longLongInt n3("+63");


    cout << n1 << '+' << n2 << "= " << n1 + n2 << endl;

    return 0;
}
