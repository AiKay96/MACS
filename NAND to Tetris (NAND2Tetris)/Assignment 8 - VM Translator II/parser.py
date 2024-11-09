from n2t.core.vm_translator.data import command_types


class Parser:
    def __init__(self, file: str) -> None:
        self.lines = open(file, "r").readlines()
        self.ind = -1
        self.instruction = ""

    def has_more_lines(self) -> bool:
        return self.ind + 1 != len(self.lines)

    def advance(self) -> None:
        self.ind += 1
        self.instruction = self.lines[self.ind].strip()

    def command_type(self) -> str | None:
        if not self.instruction.strip():
            return None
        return command_types.get(self.instruction.split()[0])

    def arg1(self) -> str:
        if self.command_type() == "C_ARITHMETIC":
            return self.instruction.split()[0]
        else:
            return self.instruction.split()[1]

    def arg2(self) -> int:
        return int(self.instruction.split()[2])
