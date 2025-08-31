INCLUDE Irvine32.inc

.code
main PROC
    mov eax, 111b
    sub eax, 12
    add eax, 1F3h
    sub eax, 745o
    call WriteInt
    exit
main ENDP
END main
