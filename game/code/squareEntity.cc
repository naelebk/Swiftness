#include "squareEntity.h"
#include "staticPlateforme.h"
#include "constants.h"

namespace swiftness
{
    Square::Square(gf::Vector2f position, float size, gf::Color4f color, float gravity)
        : m_position(position), m_position_start(position), m_velocity(0, 0), m_size(size), m_color(color), gravity(GRAVITY_SQUARE), m_jump(false), nb_jumps(0), m_gravity(1), horizontal_g(false), goLeft(false), goRight(false), goUp(false), goDown(false), isOver(false), nb_deaths(0), timer(0.0f)
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
        if (Z != inputs.end() || Up != inputs.end()) {
            goUp=true;
            if (horizontal_g){
                m_velocity.y = -SPEED_SQUARE;
            }else{
                m_jump=canJump(plateforms);
                bool walljumpRight=canWallJumpRight(plateforms);
                bool walljumpLeft=canWallJumpLeft(plateforms);
                if(m_jump || (nb_jumps==1 && !walljumpRight && !walljumpLeft)){
                    m_velocity.y = JUMP*m_gravity;
                    nb_jumps+=1;
                }else{
                    if(walljumpRight){
                        m_velocity.y=WALL_JUMP_HEIGHT*m_gravity;
                        nb_jumps=0;
                        m_velocity.x=-WALL_JUMP_SPEED;
                    }else{
                        if(walljumpLeft){
                            m_velocity.y=WALL_JUMP_HEIGHT*m_gravity;
                            nb_jumps=0;
                            m_velocity.x=WALL_JUMP_SPEED;
                        }
                    }
                }
                m_jump=false;
            }
        }
        std::vector<Input>::iterator Space = std::find(inputs.begin(), inputs.end(), Input::Space);
        if (Space != inputs.end()){
            if(horizontal_g){
                if(m_gravity>0){
                    bool walljumpRight=canWallJumpRight(plateforms);
                    bool walljumpUp=canWallJumpUp(plateforms);
                    bool wallJumpDown=canWallJumpDown(plateforms);
                    if(walljumpRight || (nb_jumps==1 && !walljumpUp && !wallJumpDown)){
                        m_velocity.x = JUMP*m_gravity;
                        nb_jumps+=1;
                    }else{
                        if(wallJumpDown){
                            m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                            nb_jumps=0;
                            m_velocity.y=-WALL_JUMP_SPEED;
                        }else{
                            if(walljumpUp){
                                m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                                nb_jumps=0;
                                m_velocity.y=WALL_JUMP_SPEED;
                            }
                        }
                    }
                }else{
                    bool walljumpLeft=canWallJumpLeft(plateforms);
                    bool walljumpUp=canWallJumpUp(plateforms);
                    bool wallJumpDown=canWallJumpDown(plateforms);
                    if(walljumpLeft || (nb_jumps==1 && !walljumpUp && !wallJumpDown)){
                        m_velocity.x = JUMP*m_gravity;
                        nb_jumps+=1;
                    }else{
                        if( wallJumpDown){
                            m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                            nb_jumps=0;
                            m_velocity.y=-WALL_JUMP_SPEED;
                        }else{
                            if(walljumpUp){
                                m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                                nb_jumps=0;
                                m_velocity.y=WALL_JUMP_SPEED;
                            }
                        }
                    }
                }
            }else{
                m_jump=canJump(plateforms);
                bool walljumpRight=canWallJumpRight(plateforms);
                bool walljumpLeft=canWallJumpLeft(plateforms);
                if(m_jump || (nb_jumps==1  && !walljumpRight && !walljumpLeft)){
                    m_velocity.y = JUMP*m_gravity;
                    nb_jumps+=1;
                }else{
                    if( walljumpRight){
                        m_velocity.y=WALL_JUMP_HEIGHT*m_gravity;
                        nb_jumps=0;
                        m_velocity.x=-WALL_JUMP_SPEED;
                    }else{
                        if( walljumpLeft){
                            m_velocity.y=WALL_JUMP_HEIGHT*m_gravity;
                            nb_jumps=0;
                            m_velocity.x=WALL_JUMP_SPEED;
                        }
                    }
                }
                m_jump=false;
            }
        }
        
