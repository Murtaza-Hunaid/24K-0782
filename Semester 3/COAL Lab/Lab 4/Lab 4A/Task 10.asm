; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
A DWORD 0FF10h
B DWORD 0E10Bh

.code
main PROC
    mov eax, A
    mov ebx, B
    xchg eax, ebx
    mov A, eax
    mov B, ebx
    call DumpRegs
    exit
main ENDP
END main
