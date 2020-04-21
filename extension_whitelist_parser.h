/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef EXTENSION_WHITELIST_PARSER_H_
#define EXTENSION_WHITELIST_PARSER_H_

#include <assert.h>
#include <string.h>
#include <cinttypes>
#include <string>
#include <memory>
#include <unordered_set>

#define EXTENSION_DAT_FILE "ExtensionWhitelist.dat"
#define EXTENSION_DAT_FILE_VERSION "1"
#define EXTENSION_ID_LEN 32

#define UINT32_SERIALIZE_MAX 10

namespace {
std::string Serialize(std::unordered_set<std::string>& set, uint32_t* size);
void Deserialize(std::unordered_set<std::string>& set, const char* buffer, uint32_t size);
}

class ExtensionWhitelistParser {
public:
  ExtensionWhitelistParser();
  ~ExtensionWhitelistParser();

  void addToBlacklist(const char *extensionID);
  void addToWhitelist(const char *extensionID);
  bool isBlacklisted(const char *extensionID);
  bool isWhitelisted(const char *extensionID);

  // Serializes the parsed data into a single buffer.
  // The returned buffer should be deleted.
  char* serialize(unsigned int* totalSize);

  // Deserializes the buffer, a size is not needed since a serialized
  // buffer is self described
  bool deserialize(const char* buffer);
  bool deserialize(const char* buffer, size_t);

private:
  std::unordered_set<std::string> mBlacklist;
  std::unordered_set<std::string> mWhitelist;
};

#endif  // EXTENSION_WHITELIST_PARSER_H_
