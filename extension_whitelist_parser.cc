/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "./extension_whitelist_parser.h"
#include "hash_set.h"

ExtensionWhitelistParser::ExtensionWhitelistParser() {
  mBlacklist.reset(new HashSet<ST_EXTENSION_WHITELIST_DATA>(256, false));
  mWhitelist.reset(new HashSet<ST_EXTENSION_WHITELIST_DATA>(256, false));
}

ExtensionWhitelistParser::~ExtensionWhitelistParser() {
}

void ExtensionWhitelistParser::addToBlacklist(const char *extensionID) {
  if (nullptr == extensionID)
    return;
  ST_EXTENSION_WHITELIST_DATA extensionData;
  extensionData.sExtensionID = new char[strlen(extensionID) + 1];
  if (nullptr == extensionData.sExtensionID)
    return;
  strcpy(extensionData.sExtensionID, extensionID);
  mBlacklist->Add(extensionData);
}

void ExtensionWhitelistParser::addToWhitelist(const char *extensionID) {
  if (nullptr == extensionID)
    return;
  ST_EXTENSION_WHITELIST_DATA extensionData;
  extensionData.sExtensionID = new char[strlen(extensionID) + 1];
  if (nullptr == extensionData.sExtensionID)
    return;
  strcpy(extensionData.sExtensionID, extensionID);
  mWhitelist->Add(extensionData);
}

bool ExtensionWhitelistParser::isBlacklisted(const char *extensionID) {
  ST_EXTENSION_WHITELIST_DATA extensionData;
  extensionData.sExtensionID = new char[strlen(extensionID) + 1];
  if (nullptr == extensionData.sExtensionID)
    return false;
  strcpy(extensionData.sExtensionID, extensionID);
  return mBlacklist->Exists(extensionData);
}

bool ExtensionWhitelistParser::isWhitelisted(const char *extensionID) {
  ST_EXTENSION_WHITELIST_DATA extensionData;
  extensionData.sExtensionID = new char[strlen(extensionID) + 1];
  if (nullptr == extensionData.sExtensionID)
    return false;
  strcpy(extensionData.sExtensionID, extensionID);
  return mWhitelist->Exists(extensionData);
}

// Returns a newly allocated buffer, caller must manually delete[] the buffer
char* ExtensionWhitelistParser::serialize(unsigned int* totalSize) {
  *totalSize = 0;
  uint32_t blacklistSize = 0;
  char* blacklist = mBlacklist->Serialize(&blacklistSize);
  uint32_t whitelistSize = 0;
  char* whitelist = mWhitelist->Serialize(&whitelistSize);
  *totalSize = sizeof(blacklistSize) + blacklistSize + 1 +
    sizeof(whitelistSize) + whitelistSize + 1;
  unsigned int pos = 0;
  char* result = new char[*totalSize];
  if (!result) {
    delete []blacklist;
    delete []whitelist;
    return nullptr;
  }
  memset(result, 0, *totalSize);
  char sz[32];
  uint32_t dataLenSize = 1 + snprintf(sz, sizeof(sz), "%x", blacklistSize);
  memcpy(result + pos, sz, dataLenSize);
  pos += dataLenSize;
  memcpy(result + pos, blacklist, blacklistSize);
  pos += blacklistSize;
  dataLenSize = 1 + snprintf(sz, sizeof(sz), "%x", whitelistSize);
  memcpy(result + pos, sz, dataLenSize);
  pos += dataLenSize;
  memcpy(result + pos, whitelist, whitelistSize);
  delete []blacklist;
  delete []whitelist;
    return result;
}

bool ExtensionWhitelistParser::deserialize(char *buffer, size_t) {
  return deserialize(buffer);
}

bool ExtensionWhitelistParser::deserialize(char *buffer) {
  if (!buffer)
    return false;
  uint32_t blacklistSize = 0;
  unsigned int pos = 0;
  sscanf(buffer, "%x", &blacklistSize);
  pos += static_cast<uint32_t>(strlen(buffer) + 1);
  if (!mBlacklist->Deserialize(buffer + pos, blacklistSize))
    return false;
  pos += blacklistSize;
  uint32_t whitelistSize = 0;
  sscanf(buffer + pos, "%x", &whitelistSize);
  pos += static_cast<uint32_t>(strlen(buffer + pos) + 1);
  if (!mWhitelist->Deserialize(buffer + pos, whitelistSize)) {
    return false;
  }
  return true;
}
