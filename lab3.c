#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	asm(".intel_syntax noprefix\n\t");

	int array_size;
	asm(
		"mov	edi, 0\n\t"
		"call	time\n\t"
		"mov	edi, eax\n\t"
		"call	srand\n\t"
		"call 	rand\n\t"
		"and 	eax, 0x1F\n\t"
		"add	eax, 5\n\t"
		: "=r" (array_size)
		:
		:
	);
	/*
	srand(time(0));
	array_size = rand() % 32 + 5;
	*/

	printf("Выбранный размер массива: %d\n", array_size);

	int* array;
	asm(
		"mov	rdi, rax\n\t"
		"call	malloc\n\t"
		: "=r" (array)
		: "r" (array_size)
		:
	);
	/* array = (int*) malloc(array_size); */

	int half_array_size;

	asm(
		"shr eax, 1"
		: "=a" (half_array_size)
		: "a" (array_size), "b" (array)
		: 
	);
	/* half_array_size = array_size / 2; */

	asm(
		"mov edx, 0\n\t"  				// int i
		"jmp is_end_of_array\n\t"
		"loop:\n\t"
		"mov [rbx + rdx * 4], edx\n\t"  // array[i] = i;
		"mov esi, eax\n\t"
		"sub esi, 1\n\t"
		"sub esi, edx\n\t"  			// array_size - 1 - i
		"mov [rbx + rsi * 4], edx\n\t"  // array[array_size - 1 - i] = i;
		"add edx, 1\n\t"  				// ++i
		"is_end_of_array:\n\t"
		"cmp edx, ecx\n\t"  			// i < half_array_size
		"jl loop\n\t"
		:
		: "a" (array_size), "b" (array), "c" (half_array_size)
		:
	);

	/*
	for (int i = 0; i < half_array_size; ++i)
	{
		array[i] = i;
		array[array_size - 1 - i] = i;
	}
	*/

	asm(
		"and	eax, 1\n\t" 
		"test	eax, eax\n\t"  			// array_size % 2 != 0
		"je when_odd_array_size\n\t"
		"mov [rbx + rcx * 4], ecx\n\t"  // array[half_array_size] = half_array_size;
		"when_odd_array_size:\n\t"
		:
		: "a" (array_size), "b" (array), "c" (half_array_size)
		:
	);

	/*
	if (array_size % 2 != 0)
		array[half_array_size] = half_array_size;
	*/

	printf("Состояние массива после обработки:");
	for (int i = 0; i < array_size; ++i)
		printf("%d ", array[i]);
	printf("\n");

	free(array);

	return 0;
}