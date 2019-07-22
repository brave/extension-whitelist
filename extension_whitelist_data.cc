/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "./extension_whitelist_data.h"
#include "hashFn.h"

static HashFn sHashFn(19);

uint64_t ST_EXTENSION_WHITELIST_DATA::GetHash() const {
  if (!sExtensionID) {
    return 0;
  }

  return sHashFn(sExtensionID, static_cast<int>(strlen(sExtensionID)));
}