        // Évènements released
        std::vector<Input>::iterator Z_Released = std::find(inputs.begin(), inputs.end(), Input::Z_Released);
        std::vector<Input>::iterator UpReleased = std::find(inputs.begin(), inputs.end(), Input::UpReleased);
        if (Z_Released != inputs.end() || UpReleased != inputs.end()) {
            if(horizontal_g){
                if(m_velocity.y<0){
                    m_velocity.y = 0;
                }
            }
            goUp=false;
        }
        std::vector<Input>::iterator D_Released = std::find(inputs.begin(), inputs.end(), Input::D_Released);
        std::vector<Input>::iterator RightReleased = std::find(inputs.begin(), inputs.end(), Input::RightReleased);
        if (D_Released != inputs.end() || RightReleased != inputs.end()) {
            if(!horizontal_g){
                if(m_velocity.x>0){
                    m_velocity.x = 0;
                }
            }
            goRight=false;
        }
        std::vector<Input>::iterator S_Released = std::find(inputs.begin(), inputs.end(), Input::S_Released);
        std::vector<Input>::iterator DownReleased = std::find(inputs.begin(), inputs.end(), Input::DownReleased);
        if (S_Released != inputs.end() || DownReleased != inputs.end()) {
            if(horizontal_g){
                if(m_velocity.y>0){
                    m_velocity.y = 0;
                }
            }
            goDown=false;
        }
        std::vector<Input>::iterator Q_Released = std::find(inputs.begin(), inputs.end(), Input::Q_Released);
        std::vector<Input>::iterator LeftReleased = std::find(inputs.begin(), inputs.end(), Input::LeftReleased);
        if (Q_Released != inputs.end() || LeftReleased != inputs.end()) {
            if(!horizontal_g){
                if(m_velocity.x<0){
                    m_velocity.x = 0;
                }
            }
            goLeft=false;
        } 

