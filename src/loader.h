#ifndef GLYPH_AUCTION_LOADER_H
#define GLYPH_AUCTION_LOADER_H

void AddGlyphAuctionModuleScripts();

// This function should match the name that the core is trying to call
void AddGlyphAuctionScripts()
{
    AddGlyphAuctionModuleScripts();
}

#endif // GLYPH_AUCTION_LOADER_H