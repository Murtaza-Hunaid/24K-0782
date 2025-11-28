; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    str1 BYTE "ASSEMBLY", 0 
    msg BYTE "Reversed string: ", 0

.code
main PROC
    mov esi, OFFSET str1    ; esi points to start of the string
    mov ecx, 0

len_loop:
    mov al, [esi]   
    cmp al, 0
    je  len_done
    inc esi
    inc ecx                          
    jmp len_loop

len_done:
    mov edx, ecx    ; edx = length
    shr edx, 1  ; edx = length / 2 (loop count)
    mov esi, OFFSET str1    ; start pointer
    mov edi, OFFSET str1    ; end pointer
    add edi, ecx
    dec edi ; point to last character

reverse_loop:
    cmp edx, 0
    je print_result

    mov al, [esi]   ; swap strl[i]
    mov bl, [edi]   ; with str1[Length-1-1]
    mov [esi], bl
    mov [edi], al
    inc esi ; move forward
    dec edi ; move backward
    dec edx ; loop counter
    jmp reverse_loop

print_result:
    mov edx, OFFSET msg
    call WriteString
    mov edx, OFFSET str1
    call WriteString
    call Crlf
    exit
main ENDP
END main
