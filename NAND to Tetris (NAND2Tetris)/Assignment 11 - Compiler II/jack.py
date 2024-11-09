from __future__ import annotations

import os
from dataclasses import dataclass

from n2t.core.compiler.vm_engine import CompilationEngine


@dataclass
class JackProgram:
    path: str

    @classmethod
    def load_from(cls, file_or_directory_name: str) -> JackProgram:
        return cls(file_or_directory_name)

    def compile(self) -> None:
        if os.path.isdir(self.path):
            for root, dirs, files in os.walk(self.path):
                for file in files:
                    if file.endswith(".jack"):
                        self.compile_file(os.path.join(root, file))
        else:
            self.compile_file(self.path)

    @staticmethod
    def compile_file(file: str) -> None:
        out_path, extension = os.path.splitext(file)
        CompilationEngine(file, out_path + ".vm").compile_class()
