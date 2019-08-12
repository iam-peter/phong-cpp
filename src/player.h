#ifndef PLAYER_H
#define PLAYER_H

#include "racket.h"

#include <QObject>
#include <Qt3DInput/QKeyEvent>

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Racket* m_racket READ racket WRITE setRacket NOTIFY racketChanged)

public:
    enum Command {
        Start = 0,
        Up,
        Down
    };

    explicit Player();

    virtual void keyPressed(Qt3DInput::QKeyEvent* event);
    virtual void keyReleased(Qt3DInput::QKeyEvent* event);

    void setRacket(Racket* racket);
    Racket* racket() const;

signals:
    void racketChanged(Racket*);

private:
    std::vector<int> m_keyBinding;
    Racket* m_racket;
};

#endif // PLAYER_H