        std::vector<Input>::iterator D = std::find(inputs.begin(), inputs.end(), Input::D);
        std::vector<Input>::iterator Right = std::find(inputs.begin(), inputs.end(), Input::Right);
        if (D != inputs.end() || Right != inputs.end()) {
            if(horizontal_g){
                if (m_gravity<0){
                    bool walljumpLeft=canWallJumpLeft(plateforms);
                    bool walljumpUp=canWallJumpUp(plateforms);
                    bool wallJumpDown=canWallJumpDown(plateforms);
                    if(walljumpLeft || (nb_jumps==1  && !walljumpUp && !wallJumpDown)){
                        m_velocity.x = JUMP*m_gravity;
                        nb_jumps+=1;
                    }else{
                        if( wallJumpDown){
                            m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                            nb_jumps=0;
                            m_velocity.y=-WALL_JUMP_SPEED;
                        }else{
                            if( walljumpUp){
                                m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                                nb_jumps=0;
                                m_velocity.y=WALL_JUMP_SPEED;
                            }
                        }
                    }
                }
            }else{
                m_velocity.x = SPEED_SQUARE;
            }
            goRight=true;
        }
        std::vector<Input>::iterator S = std::find(inputs.begin(), inputs.end(), Input::S);
        std::vector<Input>::iterator Down = std::find(inputs.begin(), inputs.end(), Input::Down);
        if (S != inputs.end() || Down != inputs.end()) {
            goDown=true;
            if (horizontal_g){
                m_velocity.y = SPEED_SQUARE;
            }
        }
        std::vector<Input>::iterator Q = std::find(inputs.begin(), inputs.end(), Input::Q);
        std::vector<Input>::iterator Left = std::find(inputs.begin(), inputs.end(), Input::Left);
        if (Q != inputs.end() || Left != inputs.end()) {
            if(horizontal_g){
                if (m_gravity>0){
                    bool walljumpRight=canWallJumpRight(plateforms);
                    bool walljumpUp=canWallJumpUp(plateforms);
                    bool wallJumpDown=canWallJumpDown(plateforms);
                    if(walljumpRight || (nb_jumps==1 && !walljumpUp && !wallJumpDown)){
                        m_velocity.x = JUMP*m_gravity;
                        nb_jumps+=1;
                    }else{
                        if( wallJumpDown){
                            m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                            nb_jumps=0;
                            m_velocity.y=-WALL_JUMP_SPEED;
                        }else{
                            if( walljumpUp){
                                m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                                nb_jumps=0;
                                m_velocity.y=WALL_JUMP_SPEED;
                            }
                        }
                    }
                }
            }else{ 
                m_velocity.x = -SPEED_SQUARE;
            }
            goLeft=true;
        }    
    }

    void Square::updateWithMap(float dt, std::map<int, StaticPlateform> plateforms, std::vector<Input> inputs)
    {
        actionWithInputs(inputs,plateforms);
        bool walljumpRight=canWallJumpRight(plateforms);
        bool walljumpLeft=canWallJumpLeft(plateforms);
        bool walljumpUp=canWallJumpUp(plateforms);
        bool wallJumpDown=canWallJumpDown(plateforms);
        timer+=dt;
        if(timer>999.99f){
            isOver=true;
        }
      
        // Appliquez la gravité
        if(horizontal_g){
            setVelocity(m_velocity + gf::Vector2f( gravity * m_gravity * dt,0));
        }else{
            setVelocity(m_velocity + gf::Vector2f(0, gravity * m_gravity * dt));
        }
        // Mettez à jour la position du carré
        m_position += dt * m_velocity;
        
        
        // Vérifiez les collisions avec la plateforme
        for (auto &plateform : plateforms)
        {
            collideWithPlateform(plateform.second.getPosition(), plateform.second.getHeight(), plateform.second.getLength(),plateform.second.getColor(),walljumpLeft,walljumpRight);
        }

        
    }

    bool Square::isPlateform(StaticPlateform plateform){
        auto color=plateform.getColor();
        return color!=gf::Color::Yellow && color!=gf::Color::Orange && color!=gf::Color::Rose && color!=gf::Color::Green && color!=gf::Color::Black && color!=gf::Color::Cyan;
    }

    bool Square::canJump(std::map<int, StaticPlateform> plateforms){
        for (auto &plateform : plateforms)
        {
            if(isPlateform(plateform.second)){
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
    
        }
        
        return false;

    }

    bool Square::canWallJumpRight(std::map<int, StaticPlateform> plateforms){
        for (auto &plateform : plateforms)
        {
            if(isPlateform(plateform.second)){
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
        }
            
        return false;

    }

    bool Square::canWallJumpLeft(std::map<int, StaticPlateform> plateforms){
        for (auto &plateform : plateforms)
        {
            if(isPlateform(plateform.second)){
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
    
        }
        
        return false;

    }

    bool Square::canWallJumpUp(std::map<int, StaticPlateform> plateforms){
        for (auto &plateform : plateforms)
        {
            if(isPlateform(plateform.second)){
                gf::Vector2f plateformPosition=plateform.second.getPosition();
                float plateformHeight=plateform.second.getHeight();
                float plateformLength=plateform.second.getLength();
                float squareLeft = m_position.x - m_size / 2;
                float squareRight = m_position.x + m_size / 2 ;
                float squareTop = m_position.y - m_size / 2 -1;
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

                    if (minOverlap == overlapBottom)
                    {
                        return true;
                    }
                    
                    

                    // Optionnellement, arrêtez le mouvement du carré lors de la collision
                    //m_velocity.y += -gravity;
                }
            }
    
        }
        
        return false;

    }

    bool Square::canWallJumpDown(std::map<int, StaticPlateform> plateforms){
        for (auto &plateform : plateforms)
        {
            if(isPlateform(plateform.second)){
                gf::Vector2f plateformPosition=plateform.second.getPosition();
                float plateformHeight=plateform.second.getHeight();
                float plateformLength=plateform.second.getLength();
                float squareLeft = m_position.x - m_size / 2;
                float squareRight = m_position.x + m_size / 2;
                float squareTop = m_position.y - m_size / 2;
                float squareBottom = m_position.y + m_size / 2 + 1;

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
                    //m_velocity.y += -gravity;
                }
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
        shape.setColor(m_color);
        shape.setAnchor(gf::Anchor::Center);
        target.draw(shape);
    }

    void Square::renderHUD(gf::RenderTarget &target,float width,float height)
    {
        gf::Font font(PATH_FONT);
        gf::Text deathText;
        deathText.setFont(font);
        deathText.setColor(gf::Color::White);
        deathText.setCharacterSize(35);
        deathText.setString(std::to_string((int)timer));
        deathText.setPosition(m_position+gf::Vector2f(-(width/2)+81.0f, -(height/2)+10.0f));
        deathText.setAnchor(gf::Anchor::TopRight);
        target.draw(deathText);
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

        if(color==gf::Color::Yellow){
            if (wallLeft){ 
                squareLeft-=1;
            }
            if (wallRight){ 
                squareRight+=1;
            }
        }

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
                nb_deaths+=1;
                return;
            }
            // close the game
            if (color==gf::Color::Black){
                isOver = true;
            }
            // Collision détectée. Maintenant, nous devons ajuster la position du carré.

            // Vérifiez de quel côté le carré entre en collision
            // gravity switch down
            else if(color==gf::Color::Cyan){
                m_gravity=-1;
                if (horizontal_g){
                    m_velocity.x=0;
                    m_velocity.y=0;
                    if (goLeft){
                        m_velocity.x=-SPEED_SQUARE;
                    }
                    if (goRight){
                        m_velocity.x=SPEED_SQUARE;
                    }
                }
                horizontal_g=false;
            }
            // gravity switch up
            else if(color==gf::Color::Rose){
                m_gravity=1;
                if (horizontal_g){
                    m_velocity.x=0;
                    m_velocity.y=0;
                    if (goLeft){
                        m_velocity.x=-SPEED_SQUARE;
                    }
                    if (goRight){
                        m_velocity.x=SPEED_SQUARE;
                    }
                }
                horizontal_g=false;
            }
            // gravity switch left
            else if(color==gf::Color::Green){
                m_gravity=-1;
                if (!horizontal_g){
                    m_velocity.x=0;
                    m_velocity.y=0;
                    if (goUp){
                        m_velocity.y=-SPEED_SQUARE;
                    }
                    if (goDown){
                        m_velocity.y=SPEED_SQUARE;
                    }
                }
                horizontal_g=true;
            }
            // gravity switch right
            else if(color==gf::Color::Orange){
                if (!horizontal_g){
                    m_velocity.x=0;
                    m_velocity.y=0;
                    if (goUp){
                        m_velocity.y=-SPEED_SQUARE;
                    }
                    if (goDown){
                        m_velocity.y=SPEED_SQUARE;
                    }
                }
                m_gravity=1;
                horizontal_g=true;
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
                    if(horizontal_g){
                        m_velocity.x=0;
                        if (m_gravity>0){
                            nb_jumps=0;
                            if(m_velocity.y==WALL_JUMP_SPEED || m_velocity.y==-WALL_JUMP_SPEED){
                                m_velocity.y=0;
                                if (goUp){
                                    m_velocity.y=-SPEED_SQUARE;
                                }
                                if (goDown){
                                    m_velocity.y=SPEED_SQUARE;
                                }
                            }
                        }
                    }else{
                        if(m_velocity.x==WALL_JUMP_SPEED){
                            m_velocity.x=0;
                            m_velocity.y=-50.0f*m_gravity;
                        }
                    }
                }
                else if (minOverlap == overlapRight)
                {
                    m_position.x += overlapRight;
                    if(horizontal_g){
                        m_velocity.x=0;
                        if (m_gravity<0){
                            nb_jumps=0;
                            if(m_velocity.y==WALL_JUMP_SPEED || m_velocity.y==-WALL_JUMP_SPEED){
                                m_velocity.y=0;
                                if (goUp){
                                    m_velocity.y=-SPEED_SQUARE;
                                }
                                if (goDown){
                                    m_velocity.y=SPEED_SQUARE;
                                }
                            }
                        }
                    }else{
                        if(m_velocity.x==-WALL_JUMP_SPEED){
                            m_velocity.x=0;
                            m_velocity.y=-50.0f*m_gravity;
                        }
                    }
                }
                else if (minOverlap == overlapTop && (((!wallRight || plateformLeft<=squareLeft) && (!wallLeft || plateformRight>=squareRight)) || (wallLeft && wallRight)))
                {
                    m_position.y -= overlapTop;
                    if(horizontal_g){
                        if(m_velocity.y!=SPEED_SQUARE){
                            m_velocity.y=0;
                            m_velocity.x=-50.0f*m_gravity;
                        }
                    }else{
                        
                        m_velocity.y=0;
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
                }
                else if (minOverlap == overlapBottom && (((!wallRight || plateformLeft<=squareLeft) && (!wallLeft || plateformRight>=squareRight)) || (wallLeft && wallRight)))
                {
                    m_position.y += overlapBottom;
                    if(horizontal_g){
                        if(m_velocity.y!=-SPEED_SQUARE){
                            m_velocity.y=0;
                            m_velocity.x=-50.0f*m_gravity;
                        }
                    }else{
                        m_velocity.y=0;
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
            }
            

            // Optionnellement, arrêtez le mouvement du carré lors de la collision
            //m_velocity.y += -gravity;
        }
    }

} // namespace swiftness