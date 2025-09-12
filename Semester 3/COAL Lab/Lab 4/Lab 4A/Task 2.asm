; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
balance DWORD 5000
deposit DWORD 1200
withdraw DWORD 2000

.code
main PROC
    mov eax, balance
    add eax, deposit
    sub eax, withdraw
    mov balance, eax
    call DumpRegs
    exit
main ENDP
END main
