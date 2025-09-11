; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.DATA
    x BYTE 12h
    y BYTE 14h
    z BYTE 5h
    w BYTE 10h
    FinalResult WORD ?

.CODE
main PROC
    movzx eax, x
    add   eax, y
    movzx ebx, z
    add   ebx, w
    sub   eax, ebx
    mov   edx, eax
    mov   FinalResult, dx
    exit
main ENDP
END main
