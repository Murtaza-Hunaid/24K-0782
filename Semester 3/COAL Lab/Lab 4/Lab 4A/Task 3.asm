; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
day_temp    DWORD 30
night_temp  DWORD 18
diff    DWORD ?

.code
main PROC
    mov eax, day_temp
    sub eax, night_temp
    mov diff, eax
    mov eax, night_temp
    add eax, 2
    mov night_temp, eax
    call DumpRegs
    exit
main ENDP
END main
