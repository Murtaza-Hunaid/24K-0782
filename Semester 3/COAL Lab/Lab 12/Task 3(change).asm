; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    str1 BYTE "ASSEMBLY", 0 ; String to reverse
    length DWORD 0  ; Will store length of string
    msg BYTE "Reversed string: ", 0

.code
main PROC
    mov esi, OFFSET str1 ; ESI points to string
    xor ecx, ecx    ; ECX = length counter

FindLen:
    mov al, [esi]   ; Load character
    cmp al, 0   ; Check if end of string
    je  LenDone
    inc esi
    inc ecx                          
    jmp FindLen

LenDone:
    mov length, ecx ; store length
    xor edi, edi    ; i = 0 points to EDI = left index
    mov eax, length1
    shr eax, 1  ; eax = length / 2  (loop limit)

ReverseLoop:
    cmp edi, eax    ; if i >= length/2, then done
    jge DoneReverse

    mov ebx, length
    dec ebx ; convert length to last index (len-1)
    sub ebx, edi    ; right index = length - i - 1
    mov dl, str1[edi]    ; temp = str[i]
    mov dh, str1[ebx]    ; str[i] = str[length - i - 1]
    mov str1[edi], dh
    mov str1[ebx], dl    ; str[length - i - 1] = temp
    inc edi                          
    jmp ReverseLoop

DoneReverse:
    mov edx, OFFSET msg
    call WriteString

    mov edx, OFFSET str1
    call WriteString
    call CrLf
    exit
main ENDP
END main
