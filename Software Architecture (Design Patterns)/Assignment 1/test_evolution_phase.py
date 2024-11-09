from __future__ import annotations

from random import randint

from constants import (
    DASHES,
    END_POSITION,
    END_STAMINA,
    MAX_CLAW_COEFFICIENT,
    MAX_FANG_COEFFICIENT,
    MAX_HEALTH,
    MAX_LEGS,
    MAX_WINGS,
    MIN_CLAW_COEFFICIENT,
    MIN_FANG_COEFFICIENT,
    MIN_LEGS,
    MIN_WINGS,
    PRAY_STR,
    PREDATOR_POSITION,
    PREDATOR_STR,
    START_POSITION,
    START_STAMINA,
)
from test_characteristics import (
    Claws,
    Fangs,
    FightCharacteristics,
    Health,
    Legs,
    MovementCharacteristics,
    Stamina,
    Wings,
)
from test_movement import Location, MovementStrategy, MyStrategy


class Character:
    def __init__(
        self,
        location: Location = Location(),
        message: str = "",
        strategy: MovementStrategy = MyStrategy(),
    ):
        stamina = randint(START_STAMINA, END_STAMINA)
        legs = Legs(randint(MIN_LEGS, MAX_LEGS))
        wings = Wings(randint(MIN_WINGS, MAX_WINGS))
        claws = Claws(randint(MIN_CLAW_COEFFICIENT, MAX_CLAW_COEFFICIENT))
        fangs = Fangs(randint(MIN_FANG_COEFFICIENT, MAX_FANG_COEFFICIENT))

        self.strategy = strategy
        self.location = location
        self.message = message
        self.stamina = Stamina(stamina)
        self.health = Health()
        self.move_characteristics = MovementCharacteristics(legs, wings)
        self.fight = FightCharacteristics(claws, fangs)

    def get_location_object(self) -> Location:
        return self.location

    def get_message(self) -> str:
        return self.message

    def get_stamina_object(self) -> Stamina:
        return self.stamina

    def get_health_object(self) -> Health:
        return self.health

    def get_movement_object(self) -> MovementCharacteristics:
        return self.move_characteristics

    def get_fight_object(self) -> FightCharacteristics:
        return self.fight

    def movement(self) -> None:
        self.strategy.move(self.location, self.stamina, self.move_characteristics)


class Predator(Character):
    def __init__(self, strategy: MovementStrategy = MyStrategy()) -> None:
        location = Location(PREDATOR_POSITION)
        super().__init__(location, PREDATOR_STR, strategy)


class Pray(Character):
    def __init__(self, strategy: MovementStrategy = MyStrategy()) -> None:
        pray_position = randint(START_POSITION, END_POSITION)
        location = Location(pray_position)
        super().__init__(location, PRAY_STR, strategy)


def print_info(character: Character) -> None:
    print()
    print(DASHES)
    print(character.get_message())
    print(DASHES)
    print(character.get_location_object().get_message())
    print(character.get_stamina_object().get_message())
    print(character.get_health_object().get_message())
    print(character.get_movement_object().get_wings_object().get_message())
    print(character.get_movement_object().get_legs_object().get_message())
    print(character.get_fight_object().get_claws_object().get_message())
    print(character.get_fight_object().get_fangs_object().get_message())


def evolution_phase() -> None:
    predator = Predator()
    pray = Pray()
    print_info(predator)
    print_info(pray)


def test_predator_position() -> None:
    predator = Predator()
    assert predator.get_location_object().get_location() == 0


def test_pray_position() -> None:
    pray = Pray()
    assert pray.get_location_object().get_location() in range(
        START_POSITION, END_POSITION + 1
    )


def test_character_stamina() -> None:
    character = Character()
    assert character.get_stamina_object().get_stamina() in range(
        START_STAMINA, END_STAMINA + 1
    )


def test_character_health() -> None:
    character = Character()
    assert character.get_health_object().get_health() == MAX_HEALTH


def test_character_legs() -> None:
    character = Character()
    assert character.get_movement_object().get_legs_object().get_number() in range(
        MIN_LEGS, MAX_LEGS + 1
    )


def test_character_wings() -> None:
    character = Character()
    assert character.get_movement_object().get_wings_object().get_number() in range(
        MIN_WINGS, MAX_WINGS + 1
    )


def test_character_claws() -> None:
    character = Character()
    assert character.get_fight_object().get_claws_object().get_damage(1) in range(
        MIN_CLAW_COEFFICIENT, MAX_CLAW_COEFFICIENT + 1
    )


def test_character_fangs() -> None:
    character = Character()
    assert character.get_fight_object().get_fangs_object().get_damage(0) in [3, 6, 9]
