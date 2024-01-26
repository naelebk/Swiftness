#include "squareEntity.h"
#include "staticPlateforme.h"
#include "constants.h"

namespace swiftness
{
    Square::Square(gf::Vector2f position, float size, gf::Color4f color, float gravity)
        : m_position(position)
        , m_position_start(position)
        , m_velocity(0, 0)
        , m_size(size)
        , m_color(color)
        , gravity(GRAVITY_SQUARE)
        , m_jump(false)
        , nb_jumps(0)
        , m_gravity(1)
        , horizontal_g(false)
        , goLeft(false)
        , goRight(false)
        , goUp(false)
        , goDown(false)
        , isOver(false)
        , nb_deaths(0)
        , timer(0.0f)
        , m_gravityDirection("down")
        , m_walljump(0.0f)
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


    void Square::actionUp() {
        if (horizontal_g && m_velocity.y<SPEED_SQUARE && m_walljump==0.0f){
            m_velocity.y = -SPEED_SQUARE;
            goUp=true;
        }
    }

    void Square::actionUpJump() {
        if(!horizontal_g){
            m_jump=canJump();
            bool walljumpRight=canWallJumpRight();
            bool walljumpLeft=canWallJumpLeft();
            if(m_jump || (nb_jumps<2 && !walljumpRight && !walljumpLeft)){
                m_velocity.y = JUMP*m_gravity;
                nb_jumps = m_jump ? 1 : 2;
            }else{
                if(walljumpRight){
                    m_velocity.y=WALL_JUMP_HEIGHT*m_gravity;
                    nb_jumps=1;
                    m_velocity.x=-WALL_JUMP_SPEED;
                    m_walljump=WALL_JUMP_TIME;
                }else{
                    if(walljumpLeft){
                        m_velocity.y=WALL_JUMP_HEIGHT*m_gravity;
                        nb_jumps=1;
                        m_velocity.x=WALL_JUMP_SPEED;
                        m_walljump=WALL_JUMP_TIME;
                    }
                }
            }
            m_jump=false;
        }
    }

    void Square::actionUpRelease(){
        if(horizontal_g && goUp){
            if(m_velocity.y<0){
                m_velocity.y = 0;
            }
        }
        goUp=false;
    }
    void Square::actionDown(){
        goDown=true; if (horizontal_g && m_velocity.y>-SPEED_SQUARE && m_walljump==0.0f) m_velocity.y = SPEED_SQUARE;
    }
    void Square::actionDownRelease(){
        if(horizontal_g && goDown){
            if(m_velocity.y>0){
                m_velocity.y = 0;
            }
        }
        goDown=false;
    }
    void Square::actionLeft(){
        if(!horizontal_g && m_velocity.x<SPEED_SQUARE && m_walljump==0.0f){ 
            m_velocity.x = -SPEED_SQUARE;
            goLeft=true;
        }
    }

    void Square::actionLeftJump() {
        if(horizontal_g){
            if (m_gravity>0){
                bool walljumpRight=canWallJumpRight();
                bool walljumpUp=canWallJumpUp();
                bool wallJumpDown=canWallJumpDown();
                if(walljumpRight || (nb_jumps<2 && !walljumpUp && !wallJumpDown)){
                    m_velocity.x = JUMP*m_gravity;
                    if (walljumpRight){
                        nb_jumps=1;
                    }else{
                        nb_jumps=2;
                    }
                }else{
                    if( wallJumpDown){
                        m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                        nb_jumps=1;
                        m_velocity.y=-WALL_JUMP_SPEED;
                        m_walljump=WALL_JUMP_TIME;
                    }else{
                        if( walljumpUp){
                            m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                            nb_jumps=1;
                            m_velocity.y=WALL_JUMP_SPEED;
                            m_walljump=WALL_JUMP_TIME;
                        }
                    }
                }
            }
        }
    }
    void Square::actionLeftRelease(){
        if(!horizontal_g && goLeft){
            if(m_velocity.x<0){
                m_velocity.x = 0;
            }
        }
        goLeft=false;
    }
    void Square::actionRight(){
        if(!horizontal_g && m_velocity.x>-SPEED_SQUARE && m_walljump==0.0f){
            m_velocity.x = SPEED_SQUARE;
            goRight=true;
        }
    }

