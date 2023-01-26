section .text
    global _start
    
_start:
    mov eax, [num1]
    sub eax, '0'
    mov ebx, [num2]
    sub ebx, '0'
    sub eax, ebx
    add eax, '0'
    
    mov [sum], eax
    
    mov ecx, msg
    mov edx, msglen
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    mov ecx, sum
    mov edx, 1
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    mov eax, 1
    int 0x80

section .data
    num1 db '9'
    num2 db '3'
    msg db 'The difference is: '
    msglen equ $ - msg
    
segment .bss
    sum resb 1
    