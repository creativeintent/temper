#!/bin/bash

set -e

export PATH=~/Library/Python/2.7/bin/aws:$PATH

deploy_win() {
    S3BUCKET="s3://mxzero"
    S3DIR="$S3BUCKET/$1"
    TMPDIR="$(mktemp -d)"
    OUTDIR="$TMPDIR/zip"

    aws s3 sync $S3DIR $TMPDIR
    mkdir -p $TMPDIR/zip
    mv $TMPDIR/Builds/VisualStudio2015/Win32/Release/mxzero.dll $OUTDIR/mxzero.dll
    mv $TMPDIR/Builds/VisualStudio2015/Win32/Release/mxzero.vst3 $OUTDIR/mxzero.vst3
    mv $TMPDIR/Builds/VisualStudio2015/x64/Release/mxzero.dll $OUTDIR/mxzero\ \(x64\).dll
    mv $TMPDIR/Builds/VisualStudio2015/x64/Release/mxzero.vst3 $OUTDIR/mxzero\ \(x64\).vst3

    pushd $OUTDIR
        zip -rq4 mxzero-$1.zip .
        aws s3 cp mxzero-$1.zip $S3BUCKET
    popd
}

case "$1" in
    windows)
        deploy_win $2
        ;;
    *)
        echo "Usage: ./Scripts/release.sh (windows|osx) (version-tag)"
        ;;
esac
