; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    readings DWORD 10 DUP(?)
    sum DWORD 0
    avg DWORD 0
    above DWORD 0
    below DWORD 0
    scaled DWORD 0
    rotated BYTE 0
    msg1 BYTE "Enter reading: ",0
    msg2 BYTE "Sum of readings= ",0
    msg3 BYTE "Average reading= ",0
    msg4 BYTE "Readings above average= ",0
    msg5 BYTE "Readings below average= ",0
    msg6 BYTE "Scaled average (SHL)= ",0
    msg7 BYTE "Encrypted result (ROR)= ",0

.code
main PROC
    mov ecx, LENGTHOF readings
    mov esi, OFFSET readings
    mov edx, OFFSET msg1
    call WriteString

inputLoop:
    call ReadInt
    mov [esi], eax
    add esi, TYPE readings
    loop inputLoop
    call CalcSumAndAvg
    mov ecx, LENGTHOF readings
    mov esi, OFFSET readings
    mov above, 0
    mov below, 0

countLoop:
    mov eax, [esi]
    cmp eax, avg
    jg aboveAvg
    jl belowAvg
    jmp next

aboveAvg:
    inc above
    jmp next

belowAvg:
    inc below

next:
    add esi, TYPE readings
    loop countLoop

    mov eax, avg
    shl eax, 1
    mov scaled, eax
    mov bl, BYTE PTR scaled
    ror bl, 1
    mov rotated, bl
    mov edx, OFFSET msg2
    call WriteString
    mov eax, sum
    call WriteDec
    call Crlf

    mov edx, OFFSET msg3
    call WriteString
    mov eax, avg
    call WriteDec
    call Crlf

    mov edx, OFFSET msg4
    call WriteString
    mov eax, above
    call WriteDec
    call Crlf

    mov edx, OFFSET msg5
    call WriteString
    mov eax, below
    call WriteDec
    call Crlf

    mov edx, OFFSET msg6
    call WriteString
    mov eax, scaled
    call WriteDec
    call Crlf

    mov edx, OFFSET msg7
    call WriteString
    movzx eax, rotated
    call WriteBinB
    call Crlf
    exit
main ENDP

CalcSumAndAvg PROC
    mov ecx, LENGTHOF readings
    mov esi, OFFSET readings
    mov eax, 0

sumLoop:
    add eax, [esi]
    add esi, TYPE readings
    loop sumLoop

    mov sum, eax
    mov ebx, LENGTHOF readings
    xor edx, edx
    div ebx
    mov avg, eax
    ret
CalcSumAndAvg ENDP
END main
