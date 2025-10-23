; Murtaza Hunaid Terai    24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter a number: ",0
    msg2 BYTE "Factorial: ",0
    num DWORD ?
    factorial DWORD ?

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    mov num, eax
    mov ecx, eax
    mov eax, 1

factorial_loop:
    cmp ecx, 0
    je done
    mul ecx
    dec ecx
    jmp factorial_loop

done:
    mov factorial, eax
    mov edx, OFFSET msg2
    call WriteString
    mov eax, factorial
    call WriteDec
    call Crlf
    exit
main ENDP
END main
