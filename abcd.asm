.model small
.stack
.data
b3 dw 0
b4 dw 0
.code
mov AX,100
mov b4b3_marks, AX
mov AX,b3
push AX
mov AX,b4
pop DX
add AX,DX
pop DX
add AX,DX
mov b4, AX
mov AX,10
push AX
mov AX,12
push AX
mov AX,14
pop DX
imul DX
pop DX
imul DX
pop DX
imul DX
mov b3, AX
mov AX,b4
push AX
mov AX,12
pop DX
cmp AX,DX
jl true_31_9383
jmp false_31_9383
true_31_9383:
mov AX, 0
false_31_9383:
mov AX, 1
cmp AX,1
jne else31
jmp then31
then31:
mov AX,1
mov b4, AX
else31:
mov AX,2
mov b4, AX
true:
mov AX,0
false:
mov AX,1
ret
end
