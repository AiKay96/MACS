from typing import Annotated

from fastapi import Depends
from fastapi.requests import Request

from DesPatterns.core.products import ProductRepository
from DesPatterns.core.receipts import ReceiptRepository
from DesPatterns.core.units import UnitRepository


def get_product_repository(request: Request) -> ProductRepository:
    return request.app.state.products  # type: ignore


def get_unit_repository(request: Request) -> UnitRepository:
    return request.app.state.units  # type: ignore


def get_receipt_repository(request: Request) -> ReceiptRepository:
    return request.app.state.receipts  # type: ignore


ProductRepositoryDependable = Annotated[
    ProductRepository, Depends(get_product_repository)
]
UnitRepositoryDependable = Annotated[UnitRepository, Depends(get_unit_repository)]
ReceiptRepositoryDependable = Annotated[
    ReceiptRepository, Depends(get_receipt_repository)
]
