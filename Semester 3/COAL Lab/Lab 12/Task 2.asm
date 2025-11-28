; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    str1 BYTE "PROGRAMMING", 0 
    target BYTE 'G'    ; Character to search for
    count DWORD 0 ; Count of occurrences

    msg1 BYTE "Character '", 0
    msg2 BYTE "' occurs ", 0
    msg3 BYTE " times", 0

.code
main PROC

    mov esi, OFFSET str1 ; ESI points to string

CountLoop:
    mov al, BYTE PTR [esi]  ; Load current character
    cmp al, 0   ; Check if end of string
    je DisplayResult    ; If null, then exit loop

    cmp al, target  ; Compare with target
    jne NextChar    ; If not equal, then skip
    inc count   

NextChar:
    inc esi ; Move to next character
    jmp CountLoop

DisplayResult:
    mov edx, OFFSET msg1
    call WriteString

    mov al, target
    call WriteChar

    mov edx, OFFSET msg2
    call WriteString

    mov eax, count
    call WriteDec

    mov edx, OFFSET msg3
    call WriteString
    call CrLf
    exit
main ENDP
END main
