INCLUDE Irvine32.inc

.code
main PROC
    mov eax, 10
    mov ebx, 20
    mov ecx, 30

    mov edx, eax
    add edx, 3
    add edx, ebx
    sub edx, ecx
    add edx, 12h
    sub edx, 45o
    add edx, 89d
    call WriteInt
    exit
main ENDP
END main
