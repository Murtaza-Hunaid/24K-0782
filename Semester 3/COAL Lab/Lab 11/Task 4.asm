; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    Str1 BYTE "Murtaza Hunaid",0
    Str2 BYTE SIZEOF Str1 DUP(0)
    msg1 BYTE "Original: ",0
    msg2 BYTE "Reversed: ",0

.code

Str_Reverse PROC source, target
    mov esi, source
    mov edi, target
    mov ecx, 0

L1:
    mov al, [esi]
    cmp al, 0
    je L2
    inc esi
    inc ecx
    jmp L1
    
L2:
    mov esi, source
    add esi, ecx
    dec esi
    mov edi, target
    
L3:
    mov al, [esi]
    mov [edi], al
    dec esi
    inc edi
    loop L3
  
    mov BYTE PTR [edi], 0
    ret
Str_Reverse ENDP

main PROC
    mov edx, OFFSET msg1
    call WriteString
    mov edx, OFFSET Str1
    call WriteString
    call Crlf   
    INVOKE Str_Reverse, OFFSET Str1, OFFSET Str2  
    mov edx, OFFSET msg2
    call WriteString
    mov edx, OFFSET Str2
    call WriteString
    call Crlf   
    exit
main ENDP
END main
