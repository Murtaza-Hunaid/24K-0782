INCLUDE Irvine32.inc

.code
main PROC
    mov ebx, 20
    mov ecx, 30

    mov edx, ecx    ; Saving original ecx to edx
    mov ecx, 101011010110b
    add ecx, 3Ah
    sub ecx, 64o
    add ecx, ebx
    sub ecx, edx    ; Substracting original ecx(edx) from new ecx
    add ecx, 5
    call WriteInt
    exit
main ENDP
END main
