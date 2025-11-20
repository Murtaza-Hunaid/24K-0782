; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    Str1 BYTE "127&j~3#^&*#*#45^",0
    msg1 BYTE "Index = ",0
    msg2 BYTE "Not found",0

.code
main PROC
    call Scan_String
    cmp eax, -1
    je not_found
    mov edx, OFFSET msg1
    call WriteString
    call WriteDec
    call Crlf
    exit

not_found:
    mov edx, OFFSET msg2
    call WriteString
    call Crlf
    exit
main ENDP

Scan_String PROC
    mov edi, OFFSET Str1
    mov al, '#'
    mov ecx, LENGTHOF Str1
    cld
    repne scasb
    jnz notfound

    sub edi, OFFSET Str1
    mov eax, edi
    dec eax
    ret
notfound:
    mov eax, -1
    ret
Scan_String ENDP

END main
