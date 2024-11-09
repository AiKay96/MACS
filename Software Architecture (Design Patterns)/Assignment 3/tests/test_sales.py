from dataclasses import dataclass, field
from typing import Any

import pytest
from faker import Faker
from fastapi.testclient import TestClient

from DesPatterns.runner.setup import init_app


@pytest.fixture
def client() -> TestClient:
    return TestClient(init_app())


@dataclass
class Fake:
    faker: Faker = field(default_factory=Faker)

    @staticmethod
    def sale() -> dict[str, Any]:
        return {
            "n_receipts": 0,
            "revenue": 0,
        }

    def receipt_product(self) -> dict[str, Any]:
        return {
            "product_id": self.faker.uuid4(),
            "quantity": self.faker.random_int(),
            "price": self.faker.random_int(),
        }

    def receipt(self) -> dict[str, Any]:
        return {"status": "open", "products": [], "total": self.faker.random_int()}


def test_get_all_sales_on_empty(client: TestClient) -> None:
    response = client.get("/sales")

    assert response.status_code == 200
    sale = Fake.sale()
    assert response.json() == {"sales": sale}


def test_get_all_sales(client: TestClient) -> None:
    response1 = client.post("/receipts")
    receipt_id1 = response1.json()["receipt"]["id"]
    product1 = Fake().receipt_product()
    client.post(f"/receipts/{receipt_id1}", json=product1)
    total_revenue = product1["price"] * product1["quantity"]

    response2 = client.post("/receipts")
    receipt_id2 = response2.json()["receipt"]["id"]
    product2 = Fake().receipt_product()
    client.post(f"/receipts/{receipt_id2}", json=product2)
    total_revenue += product2["price"] * product2["quantity"]

    response = client.get("/sales")

    assert response.status_code == 200
    expected_sales = {"sales": {"n_receipts": 2, "revenue": total_revenue}}
    assert response.json() == expected_sales
