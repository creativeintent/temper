#!/bin/bash

set -e

export PATH=~/Library/Python/2.7/bin/:$PATH

S3BUCKET="s3://ci-temper"

release() {
    S3DIR="$S3BUCKET/$1"
    TMPDIR="$(mktemp -d)"
    RELEASEDIR="$TMPDIR/zip/release"
    DEMODIR="$TMPDIR/zip/demo"
    SCRIPTDIR="${0%/*}"

    aws s3 sync $S3DIR $TMPDIR

    # Copy Windows builds
    mkdir -p "$RELEASEDIR/Win"
    mv $TMPDIR/Builds/VisualStudio2017/Release/**/*.dll "$RELEASEDIR/Win"
    mv $TMPDIR/Builds/VisualStudio2017/Release/**/*.vst3 "$RELEASEDIR/Win"
    # Copy OSX Builds
    mkdir -p "$RELEASEDIR/OSX"
    mv $TMPDIR/Builds/MacOSX/Release/*.vst "$RELEASEDIR/OSX"
    mv $TMPDIR/Builds/MacOSX/Release/*.vst3 "$RELEASEDIR/OSX"
    mv $TMPDIR/Builds/MacOSX/Release/*.component "$RELEASEDIR/OSX"

    # Copy Windows builds
    mkdir -p "$DEMODIR/Win"
    mv $TMPDIR/Builds/VisualStudio2017/Demo/**/*.dll "$DEMODIR/Win"
    mv $TMPDIR/Builds/VisualStudio2017/Demo/**/*.vst3 "$DEMODIR/Win"
    # Copy OSX Builds
    mkdir -p "$DEMODIR/OSX"
    mv $TMPDIR/Builds/MacOSX/Demo/*.vst "$DEMODIR/OSX"
    mv $TMPDIR/Builds/MacOSX/Demo/*.vst3 "$DEMODIR/OSX"
    mv $TMPDIR/Builds/MacOSX/Demo/*.component "$DEMODIR/OSX"

    # Copy installation instructions
    cp "$SCRIPTDIR/../INSTALL.txt" "$RELEASEDIR"
    cp "$SCRIPTDIR/../INSTALL.txt" "$DEMODIR"

    pushd $RELEASEDIR
        zip -rq4 Temper-$1.zip .
        aws s3 cp Temper-$1.zip $S3BUCKET
    popd

    pushd $DEMODIR
        zip -rq4 Temper-$1-Demo.zip .
        aws s3 cp Temper-$1-Demo.zip $S3BUCKET
    popd

    echo "Success!"
}

presign() {
    RELEASEURL="$(aws s3 presign $S3BUCKET/Temper-$1.zip --expires-in 604800)"
    DEMOURL="$(aws s3 presign $S3BUCKET/Temper-$1-Demo.zip --expires-in 604800)"
    echo "Demo: $DEMOURL"
    echo "Release: $RELEASEURL"
}

case $1 in
    release)
        release $2
        ;;
    presign)
        presign $2
        ;;
    *)
        echo "Usage: ./Scripts/release.sh (release|presign) (version-tag)"
        ;;
esac
