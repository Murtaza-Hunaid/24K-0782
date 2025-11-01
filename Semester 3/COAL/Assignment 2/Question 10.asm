; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    initial_val DWORD 2

.code
main PROC
    mov eax, initial_val
    mov ebx, eax
    shl eax, 4
    mov ecx, ebx
    shl ecx, 3
    add eax, ecx
    mov ecx, ebx
    shl ecx, 1
    add eax, ecx
    call WriteInt
    call Crlf
    exit
main ENDP
END main
