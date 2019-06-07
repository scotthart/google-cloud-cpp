# Importing from GitHub

go/cbt-cpp:importing-from-github

[TOC]

<!--*
# Document freshness: For more information, see go/fresh-source.
freshness: { owner: 'coryan' reviewed: '2019-01-03' }
*-->

## Background

The `//third_party/cloud_cpp` directory is periodically imported from the GitHub
[repository](https://github.com/GoogleCloudPlatform/google-cloud-cpp). We use
copybara to import the code, but we have not (yet) automated the copybara
invocation. A developer must manually call copybara to complete the import. As
we gain confidence we will automate the process, but for now, this document
describes the necessary steps.

## The Easy Case

Assuming no large changes to the code structure, the default copybara workflow
should "Just Work"[tm].

Setup an alias to type less:

```bash
alias copybara='/google/data/ro/teams/copybara/copybara'
```

Go to an updated piper client, e.g.:

```bash
g4d -f clean-client
SOURCE_CITC=$PWD
```

Run copybara to import the code:

```bash
copybara third_party/cloud_cpp/copy.bara.sky
```

If you want to import a release (we will use `0.42.0` as an example), use:

```bash
RELEASE='0.42.0'
copybara third_party/cloud_cpp/copy.bara.sky default "v${RELEASE}"
```

Copybara will create a new citc client, and a new CL in it with the changes,
make a note of the client and CL:

```bash
COPYBARA_CITC=...  # The name of the client created by copybara.
COPYBARA_CL=...    # The CL number created by copybara.
```

Go to that client.

If you are importing a release, you first need to update the
`google_cloud-cpp-${RELEASE}` checksum and links used by TensorFlow in
`third_party/tensorflow/workspace.bzl`.

Now to test the code:

```bash
g4d ${COPYBARA_CITC}
blaze build third_party/cloud_cpp/...:all
blaze test third_party/cloud_cpp/...:all
```

You may want to check the key projects that depend on `cloud_cpp`. TAP should
take care of that for you, but it is better to be proactive:

```bash
blaze build third_party/cloud_cpp/...:all \
    third_party/tensorflow/contrib/bigtable/...:all \
    iot/spot/location_server/exporters/...:all
blaze test third_party/cloud_cpp/...:all \
    third_party/tensorflow/contrib/bigtable/...:all \
    iot/spot/location_server/exporters/...:all
```

Assuming the tests pass, do the presubmit and mail your CL.

```bash
g4 presubmit -c ${COPYBARA_CL}
```

## The Not-so-easy Case

Sometimes the code will not compile, the patches will fail to apply, or there
will be other problems. We cannot provide step-by-step instructions in this case
because, well, we do not know what those are. But generally, this workflow has
worked in the past:

-   Run copybara, if necessary remove the steps (regexp replaces, patches) that
    fail.
-   Save the state of the code in a local git repository:

    ```bash
    g4d ${COPYBARA_CITC}
    cd third_party/cloud_cpp
    rm -fr $HOME/cloud-cpp-import.git
    git init --separate-git-dir $HOME/cloud-cpp-import.git .
    git add .
    git commit -m"Import state after running copybara."
    ```

-   Now fix any problems in the code, manually edit the files until they
    compile.

-   Save the changes as patches:

    ```bash
    DEST="${SOURCE_CITC}/third_party/cloud_cpp"
    for file in `git status --porcelain | grep ' M ' | awk '{print $2}'`; do
        d=$(dirname $file);
        mkdir -p "${DEST}/patches/$d" || true;
        path="patches/${file}.patch"
        output="${DEST}/${path}"
        if [ -f "${output}" ]; then
            (cd "${SOURCE_CITC}" ; g4 edit "third_party/cloud_cpp/${path}");
        fi
        git diff $file > "${output}"; echo $file;
    done
    ```

-   Commit the changes to the local git repository:

    ```bash
    git commit -m"Save manually patched files."
    ```

-   Edit `copy.bara.sky` to include these new patches.

-   Run copybara again, you should expect that the code does not change.

    ```bash
    copybara third_party/cloud_cpp/copy.bara.sky \
        --piper-description-behavior OVERWRITE \
        --destination-cl 203138210
    git status # expect no changes
    ```

-   Go back to the step where you edited the code until you get it right.
