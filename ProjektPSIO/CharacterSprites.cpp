#include "CharacterSprites.h"

CharacterSprites::CharacterSprites()
{
    currentFrame = 0;

    sprites =
    {
        &bodySprite,
        &headSprite,
        &torsoSprite,
        &armsSprite,
        &legsSprite,
        &feetSprite
    };
}

const float SPRITE_ORIGIN_X = 22.f;
const float SPRITE_ORIGIN_Y = 15.f;

void CharacterSprites::loadBody(
    const std::string& path
)
{
    bodyTexture.loadFromFile(path);

    bodySprite.setTexture(
        bodyTexture
    );


    bodySprite.setScale(
        2.f,
        2.f
    );

    bodySprite.setTextureRect(
        sf::IntRect(
            0,
            0,
            64,
            64
        )
    );
}

void CharacterSprites::loadHead(
    const std::string& path
)
{
    headTexture.loadFromFile(path);

    headSprite.setTexture(
        headTexture
    );

    headSprite.setScale(
        2.f,
        2.f
    );

    headSprite.setTextureRect(
        sf::IntRect(
            0,
            0,
            64,
            64
        )
    );
}

void CharacterSprites::loadTorso(
    const std::string& path
)
{
    torsoTexture.loadFromFile(path);

    torsoSprite.setTexture(
        torsoTexture
    );

    torsoSprite.setScale(
        2.f,
        2.f
    );

    torsoSprite.setTextureRect(
        sf::IntRect(
            0,
            0,
            64,
            64
        )
    );
}

void CharacterSprites::loadLegs(
    const std::string& path
)
{
    legsTexture.loadFromFile(path);

    legsSprite.setTexture(
        legsTexture
    );
    
	legsSprite.setScale(
		2.f,
		2.f
	);

    legsSprite.setTextureRect(
        sf::IntRect(
            0,
            0,
            64,
            64
        )
    );
}
void CharacterSprites::loadFeet(
        const std::string & path
    )
    {
        feetTexture.loadFromFile(path);

        feetSprite.setTexture(
            feetTexture
        );

		feetSprite.setScale(
			2.f,
			2.f
		);

		feetSprite.setTextureRect(
			sf::IntRect(
				0,
				0,
				64,
				64
			)
		);
}

void CharacterSprites::loadArms(
    const std::string& path
)
{
    armsTexture.loadFromFile(path);

    armsSprite.setTexture(
        armsTexture
    );


	armsSprite.setScale(
		2.f,
		2.f
	);

	armsSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			64,
			64
		)
	);
}

void CharacterSprites::loadClass(
    CharacterClass characterClass
)
{
    loadBody("assets/sprites/BODY_male.png");

    switch (characterClass)
    {
    case CharacterClass::Warrior:

        
        loadHead("assets/sprites/HEAD_plate_armor_helmet.png");
        loadTorso("assets/sprites/TORSO_plate_armor_torso.png");
        loadLegs("assets/sprites/LEGS_plate_armor_pants.png");
        loadFeet("assets/sprites/FEET_plate_armor_shoes.png");
        loadArms("assets/sprites/TORSO_plate_armor_arms_shoulders.png");

        break;

    case CharacterClass::Berserker:

        loadHead("assets/sprites/HEAD_hair_blonde.png");
        loadTorso("assets/sprites/TORSO_chain_armor_jacket_purple.png");
        loadFeet("assets/sprites/FEET_shoes_brown.png");
        loadArms("assets/sprites/TORSO_leather_armor_bracers.png");
        

        break;

    case CharacterClass::Thug:

        loadHead("assets/sprites/HEAD_robe_hood.png");
        loadTorso("assets/sprites/TORSO_robe_shirt_brown.png");
        loadLegs("assets/sprites/LEGS_robe_skirt.png");
        loadFeet("assets/sprites/FEET_shoes_brown.png");


        break;  

    case CharacterClass::Ranger:

        loadHead("assets/sprites/HEAD_leather_armor_hat.png");
        loadTorso("assets/sprites/TORSO_leather_armor_shirt_white.png");
        loadLegs("assets/sprites/LEGS_pants_greenish.png");
        loadFeet("assets/sprites/FEET_shoes_brown.png");
        loadArms("assets/sprites/TORSO_leather_armor_shoulders.png");

        break;
    }
}

void CharacterSprites::setPosition(
    float x,
    float y
)
{
    for (auto sprite : sprites)
    {
        sprite->setPosition(
            x,
            y
        );
    }
}

void CharacterSprites::draw(
    sf::RenderWindow& window
)
{
    window.draw(bodySprite);

    window.draw(legsSprite);

    window.draw(feetSprite);

    window.draw(torsoSprite);

    window.draw(armsSprite);

    window.draw(headSprite);
}

void CharacterSprites::setFrame(
    int frame,
    int row
)
{
    sf::IntRect frameRect(
        frame * 64,
        row * 64,
        64,
        64
    );
    for (auto sprite : sprites)
    {
        sprite->setTextureRect(
            frameRect
        );
    }
}

void CharacterSprites::setFacingRight(
    bool facingRight
)
{
    float scaleX = 2.f; 

    if (!facingRight)
    {
        scaleX = -2.f;
    }

    for (auto sprite : sprites)
    {
        sprite->setScale(
            scaleX,
            2.f
        );
    }

    float originX =
        facingRight
        ? SPRITE_ORIGIN_X
        : SPRITE_ORIGIN_X + 20.f;

    for (auto sprite : sprites)
    {
        sprite->setOrigin(
            originX,
            SPRITE_ORIGIN_Y
        );
    }
}

void CharacterSprites::setColor(
    const sf::Color& color
)
{
    for (auto sprite : sprites)
    {
        sprite->setColor(
            color
        );
    }
}

