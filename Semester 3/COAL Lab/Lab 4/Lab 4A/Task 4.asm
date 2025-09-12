; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
items   DWORD 50
bought  DWORD 7
restock DWORD 15

.code
main PROC
    mov eax, items
    sub eax, bought
    add eax, restock
    mov items, eax
    call DumpRegs
    exit
main ENDP
END main