    void Square::actionRightJump() {
        if(horizontal_g){
            if (m_gravity<0){
                bool walljumpLeft=canWallJumpLeft();
                bool walljumpUp=canWallJumpUp();
                bool wallJumpDown=canWallJumpDown();
                if(walljumpLeft || (nb_jumps<2  && !walljumpUp && !wallJumpDown)){
                    m_velocity.x = JUMP*m_gravity;
                    if (walljumpLeft){
                        nb_jumps=1;
                    }else{
                        nb_jumps=2;
                    }

                }else{
                    if( wallJumpDown){
                        m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                        nb_jumps=1;
                        m_velocity.y=-WALL_JUMP_SPEED;
                        m_walljump=WALL_JUMP_TIME;
                    }else{
                        if( walljumpUp){
                            m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                            nb_jumps=1;
                            m_velocity.y=WALL_JUMP_SPEED;
                            m_walljump=WALL_JUMP_TIME;
                        }
                    }
                }
            }
        }
    }
    void Square::actionRightRelease(){
        if(!horizontal_g && goRight){
            if(m_velocity.x>0){
                m_velocity.x = 0;
            }
        }
        goRight=false;
    }
    void Square::actionJump(){
        if(horizontal_g){
            if(m_gravity>0){
                bool walljumpRight=canWallJumpRight();
                bool walljumpUp=canWallJumpUp();
                bool wallJumpDown=canWallJumpDown();
                if(walljumpRight || (nb_jumps<2 && !walljumpUp && !wallJumpDown)){
                    m_velocity.x = JUMP*m_gravity;
                    if (walljumpRight){
                        nb_jumps=1;
                    }else{
                        nb_jumps=2;
                    }
                }else{
                    if(wallJumpDown){
                        m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                        nb_jumps=1;
                        m_velocity.y=-WALL_JUMP_SPEED;
                        m_walljump=WALL_JUMP_TIME;
                    }else{
                        if(walljumpUp){
                            m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                            nb_jumps=1;
                            m_velocity.y=WALL_JUMP_SPEED;
                            m_walljump=WALL_JUMP_TIME;
                        }
                    }
                }
            }else{
                bool walljumpLeft=canWallJumpLeft();
                bool walljumpUp=canWallJumpUp();
                bool wallJumpDown=canWallJumpDown();
                if(walljumpLeft || (nb_jumps<2 && !walljumpUp && !wallJumpDown)){
                    m_velocity.x = JUMP*m_gravity;
                    if (walljumpLeft){
                        nb_jumps=1;
                    }else{
                        nb_jumps=2;
                    }
                }else{
                    if( wallJumpDown){
                        m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                        nb_jumps=1;
                        m_velocity.y=-WALL_JUMP_SPEED;
                        m_walljump=WALL_JUMP_TIME;
                    }else{
                        if(walljumpUp){
                            m_velocity.x=WALL_JUMP_HEIGHT*m_gravity;
                            nb_jumps=1;
                            m_velocity.y=WALL_JUMP_SPEED;
                            m_walljump=WALL_JUMP_TIME;
                        }
                    }
                }
            }
        }else{
            m_jump=canJump();
            bool walljumpRight=canWallJumpRight();
            bool walljumpLeft=canWallJumpLeft();
            if(m_jump || (nb_jumps<2  && !walljumpRight && !walljumpLeft)){
                m_velocity.y = JUMP*m_gravity;
                if (m_jump){
                        nb_jumps=1;
                    }else{
                        nb_jumps=2;
                    }
            }else{
                if( walljumpRight){
                    m_velocity.y=WALL_JUMP_HEIGHT*m_gravity;
                    nb_jumps=1;
                    m_velocity.x=-WALL_JUMP_SPEED;
                    m_walljump=WALL_JUMP_TIME;
                }else{
                    if( walljumpLeft){
                        m_velocity.y=WALL_JUMP_HEIGHT*m_gravity;
                        nb_jumps=1;
                        m_velocity.x=WALL_JUMP_SPEED;
                        m_walljump=WALL_JUMP_TIME;
                    }
                }
            }
            m_jump=false;
        }        
    }

