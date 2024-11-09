import re

from n2t.core.compiler.data import (
    KEYWORDS,
    SYMBOLS,
    parser_regex,
)


class JackTokenizer:
    def __init__(self, input_file: str):
        self.index: int = 0
        self.tokens: list[str] = []
        self._load_and_tokenize(input_file)

    def _load_and_tokenize(self, input_file: str) -> None:
        with open(input_file, "r") as file:
            code = file.read()
        code = self._remove_comments(code)
        self.tokens = re.compile(parser_regex).findall(code)
        self.tokens = [token for token in self.tokens if token.strip()]

    @staticmethod
    def _remove_comments(code: str) -> str:
        code = re.sub(r"/\*\*.*?\*/", "", code, flags=re.DOTALL)
        code = re.sub(r"/\*.*?\*/", "", code, flags=re.DOTALL)
        code = re.sub(r"//.*", "", code)

        return code

    def has_more_tokens(self) -> bool:
        return self.index < len(self.tokens)

    def advance(self) -> None:
        self.index += 1

    def token_type(self) -> str:
        token = self.tokens[self.index]
        if token in KEYWORDS:
            return "keyword"
        if token in SYMBOLS:
            return "symbol"
        if token.isdigit() and 0 <= int(token) <= 32767:
            return "integer_constant"
        if token.startswith('"') and token.endswith('"'):
            return "string_constant"
        return "identifier"

    def keyword(self) -> str:
        return self.tokens[self.index]

    def symbol(self) -> str:
        return self.tokens[self.index]

    def identifier(self) -> str:
        return self.tokens[self.index]

    def int_val(self) -> str:
        return self.tokens[self.index]

    def string_val(self) -> str:
        return self.tokens[self.index][1:-1]
