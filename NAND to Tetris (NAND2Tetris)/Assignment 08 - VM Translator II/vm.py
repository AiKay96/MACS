from __future__ import annotations

import os
from dataclasses import dataclass

from n2t.core.vm_translator.parser import Parser
from n2t.core.vm_translator.writer import CodeWriter


@dataclass
class VmProgram:
    file: str
    directory: str

    @classmethod
    def load_from(cls, file_or_directory_name: str) -> VmProgram:
        cls.file = file_or_directory_name
        cls.directory = file_or_directory_name
        return cls(file_or_directory_name, file_or_directory_name)

    def translate(self) -> None:
        if self.file.endswith(".vm"):
            output = self.file.split(".vm")[0] + ".asm"
            parser = Parser(self.file)
            code_writer = CodeWriter(output)
            self.translate_file(parser, code_writer)
        else:
            output = self.directory + self.directory.split("/")[-2] + ".asm"
            code_writer = CodeWriter(output)
            files = os.listdir(self.directory)
            if "Sys.vm" in files:
                code_writer.set_file_name("Sys.vm")
                code_writer.start_file()
                current_file = self.directory + "/Sys.vm"
                self.file = current_file
                parser = Parser(current_file)
                self.translate_file(parser, code_writer)
            for file in files:
                if file.endswith(".vm") and file != "Sys.vm":
                    code_writer.set_file_name(file)
                    current_file = self.directory + "/" + file
                    self.file = current_file
                    parser = Parser(current_file)
                    self.translate_file(parser, code_writer)
        code_writer.close()

    @staticmethod
    def translate_file(parser: Parser, code_writer: CodeWriter) -> None:
        while parser.has_more_lines():
            parser.advance()
            command_type = parser.command_type()
            if command_type == "C_ARITHMETIC":
                code_writer.write_arithmetic(parser.arg1())
            elif command_type == "C_PUSH" or command_type == "C_POP":
                code_writer.write_push_pop(command_type, parser.arg1(), parser.arg2())
            elif command_type == "C_LABEL":
                code_writer.write_label(parser.arg1())
            elif command_type == "C_IF":
                code_writer.write_if(parser.arg1())
            elif command_type == "C_GOTO":
                code_writer.write_goto(parser.arg1())
            elif command_type == "C_FUNCTION":
                code_writer.write_function(parser.arg1(), parser.arg2())
            elif command_type == "C_RETURN":
                code_writer.write_return()
            elif command_type == "C_CALL":
                n_args = 0
                if parser.arg2():
                    n_args = parser.arg2()
                code_writer.write_call(parser.arg1(), n_args)
