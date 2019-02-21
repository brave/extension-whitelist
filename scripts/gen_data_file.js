/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

var CEWParser = require("../build/Release/ew_node_addon").CEWParser;
var addon = new CEWParser();

var fs = require("fs");
var data = fs.readFileSync("data/whitelist.json", "utf8");
var blacklist = JSON.parse(String(data))["blacklist"];
for (var i in blacklist) {
    addon.addToBlacklist(blacklist[i]["id"]);
};
var whitelist = JSON.parse(String(data))["whitelist"];
for (var i in whitelist) {
    addon.addToWhitelist(whitelist[i]["id"]);
};

var serializedObject = addon.serialize();
console.log("serializedObject == " + serializedObject);
console.log("size == " + serializedObject.length);

fs.writeFileSync("data/ExtensionWhitelist.dat", serializedObject);
