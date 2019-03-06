/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

const CEWParser = require('../build/Release/ew_node_addon').CEWParser
const addon = new CEWParser()

const fs = require('fs')
const data = fs.readFileSync('data/whitelist.json', 'utf8')
const blacklist = JSON.parse(String(data))['blacklist']
for (var i in blacklist) {
    addon.addToBlacklist(blacklist[i]['id'])
}
const whitelist = JSON.parse(String(data))['whitelist']
for (var i in whitelist) {
    addon.addToWhitelist(whitelist[i]['id'])
}

const serializedObject = addon.serialize()
console.log('serializedObject == ' + serializedObject)
console.log('size == ' + serializedObject.length)

fs.writeFileSync('data/ExtensionWhitelist.dat', serializedObject)
