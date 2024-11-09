from abc import ABC, abstractmethod
import random
from typing import List

from Product import Product


class CostumerStrategy(ABC):
    def __init__(self, shop):
        self.shop = shop
        self.cart = None

    def set_cart(self, cart):
        self.cart = cart

    @abstractmethod
    def choose_products(self):
        pass

    @abstractmethod
    def get_pay_type(self):
        pass


# Concrete Strategy: CostumerRandomStrategy
class CostumerRandomStrategy(CostumerStrategy, ABC):
    def choose_products(self):
        product_list = self.shop.fetch_products()
        is_empty = True
        while product_list:
            product = random.choice(product_list)
            if is_empty or random.choices([True, False], weights=[1, 99], k=1)[0]:
                if product.in_batches and product.batch_amount > 0 and random.choice([True, False]):
                    cart_item = CartBatchItem(product, random.randint(1, product.batch_amount))
                else:
                    cart_item = CartSingleItem(product, random.randint(1, product.quantity))
                self.cart.add_product(cart_item)
                is_empty = False
            product_list.remove(product)

    def get_pay_type(self):
        return 'cash' if random.choice([True, False]) else 'card'


# Context: Costumer
class Costumer:
    def __init__(self, strategy):
        self.cart = Cart()
        self.strategy = strategy
        self.strategy.set_cart(self.cart)
        self.has_payed = False

    def shop(self):
        self.strategy.choose_products()

    def get_cart(self):
        return self.cart

    def get_pay_type(self):
        pay_type = self.strategy.get_pay_type()
        self.has_payed = True
        return pay_type


# Other classes
class Iterator:
    def has_next(self) -> bool:
        pass

    def next(self):
        pass


# Concrete Iterator: ProductIterator
class ProductIterator(Iterator):
    def __init__(self, products):
        self.products = products
        self.index = 0

    def has_next(self) -> bool:
        return self.index < len(self.products)

    def next(self):
        if self.has_next():
            product = self.products[self.index]
            self.index += 1
            return product
        else:
            raise StopIteration


# Aggregate Interface
class Aggregate:
    def create_iterator(self) -> Iterator:
        pass


# Concrete Aggregate: Cart
class Cart(Aggregate):
    def __init__(self):
        self.iterator = None
        self.products: List[CartItem] = []
        self.price = 0

    def add_product(self, product):
        self.products.append(product)
        self.price += product.get_price()

    def create_iterator(self) -> Iterator:
        self.iterator = ProductIterator(self.products)
        return self.iterator

    def get_total(self):
        return self.price

    def get_product(self):
        if not self.iterator:
            self.iterator = self.create_iterator()
        if self.iterator.has_next():
            return self.iterator.next()
        else:
            return None


class CartItem(ABC):
    @abstractmethod
    def get_description(self):
        pass

    @abstractmethod
    def is_batch(self):
        pass

    @abstractmethod
    def get_price(self):
        pass

    @abstractmethod
    def get_product(self):
        pass

    @abstractmethod
    def get_amount(self):
        pass


# Concrete Component: CartSingleItem
class CartSingleItem(CartItem):
    def __init__(self, product, amount):
        self.product = product
        self.amount = amount

    def get_description(self):
        return f"{self.product.name} | {self.amount} | {self.product.price:.2f} | {self.get_price():.2f}"

    def is_batch(self):
        return False

    def get_price(self):
        return self.product.price * self.amount * (1 - self.product.discount_percent)

    def get_product(self):
        return self.product

    def get_amount(self):
        return self.amount


# Decorator: CartBatchItem
class CartBatchItem(CartItem):
    def __init__(self, product, amount):
        self.product = product
        self.amount = amount

    def get_description(self):
        return (
            f"{self.product.name} | "
            f"{self.amount * self.product.batch_amount} | "
            f"{self.product.price:.2f} | "
            f"{self.get_price():.2f}"
        )

    def is_batch(self):
        return True

    def get_price(self):
        # Adjust the pricing logic for batch items as needed
        return (self.product.price * self.product.batch_amount * (1 - self.product.discount_percent)) * self.amount

    def get_product(self):
        return self.product

    def get_amount(self):
        return self.amount