    void Square::update(float dt)
    {
        bool walljumpRight=canWallJumpRight();
        bool walljumpLeft=canWallJumpLeft();
        bool walljumpUp=canWallJumpUp();
        bool wallJumpDown=canWallJumpDown();
        timer+=dt;
        if(timer>999.99f){
            isOver=true;
        }
        m_walljump-=dt;
        if(m_walljump<0.0f){
            m_walljump=0.0f;
        }
      
        // Appliquez la gravité
        if(horizontal_g){
            setVelocity(m_velocity + gf::Vector2f( gravity * m_gravity * dt,0));
            if(m_velocity.x<-SPEED_LIMIT){
                m_velocity.x=-SPEED_LIMIT;
            }
            if(m_velocity.x>SPEED_LIMIT){
                m_velocity.x=SPEED_LIMIT;
            }
            if (!goUp && m_velocity.y<0.0f && m_velocity.y!=-WALL_JUMP_SPEED){
                m_velocity.y+=gravity*dt*2.5f;
                if (m_velocity.y>0.0f){
                    m_velocity.y=0.0f;
                }
            }
            if (!goDown && m_velocity.y>0.0f &&  m_velocity.y!=WALL_JUMP_SPEED){
                m_velocity.y-=gravity*dt*2.5f;
                if (m_velocity.y<0.0f){
                    m_velocity.y=0.0f;
                }
            }
        }else{
            setVelocity(m_velocity + gf::Vector2f(0, gravity * m_gravity * dt));
            if(m_velocity.y<-SPEED_LIMIT){
                m_velocity.y=-SPEED_LIMIT;
            }
            if(m_velocity.y>SPEED_LIMIT){
                m_velocity.y=SPEED_LIMIT;
            }
            if (!goLeft && m_velocity.x<0.0f &&  m_velocity.x!=-WALL_JUMP_SPEED){
                m_velocity.x+=gravity*dt*2.5f;
                if (m_velocity.x>0.0f){
                    m_velocity.x=0.0f;
                }
            }
            if (!goRight && m_velocity.x>0.0f &&  m_velocity.x!=WALL_JUMP_SPEED){
                m_velocity.x-=gravity*dt*2.5f;
                if (m_velocity.x<0.0f){
                    m_velocity.x=0.0f;
                }
            }
        }
        // Mettez à jour la position du carré
        m_position += dt * m_velocity;
        
        
        // Vérifiez les collisions avec la plateforme
        for (auto &plateform : m_plateforms)
        {
            collideWithPlateform(plateform.getPosition(), plateform.getHeight(), plateform.getLength(),plateform.getColor(),walljumpLeft,walljumpRight,wallJumpDown,walljumpUp);
        }

        
    }

    bool Square::isPlateform(StaticPlateform plateform){
        auto color=plateform.getColor();
        return color!=gf::Color::Yellow && color!=gf::Color::Orange && color!=gf::Color::Rose && color!=gf::Color::Green && color!=gf::Color::Black && color!=gf::Color::Cyan && !(color==gf::Color::fromRgb(100,100,10) && m_gravityDirection=="down") && !(color==gf::Color::fromRgb(100,100,20) && m_gravityDirection=="up") && !(color==gf::Color::fromRgb(100,100,30) && m_gravityDirection=="left") && !(color==gf::Color::fromRgb(100,100,40) && m_gravityDirection=="right");
    }

