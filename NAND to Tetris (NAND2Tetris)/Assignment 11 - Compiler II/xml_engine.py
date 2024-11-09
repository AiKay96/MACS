from __future__ import annotations

from typing import TextIO

from n2t.core.compiler.data import OPERATORS, UNARY_OPERATORS
from n2t.core.compiler.tokenizer import JackTokenizer


class CompilationEngine:
    def __init__(self, input_file: str, output_file: str) -> None:
        self.tokenizer: JackTokenizer = JackTokenizer(input_file)
        self.output_file: TextIO = open(output_file, "w")
        self.tag_num: int = 0

    def open_tag(self, name: str) -> None:
        self.output_file.write("  " * self.tag_num)
        self.output_file.write("<")
        self.output_file.write(name)
        self.output_file.write(">")
        self.output_file.write("\n")
        self.tag_num += 1

    def close_tag(self, name: str) -> None:
        self.tag_num -= 1
        self.output_file.write("  " * self.tag_num)
        self.output_file.write("</")
        self.output_file.write(name)
        self.output_file.write(">")
        self.output_file.write("\n")

    def write(self, token_type: str, line: str) -> None:
        self.output_file.write("  " * self.tag_num)
        self.output_file.write("<")
        self.output_file.write(token_type)
        self.output_file.write(">")
        self.output_file.write(" ")
        if line == "<":
            line = "&lt;"
        elif line == ">":
            line = "&gt;"
        elif line == "&":
            line = "&amp;"
        self.output_file.write(line)
        self.output_file.write(" ")
        self.output_file.write("</")
        self.output_file.write(token_type)
        self.output_file.write(">")
        self.output_file.write("\n")

    def compile_class(self) -> None:
        self.open_tag("class")
        self.write("keyword", self.tokenizer.keyword())
        self.tokenizer.advance()
        self.write("identifier", self.tokenizer.identifier())
        self.tokenizer.advance()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.compile_class_var_dec()
        self.compile_subroutine()
        self.write("symbol", self.tokenizer.symbol())
        self.close_tag("class")

    def compile_class_var_dec(self) -> None:
        while self.tokenizer.keyword() in ["static", "field"]:
            self.open_tag("classVarDec")
            self.write("keyword", self.tokenizer.keyword())
            self.tokenizer.advance()
            self.compile_type()
            self.write("identifier", self.tokenizer.identifier())
            self.tokenizer.advance()

            while self.tokenizer.symbol() == ",":
                self.write("symbol", self.tokenizer.symbol())
                self.tokenizer.advance()
                self.write("identifier", self.tokenizer.identifier())
                self.tokenizer.advance()

            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.close_tag("classVarDec")

    def compile_subroutine(self) -> None:
        while self.tokenizer.keyword() in ["constructor", "function", "method"]:
            self.open_tag("subroutineDec")
            self.write("keyword", self.tokenizer.keyword())
            self.tokenizer.advance()
            if self.tokenizer.keyword() == "void":
                self.write("keyword", self.tokenizer.keyword())
                self.tokenizer.advance()
            else:
                self.compile_type()
            self.write("identifier", self.tokenizer.identifier())
            self.tokenizer.advance()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.compile_parameter_list()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.compile_subroutine_body()
            self.close_tag("subroutineDec")

    def compile_type(self) -> None:
        if self.tokenizer.token_type() == "keyword":
            self.write("keyword", self.tokenizer.keyword())
        else:
            self.write("identifier", self.tokenizer.identifier())
        self.tokenizer.advance()

    def compile_parameter_list(self) -> None:
        self.open_tag("parameterList")
        if self.tokenizer.symbol() != ")":
            self.compile_type()
            self.write("identifier", self.tokenizer.identifier())
            self.tokenizer.advance()
            while self.tokenizer.symbol() == ",":
                self.write("symbol", self.tokenizer.symbol())
                self.tokenizer.advance()
                self.compile_type()
                self.write("identifier", self.tokenizer.identifier())
                self.tokenizer.advance()
        self.close_tag("parameterList")

    def compile_subroutine_body(self) -> None:
        self.open_tag("subroutineBody")
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.compile_var_dec()
        self.compile_statements()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.close_tag("subroutineBody")

    def compile_var_dec(self) -> None:
        while self.tokenizer.keyword() == "var":
            self.open_tag("varDec")
            self.write("keyword", self.tokenizer.keyword())
            self.tokenizer.advance()
            self.compile_type()
            self.write("identifier", self.tokenizer.identifier())
            self.tokenizer.advance()
            while self.tokenizer.symbol() == ",":
                self.write("symbol", self.tokenizer.symbol())
                self.tokenizer.advance()
                self.write("identifier", self.tokenizer.identifier())
                self.tokenizer.advance()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.close_tag("varDec")

    def compile_statements(self) -> None:
        self.open_tag("statements")
        while self.tokenizer.token_type() == "keyword":
            if self.tokenizer.keyword() == "let":
                self.compile_let()
            elif self.tokenizer.keyword() == "if":
                self.compile_if()
            elif self.tokenizer.keyword() == "while":
                self.compile_while()
            elif self.tokenizer.keyword() == "do":
                self.compile_do()
            elif self.tokenizer.keyword() == "return":
                self.compile_return()
        self.close_tag("statements")

    def compile_let(self) -> None:
        self.open_tag("letStatement")
        self.write("keyword", self.tokenizer.keyword())
        self.tokenizer.advance()
        self.write("identifier", self.tokenizer.identifier())
        self.tokenizer.advance()

        if self.tokenizer.symbol() == "[":
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.compile_expression()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.compile_expression()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.close_tag("letStatement")

    def compile_if(self) -> None:
        self.open_tag("ifStatement")
        self.write("keyword", self.tokenizer.keyword())
        self.tokenizer.advance()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.compile_expression()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.compile_statements()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        if self.tokenizer.keyword() == "else":
            self.write("keyword", self.tokenizer.keyword())
            self.tokenizer.advance()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.compile_statements()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
        self.close_tag("ifStatement")

    def compile_while(self) -> None:
        self.open_tag("whileStatement")
        self.write("keyword", self.tokenizer.keyword())
        self.tokenizer.advance()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.compile_expression()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.compile_statements()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.close_tag("whileStatement")

    def compile_do(self) -> None:
        self.open_tag("doStatement")
        self.write("keyword", self.tokenizer.keyword())
        self.tokenizer.advance()
        self.compile_subroutine_call()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.close_tag("doStatement")

    def compile_return(self) -> None:
        self.open_tag("returnStatement")
        self.write("keyword", self.tokenizer.keyword())
        self.tokenizer.advance()
        if self.tokenizer.symbol() != ";":
            self.compile_expression()
        self.write("symbol", self.tokenizer.symbol())
        self.tokenizer.advance()
        self.close_tag("returnStatement")

    def compile_expression(self) -> None:
        self.open_tag("expression")
        self.compile_term()
        if self.tokenizer.symbol() in OPERATORS:
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.compile_term()
        self.close_tag("expression")

    def compile_term(self) -> None:
        self.open_tag("term")
        if self.tokenizer.token_type() == "integer_constant":
            self.write("integerConstant", self.tokenizer.int_val())
            self.tokenizer.advance()
        elif self.tokenizer.token_type() == "string_constant":
            self.write("stringConstant", self.tokenizer.string_val())
            self.tokenizer.advance()
        elif self.tokenizer.token_type() == "keyword":
            self.write("keyword", self.tokenizer.keyword())
            self.tokenizer.advance()
        elif self.tokenizer.token_type() == "identifier":
            self.compile_subroutine_call()
        elif self.tokenizer.symbol() in UNARY_OPERATORS:
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.compile_term()
        elif self.tokenizer.token_type() == "symbol":
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.compile_expression()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
        self.close_tag("term")

    def compile_subroutine_call(self) -> None:
        self.write("identifier", self.tokenizer.identifier())
        self.tokenizer.advance()
        if self.tokenizer.symbol() == "[":
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.compile_expression()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
        elif self.tokenizer.symbol() == "(":
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.compile_expression_list()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
        elif self.tokenizer.symbol() == ".":
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.write("identifier", self.tokenizer.identifier())
            self.tokenizer.advance()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()
            self.compile_expression_list()
            self.write("symbol", self.tokenizer.symbol())
            self.tokenizer.advance()

    def compile_expression_list(self) -> None:
        self.open_tag("expressionList")
        if self.tokenizer.symbol() != ")":
            self.compile_expression()
            while self.tokenizer.symbol() == ",":
                self.write("symbol", self.tokenizer.symbol())
                self.tokenizer.advance()
                self.compile_expression()
        self.close_tag("expressionList")
