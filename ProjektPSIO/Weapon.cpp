#include "Weapon.h"

Weapon::Weapon(
    float x,
    float y,
    float damage,
    float attackCooldown,
    float knockback,
    sf::Vector2f hitboxSize
)
{
    this->damage = damage;
    this->attackCooldown = attackCooldown;
    this->knockback = knockback;
    this->hitboxSize = hitboxSize;

    body.setSize(
        sf::Vector2f(80.f, 20.f)
    );

    body.setPosition(x, y);

    sprite.setPosition(
        x,
        y
    );

    dropped = true;
    lifeTimer = 0;


}

WeaponAnimationType
Weapon::getAnimationType() const
{
    return animationType;
}

void Weapon::draw(
    sf::RenderWindow& window
)
{

    if (dropped)
    {
        sprite.setTexture(
            pickupTexture
        );
    }
    else
    {
        sprite.setTexture(
            texture
        );
    }

    if (shouldBlink())
    {
        if ((lifeTimer / 10) % 2 == 0)
        {
            return;
        }
    }

    window.draw(
        sprite
    );
}

sf::FloatRect Weapon::getBounds() const
{
    return body.getGlobalBounds();
}

float Weapon::getDamage() const
{
    return damage;
}

float Weapon::getAttackCooldown() const
{
    return attackCooldown;
}

float Weapon::getKnockback() const
{
    return knockback;
}

sf::Vector2f Weapon::getHitboxSize() const
{
    return hitboxSize;
}

void Weapon::setDropped(
    bool value
)
{
    dropped = value;
}

bool Weapon::isDropped() const
{
    return dropped;
}

void Weapon::update()
{
    lifeTimer++;
}

bool Weapon::shouldDespawn() const
{
    return lifeTimer > 15.f*60.f;
}



void Weapon::setPosition(
    float x,
    float y
)
{
    body.setPosition(x, y);

    sprite.setPosition(
        x,
        y
    );
}


sf::Vector2f Weapon::getPosition() const
{
    return body.getPosition();
}

void Weapon::setFacingRight(
    bool facingRight
)
{
    if (facingRight)
    {
        sprite.setScale(2.f, 2.f);
    }
    else
    {
        sprite.setScale(
            -2.f,
            2.f
        );
    }
}

bool Weapon::shouldBlink() const
{
    return lifeTimer > 12.f*60.f;
}


MeleeWeapon::MeleeWeapon(
    float x,
    float y,
    float damage,
    float attackCooldown,
    float knockback,
    sf::Vector2f hitboxSize
)
    : Weapon(
        x,
        y,
        damage,
        attackCooldown,
        knockback,
        hitboxSize
    )
{
}

Sword::Sword(float x, float y)
    : MeleeWeapon(
        x,
        y,
        2.f,
        25.f,
        18.f,
        sf::Vector2f(60.f, 50.f)
    )
{
    texture.loadFromFile(
        "assets/sprites/sword.png"
    );

    pickupTexture.loadFromFile(
        "assets/sprites/sword_pickup.png"
    );

    sprite.setScale(
        2.f,
        2.f
    );

    sprite.setOrigin(
        4.f,
        30.f
    );

    animationType =
        WeaponAnimationType::Swing;

}

std::unique_ptr<Weapon> Sword::clone() const
{
    return std::make_unique<Sword>(*this);
}

std::string Sword::getName() const
{
    return "Sword";
}

Katana::Katana(float x, float y)
    : MeleeWeapon(
        x,
        y,
        1.f,
        10.f,
        12.f,
        sf::Vector2f(60.f, 40.f)
    )
{
    texture.loadFromFile(
        "assets/sprites/katana.png"
    );

    pickupTexture.loadFromFile(
        "assets/sprites/katana_pickup.png"
    );

    sprite.setScale(
        2.f,
        2.f
    );

    sprite.setOrigin(
        5.f,
        30.f
    );

    animationType =
        WeaponAnimationType::Swing;
}

std::unique_ptr<Weapon> Katana::clone() const
{
    return std::make_unique<Katana>(*this);
}

std::string Katana::getName() const
{
    return "Katana";
}

Club::Club(float x, float y)
    : MeleeWeapon(
        x,
        y,
        3.f,
        40.f,
        35.f,
        sf::Vector2f(60.f, 70.f)
    )
{
    texture.loadFromFile(
        "assets/sprites/club.png"
    );

    pickupTexture.loadFromFile(
        "assets/sprites/club_pickup.png"
    );

    sprite.setScale(
        2.f,
        2.f
    );

    sprite.setOrigin(
        1.f,
        27.f
    );

    animationType =
        WeaponAnimationType::Swing;
}

std::unique_ptr<Weapon> Club::clone() const
{
    return std::make_unique<Club>(*this);
}

std::string Club::getName() const
{
    return "Club";
}

Spear::Spear(float x, float y)
    : MeleeWeapon(
        x,
        y,
        2.f,
        30.f,
        20.f,
        sf::Vector2f(100.f, 25.f)
    )
{
    texture.loadFromFile(
        "assets/sprites/spear.png"
    );

    pickupTexture.loadFromFile(
        "assets/sprites/spear_pickup.png"
    );

    sprite.setScale(
        2.f,
        2.f
    );

    sprite.setOrigin(
        2.f,
        30.f
    );

    animationType =
        WeaponAnimationType::Thrust;
 
}

std::unique_ptr<Weapon> Spear::clone() const
{
    return std::make_unique<Spear>(*this);
}

std::string Spear::getName() const
{
    return "Spear";
}

Pistol::Pistol(float x, float y)
    : Weapon(
        x,
        y,
        2.f,
        20.f,
        5.f,
        sf::Vector2f(0.f, 0.f)
    )
{
    texture.loadFromFile(
        "assets/sprites/pistol.png"
    );
    pickupTexture.loadFromFile(
        "assets/sprites/pistol_pickup.png"
    );

    sprite.setScale(
        2.f,
        2.f
    );

    sprite.setOrigin(
        8.f,
        8.f
    );

    ammo = 8;

	animationType =
		WeaponAnimationType::Recoil;
}

int Pistol::getAmmo() const
{
    return ammo;
}

void Pistol::useAmmo()
{
    if (ammo > 0)
    {
        ammo--;
    }
}

std::unique_ptr<Weapon> Pistol::clone() const
{
    return std::make_unique<Pistol>(*this);
}

std::string Pistol::getName() const
{
    return "Pistol";
}

void Weapon::setRotation(
    float angle
)
{
    sprite.setRotation(angle);
}