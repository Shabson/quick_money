#include "AnimatedSprite.h"
#include <cmath>
#include <iostream>

void AnimatedSprite::addAnimationFrame(const sf::IntRect& frame) {
    if (frames_.empty()) {
        setTextureRect(frame); // Ustawia widok na 1. klatkę natychmiast po dodaniu
    }
    frames_.push_back(frame);
}

void AnimatedSprite::updateAnimation(const float& dt) {
    if (frames_.empty()) return;

    accumulator_ += dt;

    while (accumulator_ >= frame_time_) {
        accumulator_ -= frame_time_;

        current_frame_ = (current_frame_ + 1) % frames_.size();
        setTextureRect(frames_[current_frame_]);
    }
}
void AnimatedSprite::setSpeed(float vx, float vy) {
    vx_ = vx;
    vy_ = vy;
}

void AnimatedSprite::moveHorizontal(const float& dt) {
    // Poruszamy się tylko w poziomie korzystając z vx_
    move(vx_ * dt, 0);
}

void AnimatedSprite::jump() {
    vy_ = -600.f; // Siła skoku (Y w górę to wartości ujemne)
}

void AnimatedSprite::applyGravity(const float& dt) {
    float gravity = 500.f; // Siła przyciągania
    vy_ += gravity * dt;    // Zmieniamy prędkość pionową
    move(0, vy_ * dt);      // Wykonujemy ruch w pionie
}

void AnimatedSprite::stopVertical() {
    vy_ = 0.f; // Zatrzymujemy spadanie po dotknięciu platformy
}

void AnimatedSprite::toLeft() {
    if (vx_ > 0) vx_ = -std::abs(vx_); // Upewnij się, że vx jest ujemne
    setScale(-1.f, 1.f);               // Lustrzane odbicie (patrzy w lewo)
}

void AnimatedSprite::toRight() {
    if (vx_ < 0) vx_ = std::abs(vx_);  // Upewnij się, że vx jest dodatnie
    setScale(1.f, 1.f);                // Normalna skala (patrzy w prawo)
}

void AnimatedSprite::bounce(float window_width) {
    sf::FloatRect bounds = getGlobalBounds();
    if (bounds.left < 0) {
        setPosition(bounds.width / 2.f, getPosition().y);
    }
    else if (bounds.left + bounds.width > window_width) {
        setPosition(window_width - bounds.width / 2.f, getPosition().y);
    }
}

sf::Texture loadTexture(const std::string& filename_with_path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename_with_path)) {
        std::cerr << "Could not load texture" << std::endl;
    }
    return texture;
}
