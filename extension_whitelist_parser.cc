/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "extension_whitelist_parser.h"
#include <unordered_set>
#include <stdexcept>

namespace {
std::string Serialize(std::unordered_set<std::string>& set, uint32_t* size) {
  *size = set.size() * EXTENSION_ID_LEN;
  std::string buffer;
  size_t offset = 0;
  for (std::string e : set)
    buffer += e;

  return buffer;
}

void Deserialize(std::unordered_set<std::string>& set, const char* buffer, uint32_t size) {
  set.clear();
  const char *p = buffer;
  for (uint32_t i = 0; i < size / EXTENSION_ID_LEN; i++) {
    std::string s(p, EXTENSION_ID_LEN);
    set.insert(s);
    p += EXTENSION_ID_LEN;
  }
}
}

ExtensionWhitelistParser::ExtensionWhitelistParser() {}

ExtensionWhitelistParser::~ExtensionWhitelistParser() {}

void ExtensionWhitelistParser::addToBlacklist(const char *extensionID) {
  if (!extensionID || strlen(extensionID) != EXTENSION_ID_LEN)
    return;

  std::string extensionData(extensionID);
  if (extensionData.length() != EXTENSION_ID_LEN) {
    throw std::runtime_error("Invalid extension length given!");
  }
  mBlacklist.insert(extensionData);
}

void ExtensionWhitelistParser::addToWhitelist(const char *extensionID) {
  if (!extensionID || strlen(extensionID) != EXTENSION_ID_LEN)
    return;

  std::string extensionData(extensionID);
  if (extensionData.length() != EXTENSION_ID_LEN) {
    throw std::runtime_error("Invalid extension length given!");
  }
  mWhitelist.insert(extensionData);
}

bool ExtensionWhitelistParser::isBlacklisted(const char *extensionID) {
  if (!extensionID || strlen(extensionID) != EXTENSION_ID_LEN)
    return false;

  std::string extensionData(extensionID);
  return mBlacklist.find(extensionData) != mBlacklist.end();
}

bool ExtensionWhitelistParser::isWhitelisted(const char *extensionID) {
  if (!extensionID || strlen(extensionID) != EXTENSION_ID_LEN)
    return false;

  std::string extensionData(extensionID);
  return mWhitelist.find(extensionData) != mWhitelist.end();
}

// Returns a newly allocated buffer, caller must manually delete[] the buffer
char* ExtensionWhitelistParser::serialize(unsigned int* totalSize) {
  *totalSize = 0;
  uint32_t blacklistSize = 0;
  std::string blacklist = ::Serialize(mBlacklist, &blacklistSize);
  uint32_t whitelistSize = 0;
  std::string whitelist = ::Serialize(mWhitelist, &whitelistSize);
  *totalSize = UINT32_SERIALIZE_MAX + blacklistSize + 1 +
    UINT32_SERIALIZE_MAX + whitelistSize + 1;
  unsigned int pos = 0;
  char* result = new char[*totalSize];
  memset(result, 0, *totalSize);
  uint32_t dataLenSize = 1 + sprintf(result + pos, "%" PRIu32, blacklistSize);
  pos += dataLenSize;
  memcpy(result + pos, blacklist.c_str(), blacklistSize);
  pos += 1 + blacklistSize;
  dataLenSize = 1 + sprintf(result + pos, "%" PRIu32, whitelistSize);
  pos += dataLenSize;
  memcpy(result + pos, whitelist.c_str(), whitelistSize);
  return result;
}

bool ExtensionWhitelistParser::deserialize(const char* buffer, size_t) {
  return deserialize(buffer);
}

bool ExtensionWhitelistParser::deserialize(const char* buffer) {
  if (!buffer)
    return false;
  const char *p = buffer;
  uint32_t blacklistSize = 0, whitelistSize = 0;
  int x, r;

  r = sscanf(p, "%" SCNu32 "%n", &blacklistSize, &x);
  if (r != 1 || r == EOF)
    return false;
  if (blacklistSize % EXTENSION_ID_LEN != 0)
    throw std::runtime_error("deserialize: blacklist not divisible by 32!");
  p += x + 1;
  ::Deserialize(mBlacklist, p, blacklistSize);
  p += blacklistSize + 1;

  r = sscanf(p, "%" SCNu32 "%n", &whitelistSize, &x);
  if (r != 1 || r == EOF)
    return false;
  if (whitelistSize % EXTENSION_ID_LEN != 0)
    throw std::runtime_error("deserialize: whitelist not divisible by 32!");
  p += x + 1;
  ::Deserialize(mWhitelist, p, whitelistSize);

  return true;
}
