from __future__ import annotations

from constants import PRAY_WIN_STR
from test_evolution_phase import Pray, Predator, print_info
from test_fight_phase import Fight
from test_movement import MyStrategy


class Chase:
    def __init__(self) -> None:
        self.predator = Predator(MyStrategy())
        print_info(self.predator)
        self.pray = Pray(MyStrategy())
        print_info(self.pray)

    def process(self) -> None:
        while True:
            predator_location = self.predator.get_location_object()
            prey_location = self.pray.get_location_object()

            if predator_location.is_greater_than(prey_location):
                fight = Fight(self.predator, self.pray)
                fight.fight()
                break

            self.predator.movement()
            self.pray.movement()

            predator_stamina = self.predator.get_stamina_object().get_stamina()
            if predator_stamina <= 0:
                print(PRAY_WIN_STR)
                break
