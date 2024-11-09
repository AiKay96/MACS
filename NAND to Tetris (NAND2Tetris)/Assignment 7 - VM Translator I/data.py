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

addition_schema = "@SP\n" "AM=M-1\n" "D=M\n" "A=A-1\n"

neg_schema = "@SP\n" "A=M-1\n"

eq_schema = (
    "@SP\n"
    "AM=M-1\n"
    "D=M\n"
    "A=A-1\n"
    "D=M-D\n"
    "@EQUAL{}\n"
    "D;{}\n"
    "@SP\n"
    "A=M-1\n"
    "M=0\n"
    "@CONTINUE{}\n"
    "0;JMP\n"
    "(EQUAL{})\n"
    "@SP\n"
    "A=M-1\n"
    "M=-1\n"
    "(CONTINUE{})\n"
)

constant_push_schema = "D=A\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "M=M+1\n"

static_push_schema = "D=M\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "M=M+1\n"

pointer_push_schema = "D=M\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "M=M+1\n"

local_push_schema = "A=D+A\n" "D=M\n" "@SP\n" "A=M\n" "M=D\n" "@SP\n" "M=M+1\n"

static_pop_schema = "@SP\n" "AM=M-1\n" "D=M\n"

pointer_pop_schema = "@SP\n" "M=M-1\n" "@SP\n" "A=M\n" "D=M\n"

local_pop_schema = (
    "D=D+A\n" "@R13\n" "M=D\n" "@SP\n" "AM=M-1\n" "D=M\n" "@R13\n" "A=M\n" "M=D\n"
)
