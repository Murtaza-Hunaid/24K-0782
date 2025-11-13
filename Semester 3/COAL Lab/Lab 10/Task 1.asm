; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    msg BYTE "Product of three numbers = ", 0

.code
main PROC
    push 3
    push 4
    push 5
    call ThreeProd
    exit
main ENDP

ThreeProd PROC
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    imul eax, [ebp + 12]
    imul eax, [ebp + 16]
    mov edx, OFFSET msg
    call WriteString
    call WriteInt
    call Crlf
    pop ebp
    ret 12
ThreeProd ENDP

END main
