; Murtaza Hunaid Terai    24K-0782

INCLUDE Irvine32.inc

.data
    msg_in BYTE "Enter numbers or 0 to end: ", 0
    msg BYTE "Valid numbers entered: ", 0

.code
main PROC
    mov ecx, 5
    mov ebx, 0
    mov edx, OFFSET msg_in
    call WriteString

L1:
    call ReadInt
    cmp eax, 0
    je L2
    inc ebx
    loopnz L1

    mov edx, OFFSET msg
    call WriteString
    mov eax, ebx
    call WriteInt
    call Crlf
    exit
main ENDP
END main
