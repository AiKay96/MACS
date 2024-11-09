from __future__ import annotations

from dataclasses import dataclass, field
from typing import Dict, List

from n2t.core.executor.data import COMP_MAPPING, HALF_INT, MAX_INT


@dataclass
class Cpu:
    instructions: List[str]
    a: int = 0
    d: int = 0
    pc: int = 0
    ram: Dict[str, int] = field(default_factory=dict)

    def execute_next_instruction(self) -> None:
        if self.has_instructions():
            instruction = self.instructions[self.pc]
            if instruction[0] == "0":
                self._execute_a_instruction(instruction)
            else:
                self._execute_c_instruction(instruction)
            self.pc += 1

    def has_instructions(self) -> bool:
        return self.pc < len(self.instructions)

    def _execute_a_instruction(self, instruction: str) -> None:
        binary = instruction[1:16]
        self.a = int(binary, 2)

    def _execute_c_instruction(self, instruction: str) -> None:
        comp = instruction[3:10]
        dest = instruction[10:13]
        jump = instruction[13:16]

        value = self._compute_value(comp)
        self.store_in_dest(value, dest)
        self._evaluate_jump(value, jump)

    def _compute_value(self, comp: str) -> int:
        try:
            return int(eval(COMP_MAPPING[comp]))
        except KeyError:
            self.ram[str(self.a)] = 0
            return 0

    def store_in_dest(self, value: int, dest: str) -> None:
        if dest[2] == "1":
            self.ram[str(self.a)] = value
        if dest[1] == "1":
            self.d = value
        if dest[0] == "1":
            self.a = value

    def _evaluate_jump(self, value: int, jump: str) -> None:
        if jump == "000":
            return
        elif self._should_jump(value, jump):
            self.pc = self.a - 1

    @staticmethod
    def _should_jump(value: int, jump: str) -> bool:
        jump_conditions = {
            "001": 0 < value < HALF_INT,
            "010": value == 0,
            "011": 0 <= value < HALF_INT,
            "100": HALF_INT <= value < MAX_INT,
            "101": value != 0,
            "110": HALF_INT <= value < MAX_INT or value == 0,
            "111": True,
        }
        return jump_conditions.get(jump, False)
