#include "heroEntity.h"

namespace swiftness
{
    Hero::Hero(gf::ResourceManager &resources, gf::Vector2f position, gf::Color4f color, float gravity)
        : m_resources(resources), m_position(position), m_position_start(position), m_velocity(0, 0), m_size(), m_color(color), gravity(GRAVITY), m_jump(false), nb_jumps(0), m_gravity(1), horizontal_g(false), goLeft(false), goRight(false), goUp(false), goDown(false), isOver(false), nb_deaths(0), timer(0.0f), m_gravityDirection(DOWN), m_walljump(0.0f), m_isFlying(false), m_faceDirection(false), m_rotation(0)
    {
        setSize();
        std::cout << "Square size : " << m_size.width << " " << m_size.height << std::endl;
    }

    void Hero::reset(gf::Vector2f entrance)
    {
        m_position = entrance;
        m_position_start = entrance;
        m_velocity = gf::Vector2f(0, 0);
        m_jump = false;
        nb_jumps = 0;
        m_gravity = 1;
        horizontal_g = false;
        goLeft = false;
        goRight = false;
        goUp = false;
        goDown = false;
        isOver = false;
        nb_deaths = 0;
        timer = 0.0f;
        m_gravityDirection = DOWN;
        m_walljump = 0.0f;
        m_isFlying = false;
        m_faceDirection = false;
        m_rotation = 0;
    }

    gf::Vector2f Hero::getPosition() const
    {
        return m_position;
    }

    void Hero::setVelocity(gf::Vector2f velocity)
    {
        m_velocity = velocity;
    }

    /*
    exemple : texture size = 17 x 37 and we want to set the size to 13 x y.
    we calculate the ratio of the texture size and the size we want to set.
    */
    void Hero::setSize() {
        gf::Vector2i size = m_resources.getTexture(TEXTURE_SKIN_PATH).getSize();
        float ratio = (float)size.width / (float)size.height;
        if (ratio > 1) {
            m_size.width = SQUARE_SIZE;
            m_size.height = SQUARE_SIZE / ratio+2;
        } else if (ratio < 1){
            m_size.height = SQUARE_SIZE;
            m_size.width = SQUARE_SIZE * ratio+2;
        } else {
            m_size.width = SQUARE_SIZE;
            m_size.height = SQUARE_SIZE;
        }
    }

    void Hero::setIsFlying(bool isFlying)
    {
        m_isFlying = isFlying;
        m_velocity.x = 0;
        m_velocity.y = 0;
    }

    void Hero::actionUp()
    {
        if (horizontal_g)
        {
            if (m_gravityDirection == RIGHT)
            {
                m_faceDirection = false;
            }
            else
            {
                m_faceDirection = true;
            }
        }
        if (m_isFlying || (horizontal_g && m_velocity.y < SPEED_SQUARE && m_walljump == 0.0f))
        {
            m_velocity.y = -SPEED_SQUARE;
            goUp = true;
        }
    }

    void Hero::actionUpJump()
    {
        if (!horizontal_g && !m_isFlying)
        {
            m_jump = canJump();
            bool walljumpRight = canWallJumpRight();
            bool walljumpLeft = canWallJumpLeft();
            if (m_jump || (nb_jumps < 2 && !walljumpRight && !walljumpLeft))
            {
                m_velocity.y = JUMP * m_gravity;
                nb_jumps = m_jump ? 1 : 2;
            }
            else
            {
                if (walljumpRight)
                {
                    m_velocity.y = WALL_JUMP_HEIGHT * m_gravity;
                    nb_jumps = 1;
                    m_velocity.x = -WALL_JUMP_SPEED;
                    m_walljump = WALL_JUMP_TIME;
                }
                else
                {
                    if (walljumpLeft)
                    {
                        m_velocity.y = WALL_JUMP_HEIGHT * m_gravity;
                        nb_jumps = 1;
                        m_velocity.x = WALL_JUMP_SPEED;
                        m_walljump = WALL_JUMP_TIME;
                    }
                }
            }
            m_jump = false;
        }
    }

