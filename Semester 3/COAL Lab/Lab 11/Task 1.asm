; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    Str1 BYTE "127&j~3#^&*#*#45^", 0
    msg1 BYTE "Found at ", 0
    msg2 BYTE "Not found", 0

.code
main PROC
    mov edi, OFFSET Str1
    mov al, '#'
    mov ecx, LENGTHOF Str1
    cld
    repne scasb
    jnz not_found

    sub edi, OFFSET Str1
    dec edi
    mov edx, OFFSET msg1
    call WriteString
    mov eax, edi
    call WriteDec
    call Crlf
    exit

not_found:
    mov edx, OFFSET msg2
    call WriteString
    call Crlf
    exit
main ENDP
END main
