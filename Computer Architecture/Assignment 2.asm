/*
https://codeforces.com/group/MWSDmqGsZm/contest/219856/problem/W
Given a number Q and a string S. If Q is equal to 1 then print S after encrypting it otherwise, print S after decrypting it.
Key = "PgEfTYaWGHjDAmxQqFLRpCJBownyUKZXkbvzIdshurMilNSVOtec#@_!=.+-*/".
Original = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789".
Note:
- In Encryption: For each letter x in "Original" replace it by the equivalent letter y from "Key"
- In Decryption: For each letter y in "Key" replace it by the equivalent letter x from "Original".
- Key and Original have the same length.

Input
The first line contains a number Q (1≤Q≤2).
The second line contains a string S (1≤|S|≤105) where |S| is the length of the string and it consists of lowercase and uppercase English letters.

Examples
1
Egypt

ZaoQR

2
ZaoQR

Egypt
*/

.data
key:      	.asciiz "PgEfTYaWGHjDAmxQqFLRpCJBownyUKZXkbvzIdshurMilNSVOtec#@_!=.+-*/"
original: 	.asciiz "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
s:      	.space 1000001    
input_prompt: 	.asciiz "Q: "
string_prompt: 	.asciiz "S: "

.text
.globl main
main:
	    li $v0, 4
	    la $a0, input_prompt
	    syscall
	
	    li $v0, 5
	    syscall
	    move $t0, $v0

	    li $v0, 4
	    la $a0, string_prompt
	    syscall

	    li $v0, 8
	    la $a0, s
	    li $a1, 1000000
	    syscall
    
	    li $t1, 0 				# i = 0
	    outer_loop:
	    lb $t2, s($t1) 			# t2 = s[i]
	    beqz $t2, outer_loop_end		# if s[i] == null break
	    
	    li $t3, 0				# j = 0
	    inner_loop:
	    bge $t3, 62, inner_loop_end		# if j >= size break
	    
	    beq $t0, 1, encrypt_if              # if q == 1 try encription
    	    beq $t0, 2, decrypt_if		# if q == 2 try decription
    	    
    	    encrypt_if:
    	    lb $t4, original($t3)		# t4 = original[j]
    	    bne $t2, $t4, continue		# if s[i] != original[j] continue
    	    

	    lb $a0, key($t3)			
	    li $v0, 11
	    syscall				# print key[j]
	    
	    j continue
	    
	    decrypt_if:
    	    lb $t4, key($t3)			# t4 = key[j]
    	    bne $t2, $t4, continue		# if s[i] != key[j] continue
    	    

	    lb $a0, original($t3)			
	    li $v0, 11
	    syscall				# print original[j]
	    
	    continue:
	    addi $t3, $t3, 1			# j++
	    j inner_loop
	    
	    inner_loop_end:
	    addi $t1, $t1, 1			# i++
	    j outer_loop
	    
	    outer_loop_end:    
	    li $v0, 10
	    syscall