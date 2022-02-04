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

## Trigger a CI build

The `brave-core-ext-local-data-files-update-publish` in CI polls the [`brave/brave-core-crx-packager` repository](https://github.com/brave/brave-core-crx-packager) once a day and makes a new build of the *Brave Local Data Updater* component if there are any new commits on `master`. A build can also be started manually there.

Renovate is supposed to be watching all dependent repositories (such as `brave/extension-whitelist`) for changes and to propose a PR on `brave/brave-core-crx-packager` to update `package-lock.json` (and `package.json` as needed) when one of the dependencies needs to be updated. If that doesn't happen for some reason, a manual PR can be created and merged. See https://github.com/brave/brave-core-crx-packager/pull/316 for an example.
