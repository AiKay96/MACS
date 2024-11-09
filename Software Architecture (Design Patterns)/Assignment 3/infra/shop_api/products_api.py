from typing import Any
from uuid import UUID

from fastapi import APIRouter
from pydantic import BaseModel
from starlette.responses import JSONResponse

from DesPatterns.core.errors import DoesNotExistError
from DesPatterns.core.products import Product
from DesPatterns.infra.shop_api.dependables import ProductRepositoryDependable

product_api = APIRouter(tags=["Products"])


class EmptyItem(BaseModel):
    pass


class UpdateProductRequest(BaseModel):
    price: int


class CreateProductRequest(BaseModel):
    unit_id: UUID
    name: str
    barcode: str
    price: int


class ProductItem(BaseModel):
    id: UUID
    unit_id: UUID
    name: str
    barcode: str
    price: int


class ProductItemEnvelope(BaseModel):
    product: ProductItem


class ProductListEnvelope(BaseModel):
    products: list[ProductItem]


@product_api.post(
    "/products",
    status_code=201,
    response_model=ProductItemEnvelope,
)
def create_product(
    request: CreateProductRequest, products: ProductRepositoryDependable
) -> dict[str, Product]:
    product = Product(**request.model_dump())
    products.create(product)

    return {"product": product}


@product_api.get(
    "/products/{product_id}",
    status_code=200,
    response_model=ProductItemEnvelope,
)
def show_product(
    product_id: UUID, products: ProductRepositoryDependable
) -> dict[str, Any] | JSONResponse:
    try:
        product = products.show(product_id)
        return {"product": product}
    except DoesNotExistError:
        return JSONResponse(
            status_code=404,
            content={"message": f"Product with id<{product_id}> does not exist."},
        )


@product_api.get("/products", response_model=ProductListEnvelope)
def show_all(products: ProductRepositoryDependable) -> dict[str, list[Product]]:
    return {"products": products.show_all()}


@product_api.patch(
    "/products/{product_id}",
    status_code=200,
    response_model=EmptyItem,
)
def update_product(
    product_id: UUID,
    request: UpdateProductRequest,
    products: ProductRepositoryDependable,
) -> dict[str, Product] | JSONResponse:
    try:
        products.update(product_id, **request.model_dump())
        return {}
    except DoesNotExistError:
        return JSONResponse(
            status_code=404,
            content={"message": f"Product with id<{product_id}> does not exist."},
        )
