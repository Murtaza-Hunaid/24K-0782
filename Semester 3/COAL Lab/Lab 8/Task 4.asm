; Murtaza Hunaid Terai    24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter a word: ",0
    msg2 BYTE "Vowels: ",0
    msg3 BYTE "Consonants: ",0
    input_word BYTE 50 DUP(?)
    vowels DWORD 0
    cons DWORD 0

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    mov edx, OFFSET input_word
    mov ecx, 50
    call ReadString
    mov esi, OFFSET input_word
    mov ecx, eax

count_loop:
    mov al, [esi]
    cmp al, 0
    je done
    cmp al, 'a'
    je vowel
    cmp al, 'e'
    je vowel
    cmp al, 'i'
    je vowel
    cmp al, 'o'
    je vowel
    cmp al, 'u'
    je vowel
    cmp al, 'A'
    je vowel
    cmp al, 'E'
    je vowel
    cmp al, 'I'
    je vowel
    cmp al, 'O'
    je vowel
    cmp al, 'U'
    je vowel
    inc cons
    jmp next_char

vowel:
    inc vowels

next_char:
    inc esi
    loop count_loop

done:
    mov edx, OFFSET msg2
    call WriteString
    mov eax, vowels
    call WriteDec
    call Crlf

    mov edx, OFFSET msg3
    call WriteString
    mov eax, cons
    call WriteDec
    call Crlf
    exit
main ENDP
END main
