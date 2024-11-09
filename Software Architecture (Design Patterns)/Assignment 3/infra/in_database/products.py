import sqlite3
from uuid import UUID

from DesPatterns.core.errors import DoesNotExistError
from DesPatterns.core.products import Product


class ProductInDatabase:
    def __init__(self) -> None:
        self.db = "./database.db"
        self.create_table()

    def create_table(self) -> None:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            create_table_query = """
                    CREATE TABLE IF NOT EXISTS products (
                      receipt_id CHAR(64),
                      product_id CHAR(64),
                      amount INTEGER
                    );
                """
            cursor.execute(create_table_query)

    def create(self, product: Product) -> Product:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            insert_query = """
                INSERT INTO products (id, unit_id, name, barcode, price)
                VALUES (?, ?, ?, ?, ?);
            """
            values = (
                str(product.id),
                str(product.unit_id),
                product.name,
                product.barcode,
                product.price,
            )
            cursor.execute(insert_query, values)
        return product

    def show(self, product_id: UUID) -> Product:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            select_query = """
                SELECT id, unit_id, name, barcode, price FROM products WHERE id = ?;
            """
            cursor.execute(select_query, (str(product_id),))
            row = cursor.fetchone()
            if row:
                return Product(
                    id=UUID(row[0]),
                    unit_id=row[1],
                    name=row[2],
                    barcode=row[3],
                    price=row[4],
                )
            else:
                raise DoesNotExistError(product_id)

    def show_all(self) -> list[Product]:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            select_all_query = """
                SELECT id, unit_id, name, barcode, price FROM products;
            """
            cursor.execute(select_all_query)
            rows = cursor.fetchall()
            return [
                Product(
                    id=UUID(row[0]),
                    unit_id=row[1],
                    name=row[2],
                    barcode=row[3],
                    price=row[4],
                )
                for row in rows
            ]

    def update(self, product_id: UUID, price: int) -> Product:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            update_query = """
                UPDATE products SET price = ? WHERE id = ?;
            """
            values = (price, str(product_id))
            cursor.execute(update_query, values)
            return self.show(product_id)

    def clear_tables(self) -> None:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()

            truncate_products_query = """
                DELETE FROM products;
            """

            cursor.execute(truncate_products_query)
            connection.commit()
