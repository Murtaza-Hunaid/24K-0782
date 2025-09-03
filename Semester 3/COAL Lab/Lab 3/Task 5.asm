; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.code
main PROC
	mov eax, 3000h
	add eax, 6000h
	sub eax, 1000h
	call WriteInt	
	exit
main ENDP
END main
