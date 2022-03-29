#include <stdio.h>
#include <stdlib.h>

int main()
{
    #define array_size 8
    short int array[array_size] = {
        0b10000000, 0b01000000,
        0b00100000, 0b00010000,
        0b00001000, 0b00000100,
        0b00000010, 0b00000001
    };

    int sum = 0;

    for (size_t i = 0; i < array_size; i++)
    {
        int elem = array[i];
        if (elem & 0b01000000) {
            elem >>=1;
        }
        sum += elem;
    }

    printf("Сумма элементов полученного масива: %d\n", sum);
}