#include "EclManager.h"
#include "EnemyManager.h"
#include <cstdio>

int EclManager::parse(EclManager* This, EclFile* eclFile)
{
    puts("Parsing\n");
    This->eclFiles[This->fileCount] = eclFile;
    
    // Verify "SCPT" magic
    if (eclFile->header.magic != 'TPCS' || eclFile->header.version != 1)
    {
        This->eclFiles[This->fileCount] = nullptr;
        return -1;
    }
    
    // Offsets start immediately after the include data
    uint32_t* offsetTable = (uint32_t*)((uint8_t*)&eclFile->bytes + eclFile->header.includeLength);

    // Names start immediately after the offset table
    uint32_t newSubCount = eclFile->header.numSubroutines;
    char* nameTable = (char*)(offsetTable + newSubCount);
    
    EclSubroutineRef* oldSubs = This->subroutines;
    int oldSize = This->size;
    
    This->size += newSubCount;
    EclSubroutineRef* newSubs = (EclSubroutineRef*)game_malloc(This->size * sizeof(EclSubroutineRef));
    This->subroutines = newSubs;

    // Initial load: no existing subroutines, just populate the array sequentially
    if (oldSubs == nullptr)
    {
        char* currentName = nameTable;
        for (int i = 0; i < This->size; i++)
        {
            newSubs[i].bytecode = (uint8_t*)&eclFile->header.magic + offsetTable[i];
            newSubs[i].name = currentName;
            currentName += strlen(currentName) + 1;
        }
    }

    // Reallocation: Merge and maintain alphabetical order (Insertion Sort)
    else
    {
        memcpy(newSubs, oldSubs, oldSize * sizeof(EclSubroutineRef));
        game_free(oldSubs);

        char* currentName = nameTable;
        for (uint32_t i = 0; i < newSubCount; i++)
        {
            int insertIdx = 0;
            for (; insertIdx < oldSize; insertIdx++)
            {
                if (strcmp(currentName, newSubs[insertIdx].name) < 0)
                    break;
            }
            
            // printf("Inserting ECL sub %s\n", newSubs[insertIdx].name);
            // Shift existing subroutines rightward to make room
            for (int j = oldSize; j > insertIdx; j--)
                newSubs[j] = newSubs[j - 1];
            
            // Insert the new subroutine
            newSubs[insertIdx].bytecode = (uint8_t*)&eclFile->header.magic + offsetTable[i];
            newSubs[insertIdx].name = currentName;
            
            currentName += strlen(currentName) + 1;
            oldSize++;
        }
    }
    
    int loadedIdx = This->fileCount++;
    
    // If the file has an include block (ANIM/ECLI), trigger the virtual load func
    if (eclFile->header.includeLength)
        This->loadInclude(This, (EclInclude*)(&eclFile->bytes));
    return loadedIdx;
}

int EclManager::loadInclude(EclManager* This, EclInclude* eclInclude)
{
    puts("Loading ECL include file");

    // Check for "ANIM" (0x4D494E41)
    if (eclInclude->magic != 'MINA')
        return 0;

    char* currentName = eclInclude->names;

    if (eclInclude->count != 0)
    {
        // Enemy animations are stored starting at offset 0x44 in EnemyManager
        AnmLoaded** targetAnmSlot = g_enemyManager->anmLoadeds;

        for (uint32_t i = 0; i < eclInclude->count; i++)
        {
            // Load enemy ANM into slots starting at 8
            AnmLoaded* anm = AnmManager::preloadAnm(i + 8, currentName);
            *targetAnmSlot = anm;

            // Bail out if loading fails
            if (anm == nullptr) {
                puts("データが壊れています\n");
                return -1;
            }

            // Advance pointer past the null-terminator
            currentName += strlen(currentName) + 1;
            targetAnmSlot++;
        }
    }

    // Align pointer to the next 4-byte boundary relative to the struct start
    uintptr_t alignOffset = (uintptr_t)currentName - (uintptr_t)eclInclude;
    if (alignOffset % 4 != 0) {
        currentName += 4 - (alignOffset % 4);
    }

    // Process "ECLI" (0x494C4345) chunk, if present
    if (*(uint32_t*)currentName == 'ILCE')
    {
        uint32_t ecliCount = *(uint32_t*)(currentName + 4);
        char* ecliName = currentName + 8;

        if (ecliCount != 0)
        {
            for (uint32_t i = 0; i < ecliCount; i++)
            {
                This->cacheAndParse(This, ecliName);

                ecliName += strlen(ecliName) + 1;
            }
        }
    }
    return 0;
}

int EclManager::cacheAndParse(EclManager* This, const char* eclPath)
{
    g_currentEclFilePath[0] = '\0';
    strcpy_s(g_currentEclFilePath, eclPath);

    // Read the actual ECL bytecode file from disk/archive into memory
    EclFile* eclFile = (EclFile*)openFile(g_currentEclFilePath, nullptr, 0);
    
    // Pass the newly loaded file to the main script parser
    int ret = This->parse(This, eclFile);
    
    return (ret >= 0) ? 0 : -1;
}