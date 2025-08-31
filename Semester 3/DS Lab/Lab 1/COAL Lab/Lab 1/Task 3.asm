INCLUDE Irvine32.inc

.code
main PROC
    mov eax, 101110b
    add eax, 50Ah
    add eax, 67d
    add eax, 1010001b
    add eax, 0Fh
    call WriteInt
    exit
main ENDP
END main