    void Hero::actionUpRelease()
    {
        if ((m_isFlying || horizontal_g) && goUp)
        {
            if (m_velocity.y < 0)
            {
                m_velocity.y = 0;
            }
        }
        goUp = false;
    }
    void Hero::actionDown()
    {
        if (horizontal_g)
        {
            if (m_gravityDirection == RIGHT)
            {
                m_faceDirection = true;
            }
            else
            {
                m_faceDirection = false;
            }
        }
        goDown = true;
        if (m_isFlying || (horizontal_g && m_velocity.y > -SPEED_SQUARE && m_walljump == 0.0f))
            m_velocity.y = SPEED_SQUARE;
    }
    void Hero::actionDownRelease()
    {
        if ((m_isFlying || horizontal_g) && goDown)
        {
            if (m_velocity.y > 0)
            {
                m_velocity.y = 0;
            }
        }
        goDown = false;
    }
    void Hero::actionLeft()
    {
        if (!horizontal_g)
        {
            if (m_gravityDirection == DOWN)
            {
                m_faceDirection = true;
            }
            else
            {
                m_faceDirection = false;
            }
        }
        if (m_isFlying || (!horizontal_g && m_velocity.x < SPEED_SQUARE && m_walljump == 0.0f))
        {
            m_velocity.x = -SPEED_SQUARE;
            goLeft = true;
        }
    }

    void Hero::squareReset()
    {
        m_velocity.x = 0;
        m_velocity.y = 0;
    }

    void Hero::actionLeftJump()
    {
        if (horizontal_g && !m_isFlying)
        {
            if (m_gravity > 0)
            {
                bool walljumpRight = canWallJumpRight();
                bool walljumpUp = canWallJumpUp();
                bool wallJumpDown = canWallJumpDown();
                if (walljumpRight || (nb_jumps < 2 && !walljumpUp && !wallJumpDown))
                {
                    m_velocity.x = JUMP * m_gravity;
                    if (walljumpRight)
                    {
                        nb_jumps = 1;
                    }
                    else
                    {
                        nb_jumps = 2;
                    }
                }
                else
                {
                    if (wallJumpDown)
                    {
                        m_velocity.x = WALL_JUMP_HEIGHT * m_gravity;
                        nb_jumps = 1;
                        m_velocity.y = -WALL_JUMP_SPEED;
                        m_walljump = WALL_JUMP_TIME;
                    }
                    else
                    {
                        if (walljumpUp)
                        {
                            m_velocity.x = WALL_JUMP_HEIGHT * m_gravity;
                            nb_jumps = 1;
                            m_velocity.y = WALL_JUMP_SPEED;
                            m_walljump = WALL_JUMP_TIME;
                        }
                    }
                }
            }
        }
    }
    void Hero::actionLeftRelease()
    {
        if ((m_isFlying || !horizontal_g) && goLeft)
        {
            if (m_velocity.x < 0)
            {
                m_velocity.x = 0;
            }
        }
        goLeft = false;
    }
    void Hero::actionRight()
    {
        if (!horizontal_g)
        {
            if (m_gravityDirection == DOWN)
            {
                m_faceDirection = false;
            }
            else
            {
                m_faceDirection = true;
            }
        }
        if (m_isFlying || (!horizontal_g && m_velocity.x > -SPEED_SQUARE && m_walljump == 0.0f))
        {
            m_velocity.x = SPEED_SQUARE;
            goRight = true;
        }
    }

