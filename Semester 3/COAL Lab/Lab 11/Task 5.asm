; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    array DWORD 1,2,3,4,5,6,7,8,9,10
    arraySize = ($ - array) / TYPE array
    multiplier DWORD 10
    msg BYTE "Array after multiplication: ",0

.code
main PROC
    push OFFSET array
    push arraySize
    push multiplier
    call LoadArray

    mov edx, OFFSET msg
    call WriteString
    call Crlf
    mov esi, OFFSET array
    mov ecx, arraySize
    call DisplayArray
    call Crlf
    exit
main ENDP

LoadArray PROC
    push ebp
    mov ebp, esp
    push esi
    push ecx
    push eax
    push ebx
    mov esi, [ebp+16]
    mov ecx, [ebp+12]
    mov ebx, [ebp+8]

MultiplyLoop:
    lodsd
    mul ebx
    mov [esi-4], eax
    loop MultiplyLoop

    pop ebx
    pop eax
    pop ecx
    pop esi
    pop ebp
    ret 12
LoadArray ENDP

DisplayArray PROC
DisplayLoop:
    mov eax, [esi]
    call WriteInt
    call Crlf
    add esi, 4
    loop DisplayLoop
    ret
DisplayArray ENDP

END main
