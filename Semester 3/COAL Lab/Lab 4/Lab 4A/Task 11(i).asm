; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
val2 WORD 8000h

msg1 BYTE "After incrementing val2:",0

.code
main PROC
    inc val2
    call DumpRegs
    exit
main ENDP
END main
