; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

SecondsInDay = 24 * 60 * 60

.data
seconds DWORD SecondsInDay

.code
main PROC
    mov eax, seconds
    call DumpRegs
    exit
main ENDP
END main
