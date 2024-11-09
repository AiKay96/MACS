from typing import Any
from uuid import UUID

from fastapi import APIRouter
from pydantic import BaseModel
from starlette.responses import JSONResponse

from DesPatterns.core.errors import DoesNotExistError
from DesPatterns.core.receipts import Receipt, ReceiptProduct
from DesPatterns.infra.shop_api.dependables import ReceiptRepositoryDependable

receipt_api = APIRouter(tags=["Receipts"])


class EmptyItem(BaseModel):
    pass


class AddProductRequest(BaseModel):
    product_id: UUID
    quantity: int
    price: int


class UpdateReceiptRequest(BaseModel):
    status: str


class ReceiptItem(BaseModel):
    id: UUID
    status: str
    products: list[ReceiptProduct]
    total: int


class ReceiptItemEnvelope(BaseModel):
    receipt: ReceiptItem


@receipt_api.post(
    "/receipts",
    status_code=201,
    response_model=ReceiptItemEnvelope,
)
def create_receipt(receipts: ReceiptRepositoryDependable) -> dict[str, Receipt]:
    receipt = Receipt()
    receipts.create(receipt)

    return {"receipt": receipt}


@receipt_api.get(
    "/receipts/{receipt_id}",
    status_code=200,
    response_model=ReceiptItemEnvelope,
)
def show_receipt(
    receipt_id: UUID, receipts: ReceiptRepositoryDependable
) -> dict[str, Any] | JSONResponse:
    try:
        return {"receipt": receipts.show(receipt_id)}
    except DoesNotExistError:
        return JSONResponse(
            status_code=404,
            content={"message": f"Receipt with id<{receipt_id}> does not exist."},
        )


@receipt_api.post(
    "/receipts/{receipt_id}",
    status_code=201,
    response_model=ReceiptItemEnvelope,
)
def add_product(
    request: AddProductRequest, receipt_id: UUID, receipts: ReceiptRepositoryDependable
) -> dict[str, Receipt]:
    receipt = receipts.show(receipt_id)
    receipt.add_product(**request.model_dump())

    return {"receipt": receipt}


@receipt_api.patch(
    "/receipts/{receipt_id}",
    status_code=200,
    response_model=EmptyItem,
)
def update_receipt(
    receipt_id: UUID,
    request: UpdateReceiptRequest,
    receipts: ReceiptRepositoryDependable,
) -> dict[str, Receipt] | JSONResponse:
    try:
        receipts.update_status(receipt_id, **request.model_dump())
        return {}
    except DoesNotExistError:
        return JSONResponse(
            status_code=404,
            content={"message": f"Receipt with id<{receipt_id}> does not exist."},
        )


@receipt_api.delete(
    "/receipts/{receipt_id}",
    status_code=200,
    response_model=EmptyItem,
)
def delete_receipt(
    receipt_id: UUID, receipts: ReceiptRepositoryDependable
) -> dict[Any, Any] | JSONResponse:
    try:
        if receipts.show(receipt_id).is_closed():
            return JSONResponse(
                status_code=403,
                content={"message": f"Receipt with id<{receipt_id}> is closed."},
            )
        receipts.delete(receipt_id)
        return {}
    except DoesNotExistError:
        return JSONResponse(
            status_code=404,
            content={"message": f"Receipt with id<{receipt_id}> does not exist."},
        )
