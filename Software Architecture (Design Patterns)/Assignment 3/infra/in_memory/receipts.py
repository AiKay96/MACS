from dataclasses import dataclass, field
from uuid import UUID

from DesPatterns.core.errors import DoesNotExistError
from DesPatterns.core.receipts import Receipt


@dataclass
class ReceiptInMemory:
    receipts: dict[UUID, Receipt] = field(default_factory=dict)

    def create(self, receipt: Receipt) -> None:
        self.receipts[receipt.id] = receipt

    def show(self, receipt_id: UUID) -> Receipt:
        try:
            return self.receipts[receipt_id]
        except KeyError:
            raise DoesNotExistError(receipt_id)

    def update_status(self, receipt_id: UUID, status: str) -> Receipt:
        self.receipts[receipt_id].update_status(status)
        return self.receipts[receipt_id]

    def delete(self, receipt_id: UUID) -> None:
        try:
            receipt = self.receipts[receipt_id]
            if receipt.is_closed():
                raise DoesNotExistError(
                    receipt_id, "Receipt is closed and cannot be deleted."
                )
            del self.receipts[receipt_id]
        except KeyError:
            raise DoesNotExistError(receipt_id)

    def get_number_of_receipts(self) -> int:
        return len(self.receipts)

    def get_revenue(self) -> int:
        return sum(receipt.total for receipt in self.receipts.values())
