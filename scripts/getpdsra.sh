#!/bin/bash

MYLIBRARY=libpdsra

if [ -z $1 ]
then
INSTALLDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../extras"
else
INSTALLDIR=$1
fi

echo "================================================================================"
echo "Installing ${MYLIBRARY} in: ${INSTALLDIR}"
echo "================================================================================"


#bzr branch bzr://bzr.savannah.nongnu.org/pdsplibrary/${MYLIBRARY}
bzr branch http://bzr.savannah.nongnu.org/r/pdsplibrary/${MYLIBRARY}
cd ${MYLIBRARY}

mkdir build
cd build

cmake  .. -DCMAKE_INSTALL_PREFIX=${INSTALLDIR} -DADD_INCLUDE_DIRECTORY="${INSTALLDIR}/include" -DADD_LIB_DIRECTORY="-L${INSTALLDIR}/lib"


make
make install
if [ ! -d "${INSTALLDIR}/lib" ]
then
	echo "ERROR: compiling or installing ${TAGLIBNAME}. Not exist the ${INSTALLDIR}/lib directory"
    exit 3
fi
if [ ! -d "${INSTALLDIR}/include" ]
then
	echo "ERROR: compiling or installing ${TAGLIBNAME}. Not exist the ${INSTALLDIR}/include directory"
    exit 3
fi

cd ..
rm -f -r  ${MYLIBRARY}
