; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    array DWORD 8, 5, 3, 9, 1, 7, 2
    arraySize = ($ - array) / TYPE array
    msg BYTE "Sorted array: ",0

.code
main PROC
    push OFFSET array
    push arraySize
    call BubbleSort

    mov edx, OFFSET msg
    call WriteString
    call Crlf
    mov esi, OFFSET array
    mov ecx, arraySize
    call DisplayArray
    exit
main ENDP

BubbleSort PROC
    push ebp
    mov ebp, esp
    pushad  
    mov esi, [ebp+12]
    mov ecx, [ebp+8]
    dec ecx
    mov ebx, 0

OuterLoop:
    mov ebx, 0
    mov edi, ecx
    mov esi, [ebp+12]

InnerLoop:
    mov eax, [esi]
    mov edx, [esi+4]
    cmp eax, edx
    jle NoSwap
    
    mov [esi], edx
    mov [esi+4], eax
    mov ebx, 1

NoSwap:
    add esi, 4
    dec edi
    jnz InnerLoop
    
    cmp ebx, 0
    je Sorted  
    loop OuterLoop

Sorted:
    popad
    pop ebp
    ret 8
BubbleSort ENDP

DisplayArray PROC
DisplayLoop:
    mov eax, [esi]
    call WriteDec
    call Crlf
    add esi, 4
    loop DisplayLoop
    ret
DisplayArray ENDP

END main
