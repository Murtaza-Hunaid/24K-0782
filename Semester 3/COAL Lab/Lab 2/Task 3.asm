INCLUDE Irvine32.inc

.code
main PROC
    mov eax, 10

    mov ebx, 6F1h
    sub ebx, eax
    add ebx, 92d
    add ebx, 47o
    sub ebx, 11011001b
    add ebx, 6Ch
    call WriteInt
    exit
main ENDP
END main
