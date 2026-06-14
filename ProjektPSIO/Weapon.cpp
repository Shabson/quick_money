#include "Weapon.h"

Weapon::Weapon(
    float x,
    float y,
    float damage,
    float attackCooldown,
    float knockback,
    sf::Vector2f hitboxSize,
    sf::Color color
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

    body.setFillColor(color);

    dropped = false;
    droppedTimer = 0;
}

void Weapon::draw(sf::RenderWindow& window)
{
    if (texture.getSize().x > 0)
    {
        window.draw(sprite);
    }
    else
    {
        window.draw(body);
    }
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

    if (value)
    {
        droppedTimer = 0;
    }
}

bool Weapon::isDropped() const
{
    return dropped;
}

void Weapon::update()
{
    if (dropped)
    {
        droppedTimer++;
    }
}

bool Weapon::shouldDespawn() const
{
    return dropped
        &&
        droppedTimer > 900;
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
        sprite.setRotation(20.f);
    }
    else
    {
        sprite.setScale(
            -2.f,
            2.f
        );

        sprite.setRotation(
            -20.f
        );
    }
}


MeleeWeapon::MeleeWeapon(
    float x,
    float y,
    float damage,
    float attackCooldown,
    float knockback,
    sf::Vector2f hitboxSize,
    sf::Color color
)
    : Weapon(
        x,
        y,
        damage,
        attackCooldown,
        knockback,
        hitboxSize,
        color
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
        sf::Vector2f(100.f, 40.f),
        sf::Color::White
    )
{
    texture.loadFromFile(
        "assets/sprites/sword.png"
    );

    sprite.setTexture(
        texture
    );

    sprite.setScale(
        2.f,
        2.f
    );

    sprite.setOrigin(
        2.f,
        16.f
    );

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
        sf::Vector2f(140.f, 30.f),
        sf::Color::Cyan
    )
{
    texture.loadFromFile(
        "assets/sprites/katana.png"
    );

    sprite.setTexture(texture);

    sprite.setScale(
        2.f,
        2.f
    );

    sprite.setOrigin(
        8.f,
        8.f
    );
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
        sf::Vector2f(90.f, 50.f),
        sf::Color(139, 69, 19)
    )
{
    texture.loadFromFile(
        "assets/sprites/club.png"
    );

    sprite.setTexture(texture);

    sprite.setScale(
        2.f,
        2.f
    );

    sprite.setOrigin(
        8.f,
        8.f
    );
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
        sf::Vector2f(180.f, 25.f),
        sf::Color::Yellow
    )
{
    texture.loadFromFile(
        "assets/sprites/spear.png"
    );

    sprite.setTexture(texture);

    sprite.setScale(
        2.f,
        2.f
    );

    sprite.setOrigin(
        8.f,
        8.f
    );
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
        sf::Vector2f(0.f, 0.f),
        sf::Color::Magenta
    )
{
    texture.loadFromFile(
        "assets/sprites/pistol.png"
    );

    sprite.setTexture(texture);

    sprite.setScale(
        2.f,
        2.f
    );

    sprite.setOrigin(
        8.f,
        8.f
    );

}

std::unique_ptr<Weapon> Pistol::clone() const
{
    return std::make_unique<Pistol>(*this);
}

std::string Pistol::getName() const
{
    return "Pistol";
}

