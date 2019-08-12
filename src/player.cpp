#include "player.h"

Player::Player():
    QObject(),
    m_keyBinding({Qt::Key_Return, Qt::Key_Up, Qt::Key_Down}),
    m_racket()
{
}

void Player::keyPressed(Qt3DInput::QKeyEvent* event)
{
    if (event->key() == m_keyBinding[Command::Start])
    {
    }
    else if (event->key() == m_keyBinding[Command::Up])
    {
        if (m_racket)
        {
            // Move racket up
        }
    }
    else if (event->key() == m_keyBinding[Command::Down])
    {
        if (m_racket)
        {
            // Move racket down
        }
    }

    event->setAccepted(true);
}

void Player::keyReleased(Qt3DInput::QKeyEvent* event)
{
    event->setAccepted(true);
}

void Player::setRacket(Racket* racket)
{
    m_racket = racket;
    emit racketChanged(racket);
}

Racket* Player::racket() const
{
    return m_racket;
}
