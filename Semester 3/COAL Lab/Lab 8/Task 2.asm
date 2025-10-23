; Murtaza Hunaid Terai    24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter 5 numbers:", 0
    msg2 BYTE "Reversed order: ", 0
    nums DWORD 5 DUP(?)

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

    mov edx, OFFSET msg2
    call WriteString
    mov ecx, 5
    mov esi, OFFSET nums
    add esi, 16         

print_loop:
    mov eax, [esi]
    call WriteDec
    mov al, ' '
    call WriteChar
    sub esi, 4
    loop print_loop
    call Crlf
    exit
main ENDP
END main
