; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    Str1 BYTE "127&j~3#^&*#*#45^",0
    msg1 BYTE "Index = ",0
    msg2 BYTE "Not found",0

.code
main PROC
    push '#'
    push OFFSET Str1
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
    push ebp
    mov ebp, esp
    mov edi, [ebp+8]
    mov al, BYTE PTR [ebp+12]
    mov ecx, LENGTHOF Str1
    cld
    repne scasb
    jnz notfound2

    sub edi, [ebp+8]
    mov eax, edi
    dec eax
    pop ebp
    ret 8
notfound2:
    mov eax, -1
    pop ebp
    ret 8
Scan_String ENDP

END main
