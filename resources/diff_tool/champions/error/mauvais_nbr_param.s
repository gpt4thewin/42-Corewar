#Header
.name "Error Test"
.comment "Error Tester"

#Program
live:	live	%42
ld:		ld		%42,	r1
st:		st		r1,		r2
add:	add		r1,		r2,		r3
sub:	sub		r1,		r2,		r3
and:	and		%42,	21,		r1
or:		or		42,		%21,	r1
xor:	xor		r1,		r2,		r3
zjmp:	zjmp	%42
ldi:	ldi		21,		%42,	r1
sti:	sti		r1,		%42,	r1
fork:	fork	%42
lld:	lld		42,		r1
lldi:	lldi	r1,		r2				#Param 2 should be rx
lfork:	lfork	%42
aff:	aff		r1
