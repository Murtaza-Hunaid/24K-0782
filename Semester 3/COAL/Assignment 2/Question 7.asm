; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter a number: ",0
    msg2 BYTE "The number is positive",0
    msg3 BYTE "The number is negative",0
    msg4 BYTE "The number is zero",0

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    mov al, al  
    cmp al, 0
    je isZero
    jg isPositive

isNegative:
    mov edx, OFFSET msg3
    call WriteString
    jmp done

isPositive:
    mov edx, OFFSET msg2
    call WriteString
    jmp done

isZero:
    mov edx, OFFSET msg4
    call WriteString

done:
    call Crlf
    exit
main ENDP
END main
