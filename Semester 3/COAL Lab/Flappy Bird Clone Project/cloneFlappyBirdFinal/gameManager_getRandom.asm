.386
.model flat, c
.stack 4096
.data
seed DWORD 123456789    ; initial seed, can be any number
.code

PUBLIC gameManager_getRandom

; int gameManager_getRandom(int maxValue)
gameManager_getRandom PROC maxValue:DWORD
    ; simple LCG: seed = (a*seed + c) % m
    mov eax, seed
    mov ecx, 1103515245
    mul ecx            ; eax = eax * 1103515245
    add eax, 12345
    mov seed, eax      ; update seed
    ; now we get remainder with maxValue
    xor edx, edx
    div maxValue       ; eax = quotient, edx = remainder
    mov eax, edx       ; return remainder
    ret
gameManager_getRandom ENDP

END
