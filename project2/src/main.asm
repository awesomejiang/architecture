.data
f_inA: .asciiz "A.in"
f_inB: .asciiz "B.in"
f_outC: .asciiz "C.out"
open_err_msg: .asciiz "Cannot open target file."


.text


main:
	li $t0, 8
	mul $t1, $t0, $t0				#allocate memory
	li $t2, 4
	mul $t1, $t1, $t2				#t1 = 8*8*4 = 256
	li $t3, 3
	mul $t2, $t1, $t3				#t2 = 3 *256
	sub $sp, $sp, $t2				#set stack frame for 3 matrices

	addi $t3, $sp, 0				#store addr of ABC into
	add $t4, $t3, $t1				#$t3, $t4, $t5
	add $t5, $t4, $t1

	addi $sp, $sp, -56				#set stack frame for regs
	sw $fp, 36($sp)
	sw $ra, 40($sp)

	sw $t0, 16($sp)
	sw $t2, 20($sp)
	sw $t3, 24($sp)
	sw $t4, 28($sp)
	sw $t5, 32($sp)

	addi $fp, $sp, 52				#set $fp

	la $a0, f_inA					#read/init A
	lw $a1, 24($sp)
	lw $a2, 16($sp)
	jal read

	la $a0, f_inB					#read/init B
	lw $a1, 28($sp)
	lw $a2, 16($sp)
	jal read

	lw $a0, 24($sp)
	lw $a1, 28($sp)
	lw $a2, 32($sp)
	lw $a3, 16($sp)
	jal mxm

	la $a0, f_outC					#write C
	lw $a1, 32($sp)
	lw $a2, 16($sp)
	jal write

	#restore regs
	lw $ra, 40($sp)
	lw $fp, 36($sp)

	lw $t0, 20($sp)
	add $sp, $sp, $t0
	addi $sp, $sp, 56

	li $v0, 10
	syscall



#args: file f_A, addr A, size n
read:
	addi $sp, $sp, -32				#set stack

	sw $ra, 20($sp)
	sw $fp, 16($sp)
	sw $a0, 8($sp)
	sw $a1, 4($sp)
	sw $a2, 0($sp)
	addi $fp, $sp, 28

	li $v0, 13						#open file
	lw $a0, 8($sp)
    li $a1, 00 
    li $a2, 0777
    syscall

    move $a0, $v0

    li $t1, -1
    bne $t0, $t1, open_success		# open or not?
    	li $v0, 4
    	la $a0, open_err_msg
    	syscall
    	b read_end

	open_success:

	    mul $t0, $t0, $t0			#$t0 = n*n
	    li $t1, 8
	    mul $a2, $t0, $t1			#$a2 = n*n*8
	    lw $a1, 4($sp)
	    li $v0, 14
	    syscall

		li $v0, 16					#$a0 not changed
		syscall

	read_end:
		lw $ra, 20($sp)
		lw $fp, 16($sp)
		addi $sp, $sp, 32
		jr $ra

#args: file f_A, addr A, size n
write:
	addi $sp, $sp, -32				#set stack

	sw $ra, 20($sp)
	sw $fp, 16($sp)
	sw $a0, 8($sp)
	sw $a1, 4($sp)
	sw $a2, 0($sp)
	addi $fp, $sp, 28

	li $v0, 13						#open file
	lw $a0, 8($sp)
    li $a1, 0x41
    li $a2, 0x1FF
    syscall

	move $a0, $v0


	li $v0, 15						#write
	lw $a1, 4($sp)
	lw $t0, 0($sp)	
	mul $t0, $t0, $t0				#$t0 = n*n
	li $t1, 8
	mul $t1, $t0, $t1
	move $a2, $t1
	syscall
    
	li $v0, 16					#$a0 not changed
	syscall 					#close file

	lw $ra, 20($sp)
	lw $fp, 16($sp)
	addi $sp, $sp, 32
	jr $ra


