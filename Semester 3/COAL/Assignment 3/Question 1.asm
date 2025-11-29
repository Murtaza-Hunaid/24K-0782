; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    dividend WORD 0D4A4h
    divisor WORD 0Ah
    msg BYTE "Quotient: ", 0

.code
main PROC
    movzx eax, dividend      
    movzx ebx, divisor       
    call RecursiveDivide

    mov edx, OFFSET msg
    call WriteString
    call WriteDec
    call Crlf
    exit
main ENDP

RecursiveDivide PROC
    cmp eax, 5h
    jbe Done               

    push ebx                  
    xor edx, edx              
    div ebx                  
    call RecursiveDivide       

    pop ebx  
    
Done:
    ret
RecursiveDivide ENDP
END main
