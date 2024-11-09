from __future__ import annotations

from typing import Dict, Protocol

from constants import (
    CRAWL_DICT,
    FLY_DICT,
    HOP_DICT,
    LOCATION_STR,
    RUN_DICT,
    START_POSITION,
    WALK_DICT,
)
from test_characteristics import Legs, MovementCharacteristics, Stamina, Wings


class Location:
    def __init__(self, location: int = START_POSITION):
        self.location = location

    def get_location(self) -> int:
        return self.location

    def increment_by(self, increment: int) -> None:
        self.location = self.location + increment

    def is_greater_than(self, other_location: Location) -> bool:
        return self.location >= other_location.get_location()

    def get_message(self) -> str:
        return LOCATION_STR + str(self.location)


class MovementInterface(Protocol):
    def move(
        self, location: Location, stamina: Stamina, movement: MovementCharacteristics
    ) -> None:
        pass


class Movement:
    def __init__(self, following: MovementInterface, constants: Dict[str, int]):
        self.following = following
        self.min_stamina = constants["min_stamina"]
        self.stamina_cost = constants["stamina_cost"]
        self.speed = constants["speed"]
        self.min_legs = constants["min_legs"]
        self.min_wings = constants["min_wings"]

    def move(
        self, location: Location, stamina: Stamina, movement: MovementCharacteristics
    ) -> None:
        stamina_amount = stamina.get_stamina()
        legs = movement.get_legs_object().get_number()
        wings = movement.get_wings_object().get_number()

        enough_stamina = stamina_amount >= self.min_stamina
        enough_characteristic = legs >= self.min_legs and wings >= self.min_wings

        if enough_stamina and enough_characteristic:
            stamina.decrease_by(self.stamina_cost)
            location.increment_by(self.speed)
            return
        self.following.move(location, stamina, movement)


class Fly(Movement):
    def __init__(self, following: MovementInterface):
        super().__init__(following, FLY_DICT)


class Run(Movement):
    def __init__(self, following: MovementInterface):
        super().__init__(following, RUN_DICT)


class Walk(Movement):
    def __init__(self, following: MovementInterface):
        super().__init__(following, WALK_DICT)


class Hop(Movement):
    def __init__(self, following: MovementInterface):
        super().__init__(following, HOP_DICT)


class Crawl(Movement):
    def __init__(self, following: MovementInterface):
        super().__init__(following, CRAWL_DICT)


class NoMove:
    def move(
        self, location: Location, stamina: Stamina, movement: MovementCharacteristics
    ) -> None:
        pass


class MovementStrategy(Protocol):
    movement: Movement

    def move(
        self, location: Location, stamina: Stamina, movement: MovementCharacteristics
    ) -> None:
        self.movement.move(location, stamina, movement)


class MyStrategy(MovementStrategy):
    def __init__(self) -> None:
        self.movement = Fly(Run(Walk(Hop(Crawl(NoMove())))))


def test_get_location() -> None:
    location = Location(15)
    assert location.get_location() == 15


def test_increment_by_location() -> None:
    location = Location(20)
    location.increment_by(10)
    assert location.get_location() == 30


def test_is_greater_than_location() -> None:
    location = Location(5)
    location2 = Location(3)
    assert location.is_greater_than(location2)


def test_movement_fly() -> None:
    strategy = MyStrategy()
    location = Location(0)
    strategy.move(location, Stamina(100), MovementCharacteristics(Legs(2), Wings(2)))
    assert location.get_location() == 8


def test_movement_run() -> None:
    strategy = MyStrategy()
    location = Location(0)
    strategy.move(location, Stamina(60), MovementCharacteristics(Legs(2), Wings(2)))
    assert location.get_location() == 6


def test_movement_walk() -> None:
    strategy = MyStrategy()
    location = Location(0)
    strategy.move(location, Stamina(50), MovementCharacteristics(Legs(2), Wings(2)))
    assert location.get_location() == 4


def test_movement_hop() -> None:
    strategy = MyStrategy()
    location = Location(0)
    strategy.move(location, Stamina(100), MovementCharacteristics(Legs(1), Wings(1)))
    assert location.get_location() == 3


def test_movement_crawl() -> None:
    strategy = MyStrategy()
    location = Location(0)
    strategy.move(location, Stamina(100), MovementCharacteristics(Legs(0), Wings(0)))
    assert location.get_location() == 1
