; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

MAX = 100
MIN EQU 10

.DATA
    var1 DWORD MAX
    var2 DWORD MIN
    sum  DWORD ?

.CODE
main PROC
    mov eax, var1
    add eax, var2
    mov sum, eax
    call WriteInt
    exit
main ENDP
END main