    void Hero::actionRightJump()
    {
        if (horizontal_g && !m_isFlying)
        {
            if (m_gravity < 0)
            {
                bool walljumpLeft = canWallJumpLeft();
                bool walljumpUp = canWallJumpUp();
                bool wallJumpDown = canWallJumpDown();
                if (walljumpLeft || (nb_jumps < 2 && !walljumpUp && !wallJumpDown))
                {
                    m_velocity.x = JUMP * m_gravity;
                    if (walljumpLeft)
                    {
                        nb_jumps = 1;
                    }
                    else
                    {
                        nb_jumps = 2;
                    }
                }
                else
                {
                    if (wallJumpDown)
                    {
                        m_velocity.x = WALL_JUMP_HEIGHT * m_gravity;
                        nb_jumps = 1;
                        m_velocity.y = -WALL_JUMP_SPEED;
                        m_walljump = WALL_JUMP_TIME;
                    }
                    else
                    {
                        if (walljumpUp)
                        {
                            m_velocity.x = WALL_JUMP_HEIGHT * m_gravity;
                            nb_jumps = 1;
                            m_velocity.y = WALL_JUMP_SPEED;
                            m_walljump = WALL_JUMP_TIME;
                        }
                    }
                }
            }
        }
    }
    void Hero::actionRightRelease()
    {
        if ((m_isFlying || !horizontal_g) && goRight)
        {
            if (m_velocity.x > 0)
            {
                m_velocity.x = 0;
            }
        }
        goRight = false;
    }
    void Hero::actionJump()
    {
        if (m_isFlying)
        {
            return;
        }
        if (horizontal_g)
        {
            if (m_gravity > 0)
            {
                bool walljumpRight = canWallJumpRight();
                bool walljumpUp = canWallJumpUp();
                bool wallJumpDown = canWallJumpDown();
                if (walljumpRight || (nb_jumps < 2 && !walljumpUp && !wallJumpDown))
                {
                    m_velocity.x = JUMP * m_gravity;
                    if (walljumpRight)
                    {
                        nb_jumps = 1;
                    }
                    else
                    {
                        nb_jumps = 2;
                    }
                }
                else
                {
                    if (wallJumpDown)
                    {
                        m_velocity.x = WALL_JUMP_HEIGHT * m_gravity;
                        nb_jumps = 1;
                        m_velocity.y = -WALL_JUMP_SPEED;
                        m_walljump = WALL_JUMP_TIME;
                    }
                    else
                    {
                        if (walljumpUp)
                        {
                            m_velocity.x = WALL_JUMP_HEIGHT * m_gravity;
                            nb_jumps = 1;
                            m_velocity.y = WALL_JUMP_SPEED;
                            m_walljump = WALL_JUMP_TIME;
                        }
                    }
                }
            }
            else
            {
                bool walljumpLeft = canWallJumpLeft();
                bool walljumpUp = canWallJumpUp();
                bool wallJumpDown = canWallJumpDown();
                if (walljumpLeft || (nb_jumps < 2 && !walljumpUp && !wallJumpDown))
                {
                    m_velocity.x = JUMP * m_gravity;
                    if (walljumpLeft)
                    {
                        nb_jumps = 1;
                    }
                    else
                    {
                        nb_jumps = 2;
                    }
                }
                else
                {
                    if (wallJumpDown)
                    {
                        m_velocity.x = WALL_JUMP_HEIGHT * m_gravity;
                        nb_jumps = 1;
                        m_velocity.y = -WALL_JUMP_SPEED;
                        m_walljump = WALL_JUMP_TIME;
                    }
                    else
                    {
                        if (walljumpUp)
                        {
                            m_velocity.x = WALL_JUMP_HEIGHT * m_gravity;
                            nb_jumps = 1;
                            m_velocity.y = WALL_JUMP_SPEED;
                            m_walljump = WALL_JUMP_TIME;
                        }
                    }
                }
            }
        }
        else
        {
            m_jump = canJump();
            bool walljumpRight = canWallJumpRight();
            bool walljumpLeft = canWallJumpLeft();
            if (m_jump || (nb_jumps < 2 && !walljumpRight && !walljumpLeft))
            {
                m_velocity.y = JUMP * m_gravity;
                if (m_jump)
                {
                    nb_jumps = 1;
                }
                else
                {
                    nb_jumps = 2;
                }
            }
            else
            {
                if (walljumpRight)
                {
                    m_velocity.y = WALL_JUMP_HEIGHT * m_gravity;
                    nb_jumps = 1;
                    m_velocity.x = -WALL_JUMP_SPEED;
                    m_walljump = WALL_JUMP_TIME;
                }
                else
                {
                    if (walljumpLeft)
                    {
                        m_velocity.y = WALL_JUMP_HEIGHT * m_gravity;
                        nb_jumps = 1;
                        m_velocity.x = WALL_JUMP_SPEED;
                        m_walljump = WALL_JUMP_TIME;
                    }
                }
            }
            m_jump = false;
        }
    }

