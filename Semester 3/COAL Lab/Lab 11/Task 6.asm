; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    target BYTE "AAEBDCFBBC",0
    freqTable DWORD 256 DUP(0)
    msg BYTE " = ",0

.code

PrintFreq PROC table
    mov esi, table
    mov ecx, 256

L1:
    mov eax, [esi]
    cmp eax, 0
    jz L2
    mov eax, 256
    sub eax, ecx
    call WriteHex
    mov edx, OFFSET msg
    call WriteString
    mov eax, [esi]
    call WriteInt
    call Crlf

L2:
    add esi, 4
    loop L1
    ret
PrintFreq ENDP

Get_frequencies PROC strAddr, tableAddr
    mov esi, strAddr

L1:
    mov al, [esi]
    cmp al, 0
    je finish
    movzx ebx, al
    shl ebx, 2
    add ebx, tableAddr
    inc DWORD PTR [ebx]
    inc esi
    jmp L1

finish:
    INVOKE PrintFreq, tableAddr
    ret
Get_frequencies ENDP

main PROC
    INVOKE Get_frequencies, OFFSET target, OFFSET freqTable
    exit
main ENDP

END main
