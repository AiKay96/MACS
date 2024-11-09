START_POSITION = 0
END_POSITION = 50
PREDATOR_POSITION = START_POSITION
START_STAMINA = 50
END_STAMINA = 100
MAX_HEALTH = 100
BASE_POWER = 0
MIN_LEGS = 0
MAX_LEGS = 2
MIN_WINGS = 0
MAX_WINGS = 2
MIN_CLAW_COEFFICIENT = 2
MAX_CLAW_COEFFICIENT = 4
MIN_FANG_COEFFICIENT = 1
MAX_FANG_COEFFICIENT = 3

DASHES = "---------------------------------"
PREDATOR_STR = "PREDATOR DATA:"
PRAY_STR = "PRAY DATA:"
LOCATION_STR = "Location is "
STAMINA_STR = "Stamina is "
HEALTH_STR = "Health is "
CLAWS_STR = "Claws coefficient is "
FANGS_STR = "Fangs coefficient is "
LEGS_STR = "Number of legs is "
WINGS_STR = "Number of wings is "

FLY_DICT = {
    "min_stamina": 80,
    "stamina_cost": 4,
    "speed": 8,
    "min_legs": 0,
    "min_wings": 2,
}

RUN_DICT = {
    "min_stamina": 60,
    "stamina_cost": 4,
    "speed": 6,
    "min_legs": 2,
    "min_wings": 0,
}

WALK_DICT = {
    "min_stamina": 40,
    "stamina_cost": 2,
    "speed": 4,
    "min_legs": 2,
    "min_wings": 0,
}

HOP_DICT = {
    "min_stamina": 20,
    "stamina_cost": 2,
    "speed": 3,
    "min_legs": 1,
    "min_wings": 0,
}

CRAWL_DICT = {
    "min_stamina": 1,
    "stamina_cost": 1,
    "speed": 1,
    "min_legs": 0,
    "min_wings": 0,
}

PRAY_WIN_STR = "Pray ran into infinity!"
PREDATOR_WIN_STR = "Some R-rated things have happened."
