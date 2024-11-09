from __future__ import annotations

from dataclasses import dataclass
from typing import Iterable

from n2t.core.assembler.code import Code
from n2t.core.assembler.parser import Parser
from n2t.core.assembler.symbol_table import SymbolTable


@dataclass
class Assembler:
    @classmethod
    def create(cls) -> Assembler:
        return cls()

    def assemble(self, assembly: Iterable[str]) -> Iterable[str]:
        symbol_table = SymbolTable()
        parser = Parser(assembly)
        i = 0

        while parser.has_more_lines():
            instruction_type = parser.instructionType()

            if instruction_type == "COMMENT":
                parser.advance()
                continue

            if instruction_type == "L_INSTRUCTION":
                symbol = parser.symbol()
                if not symbol_table.contains(symbol):
                    symbol_table.add_entry(symbol, i)
                else:
                    raise ValueError(f"Symbol '{symbol}' already defined")
            else:
                i += 1

            parser.advance()

        parser.reset()
        instructions = []
        i = 16
        while parser.has_more_lines():
            instruction_type = parser.instructionType()

            if instruction_type == "COMMENT" or instruction_type == 'L_INSTRUCTION':
                parser.advance()
                continue

            if instruction_type == "A_INSTRUCTION":
                symbol = parser.symbol()
                if symbol.isdigit():
                    address = int(symbol)
                else:
                    if symbol_table.contains(symbol):
                        address = symbol_table.get_address(symbol)
                    else:
                        symbol_table.add_entry(symbol, address := i)
                        i += 1
                instruction = format(address, '016b')
            else:
                instruction = ('111'
                               + Code.comp(parser.comp())
                               + Code.dest(parser.dest())
                               + Code.jump(parser.jump()))
            instructions.append(instruction + "\r")
            parser.advance()

        return instructions
