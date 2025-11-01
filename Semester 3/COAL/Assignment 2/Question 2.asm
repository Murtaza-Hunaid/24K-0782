; Murtaza Hunaid Terai    24K-0782

INCLUDE Irvine32.inc

.data
    num1 SDWORD -7
    num2 SDWORD -10
    num3 SDWORD 5
    num4 SDWORD 4
    result SDWORD ?

.code
main PROC
    mov eax, num1
    mov ebx, num2
    cmp eax, ebx
    jle check_equal         

    mov eax, num3
    mov ebx, num4
    cmp eax, ebx
    je check_equal            

    mov eax, num1
    add eax, num3
    mov result, eax
    jmp display_result

check_equal:
    mov eax, num2
    mov ebx, num4
    cmp eax, ebx
    jne else_part
    mov eax, num2
    sub eax, num1
    mov result, eax
    jmp display_result

else_part:
    mov result, 0

display_result:
    mov eax, result
    call WriteInt
    call Crlf
    exit
main ENDP
END main
