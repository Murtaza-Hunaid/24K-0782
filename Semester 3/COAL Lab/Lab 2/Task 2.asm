INCLUDE Irvine32.inc

.code
main PROC
    mov ebx, 20

    mov eax, 4C2h
    sub eax, ebx
    add eax, 72o
    add eax, 55d
    sub eax, 11101011b
    add eax, 180
    call WriteInt
    exit
main ENDP
END main
