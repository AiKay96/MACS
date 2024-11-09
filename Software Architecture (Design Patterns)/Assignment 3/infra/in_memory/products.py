from dataclasses import dataclass, field
from uuid import UUID

from DesPatterns.core.errors import DoesNotExistError
from DesPatterns.core.products import Product


@dataclass
class ProductInMemory:
    products: dict[UUID, Product] = field(default_factory=dict)

    def create(self, product: Product) -> Product:
        self.products[product.id] = product
        return product

    def show(self, product_id: UUID) -> Product:
        try:
            return self.products[product_id]
        except KeyError:
            raise DoesNotExistError(product_id)

    def show_all(self) -> list[Product]:
        return list(self.products.values())

    def update(self, product_id: UUID, price: int) -> Product:
        self.products[product_id].update_price(price)
        return self.products[product_id]
