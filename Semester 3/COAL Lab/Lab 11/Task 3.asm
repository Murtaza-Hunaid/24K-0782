; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    str1 BYTE "Murtaza",0
    str2 BYTE "Hunaid",0
    a BYTE "String 1 is greater than String 2",0
    b BYTE "String 1 is equal to String 2",0
    e BYTE "String 1 is less than String 2",0

.code
IsCompare PROC str1Addr, str2Addr
    mov esi, str1Addr
    mov edi, str2Addr
    
compare_loop:
    mov al, [esi]
    mov bl, [edi]
    cmp al, bl
    ja greater
    jb lesser
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
    ret
IsCompare ENDP

main PROC
    INVOKE IsCompare, OFFSET str1, OFFSET str2
    cmp eax, 1
    je greaterCase
    cmp eax, -1
    je lesserCase
    mov edx, OFFSET b
    jmp printmsg
    
greaterCase:
    mov edx, OFFSET a
    jmp printmsg
    
lesserCase:
    mov edx, OFFSET e
    
printmsg:
    call WriteString
    call Crlf
    exit
main ENDP
END main
