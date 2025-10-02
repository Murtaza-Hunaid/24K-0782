; Murtaza Hunaid Terai   24K-0782

INCLUDE Irvine32.inc

.code
main PROC
    mov eax, 5 
    mov ecx, 11          

    L1:
        call WriteInt     
        call Crlf        
        inc eax           
        loop L1   
    exit
main ENDP
END main
