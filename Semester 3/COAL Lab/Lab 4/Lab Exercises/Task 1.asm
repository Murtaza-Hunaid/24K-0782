; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.DATA
    num1 BYTE 25
    num2 WORD 1200h
    num3 DWORD ?

.CODE
main PROC
    mov al, num1
    mov ax, num2
    movzx eax, num1
    mov num3, eax
    movzx eax, num2
    mov num3, eax
    exit
main ENDP

END main
