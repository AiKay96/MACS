from __future__ import annotations
from abc import ABC, abstractmethod
from typing import Protocol

from Costumer import Costumer, CostumerRandomStrategy
from Employee import Cashier, Manager
from Product import Product, Report


class MyProxyAdapter:
    @staticmethod
    def get_product(product_data):
        return Product(*product_data)

    @staticmethod
    def get_reports(fetched_reports):
        return [Report(*report_data) for report_data in fetched_reports]

    @staticmethod
    def make_report(report, shift_number):
        return (
            report.product_name,
            report.amount,
            report.payment_type,
            report.revenue,
            shift_number
        )


class ProxyAdapter(Protocol):

    def get_product(self, product_data):
        pass

    def get_reports(self, fetched_reports):
        pass

    def make_report(self, report):
        pass


class Work:
    def __init__(self, database, shop, working_strategy):
        self.shop = shop
        self.database = database
        self.working_strategy = working_strategy

    def start_day(self):
        self.working_strategy.do_work(self.database, self.shop)


class WorkingStrategy(ABC):
    @abstractmethod
    def do_work(self, database, shop):
        pass


class MyWorkingStrategy(WorkingStrategy):

    def __init__(self):
        self.shop = None

    def do_work(self, database, shop):
        self.shop = shop
        cashier = self.shop.cashier
        manager = self.shop.manager
        while not self.is_close_time():
            if self.is_shift_end_time():
                manager.change_shift()
                if self.is_close_time():
                    break
            self.is_report_time() and manager.make_report()
            self.shop.increment_number_of_costumer()
            strategy = CostumerRandomStrategy(shop)
            costumer = Costumer(strategy)
            costumer.shop()
            cashier.scan_cart(costumer.get_cart(), costumer.get_pay_type())
            print('--------------RECEIPT------------------')
            cashier.get_receipt().print_receipt()
            print('----------------END--------------------')
        self.shop.close()

    def is_report_time(self):
        return self.shop.get_number_of_costumer() != 0 and self.shop.get_number_of_costumer() % 5 == 0

    def is_shift_end_time(self):
        return self.shop.get_number_of_costumer() != 0 and self.shop.get_number_of_costumer() % 20 == 0

    def is_close_time(self):
        return self.shop.get_number_of_shift() > 3 or self.shop.is_empty()


class Shop:
    def __init__(self, db):
        self.db = db
        self.number_of_costumer = 0
        self.number_of_shift = 1
        self.cashier = Cashier(self)
        self.manager = Manager(self)
        self.has_closed = False

    def fetch_products(self):
        proxy = MyProxyAdapter()
        num_products = self.db.get_products_number()

        products = [
            proxy.get_product(self.db.get_product(row_number))
            for row_number in range(1, num_products + 1)
            if proxy.get_product(self.db.get_product(row_number)).quantity > 0
        ]

        return products

    def increment_number_of_costumer(self):
        self.number_of_costumer += 1

    def get_number_of_costumer(self):
        return self.number_of_costumer

    def increment_number_of_shift(self):
        self.number_of_shift += 1

    def get_number_of_shift(self):
        return self.number_of_shift

    def update_product_quantity(self, product):
        batch = product.is_batch()
        amount = product.get_amount()
        product = product.get_product()
        if batch:
            self.db.update_batch_quantity(product, amount)
        else:
            self.db.update_batch_quantity(product, product.open_batch(amount))
            self.db.update_product_quantity(product, amount)

    def add_report(self, report):
        proxy = MyProxyAdapter()
        self.db.add_product_to_report(*(proxy.make_report(report, self.number_of_shift)))

    def fetch_reports(self):
        proxy = MyProxyAdapter()
        return proxy.get_reports(self.db.fetch_reports(self.number_of_shift))

    def clear_reports(self):
        pass

    def get_revenue(self, payment_type):
        revenue = self.db.get_revenue(payment_type, self.number_of_shift)
        return revenue if revenue is not None else 0

    def is_empty(self):
        return self.db.get_products_quantity() == 0

    def is_closed(self):
        return self.has_closed

    def register_is_clear(self):
        return self.db.get_reports_number(self.number_of_shift) == 0

    def close(self):
        if not self.register_is_clear():
            self.cashier.make_report()
            self.cashier.clear_register()
            self.has_closed = True
            print('Shop is closed!')

    def get_reports(self):
        proxy = MyProxyAdapter()
        return proxy.get_reports(self.db.get_reports())

    def get_revenues(self, payment_type):
        revenue = self.db.get_revenues(payment_type)
        return revenue if revenue is not None else 0

    def get_products(self):
        proxy = MyProxyAdapter()
        num_products = self.db.get_products_number()

        products = [
            proxy.get_product(self.db.get_product(row_number))
            for row_number in range(1, num_products + 1)
        ]

        return products
