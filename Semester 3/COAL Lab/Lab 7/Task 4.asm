; Murtaza Hunaid Terai   24K-0782

INCLUDE Irvine32.inc

.data
    msg BYTE "Enter two numbers: ", 0
    msg_true BYTE "Condition True", 0
    msg_false BYTE "Condition False", 0

.code
main PROC
    mov edx, OFFSET msg
    call WriteString
    call ReadInt
    mov ebx, eax
    call ReadInt
    cmp ebx, eax
    jle L_false
    cmp ebx, 100
    jge L_false
    mov edx, OFFSET msg_true
    jmp L_display

L_false:
    mov edx, OFFSET msg_false

L_display:
    call WriteString
    call Crlf
    exit
main ENDP
END main
