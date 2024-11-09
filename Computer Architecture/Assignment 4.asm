/*
https://codeforces.com/group/MWSDmqGsZm/contest/223338/problem/P

Given a number N
. Print the number of digits of N!.

Input
Only one line contains a number N (1≤N≤105).

Output
Print one line that contains the following respectively:

"Number of digits of " + N + "! is " + the number of digits.

Example
5

Number of digits of 5! is 3
*/

.data
prompt:     .asciiz "Enter a number: "
result1:    .asciiz "Number of digits of "
result2:    .asciiz "! is "
newline:    .asciiz "\n"

zero: .float 0.0
one:  .float 1.0
two:  .float 2.0
ln10: .float 2.302585

.text
.globl main

main:
    li $v0, 4
    la $a0, prompt
    syscall		# Print prompt

    li $v0, 5
    syscall		# Read integer
    move $t0, $v0	# Store value
    
    li $v0, 4
    la $a0, result1
    syscall		# Print first part

    li $v0, 1
    move $a0, $t0
    syscall		# Print entered number

    li $v0, 4
    la $a0, result2
    syscall		# Print second part
    
    move $a0, $t0       # Pass number as argument
    jal findDigits	# Call function

    li $v0, 1
    move $a0, $t0
    syscall		# Print answer

    li $v0, 4
    la $a0, newline
    syscall		# Print end line

    li $v0, 10
    syscall		# Exit

findDigits:		# Args: n
    bltz $a0, return_zero	# Check if n < 0
    
    li $t0, 1
    ble $a0, $t0, return_one	# Check if n <= 1
    
    l.s $f10, zero	# Store constant
    l.s $f11, one	# Store constant
    l.s $f12, two	# Store constant
    l.s $f13, ln10	# Store constant
    
    l.s $f14, zero  	# digits = 0.0
    li $t0, 2       	# i = 2	
    
    loop:

  	bgt $t0, $a0, end_loop  # Exit loop if i > n

	move $a1, $a0		# Store variable
	move $a2, $t0		# Store variable
	move $v1, $ra 		# Store return address
	
	move $a0, $t0           # Pass i as argument
	jal log_10		# Call funciton
	
	move $a0, $a1		# Restore variable
	move $t0, $a2		# Restore variable
	move $ra, $v1		# Restore return address
	
    	add.s $f14, $f14, $f0 	# digits += f0

	addi $t0, $t0, 1        # Increment i
    	
   	j loop
    
    end_loop:
      
    cvt.w.s $f14, $f14     
    mfc1 $t0, $f14  	 # Convert digits to integer    
    addi $t0, $t0, 1 	 # Calculate and Store return value to $t0
       
    j findDigits_end

log_10:
    # Args: x
    mtc1 $a0, $f0	
    cvt.s.w $f0, $f0 	# Convert x to float
    
    sub.s $f1, $f0, $f11    # x - 1
    add.s $f2, $f0, $f11    # x + 1
    div.s $f0, $f1, $f2     # (f0) term = (x - 1) / (x + 1)
    mul.s $f1, $f0, $f0     # (f1) y = term * term
    mov.s $f2, $f10         # (f2) result = 0.0
    mov.s $f3, $f11         # (f3) n = 1.0
    
    li $t0, 0               # i = 0
    li $t1, 50              # loop limit = 50
    
    loop_log:
    	bge $t0, $t1, end_loop_log  # Exit loop if i >= 50

    	div.s $f4, $f0, $f3     # term / n
    	add.s $f2, $f2, $f4     # result += term / n

    	mul.s $f0, $f0, $f1     # term *= y
    	add.s $f3, $f3, $f12    # n += 2.0

    	addi $t0, $t0, 1        # Increment i
    	j loop_log
    	
    end_loop_log:
    mul.s $f2, $f2, $f12  	# Multiply result by 2.0

    div.s $f0, $f2, $f13	# Calculate and Store return value: lnx/ln10 to $f0
    
    jr $ra
    
return_zero:
    li $t0, 0			# Store return value to $t0
    j findDigits_end

return_one:
    li $t0, 1			# Store return value to $t0
    j findDigits_end

findDigits_end:
    jr $ra
