import typer

from Database import MyDatabase
from Shop import Shop, MyWorkingStrategy, Work


def main(message: str) -> None:
    shop = None
    db = None
    if message == "list":
        if shop is None:
            print("Run simulate first!")
        else:
            shop.manager.print_products()
    elif message == "simulate":
        db = MyDatabase()
        db.connect()
        shop = Shop(db)
        work_strategy = MyWorkingStrategy()
        work = Work(shop.db, shop, work_strategy)
        work.start_day()
    elif message == "report":
        if shop is None:
            print("Run simulate first!")
        else:
            shop.manager.make_full_report()
    elif message == "exit":
        if shop is None:
            print("Run simulate first!")
        else:
            db.close_connection()


if __name__ == "__main__":
    typer.run(main)
