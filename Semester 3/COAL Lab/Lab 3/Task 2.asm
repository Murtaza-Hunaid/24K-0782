; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    message BYTE "Hello World", 0

.code
main PROC
    mov edx, OFFSET message
    CALL Writestring
    exit
main ENDP
END main
