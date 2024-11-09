from __future__ import annotations

from typing import Callable

from constants import (
    CLAWS_STR,
    FANGS_STR,
    HEALTH_STR,
    LEGS_STR,
    MAX_HEALTH,
    STAMINA_STR,
    WINGS_STR,
)


class Health:
    def __init__(self, health: int = MAX_HEALTH):
        self.health = health

    def get_health(self) -> int:
        return self.health

    def decrease_by(self, amount: int) -> None:
        self.health -= amount

    def get_message(self) -> str:
        return HEALTH_STR + str(self.health)


class Stamina:
    def __init__(self, stamina: int):
        self.stamina = stamina

    def get_stamina(self) -> int:
        return self.stamina

    def decrease_by(self, amount: int) -> None:
        self.stamina -= amount

    def get_message(self) -> str:
        return STAMINA_STR + str(self.stamina)


class MovementCharacteristics:
    def __init__(self, legs: Legs, wings: Wings):
        self.legs = legs
        self.wings = wings

    def get_legs_object(self) -> Legs:
        return self.legs

    def get_wings_object(self) -> Wings:
        return self.wings


class MovementCharacteristic:
    def __init__(self, number: int, message: str):
        self.number = number
        self.message = message

    def get_number(self) -> int:
        return self.number

    def get_message(self) -> str:
        return self.message


class Legs(MovementCharacteristic):
    def __init__(self, number_of_legs: int):
        message = LEGS_STR + str(number_of_legs)
        super().__init__(number_of_legs, message)


class Wings(MovementCharacteristic):
    def __init__(self, number_of_wings: int):
        message = WINGS_STR + str(number_of_wings)
        super().__init__(number_of_wings, message)


class FightCharacteristics:
    def __init__(self, claws: Claws, fangs: Fangs):
        self.claws = claws
        self.fangs = fangs

    def get_claws_object(self) -> Claws:
        return self.claws

    def get_fangs_object(self) -> Fangs:
        return self.fangs


class FightCharacteristic:
    def __init__(
        self,
        coefficient: int,
        damage_calculator: Callable[[int, int], int],
        message: str,
    ):
        self.coefficient = coefficient
        self.damage_calculator = damage_calculator
        self.message = message

    def get_damage(self, base_power: int) -> int:
        return self.damage_calculator(self.coefficient, base_power)

    def get_message(self) -> str:
        return self.message


def claws_damage_calculator(coefficient: int, base_power: int) -> int:
    return coefficient * base_power


class Claws(FightCharacteristic):
    def __init__(self, claw_coefficient: int):
        message = CLAWS_STR + str(claw_coefficient)
        super().__init__(claw_coefficient, claws_damage_calculator, message)


def fangs_damage_calculator(coefficient: int, base_power: int) -> int:
    return coefficient + base_power


class Fangs(FightCharacteristic):
    def __init__(self, fangs_coefficient: int):
        fangs_coefficient *= 3
        message = FANGS_STR + str(fangs_coefficient)
        super().__init__(fangs_coefficient, fangs_damage_calculator, message)


def test_get_stamina() -> None:
    stamina = Stamina(56)
    assert stamina.get_stamina() == 56


def test_stamina_decrease() -> None:
    stamina = Stamina(5)
    stamina.decrease_by(2)
    assert stamina.get_stamina() == 3


def test_health_default() -> None:
    health = Health()
    assert health.get_health() == 100


def test_get_health() -> None:
    health = Health(50)
    assert health.get_health() == 50


def test_health_decrease() -> None:
    health = Health()
    health.decrease_by(20)
    assert health.get_health() == 80


def test_legs() -> None:
    legs = Legs(1)
    assert legs.get_number() == 1


def test_wings() -> None:
    wings = Wings(2)
    assert wings.get_number() == 2


def test_claws() -> None:
    claws = Claws(3)
    assert claws.get_damage(1) == 3


def test_fangs() -> None:
    fangs = Fangs(2)
    assert fangs.get_damage(0) == 6
