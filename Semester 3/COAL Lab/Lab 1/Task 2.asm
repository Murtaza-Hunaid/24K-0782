INCLUDE Irvine32.inc

.code
main PROC
    mov eax, 95
    sub eax, 31
    add eax, 240
    sub eax, 125
    call WriteInt
    exit
main ENDP
END main
