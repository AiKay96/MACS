import sqlite3
from typing import Protocol


class MyDatabase:

    def __init__(self, db='store_database.db'):
        self.db = db
        self.connection = None
        self.cursor = None

    def connect(self):
        self.connection = sqlite3.connect(self.db)
        self.cursor = self.connection.cursor()

    def close_connection(self):
        if self.connection:
            self.connection.close()

    def get_product(self, row_number):
        self.cursor.execute('SELECT * FROM products WHERE id = ?', (row_number,))
        return self.cursor.fetchall()[0]

    def update_product_quantity(self, product, quantity):
        self.cursor.execute('''
                        UPDATE products
                        SET quantity = ?
                        WHERE id = ?;
                    ''', (product.quantity - quantity, product.id))
        self.connection.commit()

    def update_batch_quantity(self, product, quantity):
        self.cursor.execute('''
                                UPDATE products
                                SET batch_amount = ?
                                WHERE id = ?;
                            ''', (product.batch_amount - quantity, product.id))
        self.connection.commit()
        self.cursor.execute('''
                                UPDATE products
                                SET quantity = ?
                                WHERE id = ?;
                            ''', (product.quantity - quantity*product.batch_size, product.id))
        self.connection.commit()

    def fetch_reports(self, shift):
        self.cursor.execute('''
                                SELECT 
                                    product_name, 
                                    SUM(product_amount) as total_amount, 
                                    payment_type, 
                                    SUM(revenue) as total_revenue
                                FROM 
                                    reports
                                WHERE 
                                    shift = ?
                                GROUP BY 
                                    product_name, payment_type
                            ''', (shift,))
        return self.cursor.fetchall()

    def get_reports(self):
        self.cursor.execute('''
                                SELECT 
                                    product_name, 
                                    SUM(product_amount) as total_amount, 
                                    payment_type, 
                                    SUM(revenue) as total_revenue
                                FROM 
                                    reports
                                GROUP BY 
                                    product_name, payment_type
                            ''')
        return self.cursor.fetchall()

    def add_product_to_report(self, product_name, amount, payment_type, revenue, shift):
        self.cursor.execute('''
                       INSERT INTO reports (product_name, product_amount, payment_type, revenue, shift)
                       VALUES (?, ?, ?, ?, ?)
                   ''', (product_name, amount, payment_type, revenue, shift))
        self.connection.commit()

    def get_products_number(self):
        self.cursor.execute('''
                               SELECT COUNT(*) AS num_rows
                                FROM products;
                           ''', )
        return self.cursor.fetchall()[0][0]

    def get_revenue(self, payment_type, shift):
        self.cursor.execute('''
                                SELECT SUM(revenue) as total_revenue
                                FROM reports
                                WHERE payment_type = ? and shift = ?
                            ''', (payment_type, shift))

        return self.cursor.fetchone()[0]

    def get_revenues(self, payment_type):
        self.cursor.execute('''
                                SELECT SUM(revenue) as total_revenue
                                FROM reports
                                WHERE payment_type = ?
                            ''', (payment_type,))

        return self.cursor.fetchone()[0]

    def get_products_quantity(self):
        self.cursor.execute('''
                                SELECT SUM(quantity)
                                FROM products
                            ''')
        return self.cursor.fetchone()[0]

    def get_reports_number(self, shift):
        self.cursor.execute('SELECT COUNT(*) FROM reports WHERE shift = ?', (shift,))
        return self.cursor.fetchone()[0]


class Database(Protocol):

    def __init__(self, db):
        self.db = db
        self.connection = None
        self.cursor = None

    def connect(self):
        self.connection = sqlite3.connect(self.db)
        self.cursor = self.connection.cursor()

    def close_connection(self):
        if self.connection:
            self.connection.close()

    def get_product(self, row_number):
        pass

    def update_product_quantity(self, product, quantity):
        pass

    def fetch_reports(self):
        pass

    def add_product_to_report(self, product_name, amount, payment_type, revenue):
        pass

    def get_products_number(self):
        pass
