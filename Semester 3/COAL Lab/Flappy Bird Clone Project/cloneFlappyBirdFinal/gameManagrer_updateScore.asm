.386
.model flat, stdcall
option casemap:none


PUBLIC gameManager_updateScore
PUBLIC currentScore

SCOREDATA SEGMENT DWORD PUBLIC 'DATA'
currentScore DWORD 0
SCOREDATA ENDS

.code
; ------------------------------------------
; int gameManager_updateScore()
; increments score by 1 and returns new score
; ------------------------------------------
gameManager_updateScore PROC
    mov eax, currentScore
    inc eax
    mov currentScore, eax
    ret
gameManager_updateScore ENDP



END
