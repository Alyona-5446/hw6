section .text

global f1
f1: ; f1(x) = 1 + 4 / (x^2 + 1)
    push ebp
    mov ebp, esp
    push 4
    finit
    fild dword[esp]
    fld qword[ebp + 8]
    fld st0
    fmulp
    fld1
    faddp
    fdivp
    fld1
    faddp
    mov esp, ebp
    pop ebp
    ret

global f1_der
f1_der: ; f1'(x) = -8x / (x^2 + 1)^2
    push ebp
    mov ebp, esp
    push -8
    finit
    fild dword[esp]
    fld qword[ebp + 8]
    fmulp
    fld qword[ebp + 8]
    fld st0
    fmulp
    fld1
    faddp
    fld st0
    fmulp
    fdivp
    mov esp, ebp
    pop ebp
    ret

global f2
f2: ; f2(x) = x^3
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp + 8]
    fld st0
    fld st0
    fmulp
    fmulp
    mov esp, ebp
    pop ebp
    ret

global f2_der
f2_der: ; f2'(x) = 3x^2
    push ebp
    mov ebp, esp
    push 3
    finit
    fild dword[esp]
    fld qword[ebp + 8]
    fld st0
    fmulp
    fmulp
    mov esp, ebp
    pop ebp
    ret

global f3
f3: ; f3(x) = 2^{-x}
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp + 8]
    fchs
    fld st0
    frndint
    fld st1
    fsub st0, st1
    f2xm1
    fld1
    faddp
    fscale
    fstp
    fstp
    mov esp, ebp
    pop ebp
    ret

global f3_der
f3_der: ; f3'(x) = -2^{-x}ln2
    push ebp
    mov ebp, esp
    push dword[ebp + 12]
    push dword[ebp + 8]
    call f3
    fldln2
    fmulp
    fchs
    mov esp, ebp
    pop ebp
    ret
