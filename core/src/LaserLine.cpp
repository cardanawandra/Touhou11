#include "AnmManager.h"
#include "ItemManager.h"
#include "LaserLine.h"
#include "LaserManager.h"
#include "Globals.h"

// 0x426df0 (vfunc6)
int LaserLine::createOrDestroyLaserSegments(LaserLine* This, AnmId anmId, int cancelFlag)
{
    // If the flag is set but this bullet type doesn't support it, abort?
    if (cancelFlag != 0 && This->laserData.bulletType != 0)
        return 0;

    int count = 0;
    float currentLength = 8.0f;
    D3DXVECTOR3 step;
    decomposeAngle(&step, This->laserData.laserAngle, 8.0f);

    // spawnLocation is the base position of the laser. We start spawning 8.0 units ahead.
    D3DXVECTOR3 spawnLocation;
    spawnLocation = This->laserData.laserBasePosition + step;

    step *= 2; // Double the step vector to 16.0 units for the loop stride
    if (16.0f < This->laserData.totalLength)
    {
        do
        {
            count++;
            
            // Spawn an Anm node for the laser line
            int scriptNumber = This->scriptNumber * 2 + 2; // ??
            g_anmManager->spawnVmAtPosition(
                &g_laserManager->laserAnm, 
                &anmId, 
                scriptNumber, 
                22,
                &spawnLocation
            );

            // If an AnmId was provided (meaning this is likely a cancel event?) 
            // and the segment is inside the extended screen boundaries, spawn an item.
            if (anmId.id != 0 &&
                (spawnLocation.x + 32.0f > -192.0f) && (spawnLocation.x - 32.0f < 192.0f) &&
                (spawnLocation.y + 32.0f >   0.0f) && (spawnLocation.y - 32.0f < 448.0f))
            {
                // Item type 8 is the small Cancel Item (green star)?
                // -1.5707964 is -PI/2...
                g_itemManager->spawnItem(
                    g_itemManager,
                    &spawnLocation,
                    8,
                    0xFFFFFFFF,
                    -1.5707964f,
                    0.6f
                );
            }

            // Stride forward by 16.0 units
            spawnLocation.x += step.x;
            spawnLocation.y += step.y;
            spawnLocation.z += step.z;
            
            currentLength += 16.0f;

        } while (currentLength + 8.0f < This->laserData.totalLength);
    }

    This->laserData.opcode = 1;
    return count;
}