    bool Square::canJump(){
        for (auto &plateform : m_plateforms)
        {
            if(isPlateform(plateform)){
                gf::Vector2f plateformPosition=plateform.getPosition();
                float plateformHeight=plateform.getHeight();
                float plateformLength=plateform.getLength();
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

    bool Square::canWallJumpRight(){
        for (auto &plateform : m_plateforms)
        {
            if(isPlateform(plateform)){
                gf::Vector2f plateformPosition=plateform.getPosition();
                float plateformHeight=plateform.getHeight();
                float plateformLength=plateform.getLength();
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

    bool Square::canWallJumpLeft(){
        for (auto &plateform : m_plateforms)
        {
            if(isPlateform(plateform)){
                gf::Vector2f plateformPosition=plateform.getPosition();
                float plateformHeight=plateform.getHeight();
                float plateformLength=plateform.getLength();
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

    bool Square::canWallJumpUp(){
        for (auto &plateform : m_plateforms)
        {
            if(isPlateform(plateform)){
                gf::Vector2f plateformPosition=plateform.getPosition();
                float plateformHeight=plateform.getHeight();
                float plateformLength=plateform.getLength();
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

    bool Square::canWallJumpDown(){
        for (auto &plateform : m_plateforms)
        {
            if(isPlateform(plateform)){
                gf::Vector2f plateformPosition=plateform.getPosition();
                float plateformHeight=plateform.getHeight();
                float plateformLength=plateform.getLength();
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

    void Square::render(gf::RenderTarget &target)
    {
        gf::RectangleShape shape({m_size, m_size});
        shape.setPosition(m_position);
        shape.setColor(m_color);
        shape.setAnchor(gf::Anchor::Center);
        target.draw(shape);
    }

    void Square::renderHUD(gf::RenderTarget &target,float width,float height,gf::Vector2f pos)
    {
        gf::Font font(PATH_FONT);
        gf::Text deathText;
        deathText.setFont(font);
        deathText.setColor(gf::Color::White);
        deathText.setCharacterSize(20);
        deathText.setString(std::to_string((int)timer));
        deathText.setPosition(pos+gf::Vector2f(-(width/2)+45.0f, -(height/2)+10.0f));
        deathText.setAnchor(gf::Anchor::TopRight);
        target.draw(deathText);
    }

    // empeche le carré de traverser une plateforme
    void Square::collideWithPlateform(gf::Vector2f plateformPosition, float plateformHeight, float plateformLength,gf::Color4f color,bool wallLeft,bool wallRight,bool wallDown,bool wallUp)
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
            if (wallUp){ 
                squareTop-=1;
            }
            if (wallDown){ 
                squareBottom+=1;
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
                m_gravityDirection="down";
                return;
            }
            // close the game
            if (color==gf::Color::Black){
                isOver = true;
            }
            // Collision détectée. Maintenant, nous devons ajuster la position du carré.

            // Vérifiez de quel côté le carré entre en collision
            // gravity switch up
            else if(color==gf::Color::Cyan){
                m_gravityDirection = "up";
                m_gravity=-1;
                if (horizontal_g){
                    if (goLeft){
                        m_velocity.x=-SPEED_SQUARE;
                    }
                    if (goRight){
                        m_velocity.x=SPEED_SQUARE;
                    }
                }
                horizontal_g=false;
            }
            // gravity switch down
            else if(color==gf::Color::Rose){
                m_gravityDirection = "down";
                m_gravity=1;
                if (horizontal_g){
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
                m_gravityDirection = "left";
                m_gravity=-1;
                if (!horizontal_g){
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
                m_gravityDirection = "right";
                if (!horizontal_g){
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
            // plateforme that can be passed through            
            // wall down
            else if(color==gf::Color::fromRgb(100,100,10) && m_gravityDirection=="down"){
                // si la gravité est vers le bas, la plateforme est intangible
                return;
            }
            // wall up
            else if(color==gf::Color::fromRgb(100,100,20) && m_gravityDirection=="up"){
                // si la gravité est vers le haut, la plateforme est intangible
                return;
            }

            // wall left
            else if(color==gf::Color::fromRgb(100,100,30) && m_gravityDirection=="left"){
                // si la gravité est vers la gauche, la plateforme est intangible
                return;
            }
            // wall right
            else if(color==gf::Color::fromRgb(100,100,40) && m_gravityDirection=="right"){
                // si la gravité est vers la droite, la plateforme est intangible
                return;
            }
                

            else{
                float overlapLeft = squareRight - plateformLeft;
                float overlapRight = plateformRight - squareLeft;
                float overlapTop = squareBottom - plateformTop;
                float overlapBottom = plateformBottom - squareTop;

                // Trouvez le chevauchement le plus petit
                float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                // Ajustez la position du carré en fonction du plus petit chevauchement
                if (minOverlap == overlapLeft && (((!wallDown || plateformTop<=squareTop) && (!wallUp || plateformBottom>=squareBottom)) || (wallUp && wallDown)))
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
                else if (minOverlap == overlapRight && (((!wallDown || plateformTop<=squareTop) && (!wallUp || plateformBottom>=squareBottom)) || (wallUp && wallDown)))
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