; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    nums DWORD 4 DUP(?)
    msg1 BYTE "Enter number: ",0
    msg2 BYTE "At least one number is not prime",0
    msg3 BYTE "Largest prime: ",0
    msg4 BYTE "All numbers are prime",0

.code
main PROC
    mov esi, OFFSET nums
    mov ecx, 4

inputLoop:
    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    mov [esi], eax
    add esi, 4
    loop inputLoop

    mov esi, OFFSET nums
    mov ecx, 4

checkLoop:
    push [esi]
    call CheckPrime
    cmp eax, 1
    jne notPrimeFound
    add esi, 4
    loop checkLoop

    mov edx, OFFSET msg4
    call WriteString
    call Crlf
    push OFFSET nums
    call LargestPrime
    exit

notPrimeFound:
    mov edx, OFFSET msg2
    call WriteString
    call Crlf
    exit
main ENDP

CheckPrime PROC
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    cmp eax, 2
    jl notPrime
    cmp eax, 2
    je isPrime
    mov ebx, 2

chkLoop:
    mov edx, 0
    div ebx
    cmp edx, 0
    je notPrime
    inc ebx
    mov eax, [ebp+8]
    cmp ebx, eax
    jl chkLoop

isPrime:
    mov eax, 1
    jmp done

notPrime:
    mov eax, 0

done:
    pop ebp
    ret 4
CheckPrime ENDP

LargestPrime PROC
    push ebp
    mov ebp, esp
    mov esi, [ebp+8]
    mov eax, [esi]
    mov ecx, 4
    add esi, 4
    dec ecx

Lloop:
    cmp [esi], eax
    jle skip
    mov eax, [esi]

skip:
    add esi, 4
    loop Lloop

    mov edx, OFFSET msg3
    call WriteString
    call WriteInt
    call Crlf
    pop ebp
    ret 4
LargestPrime ENDP

END main
