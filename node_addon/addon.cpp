/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <node.h>
#include "EWParserWrap.h"

namespace {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  EWParserWrap::CEWParserWrap::Init(exports);
}

void InitAll(v8::Local<v8::Object> exports, v8::Local<v8::Value> unused, void* priv) {
  InitAll(exports);
}

void InitAll(v8::Local<v8::Object> exports, v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context, void* priv) {
  InitAll(exports);
}

}  // namespace

#ifdef EW_INTERNAL_MODULE
NODE_MODULE_CONTEXT_AWARE_BUILTIN(ew_node_addon, InitAll)
#else
NODE_MODULE(ew_node_addon, InitAll)
#endif
