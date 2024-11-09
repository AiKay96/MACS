from __future__ import annotations

from dataclasses import dataclass


@dataclass
class Sale:
    n_receipts: int
    revenue: int
