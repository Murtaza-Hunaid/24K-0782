; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    num1 SWORD ?
    num2 SWORD ?
    result SDWORD ?
    msg1 BYTE "Enter first number: ",0
    msg2 BYTE "Enter second number: ",0
    msg3 BYTE "Result: ",0

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    mov num1, ax

    mov edx, OFFSET msg2
    call WriteString
    call ReadInt
    mov num2, ax

    movsx eax, num1
    movsx ebx, num2
    imul ebx
    mov result, eax

    mov edx, OFFSET msg3
    call WriteString
    mov eax, result
    call WriteInt
    call Crlf
    exit
main ENDP
END main
