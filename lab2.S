DEFAULT REL

section .rodata
Hello: db "Hello world",10
len_Hello: equ $-Hello

section .text
global _start

   _start:
        push    rbp
        mov     rbp, rsp
        mov     dword [rbp - 4], 0
        mov     dword [rbp - 52], 1
        mov     dword [rbp - 56], 0
.LBB0_1:
        cmp     dword [rbp - 56], 10
        jge     .LBB0_6
        movsxd  rax, dword [rbp - 56]
        mov     eax, dword [rbp + 4*rax - 48]
        and     eax, dword [rbp - 52]
        cmp     eax, 0
        je      .LBB0_4
        movsxd  rax, dword [rbp - 56]
        mov     ecx, dword [rbp + 4*rax - 48]
        sar     ecx, 1
        movsxd  rax, dword [rbp - 56]
        mov     dword [rbp + 4*rax - 48], ecx
.LBB0_4:
        xor rax, rax
	xor rdi, rdi
        mov rax, 1
	mov rdi, 1
	mov ebx, dword [rbp - 56]
	xor rsi, rsi
	mov esi, dword [rbp + 4*rbx - 48]
	mov rdx, 4
	syscall
        jmp     .LBB0_5
.LBB0_5:
        mov     eax, dword [rbp - 56]
        add     eax, 1
        mov     dword [rbp - 56], eax
        jmp     .LBB0_1
.LBB0_6:

        mov eax, 60
        xor edi, edi
        syscall
