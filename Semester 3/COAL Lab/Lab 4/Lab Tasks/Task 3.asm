; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.DATA
    num1 WORD 1234h
    num2 WORD 5678h

.CODE
main PROC
    mov ax, num1
    mov bx, num2
    xchg ax, bx
    mov num1, ax
    mov num2, bx
    exit
main ENDP
END main
