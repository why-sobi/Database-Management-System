#include "class.h"

template <typename T>
void display(const Array<T> &arr)
{
    for (int i = 0; i < arr.getSize(); i++)
    {
        std::cout << arr[i] << ' ';
    }
}

int main()
{
    Array<int> arr;
    for (int i = 0; i < 10; i++)
        arr.add(i);
    display(arr);

    arr.pop();
    Array<int> arr2 = arr;
    display(arr2);
}