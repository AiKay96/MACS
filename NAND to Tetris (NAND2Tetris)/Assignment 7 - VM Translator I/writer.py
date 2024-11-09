from n2t.infra.data import (
    addition_schema,
    constant_push_schema,
    eq_schema,
    local_pop_schema,
    local_push_schema,
    neg_schema,
    pointer_pop_schema,
    pointer_push_schema,
    static_pop_schema,
    static_push_schema,
)


class CodeWriter:
    def __init__(self, file: str) -> None:
        self.file = open(file, "w")
        self.label_count = 0

    def write_arithmetic(self, command: str) -> None:
        if command == "add":
            self.file.write(addition_schema)
            self.file.write("M=M+D\n")
        if command == "sub":
            self.file.write(addition_schema)
            self.file.write("M=M-D\n")
        if command == "neg":
            self.file.write(neg_schema)
            self.file.write("M=-M\n")
        if command == "eq":
            self.file.write(
                eq_schema.format(
                    self.label_count,
                    "JEQ",
                    self.label_count,
                    self.label_count,
                    self.label_count,
                )
            )
            self.label_count += 1
        if command == "gt":
            self.file.write(
                eq_schema.format(
                    self.label_count,
                    "JGT",
                    self.label_count,
                    self.label_count,
                    self.label_count,
                )
            )
            self.label_count += 1
        if command == "lt":
            self.file.write(
                eq_schema.format(
                    self.label_count,
                    "JLT",
                    self.label_count,
                    self.label_count,
                    self.label_count,
                )
            )
            self.label_count += 1
        if command == "and":
            self.file.write(addition_schema)
            self.file.write("M=M&D\n")
        if command == "or":
            self.file.write(addition_schema)
            self.file.write("M=M|D\n")
        if command == "not":
            self.file.write(neg_schema)
            self.file.write("M=!M\n")

    def write_push_pop(self, command: str, segment: str, index: int) -> None:
        if command == "C_PUSH":
            if segment == "constant":
                self.file.write(f"@{index}\n")
                self.file.write(constant_push_schema)
            elif segment == "static":
                self.file.write(f"@{index + 16}\n")
                self.file.write(static_push_schema)
            elif segment == "temp":
                self.file.write(f"@{index + 5}\n")
                self.file.write(static_push_schema)
            elif segment == "pointer" and index:
                self.file.write("@THAT\n")
                self.file.write(pointer_push_schema)
            elif segment == "pointer" and not index:
                self.file.write("@THIS\n")
                self.file.write(pointer_push_schema)
            elif segment == "this":
                self.file.write("@THIS\n")
                self.file.write("D=M\n")
                self.file.write(f"@{index}\n")
                self.file.write(local_push_schema)
            elif segment == "that":
                self.file.write("@THAT\n")
                self.file.write("D=M\n")
                self.file.write(f"@{index}\n")
                self.file.write(local_push_schema)
            elif segment == "local":
                self.file.write("@LCL\n")
                self.file.write("D=M\n")
                self.file.write(f"@{index}\n")
                self.file.write(local_push_schema)
            elif segment == "argument":
                self.file.write("@ARG\n")
                self.file.write("D=M\n")
                self.file.write(f"@{index}\n")
                self.file.write(local_push_schema)

        elif command == "C_POP":
            if segment == "static":
                self.file.write(static_pop_schema)
                self.file.write(f"@{index + 16}\n")
                self.file.write("M=D\n")
            elif segment == "temp":
                self.file.write(static_pop_schema)
                self.file.write(f"@{index + 5}\n")
                self.file.write("M=D\n")
            elif segment == "pointer" and index:
                self.file.write(pointer_pop_schema)
                self.file.write("@THAT\n")
                self.file.write("M=D\n")
            elif segment == "pointer" and not index:
                self.file.write(pointer_pop_schema)
                self.file.write("@THIS\n")
                self.file.write("M=D\n")
            elif segment == "this":
                self.file.write("@THIS\n")
                self.file.write("D=M\n")
                self.file.write(f"@{index}\n")
                self.file.write(local_pop_schema)
            elif segment == "that":
                self.file.write("@THAT\n")
                self.file.write("D=M\n")
                self.file.write(f"@{index}\n")
                self.file.write(local_pop_schema)
            elif segment == "local":
                self.file.write("@LCL\n")
                self.file.write("D=M\n")
                self.file.write(f"@{index}\n")
                self.file.write(local_pop_schema)
            elif segment == "argument":
                self.file.write("@ARG\n")
                self.file.write("D=M\n")
                self.file.write(f"@{index}\n")
                self.file.write(local_pop_schema)

    def close(self) -> None:
        self.file.close()
