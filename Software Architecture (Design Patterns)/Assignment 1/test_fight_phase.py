from constants import BASE_POWER, PRAY_WIN_STR, PREDATOR_WIN_STR
from test_characteristics import Claws, Fangs, FightCharacteristics
from test_evolution_phase import Pray, Predator


class Fight:
    def __init__(self, predator: Predator, pray: Pray):
        self.predator = predator
        self.pray = pray

    def fight(self) -> None:
        while True:
            pray_health = self.pray.get_health_object().get_health()
            if pray_health <= 0:
                print(PREDATOR_WIN_STR)
                break

            predator_health = self.predator.get_health_object().get_health()
            if predator_health <= 0:
                print(PRAY_WIN_STR)
                break

            predator_power = Power(self.predator.get_fight_object())
            predator_damage = predator_power.get_damage()
            self.pray.get_health_object().decrease_by(predator_damage)

            pray_power = Power(self.pray.get_fight_object())
            pray_damage = pray_power.get_damage()
            self.predator.get_health_object().decrease_by(pray_damage)


class Power:
    def __init__(self, fight_characteristics: FightCharacteristics):
        fangs = fight_characteristics.get_fangs_object()
        claws = fight_characteristics.get_claws_object()
        self.damage = claws.get_damage(fangs.get_damage(BASE_POWER))

    def get_damage(self) -> int:
        return self.damage


def test_min_damage() -> None:
    fangs = Fangs(1)
    claws = Claws(2)
    fight_characteristics = FightCharacteristics(claws, fangs)
    assert Power(fight_characteristics).get_damage() == 6


def test_max_damage() -> None:
    fangs = Fangs(3)
    claws = Claws(4)
    fight_characteristics = FightCharacteristics(claws, fangs)
    assert Power(fight_characteristics).get_damage() == 36