    void Hero::update(gf::Time time) {
    float dt = time.asSeconds();
    bool walljumpRight = canWallJumpRight();
    bool walljumpLeft = canWallJumpLeft();
    bool walljumpUp = canWallJumpUp();
    bool wallJumpDown = canWallJumpDown();
    timer += dt;
    if (timer > 999.99f) {
        isOver = true;
    }
    m_walljump -= dt;
    if (m_walljump < 0.0f) {
        m_walljump = 0.0f;
    }

    // Vérifiez si la gravité a changé de direction et inversez la taille si nécessaire
    if (horizontal_g != wasHorizontal) { // `wasHorizontal` est une nouvelle variable booléenne membre de la classe
        std::swap(m_size.width, m_size.height); // Échangez la largeur et la hauteur
        wasHorizontal = horizontal_g; // Mettez à jour l'état précédent de la gravité
    }

    // Appliquez la gravité
    if (!m_isFlying) {
        if (horizontal_g) {
            setVelocity(m_velocity + gf::Vector2f(gravity * m_gravity * dt, 0));
            if (!goUp && m_velocity.y < 0.0f && m_velocity.y != -WALL_JUMP_SPEED) {
                m_velocity.y += gravity * 2.5f * dt;
                if (m_velocity.y > 0.0f) m_velocity.y = 0.0f;    
            }
            if (!goDown && m_velocity.y > 0.0f && m_velocity.y != WALL_JUMP_SPEED) {
                m_velocity.y -= gravity * 2.5f * dt;
                if (m_velocity.y < 0.0f) m_velocity.y = 0.0f;    
            }
            // Conditions pour limiter la vitesse et ajuster la gravité...
        } else {
            setVelocity(m_velocity + gf::Vector2f(0, gravity * m_gravity * dt));
            if (!goLeft && m_velocity.x < 0.0f && m_velocity.x != -WALL_JUMP_SPEED) {
                m_velocity.x += gravity * 2.5f * dt;
                if (m_velocity.x > 0.0f) m_velocity.x = 0.0f;    
            }
            if (!goRight && m_velocity.x > 0.0f && m_velocity.x != WALL_JUMP_SPEED) {
                m_velocity.x -= gravity * 2.5f * dt;
                if (m_velocity.x < 0.0f) m_velocity.x = 0.0f;    
            }
            // Conditions pour limiter la vitesse et ajuster la gravité...
        }
    }
    // Mettez à jour la position du carré
    m_position += dt * m_velocity;

    // Vérifiez les collisions avec la plateforme
    for (auto &plateform : m_plateforms) {
        collideWithPlateform(plateform.getPosition(), plateform.getHeight(), plateform.getLength(), plateform.getColor(), walljumpLeft, walljumpRight, wallJumpDown, walljumpUp, dt);
    }
}


    bool Hero::isPlateform(PlateformEntity plateform)
    {
        auto color = plateform.getColor();
        return color != gf::Color::Yellow && color != gf::Color::Orange && color != gf::Color::Rose && color != gf::Color::Green && color != gf::Color::Black && color != gf::Color::Cyan && !(color == gf::Color::fromRgb(100, 100, 10) && m_gravityDirection == DOWN) && !(color == gf::Color::fromRgb(100, 100, 20) && m_gravityDirection == UP) && !(color == gf::Color::fromRgb(100, 100, 30) && m_gravityDirection == LEFT) && !(color == gf::Color::fromRgb(100, 100, 40) && m_gravityDirection == RIGHT);
    }

    bool Hero::canJump()
    {
        for (auto &plateform : m_plateforms)
        {
            if (isPlateform(plateform))
            {
                gf::Vector2f plateformPosition = plateform.getPosition();
                float plateformHeight = plateform.getHeight();
                float plateformLength = plateform.getLength();
                float squareLeft = m_position.x - m_size.width / 2;
                float squareRight = m_position.x + m_size.width / 2;
                float squareTop = m_position.y - m_size.height / 2 - 1;
                float squareBottom = m_position.y + m_size.height / 2 + 1;

                // Calculez les limites de la plateforme en utilisant sa position centrale
                float plateformLeft = plateformPosition.x - plateformLength / 2;
                float plateformRight = plateformPosition.x + plateformLength / 2;
                float plateformTop = plateformPosition.y - plateformHeight / 2;
                float plateformBottom = plateformPosition.y + plateformHeight / 2;
                if (squareRight > plateformLeft && squareLeft < plateformRight &&
                    squareBottom > plateformTop && squareTop < plateformBottom)
                {

                    // Collision détectée. Maintenant, nous devons ajuster la position du carré.

                    // Vérifiez de quel côté le carré entre en collision
                    float overlapLeft = squareRight - plateformLeft;
                    float overlapRight = plateformRight - squareLeft;
                    float overlapTop = squareBottom - plateformTop;
                    float overlapBottom = plateformBottom - squareTop;

                    // Trouvez le chevauchement le plus petit
                    float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                    if (minOverlap == overlapTop && m_gravity > 0)
                    {
                        return true;
                    }

                    if (minOverlap == overlapBottom && m_gravity < 0)
                    {
                        return true;
                    }

                    // Optionnellement, arrêtez le mouvement du carré lors de la collision
                    // m_velocity.y += -gravity;
                }
            }
        }

        return false;
    }

