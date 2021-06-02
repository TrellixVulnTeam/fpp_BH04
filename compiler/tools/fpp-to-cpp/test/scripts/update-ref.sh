#!/bin/sh

. $COMPILER_ROOT/scripts/test-utils.sh

fpp_to_cpp=$COMPILER_ROOT/bin/fpp-to-cpp

update()
{
  args=$1
  infile=$2
  if test -n "$3"
  then
    outfile=$3
  else
    outfile=$infile
  fi
  $fpp_to_cpp $args $infile.fpp 2>&1 | remove_path_prefix > $outfile.ref.txt
}

for file in `find . -name '*.ref.txt'`
do
  rm $file
done

. ./tests.sh

# Default update ref
for t in $tests
do
  echo "
$t()
{
  update '' $t
}"
done > default-update-ref.sh
. ./default-update-ref.sh

constants()
{
  update "-n constants.names.txt -p $PWD" constants
  mv constants.names.txt constants.names.ref.txt
  remove_year < FppConstantsAc.hpp > FppConstantsAc_constants.ref.hpp
  remove_year < FppConstantsAc.cpp > FppConstantsAc_constants.ref.cpp
}

constants_guard()
{
  update "-g GUARD_PREFIX -p $PWD" constants
  remove_year < FppConstantsAc.hpp > FppConstantsAc_constants_guard.ref.hpp
  remove_year < FppConstantsAc.cpp > FppConstantsAc_constants_guard.ref.cpp
}

constants_output_dir()
{
  update "-d output_dir -p $PWD" constants output_dir/constants
  remove_year < output_dir/FppConstantsAc.hpp > output_dir/FppConstantsAc.ref.hpp
  remove_year < output_dir/FppConstantsAc.cpp > output_dir/FppConstantsAc.ref.cpp
}

constants_string()
{
  update "-p $PWD" constants_string
  remove_year < FppConstantsAc.hpp > FppConstantsAc_constants_string.ref.hpp
  remove_year < FppConstantsAc.cpp > FppConstantsAc_constants_string.ref.cpp
}

for t in $tests
do
  echo "updating ref output for $t"
  $t
done