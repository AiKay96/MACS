from n2t.core.vm_translator.data import (
    addition_schema,
    call_end_schema,
    call_segment_schema,
    call_start_schema,
    constant_push_schema,
    eq_schema,
    goto_schema,
    if_schema,
    label_schema,
    local_pop_schema,
    local_push_schema,
    neg_schema,
    pointer_pop_schema,
    pointer_push_schema,
    return_end_schema,
    return_restore_schema,
    return_start_schema,
    start_schema,
    static_pop_schema,
    static_push_schema,
)


class CodeWriter:
    def __init__(self, file: str) -> None:
        self.name = file
        self.file = open(file, "w")
        self.label_count = 0

    def set_file_name(self, name: str) -> None:
        self.name = name

    def start_file(self) -> None:
        self.file.write(start_schema)
        self.write_call("Sys.init", 0)

    def write_arithmetic(self, command: str) -> None:
        if command == "add":
            self.file.write(addition_schema.format("+"))
        if command == "sub":
            self.file.write(addition_schema.format("-"))
        if command == "neg":
            self.file.write(neg_schema.format("-"))
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
            self.file.write(addition_schema.format("&"))
        if command == "or":
            self.file.write(addition_schema.format("|"))
        if command == "not":
            self.file.write(neg_schema.format("!"))

    def write_push_pop(self, command: str, segment: str, index: int) -> None:
        if command == "C_PUSH":
            if segment == "constant":
                self.file.write(f"@{index}\n")
                self.file.write(constant_push_schema)
            elif segment == "static":
                self.file.write(f"@{self.name}.{index}\n")
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
                self.file.write(f"@{self.name}.{index}\n")
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
                self.file.write(f"@{index}\n")
                self.file.write("D=A\n")
                self.file.write("@THIS\n")
                self.file.write(local_pop_schema)
            elif segment == "that":
                self.file.write(f"@{index}\n")
                self.file.write("D=A\n")
                self.file.write("@THAT\n")
                self.file.write(local_pop_schema)
            elif segment == "local":
                self.file.write(f"@{index}\n")
                self.file.write("D=A\n")
                self.file.write("@LCL\n")
                self.file.write(local_pop_schema)
            elif segment == "argument":
                self.file.write(f"@{index}\n")
                self.file.write("D=A\n")
                self.file.write("@ARG\n")
                self.file.write(local_pop_schema)

    def write_label(self, label: str) -> None:
        self.file.write(label_schema.format(label))

    def write_goto(self, label: str) -> None:
        self.file.write(goto_schema.format(label))

    def write_if(self, label: str) -> None:
        self.file.write(if_schema.format(label))

    def write_function(self, function_name: str, n_vars: int) -> None:
        self.label_count = 0
        self.file.write(f"({function_name})\n")
        for _ in range(n_vars):
            self.write_push_pop("C_PUSH", "constant", 0)

    def write_call(self, function_name: str, n_args: int) -> None:
        label = f"{function_name}_RET{self.label_count}"
        self.label_count += 1
        self.file.write(call_start_schema.format(label))
        self.file.write(call_segment_schema.format("LCL"))
        self.file.write(call_segment_schema.format("ARG"))
        self.file.write(call_segment_schema.format("THIS"))
        self.file.write(call_segment_schema.format("THAT"))
        self.file.write(call_end_schema.format(str(n_args + 5)))
        self.write_goto(function_name)
        self.file.write(f"({label})\n")

    def write_return(self) -> None:
        self.file.write(return_start_schema)
        self.file.write(return_restore_schema.format("THAT", "1"))
        self.file.write(return_restore_schema.format("THIS", "2"))
        self.file.write(return_restore_schema.format("ARG", "3"))
        self.file.write(return_restore_schema.format("LCL", "4"))
        self.file.write(return_end_schema)

    def close(self) -> None:
        self.file.close()
