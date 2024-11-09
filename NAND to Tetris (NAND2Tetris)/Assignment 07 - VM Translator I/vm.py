from __future__ import annotations

from dataclasses import dataclass

from n2t.infra.parser import Parser
from n2t.infra.writer import CodeWriter


@dataclass
class VmProgram:
    file: str

    @classmethod
    def load_from(cls, file_or_directory_name: str) -> VmProgram:
        cls.file = file_or_directory_name
        return cls(file_or_directory_name)

    def translate(self) -> None:
        output = self.file.split(".vm")[0] + ".asm"
        parser = Parser(self.file)
        code_writer = CodeWriter(output)
        while parser.has_more_lines():
            parser.advance()
            command_type = parser.command_type()
            if command_type == "C_ARITHMETIC":
                code_writer.write_arithmetic(parser.arg1())
            elif command_type == "C_PUSH" or command_type == "C_POP":
                code_writer.write_push_pop(command_type, parser.arg1(), parser.arg2())
        code_writer.close()
