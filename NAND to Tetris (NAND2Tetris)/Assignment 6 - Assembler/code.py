from n2t.core.assembler.data import comp_map, dest_map, jump_map


class Code:

    @classmethod
    def dest(cls, key: str) -> str:
        return dest_map[key]

    @classmethod
    def comp(cls, key: str) -> str:
        return comp_map[key]

    @classmethod
    def jump(cls, key: str) -> str:
        return jump_map[key]
