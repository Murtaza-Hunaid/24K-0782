.386
.model flat, stdcall
option casemap:none

PUBLIC gameManager_updateScores
PUBLIC gameManager_resetScores
PUBLIC gameManager_getScores

.data
currentScore DWORD 0        ; shared variable for score

.code

; ------------------------------------------
; int gameManager_updateScore()
; increments score by 1, returns new score
; ------------------------------------------
gameManager_updateScores PROC
    mov eax, currentScore
    inc eax
    mov currentScore, eax
    ret
gameManager_updateScores ENDP

; ------------------------------------------
; int gameManager_getScore()
; returns current score
; ------------------------------------------
gameManager_getScores PROC
    mov eax, currentScore
    ret
gameManager_getScores ENDP

; ------------------------------------------
; void gameManager_resetScore()
; sets score to zero
; ------------------------------------------
gameManager_resetScores PROC
    mov currentScore, 0
    ret
gameManager_resetScores ENDP



END
