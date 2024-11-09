import os
from dataclasses import dataclass, field
from typing import Any
from unittest.mock import ANY
from uuid import uuid4

import pytest
from faker import Faker
from fastapi.testclient import TestClient

from DesPatterns.infra.in_database.products import ProductInDatabase
from DesPatterns.runner.setup import init_app


@pytest.fixture
def client() -> TestClient:
    return TestClient(init_app())


@dataclass
class Fake:
    faker: Faker = field(default_factory=Faker)

    def product(self) -> dict[str, Any]:
        return {
            "unit_id": self.faker.uuid4(),
            "name": self.faker.word(),
            "barcode": self.faker.word(),
            "price": self.faker.random_int(),
        }

    def price(self) -> dict[str, Any]:
        return {
            "price": self.faker.random_int(),
        }


def clear_tables() -> None:
    if os.getenv("REPOSITORY_KIND", "memory") == "sqlite":
        ProductInDatabase().clear_tables()


def test_should_not_read_unknown(client: TestClient) -> None:
    clear_tables()
    unknown_id = uuid4()

    response = client.get(f"/products/{unknown_id}")

    assert response.status_code == 404
    assert response.json() == {
        "message": f"Product with id<{unknown_id}> does not exist."
    }


def test_should_create(client: TestClient) -> None:
    clear_tables()
    product = Fake().product()

    response = client.post("/products", json=product)

    assert response.status_code == 201
    assert response.json() == {"product": {"id": ANY, **product}}


def test_should_persist(client: TestClient) -> None:
    clear_tables()
    product = Fake().product()

    response = client.post("/products", json=product)
    product_id = response.json()["product"]["id"]

    response = client.get(f"/products/{product_id}")

    assert response.status_code == 200
    assert response.json() == {"product": {"id": product_id, **product}}


def test_update_product(client: TestClient) -> None:
    clear_tables()
    product = Fake().product()

    response = client.post("/products", json=product)
    product_id = response.json()["product"]["id"]

    price = Fake().price()
    client.patch(f"/products/{product_id}", json=price)

    response = client.get(f"/products/{product_id}")

    assert response.status_code == 200
    assert response.json()["product"]["id"] == product_id
    assert response.json()["product"]["unit_id"] == product["unit_id"]
    assert response.json()["product"]["name"] == product["name"]
    assert response.json()["product"]["barcode"] == product["barcode"]
    assert response.json()["product"]["price"] == price["price"]


def test_get_all_products_on_empty(client: TestClient) -> None:
    clear_tables()
    response = client.get("/products")

    assert response.status_code == 200
    assert response.json() == {"products": []}


def test_get_all_products(client: TestClient) -> None:
    clear_tables()
    product = Fake().product()

    response = client.post("/products", json=product)
    product_id = response.json()["product"]["id"]

    response = client.get("/products")

    assert response.status_code == 200
    assert response.json() == {"products": [{"id": product_id, **product}]}
