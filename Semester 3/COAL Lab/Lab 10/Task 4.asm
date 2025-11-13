; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter a number: ",0
    msg2 BYTE "Factorial= ",0

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    push eax
    call Fact
    mov edx, OFFSET msg2
    call WriteString
    call WriteInt
    call Crlf
    exit
main ENDP

Fact PROC
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    cmp eax, 1
    jg recurse
    mov eax, 1
    jmp done

recurse:
    dec eax
    push eax
    call Fact
    mov ebx, [ebp+8]
    imul eax, ebx

done:
    pop ebp
    ret 4
Fact ENDP

END main
