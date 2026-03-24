#include "ReplayManager.h"
#include "Globals.h"

ReplayNode* ReplayManager::appendReplayChunk(ReplayManager* This, int currentStage)
{   
    puts("Appending chunk\n");
    ReplayDataChunk* chunk = (ReplayDataChunk*) game_new(sizeof(ReplayDataChunk));
    if (!chunk)
    {
        puts("Out of memory!");
        return nullptr;
    }
    else
    {
        memset(chunk, 0, sizeof(ReplayDataChunk));
        chunk->selfPtr = chunk;
        chunk->auxDataPtr = chunk->auxData;
        chunk->replayNode.owner = chunk;
        chunk->replayNode.next = nullptr;
        chunk->replayNode.prev = nullptr;
    }

    ReplayNode* head = &This->stageDataHeads[currentStage];
    ReplayNode* next = This->stageDataHeads[currentStage].next;

    while (next)
    {
        head = head->next;
        next = head->next;
    }

    // this is always false since we have just traversed to the end of the list...
    // if (head->next)
    // {
    //     chunk->replayNode.next = head->next;
    //     head->next->prev = &chunk->replayNode;
    // }

    head->next = &chunk->replayNode;
    chunk->replayNode.prev = head;
    ++This->chunkCount;
    return &chunk->replayNode;
}

