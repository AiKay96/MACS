from __future__ import annotations

import re
from typing import Iterable

from n2t.core.assembler.data import patterns


class Parser:
    def __init__(self, assembly: Iterable[str]) -> None:
        self.assembly = list(assembly)
        self.format_assembly()
        self.pc = 0

    def format_assembly(self) -> None:
        self.assembly = [line.split('//')[0].strip() for line in self.assembly]

    def reset(self) -> None:
        self.pc = 0

    def advance(self) -> None:
        self.pc += 1

    def currentInstruction(self) -> str:
        return self.assembly[self.pc]

    def has_more_lines(self) -> bool:
        return self.pc < len(self.assembly)

    def instructionType(self) -> str:
        line = self.currentInstruction()
        for instruction_type, pattern in patterns.items():
            if bool(re.match(pattern, line)):
                return instruction_type
        raise ValueError("Invalid instruction format")

    def symbol(self) -> str:
        instruction_type = self.instructionType()
        if instruction_type == "A_INSTRUCTION":
            return self.currentInstruction()[1:]
        elif instruction_type == "L_INSTRUCTION":
            return self.currentInstruction()[1:-1]
        else:
            raise ValueError("Current instruction is not A or L instruction")

    def dest(self) -> str:
        if self.instructionType() != "C_INSTRUCTION":
            raise ValueError("Current instruction is not a C-instruction")

        instruction = self.currentInstruction()
        parts = instruction.split("=")
        return parts[0].strip() if len(parts) > 1 else ""

    def comp(self) -> str:
        if self.instructionType() != "C_INSTRUCTION":
            raise ValueError("Current instruction is not a C-instruction")

        instruction = self.currentInstruction()
        parts = instruction.split("=")
        if len(parts) > 1:
            return parts[1].split(";")[0].strip()
        else:
            return instruction.split(";")[0].strip()

    def jump(self) -> str:
        if self.instructionType() != "C_INSTRUCTION":
            raise ValueError("Current instruction is not a C-instruction")

        instruction = self.currentInstruction()
        return instruction.split(';')[1] if ";" in instruction else ""
