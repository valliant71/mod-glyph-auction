# Glyph Auction Module

This module automatically populates the auction house with glyphs in AzerothCore.

## Features

- Adds all available glyphs for WotLK 3.3.5a to the auction house
- Implements a dynamic pricing mechanism
- Periodically refreshes the auction house entries

## Installation

1. Clone this module into the `modules` directory of your AzerothCore source:

```
cd path/to/azerothcore/modules
git clone https://github.com/your-username/mod-glyph-auction.git
```

2. Re-run CMake and rebuild AzerothCore.

## Configuration

Add the following to your `worldserver.conf` file:

```ini
###################################################################################################
#  GLYPH AUCTION HOUSE
#
#    GlyphAH.MinQuantity
#        Description: Minimum quantity of each glyph to post
#        Default:     1
#
#    GlyphAH.MaxQuantity
#        Description: Maximum quantity of each glyph to post
#        Default:     5
#
#    GlyphAH.MinPrice
#        Description: Minimum price for glyphs (in copper)
#        Default:     50000
#
#    GlyphAH.MaxPrice
#        Description: Maximum price for glyphs (in copper)
#        Default:     150000
#
#    GlyphAH.RefreshInterval
#        Description: How often to refresh the auction house (in hours)
#        Default:     6

GlyphAH.MinQuantity = 1
GlyphAH.MaxQuantity = 5
GlyphAH.MinPrice = 50000
GlyphAH.MaxPrice = 150000
GlyphAH.RefreshInterval = 6
```

## Credits

- [Your Name]
- AzerothCore: [repository](https://github.com/azerothcore/azerothcore-wotlk)
