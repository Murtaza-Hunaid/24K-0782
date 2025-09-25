; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    array1  WORD 45, 32, 71, 44, 92
    array2  WORD 32, 44, 45, 71, 92

.code
main PROC
    mov ecx, LENGTHOF array2
    mov esi, OFFSET array2

print_loop:
    movzx eax, WORD PTR [esi]
    call WriteDec
    mov al, ' '
    call WriteChar
    add esi, TYPE array2
    loop print_loop
    call Crlf
    exit
main ENDP
END main