# args:	addr A, addr B, stride p, stride q, length n
dot:
	addi $sp, $sp, -32				#set stack to store $ra, i, sum

	sw $ra, 20($sp)
	sw $fp, 16($sp)
	addi $fp, $sp, 36

	lw $t0, 32($sp)					#t0 = length n
	li $t1, 0						#sum, t1 = 0

	li $t2, 0
	dot_loop:
		beq $t2, $t0, dot_end		#if $t2==n, endloop

		move $t3, $a2				#p
		li $t4, 4
		mul $t3, $t3, $t4			#p=p*4
		mul $t4, $t2, $t3			#i*p
		move $t5, $a0				#a
		add $t3, $t4, $t5			#&a[i*p]
		lw $t6, 0($t3)				#a[i*p]

		move $t3, $a3				#q
		li $t4, 4
		mul $t3, $t3, $t4			#q=q*4
		mul $t4, $t2, $t3			#i*q
		move $t5, $a1				#b
		add $t3, $t4, $t5			#&b[i*q]
		lw $t7, 0($t3)				#b[i*q]

		mul $t3, $t6, $t7			#a[i*p] * b[i*q]
		add $t1, $t1, $t3			#sum += ...

		addi $t2, $t2, 1
		b dot_loop

	dot_end: 
		move $v0, $t1
		lw $ra, 20($sp)
		lw $fp, 16($sp)
		addi $sp, $sp, 32
		jr $ra


# args:	addr A, addr B, addr C, size n
mxm:
	addi $sp, $sp, -40				#store regs

	sw $ra, 24($sp)
	sw $fp, 20($sp)
	addi $fp, $sp, 36

	addi $t0, $0, 0
	mxm_loop1:
		beq $t0, $a3, mxm_end1		#if $t0==n, endloop

		addi $t1, $0, 0
		mxm_loop2:
			beq $t1, $a3, mxm_end2	#if $t1==n, endloop
			
			sw $a0, 0($sp)			#save args to stack
			sw $a1, 4($sp)
			sw $a2, 8($sp)
			sw $a3, 12($sp)
			sw $t0, 16($sp)			#save i
			sw $t1, 20($sp)			#save j

			lw $t2, 12($sp)			#n
			li $t3, 4
			mul $t2, $t2, $t3		#n=n*4
			mul $t3, $t0, $t2		#i*n
			lw $t4, 0($sp)			#a
			add $t4, $t4, $t3		#&a[i*n]
			move $a0, $t4

			lw $t2, 20($sp)			#j
			li $t3, 4
			mul $t2, $t2, $t3		#j=j*4
			lw $t4, 4($sp)			#b
			add $t4, $t4, $t2		#&b[j]
			move $a1, $t4

			li $t2, 1				#1
			move $a2, $t2

			lw $t2, 12($sp)			#size n
			move $a3, $t2

			addi $sp, $sp, -8		#add stack for 5th arg
			sw $t2, 0($sp)			#size n
	
			jal dot					#store res in $v0

			addi $sp, $sp, 8

			lw $a0, 0($sp)			#restore args to stack
			lw $a1, 4($sp)
			lw $a2, 8($sp)
			lw $a3, 12($sp)
			lw $t0, 16($sp)			#restore i to $t0
			lw $t1, 20($sp)			#restore j to $t1

			mul $t2, $t0, $a3		#i*n
			add $t2, $t2, $t1		#i*n+j
			li $t3, 4
			mul $t2, $t3, $t2		#*4
			add $t2, $t2, $a2		#&c[i*n+j]
			sw $v0, 0($t2)			#c[i*n+j] = $v0

			addi $t1, $t1, 1
			b mxm_loop2

		mxm_end2:
			addi $t0, $t0, 1
			b mxm_loop1

	mxm_end1:
		lw $ra, 24($sp)
		lw $fp, 20($sp)
		addi $sp, $sp, 40
		jr $ra
