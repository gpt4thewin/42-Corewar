;.name "debug"
;.comment "debug source file";
.name ""
.comment ""

;; ==== TEST fork + copie ====

;sti r1,%1,%:live
;
;;r2 = offset
;;r5 = step
;;r3 = buffer
;ld r5,4
;payload:
;ld r2,0
;ldi :payload,r2,r3
;sti r3,r2,%:target
;add r5,r2,r2
;ld r2,r6
;zjmp :payload
;fork %:loop
;loop:
;live:
;live %0
;
;add r3,r2,r2
;ld %0,r16
;zjmp %:loop
;
;payload_end:
;target:

;; ==== TEST long ld ====

ld %1,r2
ld %1,r3
sti r1,%1,%:live
loop:
live:
live %0
lldi %:loop,r2,r4
add r3,r2,r2
aff r4
ld %0,r16
zjmp %:loop

;; ==== TEST fork ====

sti r1,%1,%:live
ld %33,r2
ld %1,r3
loop:
live:
live %0
ldi :storage,r2,r10
sti r10,r2,%:storage
;aff r2

fork %:loop
add r3,r2,r2
ld %0,r16
zjmp %:loop
storage:

;; ==== TEST logic + general ====
; "SALT"

;ld %33,r14
;ld %1,r13
;ld %0,r6
;ld %4,r5
;sti r1,%1,%:live
;loop:
;aff r14
;live:
;live %0
;ld %7,r2
;ld %8,r3
;or r2,r3,r4
;sti r4,r5,%:storage
;add r6,r5,r6
;
;ld %15,r2
;ld %5,r3
;and r2,r3,r4
;sti r4,r5,%:storage
;add r6,r5,r6
;
;ld %15,r2
;ld %17,r3
;xor r2,r3,r4
;sti r4,r5,%:storage
;add r6,r5,r6
;
;;LLDI ?
;;add r6,r5,r6
;
;ld %0,r16
;fork %:fork
;zjmp %:loop
;fork:
;add r13,r14,r14
;zjmp %:loop
;
;storage:

;; ==== TEST math ====
; "SALT"

;ld %80,r2
;ld %3,r3
;add r2,r3,r4
;aff r4
;
;ld %70,r2
;ld %5,r3
;sub r2,r3,r4
;aff r4
;
;ld %82,r2
;ld %-6,r3
;add r2,r3,r4
;aff r4
;
;ld %80,r2
;ld %4,r3
;add r2,r3,r4
;aff r4

;; ==== TEST fork ====

;sti r1, %1, %:live
;fork:
;fork %:fork
;live:
;live %0
;ld %0,r16
;aff r16
;zjmp %:live

;; === TEST aff =======
;sti r1, %1, %:live
;;fork %:newproc
;live:
;live %0
;ld %41,r3
;add r3,r2,r3
;aff r3
;ld %0,r16
;zjmp %:live
;
;newproc:
;ld %42,r3
;add r3,r1,r3
;aff r3
;ld %0,r16
;zjmp %:newproc

