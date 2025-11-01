; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    array SDWORD 5, -3, 7, 0, -2
    count SDWORD 5
    sum SDWORD 0
    i SDWORD 0

.code
main PROC
    mov sum, 0
    mov i, 0

while_loop:
    mov eax, i
    cmp eax, count
    jge end_while

    mov esi, OFFSET array
    mov eax, i
    imul eax, 4
    add esi, eax
    mov eax, [esi]
    cmp eax, 0
    jle else_part

    add sum, eax
    jmp next_iter

else_part:
    sub sum, 1

next_iter:
    inc i
    jmp while_loop

end_while:
    mov eax, sum
    call WriteInt
    exit
main ENDP
END main
