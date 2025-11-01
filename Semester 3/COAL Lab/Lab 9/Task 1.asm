; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    array1 DWORD 5 DUP(?)
    array2 DWORD 5 DUP(?)
    count  DWORD 0
    msgA1  BYTE "Array 1 = ",0
    msgA2  BYTE "Array 2 = ",0
    msgOut BYTE "Matching elements = ",0

.code
main PROC
    mov edx, OFFSET msgA1
    call WriteString
    call Crlf
    mov ecx, LENGTHOF array1
    mov esi, OFFSET array1

input_array1:
    call ReadInt
    mov [esi], eax
    add esi, TYPE array1
    loop input_array1

    mov edx, OFFSET msgA2
    call WriteString
    call Crlf
    mov ecx, LENGTHOF array2
    mov esi, OFFSET array2

input_array2:
    call ReadInt
    mov [esi], eax
    add esi, TYPE array2
    loop input_array2

    mov ecx, LENGTHOF array1
    mov esi, OFFSET array1
    mov edi, OFFSET array2
    mov count, 0

compare_loop:
    mov eax, [esi]
    cmp eax, [edi]
    jne not_equal
    inc count

not_equal:
    add esi, TYPE array1
    add edi, TYPE array2
    loop compare_loop

    mov edx, OFFSET msgOut
    call WriteString
    mov eax, count
    call WriteDec
    call Crlf
    exit
main ENDP
END main
