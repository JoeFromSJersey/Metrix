// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CHAIN_PARAMS_H
#define BITCOIN_CHAIN_PARAMS_H

#include "bignum.h"
#include "core.h"
#include "chainparamsbase.h"
#include "protocol.h"
#include "uint256.h"

#include <vector>

using namespace std;

typedef unsigned char MessageStartChars[MESSAGE_START_SIZE];


struct CDNSSeedData {
    std::string name, host;
    CDNSSeedData(const std::string &strName, const std::string &strHost) : name(strName), host(strHost) {}
};

/**
 * CChainParams defines various tweakable parameters of a given instance of the
 * Bitcoin system. There are three: the main network on which people trade goods
 * and services, the public test network which gets reset from time to time and
 * a regression test mode which is intended for private networks only. It has
 * minimal difficulty to ensure that blocks can be found instantly.
 */
class CChainParams
{
public:
    enum Base58Type {
        PUBKEY_ADDRESS,
        SCRIPT_ADDRESS,
        SECRET_KEY,
        EXT_PUBLIC_KEY,
        EXT_SECRET_KEY,

        MAX_BASE58_TYPES
    };

    const uint256& HashGenesisBlock() const { return hashGenesisBlock; }
    const MessageStartChars& MessageStart() const { return pchMessageStart; }
    const std::vector<unsigned char>& AlertKey() const { return vAlertPubKey; }
    int GetDefaultPort() const { return nDefaultPort; }
    const uint256& ProofOfWorkLimit() const { return bnProofOfWorkLimit; }
    int SubsidyHalvingInterval() const { return nSubsidyHalvingInterval; }

    /* Used to check majorities for block version upgrade */
    int EnforceBlockUpgradeMajority() const { return nEnforceBlockUpgradeMajority; }
    int RejectBlockOutdatedMajority() const { return nRejectBlockOutdatedMajority; }
    int ToCheckBlockUpgradeMajority() const { return nToCheckBlockUpgradeMajority; }

	const CBlock& GenesisBlock() const { return genesis; }
	bool RequireRPCPassword() const { return fRequireRPCPassword; }
    /* Default value for -checkmempool argument */
	bool DefaultCheckMemPool() const { return fDefaultCheckMemPool; }
	/* Make standard checks */
	bool RequireStandard() const { return fRequireStandard; }
    CBaseChainParams::Network NetworkID() const { return networkID; }
    /* Return the BIP70 network string (main, test or regtest) */
    std::string NetworkIDString() const { return strNetworkID; }
    const std::vector<CDNSSeedData>& DNSSeeds() const { return vSeeds; }
	const std::vector<unsigned char>& Base58Prefix(Base58Type type) const { return base58Prefixes[type]; }
	const std::vector<CAddress>& FixedSeeds() const { return vFixedSeeds; }
    int LastPOWBlock() const { return nLastPOWBlock; }
protected:
    CChainParams() {};

    uint256 hashGenesisBlock;
    MessageStartChars pchMessageStart;
    // Raw pub key bytes for the broadcast alert signing key.
    std::vector<unsigned char> vAlertPubKey;
    int nDefaultPort;
    uint256 bnProofOfWorkLimit;
    int nSubsidyHalvingInterval;
    int nEnforceBlockUpgradeMajority;
    int nRejectBlockOutdatedMajority;
    int nToCheckBlockUpgradeMajority;
    std::vector<CDNSSeedData> vSeeds;
    std::vector<unsigned char> base58Prefixes[MAX_BASE58_TYPES];
    int nLastPOWBlock;
    CBaseChainParams::Network networkID;
    std::string strNetworkID;
	CBlock genesis;
	std::vector<CAddress> vFixedSeeds;
	bool fRequireRPCPassword;
	bool fDefaultCheckMemPool;
	bool fRequireStandard;
};

/**
 * Return the currently selected parameters. This won't change after app startup
 * outside of the unit tests.
 */
const CChainParams &Params();

/** Return parameters for the given network. */
CChainParams& Params(CBaseChainParams::Network network);

/** Sets the params returned by Params() to those for the given network. */
void SelectParams(CBaseChainParams::Network network);

/**
 * Looks for -regtest or -testnet and then calls SelectParams as appropriate.
 * Returns false if an invalid combination is given.
 */
bool SelectParamsFromCommandLine();

#endif // BITCOIN_CHAIN_PARAMS_H