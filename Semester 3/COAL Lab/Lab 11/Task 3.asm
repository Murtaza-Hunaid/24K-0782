; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    str1 BYTE "Murtaza", 0
    str2 BYTE "Hunaid", 0
    a BYTE "str 1 is greater than str 2", 0
    b BYTE "str 1 is equal to str 2", 0
    e BYTE "str 1 is less than str 2", 0

.code
main PROC
    push OFFSET str2
    push OFFSET str1
    call IsCompare

    jbe else1
    mov edx, OFFSET a
    jmp printmsg

else1:
    je equalCase
    mov edx, OFFSET e
    jmp printmsg

equalCase:
    mov edx, OFFSET b

printmsg:
    call WriteString
    exit
main ENDP

IsCompare PROC
    push ebp
    mov  ebp, esp
    mov esi, [ebp+8]
    mov edi, [ebp+12]

compare_loop:
    mov al, [esi]
    mov bl, [edi]
    cmp al, bl
    ja  greater
    jb  lesser

    cmp al, 0
    je equalEnd

    inc esi
    inc edi
    jmp compare_loop

greater:
    mov eax, 1
    jmp done

lesser:
    mov eax, -1
    jmp done

equalEnd:
    mov eax, 0

done:
    pop ebp
    ret 8
IsCompare ENDP
END main
