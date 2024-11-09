import os
from dataclasses import dataclass, field
from typing import Any
from unittest.mock import ANY
from uuid import uuid4

import pytest
from faker import Faker
from fastapi.testclient import TestClient

from DesPatterns.infra.in_database.receipts import ReceiptInDatabase
from DesPatterns.runner.setup import init_app


@pytest.fixture
def client() -> TestClient:
    return TestClient(init_app())


@dataclass
class Fake:
    faker: Faker = field(default_factory=Faker)

    @staticmethod
    def receipt() -> dict[str, Any]:
        return {"status": "open", "products": [], "total": 0}

    def receipt_product(self) -> dict[str, Any]:
        return {
            "product_id": self.faker.uuid4(),
            "quantity": self.faker.random_int(),
            "price": self.faker.random_int(),
        }

    @staticmethod
    def status() -> dict[str, Any]:
        return {
            "status": "closed",
        }


def clear_tables() -> None:
    if os.getenv("REPOSITORY_KIND", "memory") == "sqlite":
        ReceiptInDatabase().clear_tables()


def test_should_not_read_unknown(client: TestClient) -> None:
    clear_tables()
    unknown_id = uuid4()

    response = client.get(f"/receipts/{unknown_id}")

    assert response.status_code == 404
    assert response.json() == {
        "message": f"Receipt with id<{unknown_id}> does not exist."
    }


def test_should_create(client: TestClient) -> None:
    clear_tables()
    receipt = Fake().receipt()

    response = client.post("/receipts")

    assert response.status_code == 201
    assert response.json() == {"receipt": {"id": ANY, **receipt}}


def test_should_persist(client: TestClient) -> None:
    clear_tables()
    receipt = Fake().receipt()

    response = client.post("/receipts", json=receipt)
    receipt_id = response.json()["receipt"]["id"]

    response = client.get(f"/receipts/{receipt_id}")

    assert response.status_code == 200
    assert response.json() == {"receipt": {"id": receipt_id, **receipt}}


def test_add_product(client: TestClient) -> None:
    clear_tables()
    receipt = Fake().receipt()

    response = client.post("/receipts", json=receipt)
    receipt_id = response.json()["receipt"]["id"]

    product = Fake().receipt_product()
    client.post(f"/receipts/{receipt_id}", json=product)

    response = client.get(f"/receipts/{receipt_id}")

    assert response.status_code == 200
    assert response.json()["receipt"]["id"] == receipt_id
    assert response.json()["receipt"]["status"] == receipt["status"]
    assert len(response.json()["receipt"]["products"]) != 0


def test_update_receipt(client: TestClient) -> None:
    clear_tables()
    receipt = Fake().receipt()

    response = client.post("/receipts", json=receipt)
    receipt_id = response.json()["receipt"]["id"]

    status = Fake().status()
    client.patch(f"/receipts/{receipt_id}", json=status)

    response = client.get(f"/receipts/{receipt_id}")

    assert response.status_code == 200
    assert response.json()["receipt"]["status"] == status["status"]


def test_delete_receipt(client: TestClient) -> None:
    clear_tables()
    receipt = Fake().receipt()

    response = client.post("/receipts", json=receipt)
    receipt_id = response.json()["receipt"]["id"]

    response = client.delete(f"/receipts/{receipt_id}")

    assert response.status_code == 200

    response = client.get(f"/receipts/{receipt_id}")

    assert response.status_code == 404


def test_delete_closed_receipt(client: TestClient) -> None:
    clear_tables()
    receipt = Fake().receipt()

    response = client.post("/receipts", json=receipt)
    receipt_id = response.json()["receipt"]["id"]

    status = Fake().status()
    client.patch(f"/receipts/{receipt_id}", json=status)

    response = client.delete(f"/receipts/{receipt_id}")

    assert response.status_code == 403
    assert response.json() == {"message": f"Receipt with id<{receipt_id}> is closed."}


def test_should_not_delete_unknown(client: TestClient) -> None:
    clear_tables()
    unknown_id = uuid4()

    response = client.delete(f"/receipts/{unknown_id}")

    assert response.status_code == 404
    assert response.json() == {
        "message": f"Receipt with id<{unknown_id}> does not exist."
    }
