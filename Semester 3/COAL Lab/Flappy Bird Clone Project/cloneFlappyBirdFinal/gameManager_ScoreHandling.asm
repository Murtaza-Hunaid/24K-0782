.386 
.model flat, stdcall 
option casemap:none 

includelib kernel32.lib 

ExitProcess PROTO :DWORD 
WriteFile PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD 
CreateFileA PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD 
CloseHandle PROTO :DWORD 
SetFilePointer PROTO :DWORD,:DWORD,:DWORD,:DWORD 
PUBLIC gameManager_writeScore 
.data 
fileName db "players.txt",0 
comma_space db ", ",0 
newline db 0Dh,0Ah 
scoreBuffer db 16 dup(0) 
.code


gameManager_writeScore PROC lpName:DWORD, nameLen:DWORD, scoreVal:DWORD
    push ebp
    mov  ebp, esp

    ; OPEN FILE
    push 0
    push 0
    push 4
    push 0
    push 0
    push 40000000h
    push OFFSET fileName
    call CreateFileA
    mov esi, eax
    cmp esi, -1
    je exitWrite

    ; SEEK TO END
    push 2
    push 0
    push 0
    push esi
    call SetFilePointer

    ; WRITE NAME
    push 0
    push 0
    push [ebp+0Ch]          ; nameLen
    push [ebp+08h]          ; lpName
    push esi
    call WriteFile

    ; WRITE ", "
    push 0
    push 0
    push 2
    push OFFSET comma_space
    push esi
    call WriteFile

    ; CONVERT SCORE -> ASCII
    mov eax, [ebp+10h]      ; scoreVal
    mov edi, OFFSET scoreBuffer
    xor ecx, ecx

convertLoop:
    xor edx, edx
    mov ebx, 10
    div ebx
    add dl, '0'
    mov [edi], dl
    inc edi
    inc ecx
    test eax, eax
    jnz convertLoop

    ; reverse
    mov esi, OFFSET scoreBuffer
    lea edi, [esi + ecx - 1]

revLoop:
    cmp esi, edi
    jge revDone
    mov al, [esi]
    mov ah, [edi]
    mov [esi], ah
    mov [edi], al
    inc esi
    dec edi
    jmp revLoop
revDone:

    ; WRITE SCORE
    push 0
    push 0
    push ecx                ; length
    push OFFSET scoreBuffer
    push esi                ; <-- doesn't matter, dummy
    push esi                ; <-- actually WriteFile ignores extra?
    push esi                ; <-- let's fix
    push esi                ; <-- safer: just push handle, already pushed above
    push esi
    push esi

    ; Actually call:
    push 0
    push 0
    push ecx
    push OFFSET scoreBuffer
    push esi                 ; handle
    call WriteFile

    ; WRITE NEWLINE
    push 0
    push 0
    push 2
    push OFFSET newline
    push esi
    call WriteFile

    ; CLOSE FILE
    push esi
    call CloseHandle

exitWrite:
    mov esp, ebp
    pop ebp
    ret
gameManager_writeScore ENDP
END