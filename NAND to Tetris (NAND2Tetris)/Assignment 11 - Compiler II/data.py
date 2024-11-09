from enum import Enum


class TokenType(Enum):
    KEYWORD = "keyword"
    SYMBOL = "symbol"
    IDENTIFIER = "identifier"
    INT_CONST = "integer_constant"
    STRING_CONST = "string_constant"


class TokenKeyWord(Enum):
    CLASS = "class"
    METHOD = "method"
    FUNCTION = "function"
    CONSTRUCTOR = "constructor"
    INT = "int"
    BOOLEAN = "boolean"
    CHAR = "char"
    VOID = "void"
    VAR = "var"
    STATIC = "static"
    FIELD = "field"
    LET = "let"
    DO = "do"
    IF = "if"
    ELSE = "else"
    WHILE = "while"
    RETURN = "return"
    TRUE = "true"
    FALSE = "false"
    NULL = "null"
    THIS = "this"


parser_regex = (
    r'"[^"\n]*"'
    r"|class|constructor|function|method|field|static|var|int|char|"
    r"boolean|void|true|false|null|this|let|double|do|if|else|while|return"
    r"|[{}()\[\].,;+\-*/&|<>=~]|\d+|\w+"
)

KEYWORDS = [
    "class",
    "constructor",
    "function",
    "method",
    "field",
    "static",
    "var",
    "int",
    "char",
    "boolean",
    "void",
    "true",
    "false",
    "null",
    "this",
    "let",
    "do",
    "if",
    "else",
    "while",
    "return",
]

SYMBOLS = [
    "{",
    "}",
    "(",
    ")",
    "[",
    "]",
    ".",
    ",",
    ";",
    "+",
    "-",
    "*",
    "/",
    "&",
    "|",
    "<",
    ">",
    "=",
    "~",
]

TOKEN_TYPES = ["KEYWORD", "SYMBOL", "IDENTIFIER", "INT_CONST", "STRING_CONST"]

OPERATORS = ["+", "-", "*", "/", "&", "|", "<", ">", "="]

UNARY_OPERATORS = ["-", "~"]

OPERATOR_TABLE = {
    "+": "add",
    "-": "sub",
    "*": "Math.multiply",
    "/": "Math.divide",
    "&": "and",
    "|": "or",
    "<": "lt",
    ">": "gt",
    "=": "eq",
}

UNARY_OPERATORS_TABLE = {
    "-": "neg",
    "~": "not",
}
