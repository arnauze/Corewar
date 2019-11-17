.name "aaaa bbbb cccc"

.comment "dddd eeee ffff" #dlkjbas

	live %12
	ld %12, r1
	st r1, r2
	add r1, r2, r3
label:	sub r1, r2, r3
	live %12


	and r1, r2, r3
	or r1, r2, r3

	xor r1, r2, r3

	zjmp %:label
#	ldi r1, r2, r3
#	sti r1, r2, r3
#	fork %42
#	lld %42, r1
#	lldi r1, r2, r3 #khabscd
#	lfork %:label
#	lfork %:label
	aff r1

	aff r2
	aff r3


 live %-12

wipe
swap r1, r2

ab:#iub
