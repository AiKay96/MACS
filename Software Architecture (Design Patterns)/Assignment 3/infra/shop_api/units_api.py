from typing import Any
from uuid import UUID

from fastapi import APIRouter
from pydantic import BaseModel
from starlette.responses import JSONResponse

from DesPatterns.core.errors import DoesNotExistError
from DesPatterns.core.units import Unit
from DesPatterns.infra.shop_api.dependables import UnitRepositoryDependable

unit_api = APIRouter(tags=["Units"])


class CreateUnitRequest(BaseModel):
    name: str


class UnitItem(BaseModel):
    id: UUID
    name: str


class UnitItemEnvelope(BaseModel):
    unit: UnitItem


class UnitListEnvelope(BaseModel):
    units: list[UnitItem]


@unit_api.post(
    "/units",
    status_code=201,
    response_model=UnitItemEnvelope,
)
def create_unit(
    request: CreateUnitRequest, units: UnitRepositoryDependable
) -> dict[str, Unit]:
    unit = Unit(**request.model_dump())
    units.create(unit)

    return {"unit": unit}


@unit_api.get(
    "/units/{unit_id}",
    status_code=200,
    response_model=UnitItemEnvelope,
)
def show_unit(
    unit_id: UUID, units: UnitRepositoryDependable
) -> dict[str, Any] | JSONResponse:
    try:
        return {"unit": units.show(unit_id)}
    except DoesNotExistError:
        return JSONResponse(
            status_code=404,
            content={"message": f"Unit with id<{unit_id}> does not exist."},
        )


@unit_api.get("/units", response_model=UnitListEnvelope)
def show_all(units: UnitRepositoryDependable) -> dict[str, list[Unit]]:
    return {"units": units.show_all()}
