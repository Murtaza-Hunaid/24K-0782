; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data

.code
main PROC
    mov ax, 10
    mov bx, 20
    xchg ax, bx
    call DumpRegs
    exit
main ENDP
END main
