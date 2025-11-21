; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    array DWORD 1,2,3,4,5,6,7,8,9,10
    arraySize = ($ - array) / TYPE array
    multiplier DWORD 10

.code

DisplayArray PROC arrAddr, arrSize
    mov esi, arrAddr
    mov ecx, arrSize

L1:
    mov eax, [esi]
    call WriteInt
    call Crlf
    add esi, 4
    loop L1
    call Crlf
    ret
DisplayArray ENDP

LoadArray PROC arrAddr, arrSize, mult
    mov esi, arrAddr
    mov ecx, arrSize
    mov ebx, mult

L1:
    mov eax, [esi]
    mul ebx
    mov [esi], eax
    add esi, 4
    loop L1
    ret
LoadArray ENDP

main PROC
    INVOKE LoadArray, OFFSET array, arraySize, multiplier
    INVOKE DisplayArray, OFFSET array, arraySize
    exit
main ENDP
END main
