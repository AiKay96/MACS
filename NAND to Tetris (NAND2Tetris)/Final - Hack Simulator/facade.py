from __future__ import annotations

import json
from dataclasses import dataclass
from typing import Iterable

from n2t.core.executor.cpu import Cpu


@dataclass
class Executor:
    @classmethod
    def create(cls) -> Executor:
        return cls()

    @staticmethod
    def execute(hack: Iterable[str], cycles: int) -> Iterable[str]:
        cpu = Cpu(list(hack))
        current_cycle = 0

        while Executor._should_continue(cpu, cycles, current_cycle):
            cpu.execute_next_instruction()
            current_cycle += 1

        return Executor._format_output(cpu)

    @staticmethod
    def _should_continue(cpu: Cpu, cycles: int, current_cycle: int) -> bool:
        return cpu.has_instructions() and (cycles == -1 or current_cycle < cycles)

    @staticmethod
    def _format_output(cpu: Cpu) -> Iterable[str]:
        sorted_ram = dict(sorted(cpu.ram.items(), key=lambda x: int(x[0])))
        modified_ram = {
            key: value - 0x10000 if value in (0xFFFF, 0x8000) else value
            for key, value in sorted_ram.items()
        }
        json_output = json.dumps({"RAM": modified_ram}, indent=2)
        return json_output.split("\n")
