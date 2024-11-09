import copy

from n2t.core.assembler.data import symbol_table


class SymbolTable:
    def __init__(self) -> None:
        self.table = copy.deepcopy(symbol_table)

    def add_entry(self, symbol: str, address: int) -> None:
        self.table[symbol] = address

    def contains(self, symbol: str) -> bool:
        return symbol in self.table

    def get_address(self, symbol: str) -> int:
        return self.table.get(symbol, -1)
