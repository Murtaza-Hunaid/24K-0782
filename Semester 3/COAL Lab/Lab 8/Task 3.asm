; Murtaza Hunaid Terai    24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter numbers: ",0
    msg2 BYTE "Largest number: ",0
    msg3 BYTE "Smallest number: ",0
    nums DWORD 5 DUP(?)
    largest DWORD ?
    smallest DWORD ?

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    call Crlf
    mov ecx, 5
    mov esi, OFFSET nums

read_loop:
    call ReadInt
    mov [esi], eax
    add esi, 4
    loop read_loop

    mov esi, OFFSET nums
    mov eax, [esi]
    mov largest, eax
    mov smallest, eax
    add esi, 4
    mov ecx, 4

find_loop:
    mov eax, [esi]
    cmp eax, largest
    jle check_min
    mov largest, eax

check_min:
    cmp eax, smallest
    jge next_num
    mov smallest, eax

next_num:
    add esi, 4
    loop find_loop

    mov edx, OFFSET msg2
    call WriteString
    mov eax, largest
    call WriteDec
    call Crlf

    mov edx, OFFSET msg3
    call WriteString
    mov eax, smallest
    call WriteDec
    call Crlf
    exit
main ENDP
END main
