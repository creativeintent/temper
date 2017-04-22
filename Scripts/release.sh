#!/bin/bash

set -e

export PATH=~/Library/Python/2.7/bin/:$PATH

deploy_win() {
    S3BUCKET="s3://ci-temper"
    S3DIR="$S3BUCKET/$1"
    TMPDIR="$(mktemp -d)"
    RELEASEDIR="$TMPDIR/zip/release"
    DEMODIR="$TMPDIR/zip/demo"

    aws s3 sync $S3DIR $TMPDIR

    mkdir -p $RELEASEDIR
    mv $TMPDIR/Builds/VisualStudio2015/Release/*.dll $RELEASEDIR
    mv $TMPDIR/Builds/VisualStudio2015/Release/*.vst3 $RELEASEDIR

    mkdir -p $DEMODIR
    mv $TMPDIR/Builds/VisualStudio2015/Demo/*.dll $DEMODIR
    mv $TMPDIR/Builds/VisualStudio2015/Demo/*.vst3 $DEMODIR

    pushd $RELEASEDIR
        zip -rq4 Temper-$1.zip .
        aws s3 cp Temper-$1.zip $S3BUCKET
    popd

    pushd $DEMODIR
        zip -rq4 Temper-$1-Demo.zip .
        aws s3 cp Temper-$1-Demo.zip $S3BUCKET
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
