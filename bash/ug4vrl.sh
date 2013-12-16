#!/bin/bash
## author: stephan grein

###################################################
### based on Christian Poliwodas script:        ###
### compile-andzip-native-ug-parameterized.sh   ###
###################################################

# exit codes
E_USAGE=0
E_ERROR_STATUS=

# variables
UG_ROOT_FOLDER=
UG_BUILD_FOLDER=
VRL_UG_JAVA_PROJECT_FOLDER=
VRL_UG_JAVA_OS_SYSTEM_FOLDER=/osx/
UG_LIB_NAME=libug4
UG_LIB_SUFFIX=dylib
NUMBER_OF_THEADS=4
BASENAME=$(basename $0)
SCRIPT_NAME=${BASENAME%%.*}
TEMP_DIRECTORY=/tmp/$SCRIPT_NAME/
TEMP_FILE_NAME=$TEMP_DIRECTORY/temp.txt

# functions
function usage() {
   echo "Usage: $SCRIPT_NAME -r ROOT -b BUILD -v VRL_UG_PROJECT -o OS [-t] [THREADS]"
   exit $E_USAGE
}

# get command line parameters
while getopts ":rbtov:" opt;  do
  case $opt in
    r)
      UG_ROOT_FOLDER=$OPTARG
      ;;
    b)
      UG_BUILD_FOLDER=$OPTARG
      ;;
    t)
      THREADS=$OPTARG
      ;;
    v)
      VRL_UG_JAVA_PROJECT_FOLDER=$OPTARG
      ;;
   o)
      VRL_UG_JAVA_OS_SYSTEM_FOLDER=$OPTARG
      ;;
     esac
done

# check for proper usage
if test -z $UG_ROOT_FOLDER; then
   usage
elif test -z $UG_BUILD_FOLDER; then
   usage
elif test -z  $VRL_UG_JAVA_PROJECT_FOLDER; then
   usage
fi

# create temp directory if it does not exist
if ! test -e $TEMP_DIRECTORY; then
   mkdir -p $TEMP_DIRECTORY;
fi

UG_LIB_FOLDER=$UG_ROOT_FOLDER/lib

# action & error check
echo -n "Begin: " >> $TEMP_FILE_NAME
date >> $TEMP_FILE_NAME
cd $UG_BUILD_FOLDER >> $TEMP_FILE_NAME
[[ $? != 0 ]] && E_ERROR_STATUS=1
cmake $UG_ROOT_FOLDER >> $TEMP_FILE_NAME
[[ $? != 0 ]] && E_ERROR_STATUS=1
make -j$NUMBER_OF_THREADS >> $TEMP_FILE_NAME
[[ $? != 0 ]] && E_ERROR_STATUS=1

cd ${UG_LIB_FOLDER} >> $TEMP_FILE_NAME
[[ $? != 0 ]] && E_ERROR_STATUS=1
zip -r natives.zip $UG_LIB_NAME.$UG_LIB_SUFFIX >> $TEMP_FILE_NAME
[[ $? != 0 ]] && E_ERROR_STATUS=1
cp natives.zip ${VRL_UG_JAVA_PROJECT_FOLDER}/src/eu/mihosoft/vrl/plugin/content/natives/${VRL_UG_JAVA_OS_SYSTEM_FOLDER}/natives.zip >> $TEMP_FILE_NAME
[[ $? != 0 ]] && E_ERROR_STATUS=1

# ant tasks
cd ${VRL_UG_JAVA_PROJECT_FOLDER} >> $TEMP_FILE_NAME
[[ $? != 0 ]] && E_ERROR_STATUS=1
ant clean >> $TEMP_FILE_NAME
[[ $? != 0 ]] && E_ERROR_STATUS=1
ant compile >> $TEMP_FILE_NAME
[[ $? != 0 ]] && E_ERROR_STATUS=1
ant jar >> $TEMP_FILE_NAME
[[ $? != 0 ]] && E_ERROR_STATUS=1

echo -n "End: " >> $TEMP_FILE_NAME
date >> $TEMP_FILE_NAME

[[ $E_ERROR_STATUS = 1 ]] && echo "Something went wrong during processing the shell script. See temp file: $TEMP_FILE_NAME please."
