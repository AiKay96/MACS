import random
from typing import List

from Costumer import ProductIterator, CartItem
from Product import Report


class Cashier:
    def __init__(self, shop):
        self.shop = shop
        self.receipt = None

    def scan_cart(self, cart, payment_type):
        self.receipt = Receipt()
        self.receipt.open_receipt()
        cart_item = cart.get_product()
        while cart_item:
            self.shop.update_product_quantity(cart_item)
            report = Report(cart_item.get_product().name, cart_item.amount, payment_type, cart_item.get_price())
            self.shop.add_report(report)
            self.receipt.add_product(cart_item)
            cart_item = cart.get_product()
        self.receipt.close_receipt()

    def get_receipt(self):
        return self.receipt

    def make_report(self):
        print('Starting report:')
        print('Product | Sales')
        reports = self.shop.fetch_reports()
        for report in reports:
            report.print_report()
        print('Payment | Revenue')
        print('Cash |', f"{self.shop.get_revenue('cash'):.2f}")
        print('Card |', f"{self.shop.get_revenue('card'):.2f}")

    def clear_register(self):
        self.shop.clear_reports()


class Manager:
    def __init__(self, shop):
        self.shop = shop

    def change_shift(self):
        if random.choice([True, False]):
            self.shop.cashier.make_report()
            self.shop.cashier.clear_register()
            self.shop.increment_number_of_shift()
            self.shop.cashier = Cashier(self.shop)

    def make_report(self):
        if not self.shop.register_is_clear() and random.choice([True, False]):
            self.shop.cashier.make_report()

    def make_full_report(self):
        print('Full Report:')
        print('Product | Sales')
        reports = self.shop.get_reports()
        for report in reports:
            report.print_report()
        print('Payment | Revenue')
        print('Cash |', f"{self.shop.get_revenues('cash'):.2f}")
        print('Card |', f"{self.shop.get_revenues('card'):.2f}")

    def print_products(self):
        products = self.shop.get_products()
        print("Full List:")
        print('Name | Price | Discount')
        for product in products:
            print(product.name, '|', product.price, '|', f"{(product.discount_percent*10):.0f}" + '%')

class Receipt:
    def __init__(self):
        self.is_open = False
        self.cart_items: List[CartItem] = []

    def open_receipt(self):
        self.is_open = True

    def add_product(self, cart_item):
        self.cart_items.append(cart_item)

    def close_receipt(self):
        self.is_open = False

    def print_receipt(self):
        print("Printing Receipt:")
        print("Product | Units | Price | Total")
        iterator = self.create_iterator()
        while iterator.has_next():
            cart_item = iterator.next()
            print(cart_item.get_description())

    def create_iterator(self):
        return ProductIterator(self.cart_items)
