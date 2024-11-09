import sqlite3
from uuid import UUID

from DesPatterns.core.errors import DoesNotExistError
from DesPatterns.core.units import Unit


class UnitInDatabase:
    def __init__(self) -> None:
        self.db = "./database.db"
        self.create_table()

    def create_table(self) -> None:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            create_table_query = """
                CREATE TABLE IF NOT EXISTS units (
                  id CHAR(64),
                  name CHAR(64)
                );
            """
            cursor.execute(create_table_query)

    def create(self, unit: Unit) -> Unit:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            insert_query = """
                INSERT INTO units (id, name)
                VALUES (?, ?);
            """
            values = (str(unit.id), unit.name)
            cursor.execute(insert_query, values)
            connection.commit()
            return unit

    def show(self, unit_id: UUID) -> Unit:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()

            select_query = """
                SELECT id, name FROM units WHERE id = ?;
            """
            cursor.execute(select_query, (str(unit_id),))
            row = cursor.fetchone()

            if row:
                return Unit(id=UUID(row[0]), name=row[1])
            else:
                raise DoesNotExistError(f"Unit with id<{unit_id}> does not exist.")

    def show_all(self) -> list[Unit]:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()
            select_all_query = """
                SELECT id, name FROM units;
            """
            cursor.execute(select_all_query)
            rows = cursor.fetchall()
            return [Unit(id=UUID(row[0]), name=row[1]) for row in rows]

    def clear_tables(self) -> None:
        with sqlite3.connect(self.db) as connection:
            cursor = connection.cursor()

            truncate_units_query = """
                DELETE FROM units;
            """

            cursor.execute(truncate_units_query)
            connection.commit()