    bool Hero::canWallJumpRight()
    {
        for (auto &plateform : m_plateforms)
        {
            if (isPlateform(plateform))
            {
                gf::Vector2f plateformPosition = plateform.getPosition();
                float plateformHeight = plateform.getHeight();
                float plateformLength = plateform.getLength();
                float squareLeft = m_position.x - m_size.width / 2;
                float squareRight = m_position.x + m_size.width / 2 + 1;
                float squareTop = m_position.y - m_size.height / 2;
                float squareBottom = m_position.y + m_size.height / 2;

                // Calculez les limites de la plateforme en utilisant sa position centrale
                float plateformLeft = plateformPosition.x - plateformLength / 2;
                float plateformRight = plateformPosition.x + plateformLength / 2;
                float plateformTop = plateformPosition.y - plateformHeight / 2;
                float plateformBottom = plateformPosition.y + plateformHeight / 2;
                if (squareRight > plateformLeft && squareLeft < plateformRight &&
                    squareBottom > plateformTop && squareTop < plateformBottom)
                {

                    // Collision détectée. Maintenant, nous devons ajuster la position du carré.

                    // Vérifiez de quel côté le carré entre en collision
                    float overlapLeft = squareRight - plateformLeft;
                    float overlapRight = plateformRight - squareLeft;
                    float overlapTop = squareBottom - plateformTop;
                    float overlapBottom = plateformBottom - squareTop;

                    // Trouvez le chevauchement le plus petit
                    float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                    if (minOverlap == overlapLeft)
                    {
                        return true;
                    }

                    // Optionnellement, arrêtez le mouvement du carré lors de la collision
                    // m_velocity.y += -gravity;
                }
            }
        }

        return false;
    }

    bool Hero::canWallJumpLeft()
    {
        for (auto &plateform : m_plateforms)
        {
            if (isPlateform(plateform))
            {
                gf::Vector2f plateformPosition = plateform.getPosition();
                float plateformHeight = plateform.getHeight();
                float plateformLength = plateform.getLength();
                float squareLeft = m_position.x - m_size.width / 2 - 1;
                float squareRight = m_position.x + m_size.width / 2;
                float squareTop = m_position.y - m_size.height / 2;
                float squareBottom = m_position.y + m_size.height / 2;

                // Calculez les limites de la plateforme en utilisant sa position centrale
                float plateformLeft = plateformPosition.x - plateformLength / 2;
                float plateformRight = plateformPosition.x + plateformLength / 2;
                float plateformTop = plateformPosition.y - plateformHeight / 2;
                float plateformBottom = plateformPosition.y + plateformHeight / 2;
                if (squareRight > plateformLeft && squareLeft < plateformRight &&
                    squareBottom > plateformTop && squareTop < plateformBottom)
                {

                    // Collision détectée. Maintenant, nous devons ajuster la position du carré.

                    // Vérifiez de quel côté le carré entre en collision
                    float overlapLeft = squareRight - plateformLeft;
                    float overlapRight = plateformRight - squareLeft;
                    float overlapTop = squareBottom - plateformTop;
                    float overlapBottom = plateformBottom - squareTop;

                    // Trouvez le chevauchement le plus petit
                    float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                    if (minOverlap == overlapRight)
                    {
                        return true;
                    }

                    // Optionnellement, arrêtez le mouvement du carré lors de la collision
                    // m_velocity.y += -gravity;
                }
            }
        }

        return false;
    }

    bool Hero::canWallJumpUp()
    {
        for (auto &plateform : m_plateforms)
        {
            if (isPlateform(plateform))
            {
                gf::Vector2f plateformPosition = plateform.getPosition();
                float plateformHeight = plateform.getHeight();
                float plateformLength = plateform.getLength();
                float squareLeft = m_position.x - m_size.width / 2;
                float squareRight = m_position.x + m_size.width / 2;
                float squareTop = m_position.y - m_size.height / 2 - 1;
                float squareBottom = m_position.y + m_size.height / 2;

                // Calculez les limites de la plateforme en utilisant sa position centrale
                float plateformLeft = plateformPosition.x - plateformLength / 2;
                float plateformRight = plateformPosition.x + plateformLength / 2;
                float plateformTop = plateformPosition.y - plateformHeight / 2;
                float plateformBottom = plateformPosition.y + plateformHeight / 2;
                if (squareRight > plateformLeft && squareLeft < plateformRight &&
                    squareBottom > plateformTop && squareTop < plateformBottom)
                {

                    // Collision détectée. Maintenant, nous devons ajuster la position du carré.

                    // Vérifiez de quel côté le carré entre en collision
                    float overlapLeft = squareRight - plateformLeft;
                    float overlapRight = plateformRight - squareLeft;
                    float overlapTop = squareBottom - plateformTop;
                    float overlapBottom = plateformBottom - squareTop;

                    // Trouvez le chevauchement le plus petit
                    float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                    if (minOverlap == overlapBottom)
                    {
                        return true;
                    }

                    // Optionnellement, arrêtez le mouvement du carré lors de la collision
                    // m_velocity.y += -gravity;
                }
            }
        }

        return false;
    }

