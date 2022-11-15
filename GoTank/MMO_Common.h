#ifndef MMO_COMMON_H
#define MMO_COMMON_H

#include <cstdint>

#define OLC_PGEX_NETWORK
#include "olcPGEX_Network.h"

const int UNIT_SIZE = 30;

enum class GameMsg : uint32_t
{
    Server_GetStatus,
    Server_GetPing,

    Client_Accepted,
    Client_AssignID,
    Client_RegisterWithServer,
    Client_UnregisterWithServer,

    Game_AddPlayer,
    Game_RemovePlayer,
    Game_UpdatePlayer,

    FireBullet,
};

enum Direction {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown
};

struct sPlayerDescription
{
    uint32_t nUniqueID = 0;
    uint32_t nAvatarID = 0;

    uint32_t nHealth = 100;
    uint32_t nAmmo = 20;
    uint32_t nKills = 0;
    uint32_t nDeaths = 0;

    int32_t x;
    int32_t y;
    Direction direction;
    uint32_t vVel;
};

struct sBulletDescription
{
    int32_t x;
    int32_t y;
    Direction direction;
    uint32_t vVel;
};



#endif // MMO_COMMON_H
