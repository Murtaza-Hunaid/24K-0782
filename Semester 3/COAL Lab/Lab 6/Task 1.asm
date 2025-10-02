; Murtaza Hunaid Terai   24K-0782

INCLUDE Irvine32.inc

.data
    msg_1 BYTE "Welcome", 0
    msg_2 BYTE "You should not see this line", 0
    msg_3 BYTE "Goodbye", 0

.code
main PROC
    mov edx, OFFSET msg_1
    call WriteString
    call CrLf
    jmp LineSkip
    mov edx, OFFSET msg_2
    call WriteString
    call CrLf
    LineSkip:
    mov edx, OFFSET msg_3
    call WriteString
    call CrLf
    exit
    exit
main ENDP
END main
