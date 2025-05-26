#include "CollisionHandling.h"

namespace // anonymous namespace — the standard way to make function "static"
{
    // Function to handle collision between player and car.
    // The car is stopped on collision.
    void playerCar(Object& player, Object& car)
    {
        auto& car_c = static_cast<CarRectBase&>(car);
        car_c.stop();
        //static_cast<Player&>(player).handleCarCollision(std::make_shared<CarRectBase>(car_c));
    }

    // Function to handle collision between player and gift.
    void playerGift(Object& player, Object& gift)
    {
        Gift& gift_c = static_cast<Gift&>(gift);
        gift_c.Collect();
        gift_c.HandleGift();
    }

    // Function to handle collision between two cars.
    void carCar(Object& car1, Object& car2)
    {
        CarRectBase& car1_c = static_cast<CarRectBase&>(car1);
        CarRectBase& car2_c = static_cast<CarRectBase&>(car2);
        car1_c.HandleCarCollision(car2_c);
    }


    // Function to handle collision between car and player.
    void carPlayer(Object& car, Object& player)
    {
        playerCar(player, car);
    }

    void giftPlayer(Object& gift, Object& player)
    {
        playerGift(player, gift);
    }


    using HitFunctionPtr = std::function<void(Object&, Object&)>;
    // typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    // std::unordered_map is better, but it requires defining good hash function for pair
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;

        phm[Key(typeid(Player), typeid(CarRectBase))] = &playerCar;
        phm[Key(typeid(CarRectBase), typeid(Player))] = &carPlayer;

        phm[Key(typeid(Player), typeid(Gift))] = &playerGift;
        phm[Key(typeid(Gift), typeid(Player))] = &giftPlayer;

        phm[Key(typeid(CarRectBase), typeid(CarRectBase))] = &carCar;

        return phm;
    }

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace

void processCollision(Object& object1, Object& object2)
{
    auto phf = lookup(getParentTypeId(object1), getParentTypeId(object2));
    if (!phf)
    {
        throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}

std::type_index getParentTypeId(Object& object)
{
    if(dynamic_cast<CarRectBase*>(&object))
        return typeid(CarRectBase);
    if (dynamic_cast<Gift*>(&object))
        return typeid(Gift);
    
    return typeid(object);
}