    bool Hero::canWallJumpDown()
    {
        for (auto &plateform : m_plateforms)
        {
            if (isPlateform(plateform))
            {
                gf::Vector2f plateformPosition = plateform.getPosition();
                float plateformHeight = plateform.getHeight();
                float plateformLength = plateform.getLength();
                float squareLeft = m_position.x - m_size.width / 2;
                float squareRight = m_position.x + m_size.width / 2;
                float squareTop = m_position.y - m_size.height / 2;
                float squareBottom = m_position.y + m_size.height / 2 + 1;

                // Calculez les limites de la plateforme en utilisant sa position centrale
                float plateformLeft = plateformPosition.x - plateformLength / 2;
                float plateformRight = plateformPosition.x + plateformLength / 2;
                float plateformTop = plateformPosition.y - plateformHeight / 2;
                float plateformBottom = plateformPosition.y + plateformHeight / 2;
                if (squareRight > plateformLeft && squareLeft < plateformRight &&
                    squareBottom > plateformTop && squareTop < plateformBottom)
                {

                    // Collision détectée. Maintenant, nous devons ajuster la position du carré.

                    // Vérifiez de quel côté le carré entre en collision
                    float overlapLeft = squareRight - plateformLeft;
                    float overlapRight = plateformRight - squareLeft;
                    float overlapTop = squareBottom - plateformTop;
                    float overlapBottom = plateformBottom - squareTop;

                    // Trouvez le chevauchement le plus petit
                    float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                    if (minOverlap == overlapTop)
                    {
                        return true;
                    }

                    // Optionnellement, arrêtez le mouvement du carré lors de la collision
                    // m_velocity.y += -gravity;
                }
            }
        }

        return false;
    }

    void Hero::render(gf::RenderTarget &target, const gf::RenderStates &states)
    {
        gf::RectangleShape shape;
        if (horizontal_g)
        {
            shape = gf::RectangleShape({(float)(m_size.height), (float)(m_size.width)});
        }
        else {
            shape = gf::RectangleShape({(float)(m_size.width), (float)(m_size.height)});
        }
        shape.setPosition(m_position);
        shape.setRotation(m_rotation);
        if (m_faceDirection && !horizontal_g)
        {
            shape.setScale({-1.0f, 1.0f});
        }
        else if (m_faceDirection && horizontal_g)
        {
            shape.setScale({-1.0f, 1.0f});
        }
        else
        {
            shape.setScale({1.0f, 1.0f});
        }
        // shape.setColor(m_color);
        gf::Texture &texture = m_resources.getTexture(TEXTURE_SKIN_PATH);
        shape.setTexture(texture);
        shape.setAnchor(gf::Anchor::Center);
        target.draw(shape);
    }

    void Hero::renderHUD(gf::RenderTarget &target, float width, float height, gf::Vector2f pos)
    {
        gf::Font font(PATH_FONT);
        gf::Text deathText;
        deathText.setFont(font);
        deathText.setColor(gf::Color::White);
        deathText.setCharacterSize(20);
        deathText.setString(std::to_string((int)timer));
        deathText.setPosition(pos + gf::Vector2f(-(width / 2) + 45.0f, -(height / 2) + 10.0f));
        deathText.setAnchor(gf::Anchor::TopRight);
        target.draw(deathText);
    }

