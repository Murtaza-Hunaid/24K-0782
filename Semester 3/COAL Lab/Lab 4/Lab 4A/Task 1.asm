; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
mark1 DWORD 45
mark2 DWORD 35
total DWORD ?
diff  DWORD ?

.code
main PROC
    mov eax, mark1
    add eax, mark2
    mov total, eax
    mov eax, mark1
    sub eax, mark2
    mov diff, eax
    call DumpRegs
    exit
main ENDP
END main
