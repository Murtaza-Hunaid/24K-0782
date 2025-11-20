; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    Str1 BYTE "Murtaza Hunaid",0
    Str2 BYTE SIZEOF Str1 DUP(0)
    msg1 BYTE "Original: ",0
    msg2 BYTE "Reversed: ",0

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    mov edx, OFFSET Str1
    call WriteString
    call Crlf

    push OFFSET Str1
    push OFFSET Str2
    call Str_Reverse

    mov edx, OFFSET msg2
    call WriteString
    mov edx, OFFSET Str2
    call WriteString
    call Crlf
    exit
main ENDP

Str_Reverse PROC
    push ebp
    mov ebp, esp
    push esi
    push edi
    push ecx
    push eax
    mov esi, [ebp+12]
    mov edi, [ebp+8]
    mov edi, esi
    mov al, 0
    mov ecx, -1
    cld
    repne scasb
    mov eax, edi
    sub eax, esi
    dec eax
    mov ecx, eax  
    mov esi, [ebp+12]
    add esi, ecx
    dec esi
    mov edi, [ebp+8]  
    std
ReverseLoop:
    lodsb
    cld
    stosb
    std
    loop ReverseLoop
    
    cld
    mov BYTE PTR [edi], 0
    pop eax
    pop ecx
    pop edi
    pop esi
    pop ebp
    ret 8
Str_Reverse ENDP

END main
