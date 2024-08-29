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
    // Declare your private methods here
    void LoadConfigValues();
    void PopulateAuctionHouse();
    uint32 CalculateGlyphPrice();
    int GenerateRandomNumber(int min, int max);
    void ScheduleNextRefresh();
};

#endif // GLYPH_AUCTION_HOUSE_H