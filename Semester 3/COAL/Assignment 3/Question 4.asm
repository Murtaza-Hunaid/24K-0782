; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    arr1 DWORD 1,2,5,5,5,5,5,3,4
    size1 = ($ - arr1) / TYPE arr1
    arr2 DWORD 5,5,5,5,1,2,3
    size2 = ($ - arr2) / TYPE arr2
    arr3 DWORD 1,2,3,5,5,5,5,5
    size3 = ($ - arr3) / TYPE arr3

.code

FindFive PROC, pArray:PTR DWORD, arrSize:DWORD
    
    push ebx
    push ecx
    push esi
    push edi
    
    mov esi, pArray
    mov ecx, arrSize
    sub ecx, 4
    jle NotFound
    
CheckLoop:
    mov edi, 0
    mov ebx, 0
    
CheckConsecutive:
    cmp edi, 5
    je Found
    mov eax, [esi + ebx*4]
    cmp eax, 5
    jne NextPosition
    inc edi
    inc ebx
    jmp CheckConsecutive
    
NextPosition:
    add esi, 4
    loop CheckLoop
    
NotFound:
    mov eax, 0
    jmp Done
    
Found:
    mov eax, 1
    
Done:
    pop edi
    pop esi
    pop ecx
    pop ebx
    ret
FindFive ENDP

main PROC
    INVOKE FindFive, ADDR arr1, size1
    call WriteDec
    call Crlf
    
    INVOKE FindFive, ADDR arr2, size2
    call WriteDec
    call Crlf
    
    INVOKE FindFive, ADDR arr3, size3
    call WriteDec
    call Crlf
    
    exit
main ENDP
END main
