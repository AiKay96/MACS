from typing import TextIO


class VMWriter:
    def __init__(self, output_file: str) -> None:
        self.output_file: TextIO = open(output_file, "w")

    def write_push(self, segment: str, index: int) -> None:
        self.output_file.write(f"push {segment} {index}\n")

    def write_pop(self, segment: str, index: int) -> None:
        self.output_file.write(f"pop {segment} {index}\n")

    def write_arithmetic(self, command: str) -> None:
        self.output_file.write(command + "\n")

    def write_label(self, label: str) -> None:
        self.output_file.write(f"label {label}\n")

    def write_goto(self, label: str) -> None:
        self.output_file.write(f"goto {label}\n")

    def write_if(self, label: str) -> None:
        self.output_file.write(f"if-goto {label}\n")

    def write_call(self, name: str, n_args: int) -> None:
        self.output_file.write(f"call {name} {n_args}\n")

    def write_function(self, name: str, n_vars: int) -> None:
        self.output_file.write(f"function {name} {n_vars}\n")

    def write_return(self) -> None:
        self.output_file.write("return\n")

    def close(self) -> None:
        self.output_file.close()
