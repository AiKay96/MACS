from fastapi import APIRouter
from pydantic import BaseModel

from DesPatterns.core.sales import Sale
from DesPatterns.infra.shop_api.dependables import ReceiptRepositoryDependable

sale_api = APIRouter(tags=["Sales"])


class SaleItem(BaseModel):
    n_receipts: int
    revenue: int


class SaleItemEnvelope(BaseModel):
    sales: SaleItem


@sale_api.get(
    "/sales",
    status_code=200,
    response_model=SaleItemEnvelope,
)
def show_sale(receipts: ReceiptRepositoryDependable) -> dict[str, Sale]:
    sale = Sale(receipts.get_number_of_receipts(), receipts.get_revenue())
    return {"sales": sale}
