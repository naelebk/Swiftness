#include "squareEntity.h"
#include "staticPlateforme.h"
#include "constants.h"

namespace swiftness
{
    Square::Square(gf::Vector2f position, float size, gf::Color4f color, float gravity)
        : m_position(position), m_position_start(position), m_velocity(0, 0), m_size(size), m_color(color), gravity(GRAVITY_SQUARE), m_jump(false), m_bullet(false), m_bullet_bar(0.0f), nb_jumps(0), m_gravity(1), goLeft(false), goRight(false)
    {
    }
    gf::Vector2f Square::getPosition() const
    {
        return m_position;
    }

    void Square::setVelocity(gf::Vector2f velocity)
    {
        m_velocity = velocity;
    }

    void Square::actionWithInputs(std::vector<Input> inputs,std::map<int, StaticPlateform> plateforms) {
        if (inputs.empty()) return;      
        // On ne return pas à chaque action
        // Pourquoi ? Dans le cas où le joueur voudrait faire plusieurs actions dans une même frame
        // Par exemple : aller en haut à gauche

        // Évènement non released
        std::vector<Input>::iterator Z = std::find(inputs.begin(), inputs.end(), Input::Z);
        std::vector<Input>::iterator Up = std::find(inputs.begin(), inputs.end(), Input::Up);  
        std::vector<Input>::iterator Space = std::find(inputs.begin(), inputs.end(), Input::Space);      
        if (Z != inputs.end() || Up != inputs.end() || Space != inputs.end()) {
            m_jump=canJump(plateforms);
            bool walljumpRight=canWallJumpRight(plateforms);
            bool walljumpLeft=canWallJumpLeft(plateforms);
            if(m_jump || (nb_jumps==1 && m_bullet && !walljumpRight && !walljumpLeft)){
                m_velocity.y = JUMP*m_gravity;
                nb_jumps+=1;
            }else{
                if(m_bullet && walljumpRight){
                    m_velocity.y=WALL_JUMP_HEIGHT*m_gravity;
                    nb_jumps=0;
                    m_velocity.x=-WALL_JUMP_SPEED;
                }else{
                    if(m_bullet && walljumpLeft){
                        m_velocity.y=WALL_JUMP_HEIGHT*m_gravity;
                        nb_jumps=0;
                        m_velocity.x=WALL_JUMP_SPEED;
                    }
                }
            }
            m_jump=false;
        }
        std::vector<Input>::iterator B = std::find(inputs.begin(), inputs.end(), Input::B);      
        if (B != inputs.end()) {
            if(m_bullet_bar>0.0f){
                m_bullet=!m_bullet;
            }
        }
        
        // Évènements released
        // std::vector<Input>::iterator Z_Released = std::find(inputs.begin(), inputs.end(), Input::Z_Released);
        // std::vector<Input>::iterator UpReleased = std::find(inputs.begin(), inputs.end(), Input::UpReleased);
        // std::vector<Input>::iterator SpaceReleased = std::find(inputs.begin(), inputs.end(), Input::Space_Released);
        /*if (Z_Released != inputs.end() || UpReleased != inputs.end()) {
            m_velocity.y += SPEED;
        }*/
        std::vector<Input>::iterator D_Released = std::find(inputs.begin(), inputs.end(), Input::D_Released);
        std::vector<Input>::iterator RightReleased = std::find(inputs.begin(), inputs.end(), Input::RightReleased);
        if (D_Released != inputs.end() || RightReleased != inputs.end()) {
            if(m_velocity.x>0){
                m_velocity.x = 0;
            }
            goRight=false;
        }
        // std::vector<Input>::iterator S_Released = std::find(inputs.begin(), inputs.end(), Input::S_Released);
        // std::vector<Input>::iterator DownReleased = std::find(inputs.begin(), inputs.end(), Input::DownReleased);
        /*if (S_Released != inputs.end() || DownReleased != inputs.end()) {
            m_velocity.y -= SPEED;
        }*/
        std::vector<Input>::iterator Q_Released = std::find(inputs.begin(), inputs.end(), Input::Q_Released);
        std::vector<Input>::iterator LeftReleased = std::find(inputs.begin(), inputs.end(), Input::LeftReleased);
        if (Q_Released != inputs.end() || LeftReleased != inputs.end()) {
            if(m_velocity.x<0){
                m_velocity.x = 0;
            }
            goLeft=false;
        } 

        std::vector<Input>::iterator D = std::find(inputs.begin(), inputs.end(), Input::D);
        std::vector<Input>::iterator Right = std::find(inputs.begin(), inputs.end(), Input::Right);
        if (D != inputs.end() || Right != inputs.end()) {
            m_velocity.x = SPEED_SQUARE;
            goRight=true;
        }
        std::vector<Input>::iterator S = std::find(inputs.begin(), inputs.end(), Input::S);
        std::vector<Input>::iterator Down = std::find(inputs.begin(), inputs.end(), Input::Down);
        if (S != inputs.end() || Down != inputs.end()) {
        }
        std::vector<Input>::iterator Q = std::find(inputs.begin(), inputs.end(), Input::Q);
        std::vector<Input>::iterator Left = std::find(inputs.begin(), inputs.end(), Input::Left);
        if (Q != inputs.end() || Left != inputs.end()) { 
            m_velocity.x = -SPEED_SQUARE;
            goLeft=true;
        }    
    }

