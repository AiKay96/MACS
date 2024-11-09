from __future__ import annotations

from n2t.core.compiler.data import (
    OPERATOR_TABLE,
    OPERATORS,
    UNARY_OPERATORS,
    UNARY_OPERATORS_TABLE,
)
from n2t.core.compiler.symbol_table import SymbolTable
from n2t.core.compiler.tokenizer import JackTokenizer
from n2t.core.compiler.vm_writer import VMWriter


class CompilationEngine:
    def __init__(self, input_file: str, output_file: str) -> None:
        self.tokenizer: JackTokenizer = JackTokenizer(input_file)
        self.class_name: str = ""
        self.class_table: SymbolTable = SymbolTable()
        self.table: SymbolTable = SymbolTable()
        self.vm_writer: VMWriter = VMWriter(output_file)
        self.count: int = 0
        self.args: int = 0

    def next_token(self) -> str:
        self.tokenizer.advance()
        return self.tokenizer.token()

    def compile_class(self) -> None:
        self.class_name = self.next_token()
        self.tokenizer.advance()
        self.tokenizer.advance()
        self.compile_class_var_dec()
        while self.tokenizer.token() in ["constructor", "function", "method"]:
            self.compile_subroutine()
        self.vm_writer.close()

    def compile_class_var_dec(self) -> None:
        kind = self.tokenizer.token()
        if kind not in ["static", "field"]:
            return
        while kind in ["static", "field"]:
            type = self.next_token()
            name = self.next_token()
            self.class_table.define(name, type, kind)
            while self.next_token() == ",":
                name = self.next_token()
                self.class_table.define(name, type, kind)
            kind = self.next_token()

    def compile_subroutine(self) -> None:
        self.table.reset()
        type = self.tokenizer.token()
        self.tokenizer.advance()
        name = self.next_token()
        self.tokenizer.advance()
        if type == "method":
            self.table.define("this", self.class_name, "argument")
        self.tokenizer.advance()
        self.compile_parameter_list()
        self.tokenizer.advance()
        self.tokenizer.advance()
        while self.tokenizer.token() == "var":
            self.compile_var_dec()
        self.vm_writer.write_function(
            self.class_name + "." + name, self.table.var_count("local")
        )
        if type == "constructor":
            n_fields = self.class_table.var_count("field")
            self.vm_writer.write_push("constant", n_fields)
            self.vm_writer.write_call("Memory.alloc", 1)
            self.vm_writer.write_pop("pointer", 0)
        elif type == "method":
            self.vm_writer.write_push("argument", 0)
            self.vm_writer.write_pop("pointer", 0)
        self.compile_statements()

        self.tokenizer.advance()

    def compile_parameter_list(self) -> None:
        while self.tokenizer.token() != ")":
            type = self.tokenizer.token_type()
            name = self.next_token()
            self.tokenizer.advance()
            self.table.define(name, type, "argument")
            if self.tokenizer.token() == ",":
                self.tokenizer.advance()

    def compile_var_dec(self) -> None:
        type = self.next_token()
        while True:
            name = self.next_token()
            self.table.define(name, type, "local")
            if self.next_token() == ";":
                break
        self.tokenizer.advance()

    def compile_statements(self) -> None:
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

    def compile_let(self) -> None:
        name = self.next_token()
        if self.next_token() == "[":
            kind = self.table.kind_of(name)
            index = self.table.index_of(name)
            self.vm_writer.write_push(kind, index)
            self.tokenizer.advance()
            self.compile_expression()
            self.vm_writer.write_arithmetic("add")
            self.tokenizer.advance()
            self.tokenizer.advance()
            self.compile_expression()
            self.vm_writer.write_pop("temp", 0)
            self.vm_writer.write_pop("pointer", 1)
            self.vm_writer.write_push("temp", 0)
            self.vm_writer.write_pop("that", 0)
        else:
            self.tokenizer.advance()
            self.compile_expression()

            kind = self.table.kind_of(name)
            if kind == "not found":
                kind = self.class_table.kind_of(name)
            index = self.table.index_of(name)
            if index == -1:
                index = self.class_table.index_of(name)
            self.vm_writer.write_pop(kind, index)
        self.tokenizer.advance()

    def compile_if(self) -> None:
        self.tokenizer.advance()
        self.tokenizer.advance()
        self.compile_expression()
        self.vm_writer.write_arithmetic("not")
        self.tokenizer.advance()
        self.tokenizer.advance()
        count = self.count
        self.count += 1
        self.vm_writer.write_if("L1" + str(count))
        self.compile_statements()
        self.vm_writer.write_goto("L2" + str(count))
        self.tokenizer.advance()
        self.vm_writer.write_label("L1" + str(count))
        if self.tokenizer.token() == "else":
            self.tokenizer.advance()
            self.tokenizer.advance()
            self.compile_statements()
            self.tokenizer.advance()
        self.vm_writer.write_label("L2" + str(count))

    def compile_while(self) -> None:
        count = self.count
        self.count += 1
        self.tokenizer.advance()
        self.tokenizer.advance()
        self.vm_writer.write_label("L1" + str(count))
        self.compile_expression()
        self.vm_writer.write_arithmetic("not")
        self.vm_writer.write_if("L2" + str(count))
        self.tokenizer.advance()
        self.tokenizer.advance()
        self.compile_statements()
        self.vm_writer.write_goto("L1" + str(count))
        self.vm_writer.write_label("L2" + str(count))
        self.tokenizer.advance()

    def compile_do(self) -> None:
        self.tokenizer.advance()
        self.compile_function_call()
        self.vm_writer.write_pop("temp", 0)
        self.tokenizer.advance()

    def compile_return(self) -> None:
        if self.next_token() != ";":
            self.compile_expression()
        else:
            self.vm_writer.write_push("constant", 0)
        self.vm_writer.write_return()
        self.tokenizer.advance()

    def compile_expression(self) -> None:
        self.compile_term()
        if self.tokenizer.symbol() in OPERATORS:
            operator = self.tokenizer.symbol()
            self.tokenizer.advance()
            self.compile_term()
            command = OPERATOR_TABLE[operator]
            if operator in ["*", "/"]:
                self.vm_writer.write_call(command, 2)
            else:
                self.vm_writer.write_arithmetic(command)

    def compile_term(self) -> None:
        token = self.tokenizer.token()
        type = self.tokenizer.token_type()
        if token == "(":
            self.tokenizer.advance()
            self.compile_expression()
            self.tokenizer.advance()
        elif token in UNARY_OPERATORS:
            self.tokenizer.advance()
            self.compile_term()
            self.vm_writer.write_arithmetic(UNARY_OPERATORS_TABLE[token])
        elif type != "identifier":
            if type == "integer_constant":
                self.vm_writer.write_push("constant", int(token))
            elif type == "keyword":
                if token == "this":
                    self.vm_writer.write_push("pointer", 0)
                elif token == "true":
                    self.vm_writer.write_push("constant", 0)
                    self.vm_writer.write_arithmetic("not")
                elif token in ["false", "null"]:
                    self.vm_writer.write_push("constant", 0)
                else:
                    self.vm_writer.write_push("constant", 0)
            else:
                if token[0] == '"':
                    token = token[1:-1]
                self.vm_writer.write_push("constant", len(token))
                self.vm_writer.write_call("String.new", 1)
                for char in token:
                    self.vm_writer.write_push("constant", ord(char))
                    self.vm_writer.write_call("String.appendChar", 2)
            self.tokenizer.advance()
        else:
            old_token = token
            token = self.next_token()
            if token == "[":
                kind = self.table.kind_of(old_token)
                if kind == "not found":
                    kind = self.class_table.kind_of(old_token)
                index = self.table.index_of(old_token)
                if index == -1:
                    index = self.class_table.index_of(old_token)
                self.vm_writer.write_push(kind, index)
                self.tokenizer.advance()
                self.compile_expression()
                self.tokenizer.advance()
                self.vm_writer.write_arithmetic("add")
                self.vm_writer.write_pop("pointer", 1)
                self.vm_writer.write_push("that", 0)
            elif token == "(" or token == ".":
                self.tokenizer.impede()
                self.compile_function_call()
            else:
                segment = self.table.kind_of(old_token)
                if segment == "not found":
                    segment = self.class_table.kind_of(old_token)
                index = self.table.index_of(old_token)
                if index == -1:
                    index = self.class_table.index_of(old_token)

                self.vm_writer.write_push(segment, index)

    def compile_function_call(self) -> None:
        name = self.tokenizer.token()
        class_name = self.class_name
        self.args = 1
        if self.next_token() == ".":
            if name in self.table.table:
                class_name = self.table.type_of(name)
                kind = self.table.kind_of(name)
                index = self.table.index_of(name)
                self.vm_writer.write_push(kind, index)
            elif name in self.class_table.table:
                class_name = self.class_table.type_of(name)
                kind = self.class_table.kind_of(name)
                index = self.class_table.index_of(name)
                self.vm_writer.write_push(kind, index)
            else:
                self.args = 0
                class_name = name
            name = self.next_token()
            self.tokenizer.advance()
        else:
            self.vm_writer.write_push("pointer", 0)
        self.tokenizer.advance()
        self.compile_expression_list()
        self.vm_writer.write_call(f"{class_name}.{name}", self.args)
        self.tokenizer.advance()

    def compile_subroutine_call(self) -> None:
        self.args = 1
        class_name = self.class_name
        name = self.tokenizer.token()
        if self.next_token() == ".":
            if name not in self.class_table.table:
                self.args = 0
                class_name = name
            else:
                class_name = self.class_table.type_of(name)
                kind = self.class_table.kind_of(name)
                index = self.class_table.index_of(name)
                self.vm_writer.write_push(kind, index)
            name = self.next_token()
        else:
            self.vm_writer.write_push("pointer", 0)
        name = class_name + "." + name
        self.tokenizer.advance()
        self.compile_expression_list()
        self.vm_writer.write_call(name, self.args)
        self.tokenizer.advance()

    def compile_expression_list(self) -> None:
        while self.tokenizer.token() != ")":
            self.args += 1
            self.compile_expression()
            if self.tokenizer.token() == ",":
                self.tokenizer.advance()
