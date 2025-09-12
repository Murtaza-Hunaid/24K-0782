; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
num DWORD 10

.code
main PROC
    mov eax, num
    inc eax
    inc eax
    inc eax
    dec eax
    dec eax
    mov num, eax
    call DumpRegs
    exit
main ENDP
END main
