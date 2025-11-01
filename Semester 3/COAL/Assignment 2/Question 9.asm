; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    array WORD 10,60,20,33,72,89,45,65,72,18
    sample WORD 50
    arraySize WORD LENGTHOF array
    index WORD 0
    sum WORD 0

.code
main PROC
while_loop:
    mov AX, index
    cmp AX, arraySize
    jge end_while

    movzx ESI, AX
    mov bx, array[esi*2]
    cmp bx, sample
    jge skip_add
    add sum, bx

skip_add:
    inc index
    jmp while_loop

end_while:
    movzx EAX, sum
    call WriteDec
    exit
main ENDP
END main
