; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter first number: ",0
    msg2 BYTE "Enter second number: ",0
    msg3 BYTE "GCD = ",0
    msg4 BYTE "ESP = ",0

.code
main PROC
    call TakeInput
    exit
main ENDP

TakeInput PROC
    push ebp
    mov ebp, esp
    mov edx, OFFSET msg4
    call WriteString
    mov eax, esp
    call WriteHex
    call Crlf

    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    push eax

    mov edx, OFFSET msg2
    call WriteString
    call ReadInt
    push eax
    call GCD
    pop ebp
    ret
TakeInput ENDP

GCD PROC
    push ebp
    mov ebp, esp
    mov edx, OFFSET msg4
    call WriteString
    mov eax, esp
    call WriteHex
    call Crlf

    mov eax, [ebp+12]
    mov ebx, [ebp+8]

GCDLoop:
    cmp ebx, 0
    je Done
    mov edx, 0
    div ebx
    mov eax, ebx
    mov ebx, edx
    jmp GCDLoop

Done:
    push eax
    call Display
    pop eax
    pop ebp
    ret 8
GCD ENDP

Display PROC
    push ebp
    mov ebp, esp
    mov edx, OFFSET msg4
    call WriteString
    mov eax, esp
    call WriteHex
    call Crlf

    mov edx, OFFSET msg3
    call WriteString
    mov eax, [ebp+8]
    call WriteInt
    call Crlf

    pop ebp
    ret 4
Display ENDP

END main
