command_types = {
    "add": "C_ARITHMETIC",
    "sub": "C_ARITHMETIC",
    "neg": "C_ARITHMETIC",
    "eq": "C_ARITHMETIC",
    "gt": "C_ARITHMETIC",
    "lt": "C_ARITHMETIC",
    "and": "C_ARITHMETIC",
    "or": "C_ARITHMETIC",
    "not": "C_ARITHMETIC",
    "push": "C_PUSH",
    "pop": "C_POP",
    "label": "C_LABEL",
    "goto": "C_GOTO",
    "if-goto": "C_IF",
    "function": "C_FUNCTION",
    "return": "C_RETURN",
    "call": "C_CALL",
}

addition_schema = (
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "@SP\n"
    "AM=M-1\n"
    "D=M{}D\n"
    "@SP\n"
    "A=M\n"
    "M=D\n"
    "@SP\n"
    "AM=M+1\n"
)

neg_schema = "@SP\n" "AM=M-1\n" "D={}M\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "AM=M+1\n"

eq_schema = (
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "@SP\n"
    "AM=M-1\n"
    "D=M-D\n"
    "@EQ{}\n"
    "D;{}\n"
    "@SP\n"
    "A=M\n"
    "M=0\n"
    "@CONTINUE{}\n"
    "0;JMP\n"
    "(EQ{})\n"
    "@SP\n"
    "A=M\n"
    "M=-1\n"
    "(CONTINUE{})\n"
    "@SP\n"
    "AM=M+1\n"
)

constant_push_schema = "D=A\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "AM=M+1\n"

static_push_schema = "D=M\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "M=M+1\n"

pointer_push_schema = "D=M\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "M=M+1\n"

local_push_schema = "A=D+A\n" "D=M\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "AM=M+1\n"

static_pop_schema = "@SP\n" "AM=M-1\n" "D=M\n"

pointer_pop_schema = "@SP\n" "M=M-1\n" "@SP\n" "A=M\n" "D=M\n"

local_pop_schema = (
    "A=M\n"
    "A=A+D\n"
    "D=A\n"
    "@TEMP\n"
    "M=D\n"
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "@TEMP\n"
    "A=M\n"
    "M=D\n"
)

label_schema = "({})\n"

goto_schema = "@{}\n" "0;JMP\n"

if_schema = "@SP\n" "AM=M-1\n" "D=M\n" "@{}\n" "D;JNE\n"

call_start_schema = "@{}\n" "D=A\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "AM=M+1\n"

call_segment_schema = "@{}\n" "D=M\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "AM=M+1\n"

call_end_schema = (
    "@SP\n" "D=M\n" "@{}\n" "D=D-A\n" "@ARG\n" "M=D\n" "@SP\n" "D=M\n" "@LCL\n" "M=D\n"
)

return_start_schema = (
    "@LCL\n"
    "D=M\n"
    "@BOX\n"
    "M=D\n"
    "@BOX\n"
    "D=M\n"
    "@5\n"
    "A=D-A\n"
    "D=M\n"
    "@RET\n"
    "M=D\n"
    "@0\n"
    "D=A\n"
    "@ARG\n"
    "A=M\n"
    "A=A+D\n"
    "D=A\n"
    "@TEMP\n"
    "M=D\n"
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "@TEMP\n"
    "A=M\n"
    "M=D\n"
    "@ARG\n"
    "D=M\n"
    "D=D+1\n"
    "@SP\n"
    "M=D\n"
)

return_restore_schema = "@BOX\n" "D=M\n" "@{}\n" "A=D-A\n" "D=M\n" "@{}\n" "M=D\n"

return_end_schema = "@RET\n" "A=M\n" "0;JMP\n"

start_schema = "@256\n" "D=A\n" "@SP\n" "M=D\n"
