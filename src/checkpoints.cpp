// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of // TODO: needs to adjusted for checkpoint checks, also see main.cpp
        (         1, uint256("0x8c006330b854ec9186e089296f9f066def657c8b2536c550153793e1bc2d3db8"))
        (         2, uint256("0xe2e4ed77e8929e2df99017941ae1bbb3529e8408475dde9a8b85f77acf4d6784"))
        (         5, uint256("0x92ccf402a68f2728b44443bc2e72f73ef7e4752446de70cb8c833e8d791c8b64"))
        (        10, uint256("0xf364fa21b600c80dc9caa7efb72d2eee8ddf43d2ab344da726fb8f48d71b30b7"))
        (        20, uint256("0x07eefa223ac17a93a10ffebef093ad07a816c19fe867fc47a06a4b3ed8b8fd6b"))
        (        25, uint256("0xabe8a64ce63f8de5b7b585c4f9ddb1fd19f0c32e8d22e7d4f63567ea44034658"))
        (        40, uint256("0x6061840b0117bca2f504bcadd5572b517d642a85371c740a779a78c30072aaec"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
