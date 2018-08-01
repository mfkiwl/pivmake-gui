#!/bin/bash
INSTALLBASE='output'
INSTALLPATH='usr'

################################################################################
cd ..
qmake PREFIX=./deb/${INSTALLBASE}/${INSTALLPATH}
make
make install
mkdir deb/${INSTALLBASE}/DEBIAN
mv deb/control deb/${INSTALLBASE}/DEBIAN/control
./clean_all.sh
cd deb

################################################################################
echo ''
APPFILENAME=$(grep 'Package: ' ${INSTALLBASE}/DEBIAN/control | cut -d' ' -f2)
echo 'Package:'$APPFILENAME
APPVERSION=$(grep 'Version: ' ${INSTALLBASE}/DEBIAN/control | cut -d' ' -f2)
echo 'Version:'$APPVERSION
APPARCH=$(grep 'Architecture: ' ${INSTALLBASE}/DEBIAN/control | cut -d' ' -f2)
echo 'Architecture:'$APPARCH
echo ''

DEBFILENAME="${APPFILENAME}_${APPVERSION}_${APPARCH}".deb
dpkg-deb --build $INSTALLBASE $DEBFILENAME

gpg -b --use-agent $DEBFILENAME
#
echo ""
echo "To install please do:"
echo "                      sudo dpkg -i $DEBFILENAME"
echo ""
echo "To upload please do:"
echo "                     rsync $DEBFILENAME     trucomanx@dl.sv.nongnu.org:/releases/${APPFILENAME}-project/${APPFILENAME}/"
echo "                     rsync $DEBFILENAME.sig trucomanx@dl.sv.nongnu.org:/releases/${APPFILENAME}-project/${APPFILENAME}/"
echo ""
rm -r -f ${INSTALLBASE}


