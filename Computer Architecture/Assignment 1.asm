/*
მოცემულია ორი მთელი რიცხვი N და M (2<=N<M<=1000). დაწერეთ პროგრამა, რომელიც გამოიტანს ყველა მარტივ რიცხვს [N,M] შუალედიდან საზღვრების ჩათვლით.
შესატანი მონაცემების მაგალითი:
25
45
გამოსატანი მონაცემები: 29 31 37 41 43
*/

.data
prompt1: .asciiz "Enter starting number N: \n"
prompt2: .asciiz "Enter ending number M: \n"
invalid: .asciiz "Invalid input! \n"
space: .asciiz " "
.globl main
.text
	main:
	
	la $a0,prompt1 # Display prompt1 string
	li $v0,4
	syscall

        li $v0,5 # Read N into $t0
	syscall
	move $t0,$v0
	
	la $a0,prompt2 # display prompt2 string
	li $v0,4
	syscall

	li $v0,5 # Read M into $t1
	syscall
	move $t1,$v0
	
	ble $t0, $t1, outer_loop  # If N <= M, start loop
	j invalid_input
	
	outer_loop:
	blt $t0, 2, continue_outer_loop_if # Skip numbers before 2
	
	li $t3, 2          # Load the value 2 into $t3
    	beq $t0, $t3, is_prime # 2 is prime
	
	li $t3, 0 # Initialize t3 to false (is not prime)
    		# Inner loop
    		li $t2, 2          # Initialize j = 2
		inner_loop:
    		# Your inner loop body code goes here
		div $t0, $t2     # Divide t0 by t2
    		mfhi $t4         # Get the remainder
    		beqz $t4, not_prime  # If remainder is 0
    		j continue_inner_loop
    		
		not_prime:
    		li $t3, 1        # Set t3 to true (is not prime)
    		j continue_outer_loop_if
    		
    		continue_inner_loop:
    		addi $t2, $t2, 1   # Increment the inner loop variable (j)
    		blt $t2, $t0, inner_loop  # Branch back to inner loop if j < N
    		
    	beqz $t3, is_prime
    	j continue_outer_loop_if
    	
    	is_prime:
    	move $a0,$t0 # Print prime number
	li $v0,1
	syscall
	la $a0,space # Print space
	li $v0,4
	syscall
    	
    	continue_outer_loop_if:
    	addi $t0, $t0, 1   # Increment the outer loop variable (i)
    	ble $t0, $t1, outer_loop  # Branch back to outer loop if i <= M
	
	end_outer_loop:
   	# Code after the outer loop
	li $v0,10
	syscall
	
	invalid_input:
	la $a0,invalid # display invalid string
	li $v0,4
	syscall
	j main
