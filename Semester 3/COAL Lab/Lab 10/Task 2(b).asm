; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    arr DWORD 20 DUP(?)
    msg1 BYTE "Enter 20 numbers= ",0
    msg2 BYTE "Minimum value= ",0
    msg3 BYTE "Maximum value= ",0

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    call Crlf

    mov ecx, LENGTHOF arr
    mov esi, OFFSET arr
input_loop:
    call ReadInt
    mov [esi], eax
    add esi, TYPE arr
    loop input_loop

    push OFFSET arr
    call MinMaxArray
    exit
main ENDP

MinMaxArray PROC
    push ebp
    mov ebp, esp
    mov esi, [ebp+8]
    mov eax, [esi]
    mov ebx, eax
    mov ecx, LENGTHOF arr
    dec ecx
    add esi, TYPE arr

find_loop:
    mov edx, [esi]
    cmp edx, eax
    jl new_min
    cmp edx, ebx
    jg new_max
    jmp next

new_min:
    mov eax, edx
    jmp next

new_max:
    mov ebx, edx

next:
    add esi, TYPE arr
    loop find_loop
    mov edx, OFFSET msg2
    call WriteString
    mov eax, eax
    call WriteInt
    call Crlf

    mov edx, OFFSET msg3
    call WriteString
    mov eax, ebx
    call WriteInt
    pop ebp
    ret 4
MinMaxArray ENDP

END main
