#!/bin/sh -e

indir=$1
outh=$2/containers.decl.h
outc=$2/containers.impl.h

echo Writing $outh and $outc from $indir.

function template {
    subst="s/ubw_contname/$2/g;s/ubw_conttype/$3/g;"

    sed $subst $indir/tpl/$1.tpl.h >> $outh
    sed $subst $indir/tpl/$1.tpl.c >> $outc
}

echo "// Generated file, DO NOT EDIT." | tee $outc > $outh

template stack ubw_los ubw_obj
template stack ubw_lops ubw_obj*
template stack ubw_ps void*
