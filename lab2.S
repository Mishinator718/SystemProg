.data

print_n:
.string "\n"

print_format:
.string "%d "

print_summ:
.string "%d\n"


arr:
        .long 1, 2, 3, 64, 65, 126, 7, 8
arr_end:


.text
.globl main
.type main, @function

main:
	movl $arr, %ebx  /* в ebx, кладем массив */
	movl $0, %ecx /* в %ecx значение суммы */
	movl (%ebx), %eax
jmp bound 

start:
        xor $64, %eax /*проверка на 7 бит */
        and $64, %eax
        cmpl $64, %eax
        je next_element 

	movl (%ebx), %eax /* в %eax помещаем первый элемент массива  */
        shr $1, %eax  
        movl %eax, (%ebx) /* в %ebx помещаем обнолвенное значение %eax */

next_element:
	addl (%ebx), %ecx /* увеличиваем значение суммы */
	addl $4, %ebx /* переходим к адресу след эл-та массива; */
	movl (%ebx), %eax

bound:
        cmpl $arr_end, %ebx 
        jne start 

print_sum:
        push %ecx 
        push $print_summ 
        call printf 
        addl $8, %esp /* очищаем регистр, который отвечает за стек */

movl $arr, %ebx  /* в ebx массив */
print_mass:
        push (%ebx)  
        push $print_format 
        call printf  
        addl $8, %esp /* очищаем регистр, который отвечает за стек */

        addl $4, %ebx /* переходим к адресу следующего элемента массива */
        cmpl $arr_end, %ebx 
        jne print_mass 


print:
        push $print_n 
        call printf 
        addl $4, %esp /* очищаем регистр, который отвечает за стек */
        ret 
