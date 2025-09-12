; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
vala DWORD 10h
valb DWORD 12h
valc DWORD 20h
vald DWORD 25h

.code
main PROC
    mov eax, vala
    add eax, valb
    mov ebx, eax
    mov edx, vala
    sub edx, valb
    sub ebx, edx
    add ebx, valc
    add ebx, vald
    call DumpRegs
    exit
main ENDP
END main
