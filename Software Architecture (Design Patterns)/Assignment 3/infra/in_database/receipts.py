import sqlite3
from uuid import UUID

from DesPatterns.core.errors import DoesNotExistError
from DesPatterns.core.receipts import Receipt, ReceiptProduct


class ReceiptInDatabase:
    def __init__(self) -> None:
        self.db = "database.db"
        self.create_table()

    def create_table(self) -> None:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            create_table_query = """
                        CREATE TABLE IF NOT EXISTS receipt_products (
                          id CHAR(64),
                          unit_id CHAR(64),
                          name CHAR(64),
                          barcode CHAR(64),
                          price INTEGER
                        );
                    """
            cursor.execute(create_table_query)
            create_table_query = """
                        CREATE TABLE IF NOT EXISTS receipts (
                          receipt_id CHAR(64),
                          status TEXT CHECK(status IN ('open', 'closed')) NOT NULL,
                          n_products INTEGER,
                          total INTEGER
                        );
                                """
            cursor.execute(create_table_query)

    def create(self, receipt: Receipt) -> None:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            insert_query = """
                INSERT INTO receipts (receipt_id, status, n_products, total)
                VALUES (?, ?, ?, ?);
            """
            values = (
                str(receipt.id),
                receipt.status,
                len(receipt.products),
                receipt.total,
            )
            cursor.execute(insert_query, values)

    def show(self, receipt_id: UUID) -> Receipt:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            select_query = """
                SELECT status, n_products, total FROM receipts WHERE receipt_id = ?;
            """
            cursor.execute(select_query, (str(receipt_id),))
            row = cursor.fetchone()

            if row:
                status, n_products, total = row
                products = self.get_receipt_products(receipt_id)
                receipt = Receipt()
                receipt.status = status
                receipt.total = total
                receipt.products = products
                receipt.id = receipt_id
                return receipt
            else:
                raise DoesNotExistError(
                    f"Receipt with id<{receipt_id}> does not exist."
                )

    def get_receipt_products(self, receipt_id: UUID) -> list[ReceiptProduct]:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            select_query = """
                SELECT product_id, amount FROM receipt_products WHERE receipt_id = ?;
            """
            cursor.execute(select_query, (str(receipt_id),))
            rows = cursor.fetchall()

            products = []
            for row in rows:
                product_id, amount = row
                receipt_product = ReceiptProduct(
                    product_id=UUID(product_id), quantity=amount, price=1
                )
                products.append(receipt_product)

            return products

    def update_status(self, receipt_id: UUID, status: str) -> Receipt:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            update_query = """
                UPDATE receipts SET status = ? WHERE receipt_id = ?;
            """
            values = (status, str(receipt_id))
            cursor.execute(update_query, values)
            connection.commit()

            return self.show(receipt_id)

    def delete(self, receipt_id: UUID) -> None:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            select_status_query = """
                SELECT status FROM receipts WHERE receipt_id = ?;
            """
            cursor.execute(select_status_query, (str(receipt_id),))
            status = cursor.fetchone()

            if not status:
                raise DoesNotExistError(receipt_id)

            if status[0] == "closed":
                raise DoesNotExistError(
                    receipt_id, "Receipt is closed and cannot be deleted."
                )

            delete_query = """
                DELETE FROM receipts WHERE receipt_id = ?;
            """
            cursor.execute(delete_query, (str(receipt_id),))
            connection.commit()

    def get_number_of_receipts(self) -> int:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            count_query = """
                SELECT COUNT(*) FROM receipts;
            """
            cursor.execute(count_query)
            count = cursor.fetchone()[0]
        return int(count)

    def get_revenue(self) -> int:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            total_query = """
                SELECT SUM(total) FROM receipts;
            """
            cursor.execute(total_query)
            total = cursor.fetchone()[0] or 0
        return total

    def clear_tables(self) -> None:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()

            truncate_products_query = """
                DELETE FROM receipt_products;
            """

            cursor.execute(truncate_products_query)

            truncate_products_query = """
                            DELETE FROM receipts;
                        """

            cursor.execute(truncate_products_query)
            connection.commit()
