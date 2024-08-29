#ifndef GLYPH_AUCTION_HOUSE_H
#define GLYPH_AUCTION_HOUSE_H

#include "ScriptMgr.h"

class GlyphAuctionHouse : public WorldScript
{
public:
    GlyphAuctionHouse();

    void OnStartup() override;
    void OnConfigLoad(bool reload) override;
    void OnUpdate(uint32 diff) override;

private:
    // Declare your private methods and variables here
    uint32 _refreshTimer;
    
    // ... (other private method declarations)
};

#endif // GLYPH_AUCTION_HOUSE_H