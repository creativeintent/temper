#!/bin/bash

set -e

export PATH=~/Library/Python/2.7/bin/:$PATH

release() {
    S3BUCKET="s3://ci-temper"
    S3DIR="$S3BUCKET/$1"
    TMPDIR="$(mktemp -d)"
    RELEASEDIR="$TMPDIR/zip/release"
    DEMODIR="$TMPDIR/zip/demo"
    SCRIPTDIR="${0%/*}"

    aws s3 sync $S3DIR $TMPDIR

    # Copy Windows builds
    mkdir -p "$RELEASEDIR/Win"
    mv $TMPDIR/Builds/VisualStudio2015/Release/*.dll "$RELEASEDIR/Win"
    mv $TMPDIR/Builds/VisualStudio2015/Release/*.vst3 "$RELEASEDIR/Win"
    # Copy OSX Builds
    mkdir -p "$RELEASEDIR/OSX"
    mv $TMPDIR/Builds/MacOSX/Release/*.vst "$RELEASEDIR/OSX"
    mv $TMPDIR/Builds/MacOSX/Release/*.vst3 "$RELEASEDIR/OSX"
    mv $TMPDIR/Builds/MacOSX/Release/*.component "$RELEASEDIR/OSX"

    # Copy Windows builds
    mkdir -p "$DEMODIR/Win"
    mv $TMPDIR/Builds/VisualStudio2015/Demo/*.dll "$DEMODIR/Win"
    mv $TMPDIR/Builds/VisualStudio2015/Demo/*.vst3 "$DEMODIR/Win"
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
        RELEASEURL="$(aws s3 presign $S3BUCKET/Temper-$1.zip --expires-in 604800)"
    popd

    pushd $DEMODIR
        zip -rq4 Temper-$1-Demo.zip .
        aws s3 cp Temper-$1-Demo.zip $S3BUCKET
        DEMOURL="$(aws s3 presign $S3BUCKET/Temper-$1-Demo.zip --expires-in 604800)"
    popd

    echo "Success!"
    echo "Demo: $DEMOURL"
    echo "Release: $RELEASEURL"
}

if [ $# -eq 0 ]
then
    echo "Usage: ./Scripts/release.sh (version-tag)"
else
    release $1
fi
