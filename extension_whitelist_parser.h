/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef EXTENSION_WHITELIST_PARSER_H_
#define EXTENSION_WHITELIST_PARSER_H_

#include <memory>

#include "./extension_whitelist_data.h"

#define EXTENSION_DAT_FILE "ExtensionWhitelist.dat"
#define EXTENSION_DAT_FILE_VERSION "1"

template<class T>
class HashSet;

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
  bool deserialize(char *buffer);
  bool deserialize(char *buffer, size_t);

private:
  std::unique_ptr<HashSet<ST_EXTENSION_WHITELIST_DATA> > mBlacklist;
  std::unique_ptr<HashSet<ST_EXTENSION_WHITELIST_DATA> > mWhitelist;
};

#endif  // EXTENSION_WHITELIST_PARSER_H_
