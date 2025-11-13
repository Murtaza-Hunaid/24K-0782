; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Enter a number= ",0
    msg2 BYTE "Square= ",0

.code
main PROC
    call LocalSquare
    exit
main ENDP

LocalSquare PROC
    enter 4, 0
    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    mov [ebp-4], eax
    mov eax, [ebp-4]
    imul eax, eax
    mov edx, OFFSET msg2
    call WriteString
    call WriteInt
    call Crlf
    leave
    ret
LocalSquare ENDP

END main
