#include "ScriptMgr.h"
#include "Config.h"
#include "AuctionHouseMgr.h"
#include "ObjectMgr.h"
#include "GameEventMgr.h"
#include "DatabaseEnv.h"
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

#define GLYPH_AUCTION_REFRESH_EVENT 1234 // Choose a unique event ID

class GlyphAuctionHouse : public WorldScript
{
public:
    GlyphAuctionHouse() : WorldScript("GlyphAuctionHouseScript"), _refreshTimer(0) {}

    void OnStartup() override
    {
        PopulateAuctionHouse();
    }

    void OnConfigLoad(bool /*reload*/)
    {
        LoadConfigValues();
    }

    void OnUpdate(uint32 diff) override
    {
        _refreshTimer += diff;
        if (_refreshTimer >= refreshInterval * HOUR * IN_MILLISECONDS)
        {
            PopulateAuctionHouse();
            _refreshTimer = 0;
        }
    }

private:
    uint32 _refreshTimer;
    std::vector<uint32> glyphIds = {
        // Combined Glyph IDs
        43533, 43534, 43535, 43536, 43537, 43538, 43539, 43541, 43542, 43543,
        43544, 43545, 43546, 43547, 43548, 43549, 43550, 43551, 43552, 43553,
        43554, 43825, 43826, 43827, 45799, 45800, 45803, 45804, 45805, 45806,
        40896, 40897, 40899, 40900, 40901, 40902, 40903, 40906, 40908, 40909,
        40912, 40913, 40914, 40915, 40916, 40919, 40920, 40921, 40922, 40923,
        40924, 44928, 45601, 45602, 45603, 45604, 45622, 45623, 45625, 46372,
        42897, 42898, 42899, 42900, 42901, 42902, 42903, 42904, 42905, 42906,
        42907, 42908, 42909, 42910, 42911, 42912, 42913, 42914, 42915, 42916,
        42917, 45625, 45731, 45732, 45733, 45734, 45735, 45740, 45741, 45742,
        42734, 42735, 42736, 42737, 42738, 42739, 42740, 42741, 42742, 42743,
        42744, 42745, 42746, 42747, 42748, 42749, 42750, 42751, 42752, 42753,
        42754, 44684, 44920, 44955, 45736, 45737, 45738, 45739, 45740, 45741,
        41092, 41094, 41095, 41096, 41097, 41098, 41099, 41100, 41101, 41102,
        41103, 41104, 41105, 41106, 41107, 41108, 41109, 41110, 41099, 41100,
        41101, 43867, 43868, 43869, 45741, 45742, 45743, 45744, 45745, 45746,
        42396, 42397, 42398, 42399, 42400, 42401, 42402, 42403, 42404, 42405,
        42406, 42407, 42408, 42409, 42410, 42411, 42412, 42414, 42415, 42416,
        42417, 43342, 43370, 43371, 45753, 45755, 45756, 45757, 45758, 45760,
        42954, 42955, 42956, 42957, 42958, 42959, 42960, 42961, 42962, 42963,
        42964, 42965, 42966, 42967, 42968, 42969, 42970, 42971, 42972, 42973,
        42974, 45761, 45762, 45764, 45766, 45767, 45768, 45769, 45770, 45775,
        41517, 41518, 41524, 41526, 41527, 41529, 41530, 41531, 41532, 41533,
        41534, 41535, 41536, 41537, 41538, 41539, 41540, 41541, 41542, 41547,
        41552, 44923, 45770, 45771, 45772, 45775, 45776, 45777, 45778, 45779,
        42454, 42455, 42456, 42457, 42458, 42459, 42460, 42461, 42462, 42463,
        42464, 42465, 42466, 42467, 42468, 42469, 42470, 42471, 42472, 42473,
        42474, 45779, 45780, 45781, 45782, 45783, 45785, 45789, 45790, 45792,
        43412, 43413, 43414, 43415, 43416, 43417, 43418, 43419, 43420, 43421,
        43422, 43423, 43424, 43425, 43426, 43427, 43428, 43429, 43430, 43431,
        43432, 45790, 45792, 45793, 45794, 45795, 45797, 45798, 45799, 45800,
        42897, 43366, 43367, 43368, 43369, 43370, 43371, 43372, 43373, 43374,
        43375, 43376, 43377, 43378, 43379, 43380, 43381, 43382, 43383, 43384,
        43385, 43386, 43387, 43388, 43389, 43390, 43391, 43392, 43393, 43394
    };

    int minQuantity = 1;
    int maxQuantity = 5;
    uint32 minPrice = 50000;  // 5 gold
    uint32 maxPrice = 150000; // 15 gold
    int refreshInterval = 6;  // hours
    uint32 auctionDuration = 12 * HOUR; // New member for auction duration

    void LoadConfigValues()
    {
        minQuantity = sConfigMgr->GetOption<int32>("GlyphAH.MinQuantity", 1);
        maxQuantity = sConfigMgr->GetOption<int32>("GlyphAH.MaxQuantity", 5);
        minPrice = sConfigMgr->GetOption<uint32>("GlyphAH.MinPrice", 50000);
        maxPrice = sConfigMgr->GetOption<uint32>("GlyphAH.MaxPrice", 150000);
        refreshInterval = sConfigMgr->GetOption<int32>("GlyphAH.RefreshInterval", 6);
        auctionDuration = sConfigMgr->GetOption<uint32>("GlyphAH.AuctionDuration", 12) * HOUR;
    }

    void PopulateAuctionHouse()
    {
        CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

        for (uint32 glyphId : glyphIds)
        {
            int quantity = GenerateRandomNumber(minQuantity, maxQuantity);
            uint32 price = CalculateGlyphPrice();

            AuctionHouseObject* auctionHouse = sAuctionMgr->GetAuctionsMap(2);  // 2 is for neutral AH
            AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(2);

            Item* item = Item::CreateItem(glyphId, quantity);
            if (!item)
                continue;

            uint32 etime = auctionDuration; // Use the configurable auction duration

            AuctionEntry* auctionEntry = new AuctionEntry();
            auctionEntry->Id = sObjectMgr->GenerateAuctionID();
            auctionEntry->item_guid = item->GetGUID();
            auctionEntry->owner = ObjectGuid::Empty;
            auctionEntry->startbid = price * 0.95;  // Start bid at 95% of buyout
            auctionEntry->buyout = price;
            auctionEntry->expire_time = time(nullptr) + etime;
            auctionEntry->deposit = 0;
            auctionEntry->auctionHouseEntry = ahEntry;

            item->SaveToDB(trans);
            sAuctionMgr->AddAItem(item);
            auctionHouse->AddAuction(auctionEntry);
            auctionEntry->SaveToDB(trans);
        }

        CharacterDatabase.CommitTransaction(trans);

        ScheduleNextRefresh();
    }

    uint32 CalculateGlyphPrice()
    {
        return GenerateRandomNumber(minPrice, maxPrice);
    }

    int GenerateRandomNumber(int min, int max)
    {
        static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    void ScheduleNextRefresh()
    {
        // This method is no longer needed, as we're using OnUpdate for periodic refresh
    }
};

void AddGlyphAuctionModuleScripts()
{
    new GlyphAuctionHouse();
}
