; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

COUNT = 5
LIMIT EQU 10

.DATA
    Result WORD ?

.CODE
main PROC
    mov ax, COUNT
    add ax, LIMIT
    inc ax
    mov Result, ax
    exit
main ENDP
END main
