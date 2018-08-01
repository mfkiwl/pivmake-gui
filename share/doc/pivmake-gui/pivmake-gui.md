#pivmake-gui

##DESCRIPTION

The program use a image ROOTIMAGE and select regions over it, the result is saved in the file OUTFILE.

##PARAMETERS

### Primary parameters

The next parameter specify the image filename ROOTIMAGE. By default ROOTIMAGE is void.

    --rootimage ROOTIMAGE


The next parameter specify the result output file OUTFILE, where the selected regions will be saved. By default OUTFILE is equal to the file pivmake-gui.dat in the home directory.

    --outfile OUTFILE

### Secondary parameters

The next parameter disable the graphic selection of ROOTIMAGE variable.

    --dis-rootimage

The next parameter enable the graphic selection of ROOTIMAGE variable.

    --en-rootimage
    
The next parameter disable the graphic selection of OUTDIR variable.

    --dis-outdir

The next parameter enable the graphic selection of OUTDIR variable.

    --en-outdir

##EXAMPLE

The next command start the program, with the variables ROOTIMAGE and OUTFILE with yours values by default.

	pivmake-gui 


The next command start the program, with the variable ROOTIMAGE set as "/di/rec/to/ry/" and OUTFILE set as "/fi/le/na/me".

	pivmake-gui --rootimage "/di/rec/to/ry/" --outfile "/fi/le/na/me" 

The next command start the program, with the variable ROOTIMAGE set as "/di/rec/to/ry/" and OUTFILE set as "/fi/le/na/me". The additinal parameters disable the new selection of ROOTIMAGE and OUTFILE variables.

	pivmake-gui --rootimage "/di/rec/to/ry/" --outfile "/fi/le/na/me" --dis-rootimage  --dis-outfile
