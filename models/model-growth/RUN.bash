#!/bin/bash

# You'll need to edit this if your Biocellion is installed elsewhere
BIOCELLION_BASE=${HOME}/biocellion

BASE_NAME=growth
MODEL_NAME=model-${BASE_NAME}
XML_FILE=${BASE_NAME}.xml
OUTPUT_NAME=output
RUN_LOG=${XML_FILE}.out
MAIN=framework/main

# Go to the model directory
dir=`dirname $0`
model_dir=`pwd`

cd "$dir"

# Setup XML and output files, directories
cp -f $XML_FILE $BIOCELLION_BASE/$MAIN/
mkdir -p $OUTPUT_NAME
rm -f $OUTPUT_NAME/*

# Copy/Link the model in correctly
cd $BIOCELLION_BASE/libmodel
rm -f model
mkdir model-${BASE_NAME}
for f in `ls $model_dir`; do
    ln -s $model_dir/$f model-${BASE_NAME}/
done
ln -s model-${BASE_NAME} model

#make clean
make
cd ..
cd $MAIN
/usr/bin/time ./biocellion.DP.SPAGENT.OPT $XML_FILE > $RUN_LOG 2>&1
#./biocellion.DP.SPAGENT.OPT $XML_FILE

cd ../../libmodel
rm model
rm -rf model-${BASE_NAME}

