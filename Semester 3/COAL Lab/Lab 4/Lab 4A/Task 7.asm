; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

PI = 3

.data
result DWORD ?

.code
main PROC
    mov eax, PI
    mov ebx, 4
    imul eax, ebx
    mov result, eax
    call DumpRegs
    exit
main ENDP
END main
