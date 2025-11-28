; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    str1 BYTE "ASSEMBLY",0       
    target BYTE 'E' ; Character to search for
    found DWORD 0   ; 0 = not found, 1 = found
    msg1 BYTE "Character found!",0
    msg2 BYTE "Character not found!",0

.code
main PROC
    mov esi, OFFSET str1    ; esi points to start of the string

SearchLoop:
    mov al, BYTE PTR [esi]  ; Loads current character
    cmp al, 0   ; Check if end of string or not
    je NotFound ; If null terminator, then exit loop

    cmp al, target  ; Compare with the target character
    je FoundChar    ; If equal, then go to found

    inc esi ; Move to next character
    jmp SearchLoop

FoundChar:
    mov found, 1    ; Set found = 1

NotFound:
    mov eax, found 
    cmp eax, 1
    jne PrintNotFound

PrintFound:
    mov edx, OFFSET msg1
    call Writestring
    call CrLf
    jmp EndProgram

PrintNotFound:
    mov edx, OFFSET msg2
    call Writestring
    call Crlf

EndProgram:
    exit
main ENDP
END main
