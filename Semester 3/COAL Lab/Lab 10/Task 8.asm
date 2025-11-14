; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter a number: ",0
    msg2 BYTE " is an Armstrong number",0
    msg3 BYTE " is not an Armstrong number",0
    msg4 BYTE "ESP: ",0
    num DWORD ?

.code
main PROC
    call TakeInput
    exit
main ENDP

TakeInput PROC
    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    mov num, eax
    mov edx, OFFSET msg4
    call WriteString
    mov eax, esp
    call WriteHex
    call Crlf

    push num
    call Armstrong
    ret
TakeInput ENDP

Armstrong PROC
    push ebp
    mov ebp, esp
    pushad
    mov edx, OFFSET msg4
    call WriteString
    mov eax, esp
    call WriteHex
    call Crlf
    mov eax, [ebp+8]
    mov ebx, eax
    mov ecx, 0
    mov esi, 10

CountDigits:
    cmp eax, 0
    je StartCheck
    mov edx, 0
    div esi
    inc ecx
    jmp CountDigits

StartCheck:
    mov eax, ebx
    mov edi, 0

SumDigits:
    cmp eax, 0
    je Compare
    mov edx, 0
    div esi
    push eax
    mov eax, edx
    call CalculatePower
    add edi, eax
    pop eax
    jmp SumDigits

CalculatePower:
    push ecx
    mov ecx, ecx
    dec ecx
    mov edx, eax
    cmp ecx, 0
    je PowerDone

PowerLoop:
    imul eax, edx
    loop PowerLoop

PowerDone:
    pop ecx
    ret

Compare:
    cmp edi, ebx
    jne NotArmstrong
    push ebx
    push 1
    call Display
    jmp Done

NotArmstrong:
    push ebx
    push 0
    call Display

Done:
    popad
    pop ebp
    ret 4
Armstrong ENDP

Display PROC
    push ebp
    mov ebp, esp
    mov edx, OFFSET msg4
    call WriteString
    mov eax, esp
    call WriteHex
    call Crlf
    mov eax, [ebp+12]
    call WriteDec
    cmp DWORD PTR [ebp+8], 1
    jne NotArmstrongDisplay
    mov edx, OFFSET msg2
    jmp DisplayDone

NotArmstrongDisplay:
    mov edx, OFFSET msg3

DisplayDone:
    call WriteString
    call Crlf
    pop ebp
    ret 8
Display ENDP

END main
