from dataclasses import dataclass


@dataclass
class Variable:
    name: str
    type: str
    kind: str
    index: int


class SymbolTable:
    def __init__(self) -> None:
        self.table: dict[str, Variable] = {}
        self.indexes = {"static": 0, "field": 0, "argument": 0, "local": 0}

    def reset(self) -> None:
        self.table = {}
        self.indexes = {"static": 0, "field": 0, "argument": 0, "local": 0}

    def define(self, name: str, type: str, kind: str) -> None:
        if kind == "field":
            kind = "this"
        if kind not in self.indexes:
            self.indexes[kind] = 0
        self.table[name] = Variable(name, type, kind, self.indexes[kind])
        self.indexes[kind] += 1

    def var_count(self, kind: str) -> int:
        if kind == "field":
            kind = "this"
        return self.indexes[kind]

    def kind_of(self, name: str) -> str:
        if name not in self.table:
            return "not found"
        return self.table[name].kind

    def type_of(self, name: str) -> str:
        if name not in self.table:
            return "not found"
        return self.table[name].type

    def index_of(self, name: str) -> int:
        if name not in self.table:
            return -1
        return self.table[name].index