    // empeche le carré de traverser une plateforme
    void Hero::collideWithPlateform(gf::Vector2f plateformPosition, float plateformHeight, float plateformLength, gf::Color4f color, bool wallLeft, bool wallRight, bool wallDown, bool wallUp, float dt)
    {
        // Supposons que la classe Square ait des membres m_position (position centrale du carré),
        // m_size (longueur d'un côté du carré), et m_velocity (vecteur de mouvement du carré)
        // Calculez les limites du carré en utilisant sa position centrale
        float squareLeft = m_position.x - m_size.width / 2;
        float squareRight = m_position.x + m_size.width / 2;
        float squareTop = m_position.y - m_size.height / 2;
        float squareBottom = m_position.y + m_size.height / 2;

        if (color == gf::Color::Yellow)
        {

            if (wallLeft)
            {

                squareLeft -= 1;
            }
            if (wallRight)
            {

                squareRight += 1;
            }
            if (wallUp)
            {

                squareTop -= 1;
            }
            if (wallDown)
            {

                squareBottom += 1;
            }
        }

        // Calculez les limites de la plateforme en utilisant sa position centrale
        float plateformLeft = plateformPosition.x - plateformLength / 2;
        float plateformRight = plateformPosition.x + plateformLength / 2;
        float plateformTop = plateformPosition.y - plateformHeight / 2;
        float plateformBottom = plateformPosition.y + plateformHeight / 2;

        float speedX = dt * m_velocity.x;
        float speedY = dt * m_velocity.y;

        if (speedX < 0 && squareLeft + speedX > plateformLeft)
        {
            plateformLeft += speedX * 2;
        }
        if (speedX > 0 && squareRight - speedX < plateformRight)
        {
            plateformRight += speedX * 2;
        }
        if (speedY > 0 && squareBottom - speedY < plateformBottom)
        {
            plateformBottom += speedY * 2;
        }
        if (speedY < 0 && squareTop - speedY > plateformTop)
        {
            plateformTop += speedY * 2;
        }

        // Vérifiez la collision
        if (squareRight > plateformLeft && squareLeft < plateformRight &&
            squareBottom > plateformTop && squareTop < plateformBottom)
        {
            if (color == gf::Color::Yellow)
            {
                m_position = m_position_start;

                m_faceDirection = false;
                m_jump = 0;
                m_velocity = gf::Vector2f(0, 0);
                m_gravity = 1;
                m_rotation = 0;
                nb_deaths += 1;
                m_gravityDirection = DOWN;
                horizontal_g = false;
                return;
            }
            // close the game
            if (color == gf::Color::Black)
            {
                isOver = true;
            }
            // Collision détectée. Maintenant, nous devons ajuster la position du carré.

            // Vérifiez de quel côté le carré entre en collision
            // gravity switch up
            else if (color == gf::Color::Cyan)
            {
                m_gravityDirection = UP;
                m_rotation = gf::Pi;
                m_gravity = -1;
                if (horizontal_g)
                {
                    if (goLeft)
                    {
                        m_velocity.x = -SPEED_SQUARE;
                    }
                    if (goRight)
                    {
                        m_velocity.x = SPEED_SQUARE;
                    }
                }
                horizontal_g = false;
            }
            // gravity switch down
            else if (color == gf::Color::Rose)
            {
                m_gravityDirection = DOWN;
                m_rotation = 0;
                m_gravity = 1;
                if (horizontal_g)
                {
                    if (goLeft)
                    {
                        m_velocity.x = -SPEED_SQUARE;
                    }
                    if (goRight)
                    {
                        m_velocity.x = SPEED_SQUARE;
                    }
                }
                horizontal_g = false;
            }
            // gravity switch left
            else if (color == gf::Color::Green)
            {
                m_gravityDirection = LEFT;
                m_rotation = gf::Pi / 2;
                m_gravity = -1;
                if (!horizontal_g)
                {
                    if (goUp)
                    {
                        m_velocity.y = -SPEED_SQUARE;
                    }
                    if (goDown)
                    {
                        m_velocity.y = SPEED_SQUARE;
                    }
                }
                horizontal_g = true;
            }
            // gravity switch right
            else if (color == gf::Color::Orange)
            {
                m_gravityDirection = RIGHT;
                m_rotation = -gf::Pi / 2;
                if (!horizontal_g)
                {
                    if (goUp)
                    {
                        m_velocity.y = -SPEED_SQUARE;
                    }
                    if (goDown)
                    {
                        m_velocity.y = SPEED_SQUARE;
                    }
                }
                m_gravity = 1;
                horizontal_g = true;
            }
            // plateforme that can be passed through
            // wall down
            else if (color == gf::Color::fromRgb(100, 100, 10) && m_gravityDirection == DOWN)
            {
                // si la gravité est vers le bas, la plateforme est intangible
                return;
            }
            // wall up
            else if (color == gf::Color::fromRgb(100, 100, 20) && m_gravityDirection == UP)
            {
                // si la gravité est vers le haut, la plateforme est intangible
                return;
            }

            // wall left
            else if (color == gf::Color::fromRgb(100, 100, 30) && m_gravityDirection == LEFT)
            {
                // si la gravité est vers la gauche, la plateforme est intangible
                return;
            }
            // wall right
            else if (color == gf::Color::fromRgb(100, 100, 40) && m_gravityDirection == RIGHT)
            {
                // si la gravité est vers la droite, la plateforme est intangible
                return;
            }

            else
            {
                float overlapLeft = squareRight - plateformLeft;
                float overlapRight = plateformRight - squareLeft;
                float overlapTop = squareBottom - plateformTop;
                float overlapBottom = plateformBottom - squareTop;

                // Trouvez le chevauchement le plus petit
                float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                // Ajustez la position du carré en fonction du plus petit chevauchement
                if (minOverlap == overlapLeft && (((!wallDown || plateformTop <= squareTop) && (!wallUp || plateformBottom >= squareBottom)) || (wallUp && wallDown)))
                {
                    m_position.x -= overlapLeft;
                    if (horizontal_g)
                    {
                        m_velocity.x = 0;
                        if (m_gravity > 0)
                        {
                            nb_jumps = 0;
                            if (m_velocity.y == WALL_JUMP_SPEED || m_velocity.y == -WALL_JUMP_SPEED)
                            {
                                m_velocity.y = 0;
                                if (goUp)
                                {
                                    m_velocity.y = -SPEED_SQUARE;
                                }
                                if (goDown)
                                {
                                    m_velocity.y = SPEED_SQUARE;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (m_velocity.x == WALL_JUMP_SPEED)
                        {
                            m_velocity.x = 0;
                            m_velocity.y = -50.0f * m_gravity;
                        }
                    }
                }
                else if (minOverlap == overlapRight && (((!wallDown || plateformTop <= squareTop) && (!wallUp || plateformBottom >= squareBottom)) || (wallUp && wallDown)))
                {
                    m_position.x += overlapRight;
                    if (horizontal_g)
                    {
                        m_velocity.x = 0;
                        if (m_gravity < 0)
                        {
                            nb_jumps = 0;
                            if (m_velocity.y == WALL_JUMP_SPEED || m_velocity.y == -WALL_JUMP_SPEED)
                            {
                                m_velocity.y = 0;
                                if (goUp)
                                {
                                    m_velocity.y = -SPEED_SQUARE;
                                }
                                if (goDown)
                                {
                                    m_velocity.y = SPEED_SQUARE;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (m_velocity.x == -WALL_JUMP_SPEED)
                        {
                            m_velocity.x = 0;
                            m_velocity.y = -50.0f * m_gravity;
                        }
                    }
                }
                else if (minOverlap == overlapTop && (((!wallRight || plateformLeft <= squareLeft) && (!wallLeft || plateformRight >= squareRight)) || (wallLeft && wallRight)))
                {
                    m_position.y -= overlapTop;
                    if (horizontal_g)
                    {
                        if (m_velocity.y != SPEED_SQUARE)
                        {
                            m_velocity.y = 0;
                            m_velocity.x = -50.0f * m_gravity;
                        }
                    }
                    else
                    {

                        m_velocity.y = 0;
                        if (m_gravity > 0)
                        {
                            nb_jumps = 0;
                            if (m_velocity.x == WALL_JUMP_SPEED || m_velocity.x == -WALL_JUMP_SPEED)
                            {
                                m_velocity.x = 0;
                                if (goLeft)
                                {
                                    m_velocity.x = -SPEED_SQUARE;
                                }
                                if (goRight)
                                {
                                    m_velocity.x = SPEED_SQUARE;
                                }
                            }
                        }
                    }
                }
                else if (minOverlap == overlapBottom && (((!wallRight || plateformLeft <= squareLeft) && (!wallLeft || plateformRight >= squareRight)) || (wallLeft && wallRight)))
                {
                    m_position.y += overlapBottom;
                    if (horizontal_g)
                    {
                        if (m_velocity.y != -SPEED_SQUARE)
                        {
                            m_velocity.y = 0;
                            m_velocity.x = -50.0f * m_gravity;
                        }
                    }
                    else
                    {
                        m_velocity.y = 0;
                        if (m_gravity < 0)
                        {
                            nb_jumps = 0;
                            if (m_velocity.x == WALL_JUMP_SPEED || m_velocity.x == -WALL_JUMP_SPEED)
                            {
                                m_velocity.x = 0;
                                if (goLeft)
                                {
                                    m_velocity.x = -SPEED_SQUARE;
                                }
                                if (goRight)
                                {
                                    m_velocity.x = SPEED_SQUARE;
                                }
                            }
                        }
                    }
                }
            }

            // Optionnellement, arrêtez le mouvement du carré lors de la collision
            // m_velocity.y += -gravity;
        }
    }

} // namespace swiftness
