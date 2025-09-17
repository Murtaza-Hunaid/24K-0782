INCLUDE Irvine32.inc 

.code 
  main proc 
  mov eax, 15000 
  add eax, 1 
  call dumpregs 
  EXIT 
MAIN ENDP 
END main
