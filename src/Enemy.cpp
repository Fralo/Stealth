//
//
// Created by vivedo on 09/05/20.
//

#include "Enemy.hpp"

Enemy::Enemy(sf::Vector2f position, float orientation, Weapon weapon, EnemyView view, const std::shared_ptr<Strategy>& defaultStrategy)
        : orientation(orientation), defaultStrategy(defaultStrategy), strategy(defaultStrategy), weapon(weapon), view(view) {
    setPos(position);
    orientationTarget = orientation;
}

void Enemy::update(const std::list<std::shared_ptr<Object>> &objects, Player &player, TiledMap &map) {
    //enemy death
    if(getHealth() == 0) {
        //TODO: fix the enemy death, also if we do return game call the enemy update every time !! The SIGSEGV error is for this
        std::cout<<"hello"<<std::endl;
        notifyEnemyKilled();
        unsubscribe(killedEnemyObservers.back());
        unsubscribe(stealthStatusObserver.back());
    }

    //generate the vector of vertices to find the player
    std::vector<sf::Vector2f> coordinates;
    coordinates.push_back(getPos());
    coordinates.push_back(MathHelper::getAbsoluteCoordinates(MathHelper::getVertices(view.distance,view.angle,orientation,sightSwingVariation).at(0),getPos()));
    coordinates.push_back(MathHelper::getAbsoluteCoordinates(MathHelper::getVertices(view.distance,view.angle,orientation,sightSwingVariation).at(1),getPos()));


    if (MathHelper::distanceBetweenTwoPoints(player.getPos(), getPos()) <
        MathHelper::distanceBetweenTwoPoints(coordinates.at(1), getPos()))
        if (MathHelper::isTargetInside(coordinates, player.getPos()))
            for (const std::shared_ptr<Object>& obj : objects) {
                if (MathHelper::hasLineOfSight(obj->getPos(), player.getPos(), obj->getAbsCollisionBox()))
                    strategy = std::make_shared<HunterStrategy>();
                    notifyStealthObserver();
            }


    sf::Vector2f next = strategy->getNextMove(*this, objects, player, map);

    if (MathHelper::distanceBetweenTwoPoints(getPos(), player.getPos()) > weapon.distanceOfUse - 10) {

        float movementFactor = 1;
        setPos(sf::Vector2f(getPos().x + next.x * movementFactor, getPos().y + next.y * movementFactor));

        if (next.x || next.y)
            orientationTarget = -std::atan2(next.y, next.x) / M_PI;

        if (orientation != orientationTarget) {
            double diff = orientationTarget - orientation;
            diff += (diff > 1) ? -2 : (diff < -1) ? 2 : 0;
            orientation += diff / 10;
        }
        sightSwingVariation = view.swing * std::sin(clock.getElapsedTime().asMilliseconds() / 500.0f);
    } else {
        coordinates.clear();
        coordinates.push_back(getPos());
        coordinates.push_back(MathHelper::getAbsoluteCoordinates(MathHelper::getVertices(weapon.distanceOfUse,weapon.angle,orientation,sightSwingVariation).at(0),getPos()));
        coordinates.push_back(MathHelper::getAbsoluteCoordinates(MathHelper::getVertices(weapon.distanceOfUse,weapon.angle,orientation,sightSwingVariation).at(1),getPos()));

        if(MathHelper::isTargetInside(coordinates,player.getPos()))
            if (player.getHealth()>0)
                player.applyDamage(1);
    }


    const char *dir = "idle";
    switch(Direction(next)){
        case Direction::NORTH:
            dir = "walk_n";
            break;
        case Direction::NORTH_EAST:
            dir = "walk_ne";
            break;
        case Direction::EAST:
            dir = "walk_e";
            break;
        case Direction::SUD_EAST:
            dir = "walk_se";
            break;
        case Direction::SUD:
            dir = "walk_s";
            break;
        case Direction::SUD_OVEST:
            dir = "walk_so";
            break;
        case Direction::OVEST:
            dir = "walk_o";
            break;
        case Direction::NORTH_OVEST:
            dir = "walk_no";
            break;
    }

    tile = map.getAnimation("player", dir).getCurrentFrame();
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    tile->setPosition(getPos().x - 30, getPos().y - 30);
    target.draw(*tile);

    sf::ConvexShape sightTriangle = getSightTraigle();
    sightTriangle.setFillColor(sf::Color(0x0, 0xd0, 0x20, 0x7f));

    target.draw(sightTriangle);

    sf::RectangleShape re({static_cast<float>(getHealth()) / 100 * 20, 2});
    re.setPosition({getPos().x - 10, getPos().y - 25});
    re.setFillColor(sf::Color::Red);

    target.draw(re);
}


sf::ConvexShape Enemy::getSightTraigle() const {
    sf::ConvexShape triangle(3);
    triangle.setPoint(0, sf::Vector2f(0, 0));
    triangle.setPoint(1, MathHelper::getVertices(view.distance,view.angle,orientation,sightSwingVariation).at(0));
    triangle.setPoint(2, MathHelper::getVertices(view.distance,view.angle,orientation,sightSwingVariation).at(1));

    triangle.setPosition(sf::Vector2f(getPos()));
    return triangle;
}


void Enemy::applyDamage(int damage) {
    setHealth(getHealth() - 1);
}

//new observer implementation

void Enemy::subscribe(std::shared_ptr<KilledEnemyObserver> observer) {
    killedEnemyObservers.push_back(observer);
}

void Enemy::unsubscribe(std::shared_ptr<KilledEnemyObserver> observer) {

    killedEnemyObservers.remove(observer);
}

void Enemy::notifyEnemyKilled() {
    for(auto&& o : killedEnemyObservers)
        o->update();
}

void Enemy::subscribe(std::shared_ptr<StealthStatusObserver> observer) {
    stealthStatusObserver.push_back(observer);

}

void Enemy::unsubscribe(std::shared_ptr<StealthStatusObserver> observer) {
    stealthStatusObserver.remove(observer);
}

void Enemy::notifyStealthObserver() {
    for(auto&& o : stealthStatusObserver)
        o->update();
}


