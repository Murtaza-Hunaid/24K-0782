.386
.model flat, c
.stack 4096
.code

PUBLIC gameManager_stateChanger

; int gameManager_stateChanger(int currentState, int command)
gameManager_stateChanger PROC currentState:DWORD, command:DWORD
    mov eax, currentState        ; eax will hold the next state by default

    ; ---- MENU ----
    cmp currentState, 0
    jne check_gameplay

    cmp command, 1
    je to_gameplay
    cmp command, 2
    je to_highscore
    cmp command, 3
    je to_credits
    cmp command, 4
    je to_exit
    cmp command, 5      ; ESC
    je to_menu
    jmp done

to_gameplay: 
    mov eax, 1
    ret
to_highscore:
    mov eax, 2
    ret
to_credits:
    mov eax, 3
    ret
to_exit:
    mov eax, 4
    ret
to_menu:
    mov eax, 0
    ret

; ---- GAMEPLAY ----
check_gameplay:
    cmp currentState, 1
    jne check_highscore
    cmp command, 5      ; ESC
    je back_to_menu_from_gameplay
    cmp command, 6      ; collision -> GAMEOVER
    je to_gameover
    jmp done

back_to_menu_from_gameplay:
    mov eax, 0
    ret

to_gameover:
    mov eax, 5
    ret

; ---- HIGHSCORE ----
check_highscore:
    cmp currentState, 2
    jne check_credits
    cmp command, 5      ; ESC
    je back_to_menu_from_hs
    jmp done

back_to_menu_from_hs:
    mov eax, 0
    ret

; ---- CREDITS ----
check_credits:
    cmp currentState, 3
    jne done
    cmp command, 5      ; ESC
    je back_to_menu_from_credits
    jmp done

back_to_menu_from_credits:
    mov eax, 0
    ret

; ---- GAMEOVER ----
check_gameover:
    cmp currentState, 5
    jne done
    cmp command, 5      ; ESC
    je back_to_menu_from_gameover
    jmp done

back_to_menu_from_gameover:
    mov eax, 0
    ret

done:
    ret
gameManager_stateChanger ENDP
END
