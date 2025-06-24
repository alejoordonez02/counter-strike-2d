#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/game/world/equipment/weapon.h"

class RapidWeapon: public Weapon {
public:
    RapidWeapon(float fire_rate):
        Weapon(WeaponName::NONE, WeaponType::NONE, 100, 100, 1000, 0, fire_rate,
               0, 100, 100, 0, 0) {}
};

class FatHitbox: public Hitbox {
private:
    Position dummy_pos{0, 0};

public:
    FatHitbox(): Hitbox(dummy_pos) {}

    MOCK_METHOD(void, get_attacked, (int), (override));

    std::optional<Position> intersect(
        const Trajectory& /* t */) const override {
        return dummy_pos;
    }
};

class FireRateTest: public ::testing::Test {
protected:
    std::shared_ptr<FatHitbox> hitbox = std::make_shared<FatHitbox>();
    std::vector<std::shared_ptr<Hitbox>> collidables{hitbox};
    std::vector<size_t> idx{0};
    float fire_rate = 1;
    RapidWeapon weapon{fire_rate};
    Position dummy_origin{0, 0};
    Direction dummy_dir{0, 0};

    void SetUp() override {}
};

TEST_F(FireRateTest, WeaponsCanNotAttackImmediatelyAfterBeingEquipped) {
    EXPECT_CALL(*hitbox, get_attacked(::testing::_)).Times(0);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
}

TEST_F(FireRateTest, WeaponsCanAttackAfterFireRateDelayEndsOnceEquipped) {
    weapon.update(1);

    EXPECT_CALL(*hitbox, get_attacked(::testing::_));
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
}

TEST_F(FireRateTest, RepeatedlyAttackingDoesNotAffectFireRate) {
    weapon.update(1);

    EXPECT_CALL(*hitbox, get_attacked(::testing::_)).Times(1);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
}

TEST_F(FireRateTest, WeaponFireDelayRestartsAfterAttacking) {
    weapon.update(1);

    EXPECT_CALL(*hitbox, get_attacked(::testing::_)).Times(1);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
}

TEST_F(FireRateTest, WeaponCannotAttackIfUpdateIsLessThanFireRate) {
    weapon.update(0.5f);

    EXPECT_CALL(*hitbox, get_attacked(::testing::_)).Times(0);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
}

TEST_F(FireRateTest, WeaponCanNotAttackMultipleTimesIfEnoughTimeAccumulates) {
    weapon.update(3);

    EXPECT_CALL(*hitbox, get_attacked(::testing::_)).Times(1);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
}

TEST_F(FireRateTest, WeaponCanAttackAfterMultipleSmallUpdates) {
    weapon.update(0.3f);
    weapon.update(0.3f);
    weapon.update(0.4f);

    EXPECT_CALL(*hitbox, get_attacked(::testing::_)).Times(1);
    weapon.attack(dummy_origin, dummy_dir, collidables, idx);
}

TEST_F(FireRateTest, WeaponDoesNotFailIfNoCollidables) {
    weapon.update(1);
    std::vector<std::shared_ptr<Hitbox>> empty_collidables;
    std::vector<size_t> empty_idx;

    weapon.attack(dummy_origin, dummy_dir, empty_collidables, empty_idx);
}
