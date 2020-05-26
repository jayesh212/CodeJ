#ifndef __$__STRING_HPP
#define __$__STRING_HPP 7
#include <string.h>
#include <iostream>
char *intToString(int num);
using namespace std;
class JString
{
private:
    char *ptr;
    int size;
    void append(const char *string)
    {
        int newStringSize, i, j;
        newStringSize = strlen(string);
        newStringSize--;
        char *stringCopy;
        stringCopy = new char[this->size];
        for (i = 0; this->ptr[i] != '\0'; i++)
        {
            stringCopy[i] = this->ptr[i];
        }
        stringCopy[i] = '\0';
        this->size += newStringSize;
        this->ptr = new char[this->size];
        for (i = 0; stringCopy[i] != '\0'; i++)
        {
            this->ptr[i] = stringCopy[i];
        }
        for (j = 0; string[j] != '\0'; j++, i++)
        {
            this->ptr[i] = string[j];
        }
        this->ptr[i] = '\0';
        delete[] stringCopy;
    }
    void setString(char *string)
    {
        int i;
        if (this->ptr != NULL)
            delete[] this->ptr;
        this->size = strlen(string);
        this->ptr = new char[this->size];
        for (i = 0; string[i] != '\0'; i++)
        {
            this->ptr[i] = string[i];
        }
        this->ptr[i] = '\0';
    }

public:
    JString()
    {
        this->ptr = new char;
        this->size = 1;
        this->ptr[0] = '\0';
    }
    JString(const char *string)
    {
        int length = strlen(string);
        this->ptr = new char[length];
        strcpy(this->ptr, string);
        this->size = length;
    }
    JString(char c)
    {
        this->ptr = new char[2];
        this->ptr[0] = c;
        this->ptr[1] = '\0';
        this->size = 2;
    }
    JString(JString &other)
    {
        this->ptr = new char[other.size];
        this->size = other.size;
        strcpy(this->ptr, other.ptr);
    }
    JString(int num)
    {
        char *string;
        string = intToString(num);
        this->size = strlen(string);
        this->ptr = string;
    }
    void operator=(JString &other)
    {
        release();
        this->size = other.size;
        this->ptr = new char[this->size];
        strcpy(this->ptr, other.ptr);
    }
    void operator=(const char *str)
    {
        release();
        this->size = strlen(str);
        this->ptr = new char[this->size];
        strcpy(this->ptr, str);
    }
    void operator=(int num)
    {
        release();
        char *string;
        string = intToString(num);
        this->size = strlen(string);
        this->ptr = string;
    }
    void operator=(char c)
    {
        release();
        this->size = 2;
        this->ptr = new char[2];
        this->ptr[0] = c;
        this->ptr[1] = '\0';
    }
    void operator+=(const char *string)
    {
        append(string);
        this->size = strlen(this->ptr);
    }
    void operator+=(JString &other)
    {
        append(other.ptr);
        this->size = strlen(this->ptr);
    }
    void operator+=(int num)
    {
        char *string = intToString(num);
        append(string);
        this->size = strlen(this->ptr);
    }
    void operator+=(char c)
    {
        char string[2];
        string[0] = c;
        string[1] = '\0';
        append(string);
        this->size++;
    }
    void operator<<(int num)
    {
        char *string = intToString(num);
        append(string);
        this->size = strlen(this->ptr);
    }
    void operator<<(const char *string)
    {
        append(string);
        this->size = strlen(this->ptr);
    }
    void operator<<(char c)
    {
        char *string;
        string = new char[2];
        string[0] = c;
        string[1] = '\0';
        append(string);
        this->size = strlen(this->ptr);
    }
    int getSize()
    {
        return this->size;
    }
    int operator[](int index)
    {
        if (index < 0 || index >= size)
            return 0;
        return this->ptr[index];
    }
    void getString(char *string)
    {
        if (string == NULL)
            return;
        strcpy(string, this->ptr);
    }
    void getString(JString &str)
    {
        str = this->ptr;
    }
    void pop()
    {
        this->size--;
        this->ptr[size]='\0';
    }
    void release()
    {
        if (this->ptr)
        {
            delete[] this->ptr;
        }
    }
    ~JString()
    {
        release();
    }
    friend std::ostream &operator<<(std::ostream &r, JString &t);
};
std::ostream &operator<<(std::ostream &r, JString &t)
{
    if (t.ptr == NULL)
        return r;
    std::cout << t.ptr;
    return r;
}
char *intToString(int num)
{
    int res, i, j, dc, div;
    char *string;
    string = new char[10];
    i = num;
    dc = 1;
    while (i > 9)
    {
        i /= 10;
        dc++;
    }
    res = 1;
    i = 1;
    while (i < dc)
    {
        res = res * 10;
        i++;
    }
    j = 0;
    div = res;
    i = 0;
    while (div > 0)
    {
        j = (num / div) % 10;
        string[i] = 48 + j;
        div /= 10;
        i++;
    }
    string[i] = '\0';
    return string;
}

#endif