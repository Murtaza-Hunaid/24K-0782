.386
.model flat, stdcall
option casemap:none

includelib kernel32.lib

ExitProcess PROTO :DWORD
WriteFile PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
CreateFileA PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
CloseHandle PROTO :DWORD
SetFilePointer PROTO :DWORD,:DWORD,:DWORD,:DWORD

PUBLIC gameManager_writeToFile

.data
fileName db "players.txt",0
comma_space db ", ",0
newline      db 0Dh,0Ah

; buffer for converting score to ASCII
scoreBuffer db 16 dup(0)

.code

; ---------------------------------------------
; OLD FUNCTION (still used for name only)
; void __stdcall gameManager_writeToFile(const char* buffer, int length)
; ---------------------------------------------
gameManager_writeToFile PROC lpBuffer:DWORD, nLength:DWORD
    push 0
    push 0
    push 4               ; OPEN_ALWAYS
    push 0
    push 0
    push 40000000h       ; GENERIC_WRITE
    push OFFSET fileName
    call CreateFileA
    mov ebx, eax

    cmp ebx, -1
    je done1

    ; move to EOF
    push 2
    push 0
    push 0
    push ebx
    call SetFilePointer

    ; write buffer (name)
    sub esp, 4
    lea eax, [esp]
    push 0
    push eax
    push nLength
    push lpBuffer
    push ebx
    call WriteFile
    add esp, 4

    ; newline
    sub esp, 4
    lea eax, [esp]
    push 0
    push eax
    push 2
    push OFFSET newline
    push ebx
    call WriteFile
    add esp, 4

    push ebx
    call CloseHandle

done1:
    ret
gameManager_writeToFile ENDP




END
