import os

from fastapi import FastAPI

from DesPatterns.infra.in_database.products import ProductInDatabase
from DesPatterns.infra.in_database.receipts import ReceiptInDatabase
from DesPatterns.infra.in_database.units import UnitInDatabase
from DesPatterns.infra.in_memory.products import ProductInMemory
from DesPatterns.infra.in_memory.receipts import ReceiptInMemory
from DesPatterns.infra.in_memory.units import UnitInMemory
from DesPatterns.infra.shop_api.products_api import product_api
from DesPatterns.infra.shop_api.receipts_api import receipt_api
from DesPatterns.infra.shop_api.sales_api import sale_api
from DesPatterns.infra.shop_api.units_api import unit_api


def init_app() -> FastAPI:
    app = FastAPI()
    app.include_router(product_api)
    app.include_router(receipt_api)
    app.include_router(unit_api)
    app.include_router(sale_api)

    if os.getenv("REPOSITORY_KIND", "memory") == "sqlite":
        app.state.products = ProductInDatabase()
        app.state.receipts = ReceiptInDatabase()
        app.state.units = UnitInDatabase()

    else:
        app.state.products = ProductInMemory()
        app.state.receipts = ReceiptInMemory()
        app.state.units = UnitInMemory()

    return app
