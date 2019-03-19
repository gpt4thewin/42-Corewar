.name "debug"
.comment "debug source file"

ld %1, r1 ; 2 - 3 = 10 01 00 00 = 0x90
ld %2, r2
ld %3, r3
ld %4, r4
ld %5, r5
ld %6, r6
ld %7, r7
ld %8, r8
ld %9, r9
ld %10, r10
ld %11, r11
ld %12, r12
ld %13, r13
ld %14, r14
ld %15, r15
ld %16, r16

sti r1, :fin, %201
sti r2, :fin, %202
sti r3, :fin, %203
sti r4, :fin, %204
sti r5, :fin, %205
sti r6, :fin, %206
sti r7, :fin, %207
sti r8, :fin, %208
sti r9, :fin, %209
sti r10, :fin, %210
sti r11, :fin, %211
sti r12, :fin, %212
sti r13, :fin, %213
sti r14, :fin, %214
sti r15, :fin, %215
sti r16, :fin, %216

fin:
