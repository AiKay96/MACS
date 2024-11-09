from dataclasses import dataclass, field
from uuid import UUID

from DesPatterns.core.errors import DoesNotExistError
from DesPatterns.core.units import Unit


@dataclass
class UnitInMemory:
    units: dict[UUID, Unit] = field(default_factory=dict)

    def create(self, unit: Unit) -> Unit:
        self.units[unit.id] = unit
        return unit

    def show(self, unit_id: UUID) -> Unit:
        try:
            return self.units[unit_id]
        except KeyError:
            raise DoesNotExistError(unit_id)

    def show_all(self) -> list[Unit]:
        return list(self.units.values())