    void Square::updateWithMap(float dt, std::map<int, StaticPlateform> plateforms, std::vector<Input> inputs)
    {
        actionWithInputs(inputs,plateforms);
        bool walljumpRight=canWallJumpRight(plateforms);
        bool walljumpLeft=canWallJumpLeft(plateforms);
        if (m_bullet){
            if ((goLeft && walljumpLeft) || (goRight && walljumpRight)){
                m_velocity.y=-SPEED_SQUARE*m_gravity;
            }
            m_bullet_bar-=dt*10;
            if(m_bullet_bar<=0.0f){
                m_bullet_bar=0.0f;
                m_bullet=false;
            }
            
        }
        if ((m_gravity==1 && m_velocity.y>0) || (m_gravity==-1 && m_velocity.y<0)){
            m_bullet_bar+=m_gravity*m_velocity.y*dt/10;
            if (m_bullet_bar>100.0f){
                m_bullet_bar=100.0f;
            }
        }
        // Appliquez la gravité
        setVelocity(m_velocity + gf::Vector2f(0, gravity * m_gravity * dt));
        // Mettez à jour la position du carré
        m_position += dt * m_velocity;
        
        
        // Vérifiez les collisions avec la plateforme
        for (auto &plateform : plateforms)
        {
            collideWithPlateform(plateform.second.getPosition(), plateform.second.getHeight(), plateform.second.getLength(),plateform.second.getColor(),walljumpLeft,walljumpRight);
        }

        
    }

    bool Square::canJump(std::map<int, StaticPlateform> plateforms){
        for (auto &plateform : plateforms)
        {
            gf::Vector2f plateformPosition=plateform.second.getPosition();
            float plateformHeight=plateform.second.getHeight();
            float plateformLength=plateform.second.getLength();
            float squareLeft = m_position.x - m_size / 2;
            float squareRight = m_position.x + m_size / 2;
            float squareTop = m_position.y - m_size / 2 -1;
            float squareBottom = m_position.y + m_size / 2 +1;

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

                if (minOverlap == overlapTop && m_gravity>0)
                {
                    return true;
                }
                
                if (minOverlap == overlapBottom && m_gravity<0)
                {
                    return true;
                }

                // Optionnellement, arrêtez le mouvement du carré lors de la collision
                //m_velocity.y += -gravity;
            }
    
        }
        
