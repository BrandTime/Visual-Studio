#include<iostream>
typedef int Elem;
using namespace std;

class Aqueue
{
    Elem *front,*rear;
    int size;
public:
    bool Creat(int maxsize);
    bool Clear();
    Elem GetValue();
    int GetSize();
    bool Enqueue(const Elem &it);
    bool Dequeue(const Elem &it);
};

int main(void)
{
    return ;
}
