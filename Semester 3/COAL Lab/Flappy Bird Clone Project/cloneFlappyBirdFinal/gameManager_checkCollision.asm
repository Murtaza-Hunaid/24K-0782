.386
.model flat, stdcall
option casemap:none

INCLUDE Irvine32.inc
PUBLIC gameManager_checkCollision

.code
; birdX, birdY, birdW, birdH, pipeX, pipeTopY, pipeBottomY, pipeW
gameManager_checkCollision PROC birdX:DWORD, birdY:DWORD, birdW:DWORD, birdH:DWORD,
                                pipeX:DWORD, pipeTopY:DWORD, pipeBottomY:DWORD, pipeW:DWORD
    ; ---- Compute bird edges ----
    mov eax, birdX
    add eax, birdW      ; EAX = birdRight
    mov ebx, birdX      ; EBX = birdLeft

    ; ---- Compute pipe edges ----
    mov ecx, pipeX
    add ecx, pipeW      ; ECX = pipeRight

    ; ---- Horizontal overlap check ----
    cmp eax, pipeX      ; birdRight >= pipeLeft ?
    jl noCollision      ; if not, no collision
    cmp ebx, ecx        ; birdLeft <= pipeRight ?
    jg noCollision      ; if not, no collision

    ; ---- Vertical overlap check ----
    mov edx, birdY      ; birdTop
    cmp edx, pipeTopY
    jl collisionTop     ; birdTop < pipeTopY -> collision with top
    mov edx, birdY
    add edx, birdH      ; birdBottom
    cmp edx, pipeBottomY
    jg collisionBottom  ; birdBottom > pipeBottomY -> collision with bottom

    ; No collision
noCollision:
    xor eax, eax
    ret 32

collisionTop:
    mov eax, 1
    ret 32

collisionBottom:
    mov eax, 1
    ret 32

gameManager_checkCollision ENDP
END
