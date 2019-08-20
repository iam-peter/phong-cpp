#ifndef PLAYER_H
#define PLAYER_H

#include "racket.h"

#include <QObject>
#include <Qt3DInput/QKeyEvent>

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(Racket* m_racket READ racket WRITE setRacket NOTIFY racketChanged)
    Q_PROPERTY(unsigned m_score READ score WRITE setScore NOTIFY scoreChanged)

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

    void setName(const QString& name);
    QString name() const;

    void setScore(unsigned score);
    unsigned score() const;

signals:
    void nameChanged(const QString&);
    void racketChanged(Racket*);
    void scoreChanged(unsigned);

private:
    std::vector<int> m_keyBinding;
    QString m_name;
    Racket* m_racket;
    unsigned m_score;
};

#endif // PLAYER_H
