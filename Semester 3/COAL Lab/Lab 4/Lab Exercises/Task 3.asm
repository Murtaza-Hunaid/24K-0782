; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.DATA
    valA SBYTE -15
    valB BYTE 25
    valC WORD ?

.CODE
main PROC
    movsx ax, valA
    add   ax, valB
    sub   ax, 5
    mov   valC, ax
    exit
main ENDP
END main
