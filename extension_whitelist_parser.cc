/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "extension_whitelist_parser.h"

ExtensionWhitelistParser::ExtensionWhitelistParser() {
  mBlacklist = std::make_unique<ExtensionSet>();
  mWhitelist = std::make_unique<ExtensionSet>();
}

ExtensionWhitelistParser::~ExtensionWhitelistParser() {
}

void ExtensionWhitelistParser::addToBlacklist(const char *extensionID) {
  if (!extensionID || strlen(extensionID) != EXTENSION_ID_LEN)
    return;

  std::string extensionData(extensionID);
  mBlacklist->Add(extensionData);
}

void ExtensionWhitelistParser::addToWhitelist(const char *extensionID) {
  if (!extensionID || strlen(extensionID) != EXTENSION_ID_LEN)
    return;

  std::string extensionData(extensionID);
  mWhitelist->Add(extensionData);
}

bool ExtensionWhitelistParser::isBlacklisted(const char *extensionID) {
  if (!extensionID || strlen(extensionID) != EXTENSION_ID_LEN)
    return false;

  std::string extensionData(extensionID);
  return mBlacklist->Exists(extensionData);
}

bool ExtensionWhitelistParser::isWhitelisted(const char *extensionID) {
  if (!extensionID || strlen(extensionID) != EXTENSION_ID_LEN)
    return false;

  std::string extensionData(extensionID);
  return mWhitelist->Exists(extensionData);
}

// Returns a newly allocated buffer, caller must manually delete[] the buffer
char* ExtensionWhitelistParser::serialize(unsigned int* totalSize) {
  *totalSize = 0;
  uint32_t blacklistSize = 0;
  char* blacklist = mBlacklist->Serialize(&blacklistSize);
  uint32_t whitelistSize = 0;
  char* whitelist = mWhitelist->Serialize(&whitelistSize);
  *totalSize = DECIMAL_STR_MAX(uint32_t) + blacklistSize + 1 +
    DECIMAL_STR_MAX(uint32_t) + whitelistSize + 1;
  unsigned int pos = 0;
  char* result = new char[*totalSize];
  if (!result) {
    delete []blacklist;
    delete []whitelist;
    return nullptr;
  }
  memset(result, 0, *totalSize);
  uint32_t dataLenSize = 1 + sprintf(result + pos, "%" PRIu32, blacklistSize);
  pos += dataLenSize;
  memcpy(result + pos, blacklist, blacklistSize);
  pos += blacklistSize;
  dataLenSize = 1 + sprintf(result + pos, "%" PRIu32, whitelistSize);
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
  sscanf(buffer, "%" SCNu32, &blacklistSize);
  pos += static_cast<uint32_t>(strlen(buffer) + 1);
  mBlacklist->Deserialize(buffer + pos, blacklistSize);
  pos += blacklistSize;
  uint32_t whitelistSize = 0;
  sscanf(buffer + pos, "%" SCNu32, &whitelistSize);
  pos += static_cast<uint32_t>(strlen(buffer + pos) + 1);
  mWhitelist->Deserialize(buffer + pos, whitelistSize);
  return true;
}
