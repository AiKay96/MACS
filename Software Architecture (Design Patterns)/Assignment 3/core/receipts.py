from __future__ import annotations

from dataclasses import dataclass, field
from typing import Protocol
from uuid import UUID, uuid4


class ReceiptRepository(Protocol):
    def create(self, receipt: Receipt) -> Receipt:
        pass

    def show(self, receipt_id: UUID) -> Receipt:
        pass

    def update_status(self, receipt_id: UUID, status: str) -> Receipt:
        pass

    def delete(self, receipt_id: UUID) -> None:
        pass

    def get_number_of_receipts(self) -> int:
        pass

    def get_revenue(self) -> int:
        pass


@dataclass
class Receipt:
    status: str = field(init=False)
    products: list[ReceiptProduct] = field(init=False)
    total: int = field(init=False)
    id: UUID = field(default_factory=uuid4)

    def __post_init__(self) -> None:
        self.status = "open"
        self.products = []
        self.total = 0

    def add_product(self, product_id: UUID, quantity: int, price: int) -> None:
        receipt_product = ReceiptProduct(product_id, quantity, price)
        self.products.append(receipt_product)
        self.total += receipt_product.total

    def update_status(self, status: str) -> None:
        self.status = status

    def get_status(self) -> str:
        return self.status

    def is_closed(self) -> bool:
        return self.status == "closed"


@dataclass
class ReceiptProduct:
    product_id: UUID
    quantity: int
    price: int
    total: int = field(init=False)

    def __post_init__(self) -> None:
        self.total = self.calculate_total()

    def calculate_total(self) -> int:
        return self.price * self.quantity
