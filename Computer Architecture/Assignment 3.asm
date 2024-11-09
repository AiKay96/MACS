/*
მოცემულია ორი რიცხვი N, M და N რიცხვისაგან შედგენილი A მასივი. ყოველი რიცხვისთვის 1-დან  M-მდე, გამოთვალეთ თუ რამდენჯერ გვხვდება ის  A მასივში.
შესატანი მონაცემები:
პირველ ორ სტრიქონში ორი მთელი რიცხვი - N, M (1≤N≤100,1≤M≤100). მომდევნო N სტრიქონში თითოეულში თითო მთელი რიცხვი (1≤A_i≤M).
გამოსატანი მონაცემები:
გამოიტანეთ M სტრიქონი, სადაც i-ურ სტრიქონში ნაჩვენები იქნება, თუ რამდენჯერ გვხვდება i რიცხვი A მასივში.
შემავალი მონაცემების მაგალითი:
10 
5 
1 
2 
3 
4 
5 
3 
2 
1 
5 
3
შესაბამისი გამომავალი მონაცემი:
2 
2 
3 
1 
2
*/

.data
	prompt1: .asciiz "Enter number N: \n"
	prompt2: .asciiz "Enter number M: \n"
	arr: .space 400 # Allocate space for 100 integers (4 bytes each)
	count: .space 404 # Allocate space for 101 integers (4 bytes each)
	endl: .asciiz "\n"
.globl main
.text
	main:
	# Initialize count array with zeros
    	li $t0, 0       # $t0 = 0
    	li $t1, 101     # $t1 = 101 (array size)
    	la $t2, count   # $t2 = address of count
    	
	init_count_loop:
    	sw $zero, 0($t2)    # count[i] = 0
    	addi $t2, $t2, 4    # Increment count array address
    	addi $t0, $t0, 1    # Increment loop counter
    	blt $t0, $t1, init_count_loop # Loop if not done
	
	la $a0,prompt1 # Display prompt1 string
	li $v0,4
	syscall

        li $v0,5 # Read N into $t0
	syscall
	move $t0,$v0
	
	la $a0,prompt2 # Display prompt2 string
	li $v0,4
	syscall

	li $v0,5 # Read M into $t1
	syscall
	move $t1,$v0
	
	la $t3, arr	# $t3 = address of arr
	
	sll $t0, $t0, 2
	add $t4, $t3, $t0 # $t4 = lastAddress (address after arr)
	
	read_loop_start:
	
    	bge $t3, $t4, read_loop_end # Exit loop if arr >= lastAddress
	li $v0, 5
	syscall
	sw $v0, 0($t3) # cin arr+i
	
	sll $t5, $v0, 2 
	add $t5, $t5, $t2 # address for count[arr[i]]
	
	lw $t6, ($t5)
	addi $t6, $t6, 1
	sw $t6, ($t5) # count increment
	
	addi $t3, $t3, 4    # arr++ (next index)
	j read_loop_start
	
	read_loop_end:
	
	sll $t1, $t1, 2
	add $t2, $t2, 4		# $t2 = count[1]
	add $t4, $t2, $t1 	# $t4 = lastAddress (address after count)
	
	print_loop_start:
	
	bge $t2, $t4, print_loop_end # Exit loop if count >= lastAddress
	
	la $a0,endl
	li $v0,4
	syscall	# Print endl
	
	lw $a0, ($t2)
	li $v0,1
	syscall	# Print count + i
	
	addi $t2, $t2, 4    # count++ (next index)
	j print_loop_start
	
	print_loop_end:
		
	li $v0,10
	syscall