# extension-whitelist

C++ extension whitelist and blacklist parser for Brave

Extensions on the blacklist can not be installed by the user. Extensions on the whitelist may be installed normally. All other extensions may also be installed normally, but Brave will warn that "Brave has not reviewed this extension yet" (or similar wording).

You can view both lists in the [`whitelist.json`](https://github.com/brave/extension-whitelist/blob/master/data/whitelist.json) file.

The rest of this README is for Brave developers who need to work with this code, or any developer who wants to use it in their own project.

## Installation

1. Clone the git repository from GitHub:

        git clone https://github.com/brave/extension-whitelist

2. Open the working directory:

        cd extension-whitelist

3. Install the Node (v5+) dependencies:

        npm install

## Build the node addon

```
npm run install
```

## Generate the DAT file

```
npm run data-files
```

## Running tests

```
npm run test
```
