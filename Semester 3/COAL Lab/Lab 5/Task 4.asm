; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    arrayB  BYTE 25, 45, 65
    arrayW  WORD 155, 185, 225
    arrayD  DWORD 645, 690, 735
    SUM1    DWORD ?
    SUM2    DWORD ?
    SUM3    DWORD ?

.code
main PROC
    movzx eax, arrayB[0]
    add ax, arrayW[0]
    add eax, arrayD[0]
    mov SUM1, eax
    movzx eax, arrayB[1]
    add ax, arrayW[2]
    add eax, arrayD[4]
    mov SUM2, eax
    movzx eax, arrayB[2]
    add ax, arrayW[4]
    add eax, arrayD[8]
    mov SUM3, eax
    mov eax, SUM1
    call WriteDec
    call Crlf
    mov eax, SUM2
    call WriteDec
    call Crlf
    mov eax, SUM3
    call WriteDec
    call Crlf
    exit
main ENDP
END main
