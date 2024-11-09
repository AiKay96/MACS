from __future__ import annotations

from dataclasses import dataclass, field
from typing import Protocol
from uuid import UUID, uuid4


class ProductRepository(Protocol):
    def create(self, product: Product) -> Product:
        pass

    def show(self, product_id: UUID) -> Product:
        pass

    def show_all(self) -> list[Product]:
        pass

    def update(self, product_id: UUID, price: int) -> Product:
        pass


@dataclass
class Product:
    unit_id: str
    name: str
    barcode: str
    price: int

    id: UUID = field(default_factory=uuid4)

    def update_price(self, price: int) -> None:
        self.price = price
