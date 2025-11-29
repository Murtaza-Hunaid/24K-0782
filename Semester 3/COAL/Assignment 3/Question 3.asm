; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    str1 BYTE "###FAST", 0

.code

Str_trim_leading PROC, pString:PTR BYTE, charToTrim:BYTE
    mov esi, pString
    mov edi, esi
    mov bl, charToTrim

SkipLeading:
    mov al, [esi]
    cmp al, 0
    je EndString
    cmp al, bl
    jne CopyRest
    inc esi
    jmp SkipLeading

CopyRest:
    mov al, [esi]
    mov [edi], al
    cmp al, 0
    je Done
    inc esi
    inc edi
    jmp CopyRest

EndString:
    mov BYTE PTR [edi], 0

Done:
    ret
Str_trim_leading ENDP

main PROC
    INVOKE Str_trim_leading, ADDR str1, '#'
    mov edx, OFFSET str1
    call WriteString
    call Crlf 
    exit
main ENDP
END main
