.386
.model flat, stdcall
option casemap:none

PUBLIC gameManager_playGameMusic
PUBLIC gameManager_stopGameMusic
PUBLIC gameManager_playMenuMusic
PUBLIC gameManager_stopMenuMusic
PUBLIC gameManager_playFlapSound
PUBLIC gameManager_playScoreSound

; ----------------------------
; Prototype for PlaySoundA
; ----------------------------
PlaySoundA PROTO :PTR BYTE, :DWORD, :DWORD
includelib winmm.lib

SND_ASYNC EQU 1h
SND_LOOP  EQU 8h
SND_NODEFAULT EQU 2h
SND_NOSTOP EQU 10h

.data
bgGameMusic db "assets\\musics\\m1.wav",0
bgMenuMusic db "assets\\musics\\menu1.wav",0
flapSound db "assets\\musics\\flap.wav",0
scoreSound db "assets\\musics\\score.wav",0
.code

gameManager_playGameMusic PROC
    invoke PlaySoundA, ADDR bgGameMusic, 0, SND_ASYNC or SND_LOOP
    ret
gameManager_playGameMusic ENDP

gameManager_stopGameMusic PROC
    invoke PlaySoundA, 0, 0, 0
    ret
gameManager_stopGameMusic ENDP

gameManager_playMenuMusic PROC
    invoke PlaySoundA, ADDR bgMenuMusic, 0, SND_ASYNC or SND_LOOP
    ret
gameManager_playMenuMusic ENDP

gameManager_stopMenuMusic PROC
    invoke PlaySoundA, 0, 0, 0
    ret
gameManager_stopMenuMusic ENDP

gameManager_playFlapSound PROC
    invoke PlaySoundA, ADDR flapSound, 0, SND_ASYNC or SND_NODEFAULT or SND_NOSTOP
    ret
gameManager_playFlapSound ENDP

gameManager_playScoreSound PROC
    invoke PlaySoundA, ADDR scoreSound, 0, SND_ASYNC or SND_NODEFAULT or SND_NOSTOP
    ret
gameManager_playScoreSound ENDP


END
