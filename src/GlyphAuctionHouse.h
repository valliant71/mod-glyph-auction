#ifndef GLYPH_AUCTION_HOUSE_H
#define GLYPH_AUCTION_HOUSE_H

#include "ScriptMgr.h"

class GlyphAuctionHouse : public WorldScript
{
public:
    GlyphAuctionHouse();

    void OnStartup() override;
    void OnConfigLoad(bool reload) override;

private:
    // Declare your private methods and variables here
};

#endif // GLYPH_AUCTION_HOUSE_H