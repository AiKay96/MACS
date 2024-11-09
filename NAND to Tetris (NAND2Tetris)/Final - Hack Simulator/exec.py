from __future__ import annotations

import os
from dataclasses import dataclass, field
from pathlib import Path
from typing import Iterable, Iterator

from n2t.core import Executor
from n2t.infra import AsmProgram
from n2t.infra.io import File, FileFormat


@dataclass
class ExecProgram:
    path: Path
    cycles: int
    hack_path: Path = field(default=Path())

    @classmethod
    def load_from(cls, file_name: str, cycles: int) -> ExecProgram:
        return cls(Path(file_name), cycles)

    def __post_init__(self) -> None:
        self.hack_path = self._convert_to_hack(self.path)
        FileFormat.hack.validate(self.hack_path)

    @staticmethod
    def _convert_to_hack(path: Path) -> Path:
        if path.suffix == ".asm":
            AsmProgram.load_from(str(path)).assemble()
            return FileFormat.hack.convert(path)
        return path

    def execute(self) -> None:
        json_file = File(FileFormat.json.convert(self.hack_path))
        json_file.save(Executor.execute(self._load_hack_file(), self.cycles))
        self.remove()

    def _load_hack_file(self) -> Iterable[str]:
        return File(self.hack_path).load()

    def remove(self) -> None:
        if self.hack_path != self.path:
            os.remove(self.hack_path)

    def __iter__(self) -> Iterator[str]:
        yield from self._load_hack_file()