        return false;

    }

    bool Square::canWallJumpRight(std::map<int, StaticPlateform> plateforms){
        for (auto &plateform : plateforms)
        {
            gf::Vector2f plateformPosition=plateform.second.getPosition();
            float plateformHeight=plateform.second.getHeight();
            float plateformLength=plateform.second.getLength();
            float squareLeft = m_position.x - m_size / 2;
            float squareRight = m_position.x + m_size / 2 +1;
            float squareTop = m_position.y - m_size / 2;
            float squareBottom = m_position.y + m_size / 2;

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
                //m_velocity.y += -gravity;
            }
    
        }
        
        return false;

    }

    bool Square::canWallJumpLeft(std::map<int, StaticPlateform> plateforms){
        for (auto &plateform : plateforms)
        {
            gf::Vector2f plateformPosition=plateform.second.getPosition();
            float plateformHeight=plateform.second.getHeight();
            float plateformLength=plateform.second.getLength();
            float squareLeft = m_position.x - m_size / 2 -1;
            float squareRight = m_position.x + m_size / 2;
            float squareTop = m_position.y - m_size / 2;
            float squareBottom = m_position.y + m_size / 2;

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
                //m_velocity.y += -gravity;
            }
    
        }
        
        return false;

    }

    void Square::update(float dt, StaticPlateform plateform)
    {
        // Mettez à jour la position du carré
        m_position += dt * m_velocity;

        // Appliquez la gravité
        setVelocity(m_velocity + gf::Vector2f(0, gravity * dt));

        // Vérifiez les collisions avec la plateforme
        collideWithPlateform(plateform.getPosition(), plateform.getHeight(), plateform.getLength(),plateform.getColor(),false,false);
        
    }

    void Square::render(gf::RenderTarget &target)
    {
        gf::RectangleShape shape({m_size, m_size});
        shape.setPosition(m_position);
        if(m_bullet){
            shape.setColor(gf::Color::Green);
        }else{
            shape.setColor(m_color);
        }
        shape.setAnchor(gf::Anchor::Center);
        target.draw(shape);
    }

    void Square::renderHUD(gf::RenderTarget &target,float width,float height)
    {
        gf::RectangleShape shape_bullet_bar({100.0f, 20.0f});
        shape_bullet_bar.setPosition(m_position - gf::Vector2f(width/2-55.0f, height/2-15.0f));
        shape_bullet_bar.setColor(gf::Color::Black);
        shape_bullet_bar.setAnchor(gf::Anchor::Center);
        target.draw(shape_bullet_bar);
        gf::RectangleShape shape_bullet_bar2({m_bullet_bar, 20.0f});
        shape_bullet_bar2.setPosition(m_position - gf::Vector2f(width/2-m_bullet_bar/2-5.0f, height/2-15.0f));
        shape_bullet_bar2.setColor(gf::Color::Cyan);
        shape_bullet_bar2.setAnchor(gf::Anchor::Center);
        target.draw(shape_bullet_bar2);
    }

    // empeche le carré de traverser une plateforme
    void Square::collideWithPlateform(gf::Vector2f plateformPosition, float plateformHeight, float plateformLength,gf::Color4f color,bool wallLeft,bool wallRight)
    {
        // Supposons que la classe Square ait des membres m_position (position centrale du carré),
        // m_size (longueur d'un côté du carré), et m_velocity (vecteur de mouvement du carré)

        // Calculez les limites du carré en utilisant sa position centrale
        float squareLeft = m_position.x - m_size / 2;
        float squareRight = m_position.x + m_size / 2;
        float squareTop = m_position.y - m_size / 2;
        float squareBottom = m_position.y + m_size / 2;

        // Calculez les limites de la plateforme en utilisant sa position centrale
        float plateformLeft = plateformPosition.x - plateformLength / 2;
        float plateformRight = plateformPosition.x + plateformLength / 2;
        float plateformTop = plateformPosition.y - plateformHeight / 2;
        float plateformBottom = plateformPosition.y + plateformHeight / 2;

        // Vérifiez la collision
        if (squareRight > plateformLeft && squareLeft < plateformRight &&
            squareBottom > plateformTop && squareTop < plateformBottom)
        {
            if(color==gf::Color::Yellow){
                m_position=m_position_start;
                m_jump=0;
                m_velocity=gf::Vector2f(0,0);
                m_gravity=1;
                m_bullet=false;
                m_bullet_bar=0.0f;
                return;
            }
            // Collision détectée. Maintenant, nous devons ajuster la position du carré.

            // Vérifiez de quel côté le carré entre en collision
            // gravity switch down
            else if(color==gf::Color::Cyan){
                m_gravity=-1;
            }
            // gravity switch up
            else if(color==gf::Color::Rose){
                m_gravity=1;
            }
            // gravity switch left
            else if(color==gf::Color::Green){
                m_gravity=0;
                m_velocity.x=1;
            }
            // gravity switch right
            else if(color==gf::Color::Orange){
                m_gravity=0;
                m_velocity.x=-1;
            }
            else{
                float overlapLeft = squareRight - plateformLeft;
                float overlapRight = plateformRight - squareLeft;
                float overlapTop = squareBottom - plateformTop;
                float overlapBottom = plateformBottom - squareTop;

                // Trouvez le chevauchement le plus petit
                float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                // Ajustez la position du carré en fonction du plus petit chevauchement
                if (minOverlap == overlapLeft)
                {
                    m_position.x -= overlapLeft;
                    if(m_velocity.x==WALL_JUMP_SPEED){
                        m_velocity.x=0;
                    }
                }
                else if (minOverlap == overlapRight)
                {
                    m_position.x += overlapRight;
                    if(m_velocity.x==-WALL_JUMP_SPEED){
                        m_velocity.x=0;
                    }
                }
                else if (minOverlap == overlapTop && (((!wallRight || plateformLeft<squareLeft) && (!wallLeft || plateformRight>squareRight)) || (wallLeft && wallRight)))
                {
                    m_velocity.y=0;
                    m_position.y -= overlapTop;
                    if (m_gravity>0){
                        nb_jumps=0;
                        if(m_velocity.x==WALL_JUMP_SPEED || m_velocity.x==-WALL_JUMP_SPEED){
                            m_velocity.x=0;
                            if (goLeft){
                                m_velocity.x=-SPEED_SQUARE;
                            }
                            if (goRight){
                                m_velocity.x=SPEED_SQUARE;
                            }
                        }
                    }
                }
                else if (minOverlap == overlapBottom && (((!wallRight || plateformLeft<squareLeft) && (!wallLeft || plateformRight>squareRight)) || (wallLeft && wallRight)))
                {
                    m_velocity.y=0;
                    m_position.y += overlapBottom;
                    if (m_gravity<0){
                        nb_jumps=0;
                        if(m_velocity.x==WALL_JUMP_SPEED || m_velocity.x==-WALL_JUMP_SPEED){
                            m_velocity.x=0;
                            if (goLeft){
                                m_velocity.x=-SPEED_SQUARE;
                            }
                            if (goRight){
                                m_velocity.x=SPEED_SQUARE;
                            }
                        }
                    }
                }
            }
            
            

            // Optionnellement, arrêtez le mouvement du carré lors de la collision
            //m_velocity.y += -gravity;
        }
    }

} // namespace swiftness