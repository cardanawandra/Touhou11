#include "Globals.h"
#include "TextHelper.h"

bool TextHelper::invertTextureAlpha(int height)
{
    // Pitch * Height = total bytes of the locked texture area
    int totalBytes = g_lockedTexPitch * height;
    uint8_t* pBits = static_cast<uint8_t*>(g_lockedTexBits);

    if (g_lockedTexFormat == D3DFMT_A8R8G8B8)
    {
        // 32-bit: Alpha is the 4th byte (offset 3).
        for (int i = 3; i < totalBytes; i += 4) 
            pBits[i] = ~pBits[i];
        return true;
    }
    
    if (g_lockedTexFormat == D3DFMT_A1R5G5B5)
    {
        if (totalBytes > 0) 
        {
            int numPixels = totalBytes / 2;
            uint16_t* pPixels = reinterpret_cast<uint16_t*>(pBits);
            
            for (int i = 0; i < numPixels; ++i) 
            {
                pPixels[i] ^= 0x8000;
                
                // If the new alpha bit is 0, clear the RGB data entirely
                if ((pPixels[i] & 0x8000) == 0) 
                    pPixels[i] = 0;
            }
        }
        return true;
    }
    
    if (g_lockedTexFormat == D3DFMT_A4R4G4B4) // Handled unlike in the original
    {
        for (int i = 1; i < totalBytes; i += 2) 
            pBits[i] ^= 0xF0;
        return true;
    }

    return false; // Unhandled format
}