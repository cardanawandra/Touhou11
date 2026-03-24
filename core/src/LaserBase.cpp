#include "LaserBase.h"
#include "Globals.h"

LaserBase::LaserBase()
{
    this->laserDataVtable_0x0 = &g_laserDataVftable;
    this->timer_0x14.m_isInitialized &= ~1;
    this->timer_0x28.m_isInitialized &= ~1;
    
    for (int i = 0; i < 18; ++i)
        this->tasks[i].timer.m_isInitialized &= ~1;

    this->timer1.m_isInitialized &= ~1;
    
    memset(this, 0, sizeof(LaserBase));
    
    // Inline Timer Constructor for timer_0x14
    if ((this->timer_0x14.m_isInitialized & 1) == 0)
    {
        this->timer_0x14.m_currentF = 0.0f;
        this->timer_0x14.m_current = 0;
        this->timer_0x14.m_previous = -999999;
        this->timer_0x14.m_gameSpeed = &g_gameSpeed;
        this->timer_0x14.m_isInitialized |= 1;
    }
    this->timer_0x14.m_currentF = 0.0f;
    this->timer_0x14.m_current = 0;
    this->timer_0x14.m_previous = -1;
}