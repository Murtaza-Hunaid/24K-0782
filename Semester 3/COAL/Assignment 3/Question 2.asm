; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    Str1 BYTE 100 DUP(0)
    msg1 BYTE "Enter a string: ", 0
    msg2 BYTE "Vowel Count", 0
    vowel_count BYTE 5 DUP(0)
    msg_a BYTE "a or A = ", 0
    msg_e BYTE "e or E = ", 0
    msg_i BYTE "i or I = ", 0
    msg_o BYTE "o or O = ", 0
    msg_u BYTE "u or U = ", 0

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    mov edx, OFFSET Str1
    mov ecx, SIZEOF Str1
    call ReadString
    mov esi, OFFSET Str1

CountVowels:
    mov al, [esi]
    cmp al, 0
    je DisplayResults
    
    cmp al, 'a'
    je IncA
    cmp al, 'A'
    je IncA
    
    cmp al, 'e'
    je IncE
    cmp al, 'E'
    je IncE
    
    cmp al, 'i'
    je IncI
    cmp al, 'I'
    je IncI
    
    cmp al, 'o'
    je IncO
    cmp al, 'O'
    je IncO
    
    cmp al, 'u'
    je IncU
    cmp al, 'U'
    je IncU   
    jmp NextChar

IncA:
    inc BYTE PTR [vowel_count+0]
    jmp NextChar

IncE:
    inc BYTE PTR [vowel_count+1]
    jmp NextChar

IncI:
    inc BYTE PTR [vowel_count+2]
    jmp NextChar

IncO:
    inc BYTE PTR [vowel_count+3]
    jmp NextChar

IncU:
    inc BYTE PTR [vowel_count+4]

NextChar:
    inc esi
    jmp CountVowels

DisplayResults:
    mov edx, OFFSET msg2
    call WriteString
    call Crlf
    
    mov edx, OFFSET msg_a
    call WriteString
    movzx eax, BYTE PTR [vowel_count+0]
    call WriteDec
    call Crlf
    
    mov edx, OFFSET msg_e
    call WriteString
    movzx eax, BYTE PTR [vowel_count+1]
    call WriteDec
    call Crlf
    
    mov edx, OFFSET msg_i
    call WriteString
    movzx eax, BYTE PTR [vowel_count+2]
    call WriteDec
    call Crlf
    
    mov edx, OFFSET msg_o
    call WriteString
    movzx eax, BYTE PTR [vowel_count+3]
    call WriteDec
    call Crlf
    
    mov edx, OFFSET msg_u
    call WriteString
    movzx eax, BYTE PTR [vowel_count+4]
    call WriteDec
    call Crlf
    exit
main ENDP
END main
